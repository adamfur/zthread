/*
 *  ZThreads, a platform-independant, multithreading and 
 *  synchroniation library
 *
 *  Copyright (C) 2001, 2002 Eric Crahen, See LGPL.TXT for details
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

#ifndef __ZTTHREADQUEUE_H__
#define __ZTTHREADQUEUE_H__

#include "zthread/Singleton.h"
#include "zthread/Guard.h"
#include "FastLock.h"
#include "ThreadImpl.h"
#include "DeferredInterruptionScope.h"

#include <deque>

namespace ZThread {

  class ThreadImpl;
  
  /**
   * @class ThreadQueue
   * @version 2.3.0
   * @author Eric Crahen <crahen@cse.buffalo.edu>
   * @date <2003-07-07T21:49:09-0400>
   *
   * A ThreadQueue accumulates references to user and reference threads.
   * These are threads that are running outside the scope of the Thread
   * object that created them. ZThreads doesn't have a central manager for
   * all threads (partly why I renamed the ThreadManager to someting more 
   * appropriate). Instead, ZThreads will discover threads it did not create
   * and create a reference thread that allows ZThreads to interact with it.
   * Non user threads that are created by the user never have to touch the
   * ThreadQueue.
   */
  class ThreadQueue : public Singleton<ThreadQueue> {

    //! Type for the ThreadList
    typedef std::deque<ThreadImpl*> List;

    List _pendingThreads;
    List _referenceThreads;
    List _userThreads;

    //! Serilize access to the thread list
    FastLock _lock;

    //! Reference thread waiting to cleanup any user & reference threads
    ThreadImpl* _waiter;

  public:

    ThreadQueue() 
      : _waiter(0) { }

    /**
     * The thread destroys a ThreadQueue will be a reference thread,
     * probably the main thread; but it could be another thread that
     * started and loaded the library.
     */
    ~ThreadQueue();

    /**
     * Insert a user-thread into the queue. User-threads are inserted as they
     * begin thier task. Once that task completes, user-threads are automatically
     * transitioned to pending-threads via <i>insertPendingThread()</i>.
     *
     * User-threads are known to be executing thier tasks and will be cancel()ed
     * as the ThreadQueue is destroyed when main() goes out of scope. This sends
     * a request to the task to complete soon. Once the task exits, the thread is 
     * transitioned to pending-thread status.
     */
    void insertUserThread(ThreadImpl*);

    /**
     * Insert a pending-thread into the queue. 
     * 
     * Pending-threads are known to have completed thier tasks and thier 
     * resources are reclaimed (lazily) as more threads are started or as the  
     * ThreadQueue is destroyed.
     */
    void insertPendingThread(ThreadImpl*);


    /**
     * Insert reference thread. Reference threads are not removed until
     * the ThreadQueue goes out of scope.
     */
    void insertReferenceThread(ThreadImpl*);


  private:

    void pollPendingThreads();

    void pollUserThreads();

    void pollReferenceThreads();

  };

  
  ThreadQueue::~ThreadQueue() {

    ZTDEBUG("ThreadQueue waiting on remaining threads...\n");

    // Ensure the current thread is mapped.
    ThreadImpl* impl = ThreadImpl::current();

    bool threadsWaiting = false;
    bool waitRequired = false;

    { // Check the queue to for pending user threads
      
      Guard<FastLock> g(_lock);
      
      waitRequired = (_waiter != (ThreadImpl*)1);
      _waiter = impl;

      threadsWaiting = !_userThreads.empty() || !_pendingThreads.empty();
      
      ZTDEBUG("Wait required:   %d\n", waitRequired);
      ZTDEBUG("Threads waiting: %d\n", threadsWaiting);
      
      // Auto-cancel any active threads at the time main() goes out of scope
      // "force" a gentle exit from the executing tasks; eventually the user- 
      // threads will transition into pending-threads
      pollUserThreads();

    }

    // Wait for all the users threads to get into the appropriate state
    if(threadsWaiting) {
      ZTDEBUG("Threads waiting: %d %d\n", _userThreads.size(), _pendingThreads.size());
      Monitor& m(_waiter->getMonitor());
      
      // Defer interruption while this thread waits for a signal from
      // the last pending user thread
      Guard<Monitor, CompoundScope<DeferredInterruptionScope, LockedScope> > g(m);

      // Reference threads can't be interrupted or otherwise 
      // manipulated. The only signal this monitor will recieve
      // at this point will be from the last pending thread.
      if(waitRequired && m.wait() != Monitor::SIGNALED) {
        assert(0);
      }

      // Join those pending threads
      pollPendingThreads();
      
    }
      
    // Clean up the reference threads
    pollReferenceThreads(); 
    
  }
  

  void ThreadQueue::insertPendingThread(ThreadImpl* impl) {

    Guard<FastLock> g(_lock);

    // Move from the user-thread list to the pending-thread list
    List::iterator i = std::find(_userThreads.begin(), _userThreads.end(), impl);
    if(i != _userThreads.end())
      _userThreads.erase(i);

    _pendingThreads.push_back(impl);
    
    // Wake the main thread,if its waiting, when the last pending-thread becomes available;
    // Otherwise, take note that no wait for pending threads to finish is needed
    if(_userThreads.empty())
      if(_waiter) 
        _waiter->getMonitor().notify();
      else
        _waiter = (ThreadImpl*)!_waiter;

    ZTDEBUG("1 pending-thread added.\n");

  }

  void ThreadQueue::insertReferenceThread(ThreadImpl* impl) {

    Guard<FastLock> g(_lock);
    _referenceThreads.push_back(impl);

    ZTDEBUG("1 reference-thread added.\n");

  }

  void ThreadQueue::insertUserThread(ThreadImpl* impl) {

    Guard<FastLock> g(_lock);
    _userThreads.push_back(impl);

    // Reclaim pending-threads
    pollPendingThreads();

    // Auto-cancel threads that are started when main() is out of scope
    if(_waiter)
      impl->cancel(true);

    ZTDEBUG("1 user-thread added.\n");
    
  }


  void ThreadQueue::pollPendingThreads() {

    for(List::iterator i = _pendingThreads.begin(); i != _pendingThreads.end();) {

      ThreadImpl* impl = (ThreadImpl*)*i;
      ThreadOps::join(impl);
      
      impl->delReference();
           
      i = _pendingThreads.erase(i);

      ZTDEBUG("1 pending-thread reclaimed.\n");

    }

  }

  void ThreadQueue::pollReferenceThreads() {

    for(List::iterator i = _referenceThreads.begin(); i != _referenceThreads.end(); ++i) {
      
      ThreadImpl* impl = (ThreadImpl*)*i;
      impl->delReference();
      
      ZTDEBUG("1 reference-thread reclaimed.\n");

    }
    
  }

  void ThreadQueue::pollUserThreads() {

    for(List::iterator i = _userThreads.begin(); i != _userThreads.end(); ++i) {

      ThreadImpl* impl = *i;
      impl->cancel(true);

      ZTDEBUG("1 user-thread reclaimed.\n");

    }

  }

  /*
  void ThreadQueue::pollUserThreads() {

    while(!_userThreads.empty()) {

      // Make a local copy of the known user threads
      List l;
      std::copy(_userThreads.begin(), _userThreads.end(), std::back_inserter(l));

      {

        Guard<FastLock, UnlockedScope> g(_lock);
        
        // Cancel any remaining user threads
        for(List::iterator i = l.begin(); i != l.end(); ++i) {

          ThreadImpl* impl = *i;
          Monitor& m(impl->getMonitor());
          
          if(m.tryAcquire()) {

            impl->cancel(true);
            m.release();

          }

        }

        // Join the remaining threads
        for(List::iterator i = l.begin(); i != l.end(); ++i) {

          ThreadImpl* impl = *i;
          ThreadOps::join(impl);
          
          // Update the reference count
          impl->delReference();

        }

      }

      // Erase the threads that have been joined.
      for(List::iterator i = _userThreads.begin(); i != _userThreads.end();) 
        if(std::find(l.begin(), l.end(), *i) != l.end())
          i = _userThreads.erase(i);
      
      
    }

  }
  */

} // namespace ZThread

#endif  // __ZTTHREADQUEUE_H__

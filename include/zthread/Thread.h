/*
 *  ZThreads, a platform-independant, multithreading and
 *  synchroniation library
 *
 *  Copyright (C) 2000-2002, Eric Crahen, See LGPL.TXT for details
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

#ifndef __ZTTHREAD_H__
#define __ZTTHREAD_H__

#include "zthread/CountedPtr.h"
#include "zthread/Cancelable.h"
#include "zthread/Handle.h"
#include "zthread/Priority.h"
#include "zthread/NonCopyable.h"

namespace ZThread {
  
  class ThreadImpl;
  
  /**
   * @class Thread
   *
   * @author Eric Crahen <crahen@cse.buffalo.edu>
   * @date <2003-07-07T21:53:36-0400>
   * @version 2.3.0
   *
   */
  class ZTHREAD_API Task : public CountedPtr<Runnable, AtomicCount> {
  public:
    
    Task(Runnable* raw)
      : CountedPtr<Runnable, AtomicCount>(raw) { } 
    
    template <typename U>
      Task(U* raw)
      : CountedPtr<Runnable, AtomicCount>(raw) { } 
    
    Task(const CountedPtr<Runnable, AtomicCount>& ptr) 
      : CountedPtr<Runnable, AtomicCount>(ptr) { } 
    
    template <typename U, typename V>
      Task(const CountedPtr<U, V>& ptr) 
      : CountedPtr<Runnable, AtomicCount>(ptr) { } 
    
    void operator()() {
      (*this)->run();
    }
    
  }; /* Task */
  
  
  /**
   * @class Thread
   *
   * @author Eric Crahen <crahen@cse.buffalo.edu>
   * @date <2003-07-07T21:53:36-0400>
   * @version 2.3.0
   *
   */
  class ZTHREAD_API Thread : public Cancelable, public NonCopyable {

    //! Delegate
    ThreadImpl* _impl;

  public:

    /**
     * @exception Initialization_Exception - thrown if there are not
     * enough resources to do this
     */
    Thread();

    /**
     */
    Thread(const Task&, bool autoCancel = false);

    //! Destroy a Thread
    virtual ~Thread();

    //! Comparison operator
    bool operator==(const Thread& t) const;

    //! Comparison operator
    inline bool operator!=(const Thread& t) const {
      return !(*this == t);
    }

    /**
     * Wait for the thread represented by this object to exit.
     * Only one thread can wait on any other thread.
     *
     * @param timeout - maximum amount of time (milliseconds) this method could block.
     * A timeout of 0 will block indefinently.
     *
     * @exception Deadlock_Exception thrown if thread attempts to join itself
     * @exception InvalidOp_Exception thrown if the thread cannot be joined
     * @exception Interrupted_Exception thrown if the joining thread has been interrupt()ed
     */
    bool join(unsigned long timeout = 0);
 
    /**
     * Change the priority of this Thread. This will change the actual
     * priority of the thread when the OS supports it. If there is no
     * real priority support, it's simulated.
     *
     * @param p - new Priority
     */
    void setPriority(Priority p);

    /**
     * Get the priority of this Thread.
     *
     * @return Priority
     */
    Priority getPriority();

    /**
     * Interrupts this thread.
     *
     * If this thread is blocked when this method is called, the thread will
     * abort that blocking operation with an Interrupted_Exception.
     *
     * Otherwise, the <i>interrupted</i> status of the thread is set. This status
     * is cleared by one of two methods. The first is by attempting another
     * blocking operation; this will clear the <i>interrupted</i> status and
     * immediately abort the operation with an Interrupted_Exception. The second
     * is to call isInterrupted() from the context of this thread.
     *
     * A thread is never started in an interrupted state. The interrupted status
     * of a thread will be discarded when the thread starts.
     *
     * Interrupting a thread that is no longer running will have no effect other
     * than setting the interrupt status permanently. When a thread exits, that
     * status can no longer be cleared.
     *
     * @return bool true only if the Thread was interrupted successfully and it is not
     * the current thread and it is not blocked on a synchronization object. This indicates
     * it may be blocked by a system call, or not at all. A user can extend the Thread
     * class to take advantage of this hint to implement i/o interruption for thier system.
     */
    virtual bool interrupt();

    /**
     * Tests whether the current Thread has been interrupt()ed, clearing
     * its interruption status.
     *
     * @return bool true if the Thread was interrupted, otherwise false
     */
    static bool interrupted();

    /**
     * Tests whether the current Thread has been canceled, and clears the
     * interrupted status.
     *
     * @return bool true only if the Thread::cancel() has been invoked.
     */
    static bool canceled();

    /**
     * Tests whether this thread has been canceled. If called from the context
     * of this thread, the interrupted status is cleared.
     *
     * @return bool true if the Thread was canceled, otherwise false
     *
     * @post There is no serlization garuntee with this method, Its possible
     * for a thread to be canceled immediately after this functions returns.
     */
    virtual bool isCanceled();

    /**
     * Set the cancelation and interruption status of this thread.
     *
     * @exception InvalidOp_Exception thrown if a thread attempts to cancel itself
     */
    virtual void cancel();

    /**
     * Put the currently executing thread to sleep for a given amount of
     * time.
     *
     * @param timeout - maximum amount of time (milliseconds) this method could block
     *
     * @exception Interrupted_Exception thrown if this wait was interrupt()ed
     */
    static void sleep(unsigned long timeout);

    /**
     * Cause the currently executing thread to yield, allowing the scheduler
     * to assign some execution time to another thread.
     */
    static void yield();


  }; /* Thread */


} // namespace ZThread

#endif // __ZTTHREAD_H__




/*
 *  ZThreads, a platform-independant, multithreading and
 *  synchroniation library
 *
 *  Copyright (C) 2000-2003, Eric Crahen, See LGPL.TXT for details
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

#include "zthread/Cancelable.h"
#include "zthread/Priority.h"
#include "zthread/NonCopyable.h"
#include "zthread/Task.h"
#include "zthread/Waitable.h"

namespace ZThread {
  
  class ThreadImpl;
  
  /**
   * @class Thread
   *
   * @author Eric Crahen <crahen@cse.buffalo.edu>
   * @date <2003-07-20T05:23:23-0400>
   * @version 2.3.0
   *
   */
  class ZTHREAD_API Thread 
    : public Cancelable, public Waitable, public NonCopyable {

    //! Delegate
    ThreadImpl* _impl;

  public:

    /**
     * Create a Thread that represents the current thread.
     */
    Thread();

    /**
     * Create a Thread that spawns a new thread to run the given task.
     *
     * @param task Task to be run by a thread managed by this executor 
     * @param autoCancel flag to requestion automatic cancellation
     *
     * @post if the <i>autoCancel</i> flag was true, this thread will
     *       automatically be canceled when main() goes out of scope.
     */
    Thread(const Task&, bool autoCancel = false);

    //! Destroy the Thread
    ~Thread();

    //! Comparison operator
    bool operator==(const Thread& t) const;

    //! Comparison operator
    inline bool operator!=(const Thread& t) const {
      return !(*this == t);
    }

    /**
     * Wait for the thread represented by this object to complete its task.
     * The calling thread is blocked until the thread represented by this
     * object exits.
     *
     * @exception Deadlock_Exception thrown if thread attempts to join itself
     * @exception InvalidOp_Exception thrown if the thread cannot be joined
     * @exception Interrupted_Exception thrown if the joining thread has been interrupt()ed
     */
    void wait();
 
    /**
     * Wait for the thread represented by this object to complete its task.
     * The calling thread is blocked until the thread represented by this
     * object exits, or until the timeout expires.
     *
     * @param timeout maximum amount of time (milliseconds) this method 
     *        could block the calling thread.
     *
     * @return 
     *   - <em>true</em> if the thread task complete before <i>timeout</i> 
     *     milliseconds elapse.
     *   - <em>false</em> othewise.
     *
     * @exception Deadlock_Exception thrown if thread attempts to join itself
     * @exception InvalidOp_Exception thrown if the thread cannot be joined
     * @exception Interrupted_Exception thrown if the joining thread has been interrupt()ed
     */
    bool wait(unsigned long timeout);
 
    /**
     * Change the priority of this Thread. This will change the actual
     * priority of the thread when the OS supports it. 
     *
     * If there is no real priority support, it's simulated.
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
     * Interrupts this thread, setting the <i>interrupted</i> status of the thread.
     * This status is cleared by one of three methods. 
     *
     * If this thread is blocked when this method is called, the thread will
     * abort that blocking operation with an Interrupted_Exception.
     *
     *  - The first is by attempting an operation on a synchronization object that
     *    would normally block the calling thread; Instead of blocking the calling 
     *    the calling thread, the function that would normally block will thrown an
     *    Interrupted_Exception and clear the <i>interrupted</i> status of the thread.
     *
     *  - The second is by calling Thread::interrupted().
     * 
     *  - The third is by calling Thread::canceled().
     *
     * Threads already blocked by an operation on a synchronization object will abort
     * that operation with an Interrupted_Exception, clearing the threads <i>interrupted</i>
     * status as in the first case described above.
     *
     * Interrupting a thread that is no longer running will have no effect.
     *
     * @return 
     *   - <em>true</em> if the thread was interrupted while not blocked by a wait
     *     on a synchronization object.
     *   - <em>false</em> othewise.
     */
    bool interrupt();

    /**
     * Tests whether the current Thread has been interrupt()ed, clearing
     * its interruption status.
     *
     * @return 
     *   - <em>true</em> if the Thread was interrupted.
     *   - <em>false</em> otherwise.
     *
     * @post The <i>interrupted</i> status of the current thread will be cleared, 
     *       allowing it to perform a blocking operation on a synchronization
     *       object without throwing an exception.
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
     * @return 
     *   - <em>true</em> if the Thread was canceled.
     *   - <em>false</em> otherwise.
     * 
     * @see Cancelable::isCanceled()
     */
    virtual bool isCanceled();

    /**
     * Interrupt and cancel this thread in a single operation. The thread will 
     * return <em>true</em> whenever its cancelation status is tested in the future.
     *
     * @exception InvalidOp_Exception thrown if a thread attempts to cancel itself
     *
     * @see Thread::interrupt()
     * @see Cancelable::cancel()
     */
    virtual void cancel();

    /**
     * Put the currently executing thread to sleep for a given amount of
     * time.
     *
     * @param timeout maximum amount of time (milliseconds) this method could block
     *
     * @exception Interrupted_Exception thrown if the threads sleep is interrupted
     *            before <i>timeout</i> milliseconds expire.
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




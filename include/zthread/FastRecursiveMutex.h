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

#ifndef __ZTFASTRECURSIVEMUTEX_H__
#define __ZTFASTRECURSIVEMUTEX_H__

#include "zthread/Lockable.h"
#include "zthread/NonCopyable.h"

namespace ZThread {

  class FastRecursiveLock;

  /**
   * @class FastRecursiveMutex
   *
   * @author Eric Crahen <crahen@cse.buffalo.edu>
   * @date <2003-07-16T17:49:00-0400>
   * @version 2.2.0
   *
   * A FastRecursiveMutex is a small fast implementation of a recursive, mutally exclusive
   * Lockable object. This implementation is a bit faster than the other Mutex classes
   * as it involved the least overhead. However, this slight increase in speed is 
   * gained by sacrificing the robustness provided by the other classes. 
   *
   * Typically, a FastRecursiveMutex is implemented using a spin lock. It should be reserved 
   * for synchronizing short sections of code.
   *
   * @see RecursiveMutex
   *
   * <b>Scheduling</b>
   *
   * Scheduling is left to the operating systems and may vary.

   *
   * <b>Error Checking</b>
   *
   * No error checking is performed, this means there is the potential for deadlock.
   */ 
  class ZTHREAD_API FastRecursiveMutex : public Lockable, private NonCopyable {
    
    FastRecursiveLock* _lock;

  public:
  
    //! Create a new FastRecursiveMutex
    FastRecursiveMutex();

    //! Destroy this FastRecursiveMutex
    virtual ~FastRecursiveMutex();

    /**
     * Acquire exclusive access. No safety or state checks are performed.
     */
    virtual void acquire();

    /**
     * Release exclusive access. No safety or state checks are performed.
     * 
     * @pre This should not be called more times than the acquire() method was 
     *      called.
     */
    virtual void release();
  
    /**
     * Try to acquire exclusive access. No safety or state checks are performed.
     * This function returns immediately regardless of the value of the timeout
     *
     * @param timeout unused
     * @return 
     * - <em>true</em> if the lock was acquired
     * - <em>false</em> if the lock was acquired
     */
    virtual bool tryAcquire(unsigned long timeout = 0);
  
  }; 

} // namespace ZThread

#endif // __ZTFASTRECURSIVEMUTEX_H__

/*
 *  ZThreads, a platform-independent, multi-threading and 
 *  synchronization library
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

#ifndef __ZTTHREADLOCAL_H__
#define __ZTTHREADLOCAL_H__

#include "zthread/AbstractThreadLocal.h"

namespace ZThread {

  /**
   * @class ThreadLocal
   *
   * @author Eric Crahen <crahen@cse.buffalo.edu>
   * @date <2003-07-16T19:26:38-0400>
   * @version 2.2.0
   *
   * Provides a method to access the local storage of each thread. No matter
   * what thread access this object, it will always store values unique to
   * each thread. 
   *
   * The first time a ThreadLocal variable is accessed by a thread the initialValue()
   * method will be invoked. This allows subclasses to perform any special 
   * actions they might need to when a new thread uses one of these variables.
   *
   * The destroyValue() method is invoked when a thread that has 
   * used a ThreadLocal is about to exit. 
   *
   */
  template <class T>
    class ThreadLocal : protected AbstractThreadLocal {
    public:

    /**
     * Get the value associated with the current thread and this object via fetch().
     * If no association exists, then initialValue() is invoked.
     *
     * @return <em>T</em> value associated with the current thread and this object.
     */
    inline T get() const throw() {
      return reinterpret_cast<T>( AbstractThreadLocal::get() );
    }
  
    /**
     * Set the value associated with the current thread and this object. The value 
     * can only be retrieved from the current thread.
     *
     * @param newValue to associate with the current thread and this object.
     *
     * @return <em>T</em> value previously associated with the current thread and this object.
     */
    inline T set(T val) const {
      return reinterpret_cast<T>( AbstractThreadLocal::set((void*)val) );
    }

    protected:

    /** 
     * Invoked by the framework the first time get() is invoked by the
     * current thread, if no child value has been propagated. 
     *
     * @return <em>void*</em> When invoked by the framework, the value returned is 
     *                        associated with the current thread and this object. 
     */
    inline virtual void* initialValue() const {   
      return 0;
    }

  };


} // namespace ZThread

#endif // __ZTTHREADLOCAL_H__

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

#ifndef __ZTABSTRACTTHREADLOCAL_H__
#define __ZTABSTRACTTHREADLOCAL_H__

#include "zthread/Config.h"
#include "zthread/NonCopyable.h"

namespace ZThread {

  /**
   * @class AbstractThreadLocal
   * @author Eric Crahen <crahen@cse.buffalo.edu>
   * @date <2003-07-16T09:39:23-0400>
   * @version 2.2.11
   *
   * This defines a common base class that helps to support the behavior 
   * ThreadLocal objects.
   * 
   * @see ThreadLocal
   * @see InheritableThreadLocal
   */
  class ZTHREAD_API AbstractThreadLocal : private NonCopyable {
  public:

    //! Create a AbstractThreadLocal
    AbstractThreadLocal();
  
    //! Destroy a AbstractThreadLocal
    virtual ~AbstractThreadLocal();
  
    /** 
     * Invoked by the framework the first time get() is invoked by the
     * current thread, if no child value has been propagated. 
     *
     * @return <em>void*</em> When invoked by the framework, the value returned is 
     *                        associated with the current thread and this object. 
     */
    virtual void* initialValue() const = 0;

    /** 
     * Invoked by the framework whenever the value associated with current
     * thread and object is about to propagate to a child thread. This 
     * method is not invoked if there is no value associated with the
     * current thread and this object.
     *
     * The default implementation returns null.
     *
     * @param parentValue related initialization value
     *
     * @return <em>void*</em> When invoked by the framework, the value returned 
     *                        is associated with the current thread and this object. 
     */
    virtual void* childValue(void* parentValue) const;


    /** 
     * Invoked by the framework whenever it needs to be determined whether or not 
     * this object should propagate values to child threads.
     *
     * The default implementation returns false.
     *
     * @return <em>true</em> if this value childValue() produces should propagate.
     *         <em>false</em> otherwise.
     */
    virtual bool propogateValue() const;

    /**
     * Invoked by the framework when a thread that has set a value for a ThreadLocal
     * is about to exit. The initialValue() or childValue() methods will set values 
     * implicitly and therefore cause this method to be invoked. This acts as a 
     * point to insert some some last chance operation for a ThreadLocal, and is often 
     * useful as a cleanup point.
     *
     * @param currentValue value associated with the current thread and this 
     *                     object. 
     */
    virtual void destroyValue(void* currentValue) const;

  protected:

    /**
     * Get the value associated with the current thread and this object via fetch().
     * If no association exists, then initialValue() is invoked.
     *
     * @return <em>void*</em> value associated with the current thread and this object.
     */
    void* get() const;
  
    /**
     * Set the value associated with the current thread and this object. The value 
     * can only be retrieved from the current thread.
     *
     * @param newValue to associate with the current thread and this object.
     *
     * @return <em>void*</em> value previously associated with the current thread and this object.
     */
    void* set(void* newValue) const;

  };

} // __ZTABSTRACTTHREADLOCAL_H__

#endif


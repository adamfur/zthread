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

#ifndef __ZTINHERITABLETHREADLOCAL_H__
#define __ZTINHERITABLETHREADLOCAL_H__

#include "zthread/ThreadLocal.h"

namespace ZThread {

  /**
   * @class InheritableThreadLocal
   *
   * @author Eric Crahen <crahen@cse.buffalo.edu>
   * @date <2003-07-16T19:29:59-0400>
   * @version 2.2.0
   *
   * This object acts exactly like its super class ThreadLocal with one subtle
   * difference. That difference is that parent threads values can automatically
   * be propagated to child threads as they are created.
   *
   * The childValue() method allows subclasses to alter values for ThreadLocals
   * that propagated from parent threads to their children created.
   *
   * @see ThreadLocal
   */
  template <class T>
    class ZTHREAD_API InheritableThreadLocal : public ThreadLocal<T> {
    public:

    //! Create a new InheritableThreadLocal object
    InheritableThreadLocal() { }

    protected:

    /**
     * @see ThreadLocal::childValue(void* parentValue)
     */
    virtual void* childValue(void* parentValue) const {   
      return parentValue;
    }

    /**
     * Inform the framework this value does propagate to child threads
     *
     * @return <em>true</em>
     *
     * @see AbstractThreadLocal::propogateValue()
     */
    virtual bool propogateValue() const {
      return true;
    }

  };


} // namespace ZThread

#endif //  __ZTINHERITABLETHREADLOCAL_H__

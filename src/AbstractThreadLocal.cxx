/*
 *  ZThreads, a platform-independent, multi-threading and 
 *  synchronization library
 *
 *  Copyright (C) 2000-2003 Eric Crahen, See LGPL.TXT for details
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

#include "zthread/AbstractThreadLocal.h"
#include "ThreadImpl.h"
#include "ThreadLocalMap.h"

namespace ZThread {

  AbstractThreadLocal::AbstractThreadLocal() {}

  AbstractThreadLocal::~AbstractThreadLocal() {} 

  void* AbstractThreadLocal::get() const {

    ThreadLocalMap& map = ThreadImpl::current()->getThreadLocalMap();
    void* value = 0;

    // Try to get the value directly from the map, if its not present
    // then initialize that value.
    if(!map.getValue(this, value)) {
    
      value = initialValue();
      void* oldValue;

      map.setValue(this, oldValue, value);

    }

    return value;

  }

  void* AbstractThreadLocal::set(void* newValue) const {

    ThreadLocalMap& map = ThreadImpl::current()->getThreadLocalMap();
    void* oldValue = 0;
 
    if(!map.setValue(this, oldValue, newValue))
      oldValue = initialValue();
  
    return oldValue;

  }


  void AbstractThreadLocal::destroyValue(void*) const {
  }
  
  bool AbstractThreadLocal::propogateValue() const {
    return false;
  }

  void* AbstractThreadLocal::childValue(void*) const {
    return (void*)0;
  }

} // namespace ZThread 

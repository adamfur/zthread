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

#include "zthread/PriorityCondition.h"
#include "ConditionImpl.h"

namespace ZThread {

class PriorityConditionImpl : public ConditionImpl<priority_list> {
public:
  PriorityConditionImpl(Lockable& l) : ConditionImpl<priority_list>(l) {}

};

PriorityCondition::PriorityCondition(Lockable& lock)
  /* throw(Synchronization_Exception) */ {
  
  _impl = new PriorityConditionImpl(lock);

}


PriorityCondition::~PriorityCondition() 
  throw() {
  
  if(_impl != 0)
    delete _impl;

}



void PriorityCondition::wait() 
  /* throw(Synchronization_Exception) */ {

  _impl->wait();

}



bool PriorityCondition::wait(unsigned long ms) 
  /* throw(Synchronization_Exception) */ {

  return _impl->wait(ms);

}



void PriorityCondition::signal()
  /* throw(Synchronization_Exception) */ {

  _impl->signal();

}


void PriorityCondition::broadcast()
  /* throw(Synchronization_Exception) */ {

  _impl->broadcast();

}

} // namespace ZThread


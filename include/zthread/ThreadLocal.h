r/*
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

#include "zthread/ThreadLocalImpl.h"

namespace ZThread {

  /**
   * @class ThreadLocal
   *
   * @author Eric Crahen <crahen@cse.buffalo.edu>
   * @date <2003-07-26T15:14:22-0400>
   * @version 2.3.0
   *
   * Provides access to store and retrieve value types to and from a thread local 
   * storage context. A thread local storage context consists of the calling thread
   * a specific ThreadLocal object. Since this context is specific to each thread
   * whenever a value is stored in a ThreadLocal that is accessible from multiple 
   * threads, it can only be retrieved by the thread that stored it. 
   *
   * The first time a thread accesses the value associated with a thread local storage
   * context, a value is created. That value is either an initial value (determined by 
   * InitialValueT) or an inherited value (determined by ChildValueT).
   *
   * - If a threads parent had no value associated with a ThreadLocal when the thread was created,
   *   then the InitialValueT functor is used to create an initial value.
   *
   * - If a threads parent did have a value associated with a ThreadLocal when the thread was 
   *   created, then the childValueT functor is used to create an initial value.
   *
   * Not all ThreadLocal's support the inheritance of values from parent threads. The default
   * behavoir is to create values through the InitialValueT functor for all thread when
   * they first access a thread local storage context. 
   * 
   * - Inheritance is enabled automatically when a user supplies a ChildValueT functor other
   *   than the default one supplied.
   *
   * - Inheritance can be controlled explicitly by the user through a third functor, 
   *   InheritableValueT.
   *
   * <em>InitialValueT</em>
   *
   * This template parameter should indicate the functor used to set
   * the initial value. It should support the following operator:
   *
   * <code>
   * // required operator
   * T operator() 
   *
   * // supported expression
   * InitialValueT()()
   * </code>
   *
   *
   * <em>ChildValueT</em>
   *
   * This template parameter should indicate the functor used to set
   * the value that will be inherited by thread whose parent have associated
   * a value with the ThreadLocal's context at the time they are created. 
   * It should support the following operator:
   *
   * <code>
   * // required operator
   * T operator(const T& parentValue) 
   *
   * // supported expression
   * ChildValueT()(parentValue)
   * </code>
   *
   *
   * <em>InheritableValueT</em>
   *
   * This template parameter should indicate the functor, used to determine
   * wheather or not this ThreadLocal will allow values from a parent threads
   * context to be inherited by child threads when they are created.
   * It should support the following operator:
   *
   * <code>
   * // required operator
   * bool operator(const T& childValueFunctor) 
   *
   * // supported expression
   * InheritableValueT()( ChildValueT() )
   * </code>
   *
   */
  template <
    typename T, 
    typename InitialValueT      = ThreadLocalImpl::InitialValueFn<T>,
    typename ChildValueT        = ThreadLocalImpl::UniqueChildValueFn, 
    typename InheritableValueT  = ThreadLocalImpl::InheritableValueFn
    >
    class ThreadLocal : public ThreadLocalImpl {

      typedef ThreadLocalImpl::ValuePtr ValuePtr;

      class Value : public ThreadLocalImpl::Value {
        
        T value;
        
      public:
        
        Value() : value( InitialValueT()() ) { }
        
        Value(const Value& v) : value( ChildValueT()(v.value) ) { }
        
        virtual ~Value() { } 
        
        operator T() { return value; }
        
        const Value& operator=(const T& v) { value = v; }
        
        virtual bool isInheritable() const {
          return InheritableValueT()( ChildValueT() );
        }
        
        virtual ValuePtr clone() const {
          return ValuePtr( new Value(*this) );
        }
        
      };
      
      static ValuePtr createValue() {
        return ValuePtr( new Value );
      }
      
    public:

    /**
     * Get the value associated with the context (this ThreadLocal and 
     * the calling thread) of the invoker. If no value is currently
     * associated, then an intial value is created and associated; that value
     * is returned.
     *
     * @return <em>T</em> associated value.
     *
     * @post  If no value has been associated with the invoking context
     *        then an inital value will be associated. That value is
     *        created by the <em>InitialValueT</em> functor.   
     */
    T get() const { 
      return (T)reinterpret_cast<Value&>( *value(&createValue) );
    }
  
    /**
     * Replace the value associated with the context (this ThreadLocal and 
     * the calling thread) of the invoker. If no value is currently
     * associated, then an intial value is first created and subsequently
     * replaced by the new value.
     *
     * @param v value of type <em>T</em> to associate.
     *
     * @post  If no value has been associated with the invoking context
     *        then an inital value will first be associated. That value is
     *        created by the <em>InitialValueT</em> functor and then 
     *        replaced with the new value.   
     */
    void set(T v) const {
      reinterpret_cast<Value&>( *value(&createValue) ) = v;
    }

  };


} // namespace ZThread

#endif // __ZTTHREADLOCAL_H__

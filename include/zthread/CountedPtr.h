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

#ifndef __ZTCOUNTEDPTR_H__
#define __ZTCOUNTEDPTR_H__

#include <algorithm>
#include <cassert>

#include "zthread/AtomicCount.h"

namespace ZThread {
  
  /**
   * @class CountedPtr
   *
   * @author Eric Crahen <http://www.code-foo.com>
   * @date <2003-07-26T07:00:10-0400>
   * @version 2.3.0
   *
   */
  template <typename T, typename CountT = AtomicCount>
    class CountedPtr {

      template <typename U, typename V> friend class CountedPtr;

      CountT* _count;
      T*  _instance;

      public:

      CountedPtr() : _count(0), _instance(0) { }

      explicit CountedPtr(T* raw) : _count(new CountT()), _instance(raw) {
        (*_count)++;
      }

      template <typename U>
      explicit CountedPtr(U* raw) : _count(new CountT()), _instance(raw) {
        (*_count)++;
      }

      CountedPtr(const CountedPtr& ptr) : _count(ptr._count), _instance(ptr._instance) {

        if(_count)
          (*_count)++;

      }

      template <typename U, typename V>
      CountedPtr(const CountedPtr<U, V>& ptr) : _count(ptr._count), _instance(ptr._instance) {

        if(_count)
          (*_count)++;

      }

      ~CountedPtr() {

        if(_count && --(*_count) == 0) {
   
          if(_instance) 
            delete _instance;

          delete _count;
      
        }

      }
  
      const CountedPtr& operator=(const CountedPtr& ptr) {
    
        typedef CountedPtr<T, CountT> ThisT;

        ThisT(ptr).swap(*this);
        return *this;

      } 

      template <typename U, typename V>
      const CountedPtr& operator=(const CountedPtr<U, V>& ptr) {
    
        typedef CountedPtr<T, CountT> ThisT;

        ThisT(ptr).swap(*this);
        return *this;

      } 

      void reset() {

        typedef CountedPtr<T, CountT> ThisT;
        ThisT().swap(*this);

      }

      void swap(CountedPtr& ptr) {

        std::swap(_count, ptr._count);
        std::swap(_instance, ptr._instance);

      }
  
      template <typename U, typename V>
      void swap(CountedPtr<U, V>& ptr) {

        std::swap(_count, ptr._count);
        std::swap(_instance, ptr._instance);

      }

      // Convience operators

      bool less(const CountedPtr& ptr) const {
        return _instance < ptr._instance;
      }

      template <typename U, typename V>
      bool less(const CountedPtr<U, V>& ptr) const {
        return _instance < ptr._instance;
      }

      bool equal(const CountedPtr& ptr) const {
        return _count == ptr._count;
      }

      template <typename U, typename V>
      bool equal(const CountedPtr<U, V>& ptr) const {
        return _count == ptr._count;
      }


      friend inline bool operator==(const CountedPtr& lhs, const CountedPtr& rhs) {
        return lhs.equal(rhs);
      }

      friend inline bool operator<(const CountedPtr& lhs, const CountedPtr& rhs) {
        return lhs.less(rhs);
      }


      T& operator*() {
        assert(_instance != 0);
        return *_instance;
      }

      T* operator->() {
        assert(_instance != 0);
        return _instance;
      }

      const T* operator->() const {
        assert(_instance != 0);
        return _instance;
      }
 
      bool operator!() const {
        return _instance == 0;
      }

      operator bool() const {
        return _instance != 0;
      }
      
    }; /* CountedPtr */

  template<typename U, typename V, typename X, typename Y> 
    inline bool operator<(CountedPtr<U, V> const &lhs, CountedPtr<X, Y> const &rhs) {
    return lhs.less(rhs);
  }

  template<typename U, typename V, typename X, typename Y> 
    inline bool operator==(CountedPtr<U, V> const &lhs, CountedPtr<X, Y> const &rhs) {
    return lhs.equal(rhs.get);
  }

  template<typename U, typename V, typename X, typename Y> 
    inline bool operator!=(CountedPtr<U, V> const &lhs, CountedPtr<X, Y> const &rhs) {
    return !(lhs.equal(rhs.get));
  }

  template<typename U, typename V, typename X, typename Y> 
    inline void swap(CountedPtr<U, V> const &lhs, CountedPtr<X, Y> const &rhs) {
    lhs.swap(rhs);
  }

  template<typename U, typename V>
    inline bool operator<(CountedPtr<U, V> const &lhs, CountedPtr<U, V> const &rhs) {
    return lhs.less(rhs);
  }

  template<typename U, typename V> 
    inline bool operator==(CountedPtr<U, V> const &lhs, CountedPtr<U, V> const &rhs) {
    return lhs.equal(rhs.get);
  }

  template<typename U, typename V> 
    inline bool operator!=(CountedPtr<U, V> const &lhs, CountedPtr<U, V> const &rhs) {
    return !(lhs.equal(rhs.get));
  }

  template<typename U, typename V> 
    inline void swap(CountedPtr<U, V> const &lhs, CountedPtr<U, V> const &rhs) {
    lhs.swap(rhs);
  }

} // namespace ZThread

#endif // __ZTCOUNTEDPTR_H__

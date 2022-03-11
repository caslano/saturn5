//////////////////////////////////////////////////////////////////////////////
//
// This file is the adaptation for Interprocess of boost/weak_ptr.hpp
//
// (C) Copyright Peter Dimov 2001, 2002, 2003
// (C) Copyright Ion Gaztanaga 2006-2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_WEAK_PTR_HPP_INCLUDED
#define BOOST_INTERPROCESS_WEAK_PTR_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/smart_ptr/shared_ptr.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/smart_ptr/deleter.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/move/adl_move_swap.hpp>

//!\file
//!Describes the smart pointer weak_ptr.

namespace boost{
namespace interprocess{

//!The weak_ptr class template stores a "weak reference" to an object
//!that's already managed by a shared_ptr. To access the object, a weak_ptr
//!can be converted to a shared_ptr using  the shared_ptr constructor or the
//!member function  lock. When the last shared_ptr to the object goes away
//!and the object is deleted, the attempt to obtain a shared_ptr from the
//!weak_ptr instances that refer to the deleted object will fail: the constructor
//!will throw an exception of type bad_weak_ptr, and weak_ptr::lock will
//!return an empty shared_ptr.
//!
//!Every weak_ptr meets the CopyConstructible and Assignable requirements
//!of the C++ Standard Library, and so can be used in standard library containers.
//!Comparison operators are supplied so that weak_ptr works with the standard
//!library's associative containers.
//!
//!weak_ptr operations never throw exceptions.
//!
//!The class template is parameterized on T, the type of the object pointed to.
template<class T, class A, class D>
class weak_ptr
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   // Borland 5.5.1 specific workarounds
   typedef weak_ptr<T, A, D> this_type;
   typedef typename boost::intrusive::
      pointer_traits<typename A::pointer>::template
         rebind_pointer<T>::type                         pointer;
   typedef typename ipcdetail::add_reference
                     <T>::type            reference;
   typedef typename ipcdetail::add_reference
                     <T>::type            const_reference;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   typedef T element_type;
   typedef T value_type;

   //!Effects: Constructs an empty weak_ptr.
   //!Postconditions: use_count() == 0.
   weak_ptr()
   : m_pn() // never throws
   {}
   //  generated copy constructor, assignment, destructor are fine
   //
   //  The "obvious" converting constructor implementation:
   //
   //  template<class Y>
   //  weak_ptr(weak_ptr<Y> const & r): m_px(r.m_px), m_pn(r.m_pn) // never throws
   //  {
   //  }
   //
   //  has a serious problem.
   //
   //  r.m_px may already have been invalidated. The m_px(r.m_px)
   //  conversion may require access to *r.m_px (virtual inheritance).
   //
   //  It is not possible to avoid spurious access violations since
   //  in multithreaded programs r.m_px may be invalidated at any point.

   //!Effects: If r is empty, constructs an empty weak_ptr; otherwise,
   //!constructs a weak_ptr that shares ownership with r as if by storing a
   //!copy of the pointer stored in r.
   //!
   //!Postconditions: use_count() == r.use_count().
   //!
   //!Throws: nothing.
   template<class Y>
   weak_ptr(weak_ptr<Y, A, D> const & r)
      : m_pn(r.m_pn) // never throws
   {
      //Construct a temporary shared_ptr so that nobody
      //can destroy the value while constructing this
      const shared_ptr<T, A, D> &ref = r.lock();
      m_pn.set_pointer(ref.get());
   }

   //!Effects: If r is empty, constructs an empty weak_ptr; otherwise,
   //!constructs a weak_ptr that shares ownership with r as if by storing a
   //!copy of the pointer stored in r.
   //!
   //!Postconditions: use_count() == r.use_count().
   //!
   //!Throws: nothing.
   template<class Y>
   weak_ptr(shared_ptr<Y, A, D> const & r)
      : m_pn(r.m_pn) // never throws
   {}

   //!Effects: Equivalent to weak_ptr(r).swap(*this).
   //!
   //!Throws: nothing.
   //!
   //!Notes: The implementation is free to meet the effects (and the
   //!implied guarantees) via different means, without creating a temporary.
   template<class Y>
   weak_ptr & operator=(weak_ptr<Y, A, D> const & r) // never throws
   {
      //Construct a temporary shared_ptr so that nobody
      //can destroy the value while constructing this
      const shared_ptr<T, A, D> &ref = r.lock();
      m_pn = r.m_pn;
      m_pn.set_pointer(ref.get());
      return *this;
   }

   //!Effects: Equivalent to weak_ptr(r).swap(*this).
   //!
   //!Throws: nothing.
   //!
   //!Notes: The implementation is free to meet the effects (and the
   //!implied guarantees) via different means, without creating a temporary.
   template<class Y>
   weak_ptr & operator=(shared_ptr<Y, A, D> const & r) // never throws
   {  m_pn = r.m_pn;  return *this;  }

   //!Returns: expired()? shared_ptr<T>(): shared_ptr<T>(*this).
   //!
   //!Throws: nothing.
   shared_ptr<T, A, D> lock() const // never throws
   {
      // optimization: avoid throw overhead
      if(expired()){
         return shared_ptr<element_type, A, D>();
      }
      BOOST_TRY{
         return shared_ptr<element_type, A, D>(*this);
      }
      BOOST_CATCH(bad_weak_ptr const &){
         // Q: how can we get here?
         // A: another thread may have invalidated r after the use_count test above.
         return shared_ptr<element_type, A, D>();
      }
      BOOST_CATCH_END
   }

   //!Returns: 0 if *this is empty; otherwise, the number of shared_ptr objects
   //!that share ownership with *this.
   //!
   //!Throws: nothing.
   //!
   //!Notes: use_count() is not necessarily efficient. Use only for debugging and
   //!testing purposes, not for production code.
   long use_count() const // never throws
   {  return m_pn.use_count();  }

   //!Returns: Returns: use_count() == 0.
   //!
   //!Throws: nothing.
   //!
   //!Notes: expired() may be faster than use_count().
   bool expired() const // never throws
   {  return m_pn.use_count() == 0;   }

   //!Effects: Equivalent to:
   //!weak_ptr().swap(*this).
   void reset() // never throws in 1.30+
   {  this_type().swap(*this);   }

   //!Effects: Exchanges the contents of the two
   //!smart pointers.
   //!
   //!Throws: nothing.
   void swap(this_type & other) // never throws
   {  ::boost::adl_move_swap(m_pn, other.m_pn);   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   template<class T2, class A2, class D2>
   bool _internal_less(weak_ptr<T2, A2, D2> const & rhs) const
   {  return m_pn < rhs.m_pn;  }

   template<class Y>
   void _internal_assign(const ipcdetail::shared_count<Y, A, D> & pn2)
   {

      m_pn = pn2;
   }

   private:

   template<class T2, class A2, class D2> friend class shared_ptr;
   template<class T2, class A2, class D2> friend class weak_ptr;

   ipcdetail::weak_count<T, A, D> m_pn;      // reference counter
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};  // weak_ptr

template<class T, class A, class D, class U, class A2, class D2> inline
bool operator<(weak_ptr<T, A, D> const & a, weak_ptr<U, A2, D2> const & b)
{  return a._internal_less(b);   }

template<class T, class A, class D> inline
void swap(weak_ptr<T, A, D> & a, weak_ptr<T, A, D> & b)
{  a.swap(b);  }

//!Returns the type of a weak pointer
//!of type T with the allocator boost::interprocess::allocator allocator
//!and boost::interprocess::deleter deleter
//!that can be constructed in the given managed segment type.
template<class T, class ManagedMemory>
struct managed_weak_ptr
{
   typedef weak_ptr
   < T
   , typename ManagedMemory::template allocator<void>::type
   , typename ManagedMemory::template deleter<T>::type
   > type;
};

//!Returns an instance of a weak pointer constructed
//!with the default allocator and deleter from a pointer
//!of type T that has been allocated in the passed managed segment
template<class T, class ManagedMemory>
inline typename managed_weak_ptr<T, ManagedMemory>::type
   make_managed_weak_ptr(T *constructed_object, ManagedMemory &managed_memory)
{
   return typename managed_weak_ptr<T, ManagedMemory>::type
   ( constructed_object
   , managed_memory.template get_allocator<void>()
   , managed_memory.template get_deleter<T>()
   );
}

} // namespace interprocess
} // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif  // #ifndef BOOST_INTERPROCESS_WEAK_PTR_HPP_INCLUDED

/* weak_ptr.hpp
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
*/
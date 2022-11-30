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
   typedef typename boost::container::
      allocator_traits<A>::pointer                       alloc_ptr;
   typedef typename boost::intrusive::
      pointer_traits<alloc_ptr>::template
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
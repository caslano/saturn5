//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_POLYMORPHIC_ALLOCATOR_HPP
#define BOOST_CONTAINER_PMR_POLYMORPHIC_ALLOCATOR_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/config.hpp>
#include <boost/move/detail/type_traits.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/container/detail/dispatch_uses_allocator.hpp>
#include <boost/container/new_allocator.hpp>
#include <boost/container/pmr/memory_resource.hpp>
#include <boost/container/pmr/global_resource.hpp>

#include <cstddef>

namespace boost {
namespace container {
namespace pmr {

//! A specialization of class template `polymorphic_allocator` conforms to the Allocator requirements.
//! Constructed with different memory resources, different instances of the same specialization of
//! `polymorphic_allocator` can exhibit entirely different allocation behavior. This runtime
//! polymorphism allows objects that use polymorphic_allocator to behave as if they used different
//! allocator types at run time even though they use the same static allocator type.
template <class T>
class polymorphic_allocator
{
   public:
   typedef T value_type;

   //! <b>Effects</b>: Sets m_resource to
   //! `get_default_resource()`.
   polymorphic_allocator() BOOST_NOEXCEPT
      : m_resource(::boost::container::pmr::get_default_resource())
   {}

   //! <b>Requires</b>: r is non-null.
   //!
   //! <b>Effects</b>: Sets m_resource to r.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Notes</b>: This constructor provides an implicit conversion from memory_resource*.
   polymorphic_allocator(memory_resource* r) BOOST_NOEXCEPT
      : m_resource(r)
   {  BOOST_ASSERT(r != 0);  }

   //! <b>Effects</b>: Sets m_resource to
   //!   other.resource().
   polymorphic_allocator(const polymorphic_allocator& other) BOOST_NOEXCEPT
      : m_resource(other.m_resource)
   {}

   //! <b>Effects</b>: Sets m_resource to
   //!   other.resource().
   template <class U>
   polymorphic_allocator(const polymorphic_allocator<U>& other) BOOST_NOEXCEPT
      : m_resource(other.resource())
   {}

   //! <b>Effects</b>: Sets m_resource to
   //!   other.resource().
   polymorphic_allocator& operator=(const polymorphic_allocator& other) BOOST_NOEXCEPT
   {  m_resource = other.m_resource;   return *this;  }

   //! <b>Returns</b>: Equivalent to
   //!   `static_cast<T*>(m_resource->allocate(n * sizeof(T), alignof(T)))`.
   T* allocate(size_t n)
   {  return static_cast<T*>(m_resource->allocate(n*sizeof(T), ::boost::move_detail::alignment_of<T>::value));  }

   //! <b>Requires</b>: p was allocated from a memory resource, x, equal to *m_resource,
   //! using `x.allocate(n * sizeof(T), alignof(T))`.
   //!
   //! <b>Effects</b>: Equivalent to m_resource->deallocate(p, n * sizeof(T), alignof(T)).
   //!
   //! <b>Throws</b>: Nothing.
   void deallocate(T* p, size_t n) BOOST_NOEXCEPT
   {  m_resource->deallocate(p, n*sizeof(T), ::boost::move_detail::alignment_of<T>::value);  }

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Requires</b>: Uses-allocator construction of T with allocator
   //!   `*this` and constructor arguments `std::forward<Args>(args)...`
   //!   is well-formed. [Note: uses-allocator construction is always well formed for
   //!   types that do not use allocators. - end note]
   //!
   //! <b>Effects</b>: Construct a T object at p by uses-allocator construction with allocator
   //!   `*this` and constructor arguments `std::forward<Args>(args)...`.
   //!
   //! <b>Throws</b>: Nothing unless the constructor for T throws.
   template < typename U, class ...Args>
   void construct(U* p, BOOST_FWD_REF(Args)...args)
   {
      new_allocator<U> na;
      dtl::dispatch_uses_allocator
         (na, *this, p, ::boost::forward<Args>(args)...);
   }

   #else // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //Disable this overload if the first argument is pair as some compilers have
   //overload selection problems when the first parameter is a pair.
   #define BOOST_CONTAINER_PMR_POLYMORPHIC_ALLOCATOR_CONSTRUCT_CODE(N) \
   template < typename U BOOST_MOVE_I##N BOOST_MOVE_CLASSQ##N >\
   void construct(U* p BOOST_MOVE_I##N BOOST_MOVE_UREFQ##N)\
   {\
      new_allocator<U> na;\
      dtl::dispatch_uses_allocator\
         (na, *this, p BOOST_MOVE_I##N BOOST_MOVE_FWDQ##N);\
   }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_PMR_POLYMORPHIC_ALLOCATOR_CONSTRUCT_CODE)
   #undef BOOST_CONTAINER_PMR_POLYMORPHIC_ALLOCATOR_CONSTRUCT_CODE

   #endif   //#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>:
   //!   p->~U().
   template <class U>
   void destroy(U* p)
   {  (void)p; p->~U(); }

   //! <b>Returns</b>: Equivalent to
   //!   `polymorphic_allocator()`.
   polymorphic_allocator select_on_container_copy_construction() const BOOST_NOEXCEPT
   {  return polymorphic_allocator();  }

   //! <b>Returns</b>:
   //!   m_resource.
   memory_resource* resource() const BOOST_NOEXCEPT
   {  return m_resource;  }

   private:
   memory_resource* m_resource;
};

//! <b>Returns</b>:
//!   `*a.resource() == *b.resource()`.
template <class T1, class T2>
bool operator==(const polymorphic_allocator<T1>& a, const polymorphic_allocator<T2>& b) BOOST_NOEXCEPT
{  return *a.resource() == *b.resource();  }


//! <b>Returns</b>:
//!   `! (a == b)`.
template <class T1, class T2>
bool operator!=(const polymorphic_allocator<T1>& a, const polymorphic_allocator<T2>& b) BOOST_NOEXCEPT
{  return *a.resource() != *b.resource();  }

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_POLYMORPHIC_ALLOCATOR_HPP

/* polymorphic_allocator.hpp
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
*/
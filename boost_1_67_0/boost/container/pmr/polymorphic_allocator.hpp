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
   //!   Non-standard extension: if r is null m_resource is set to get_default_resource().
   polymorphic_allocator(memory_resource* r)
      : m_resource(r ? r : ::boost::container::pmr::get_default_resource())
   {}

   //! <b>Effects</b>: Sets m_resource to
   //!   other.resource().
   polymorphic_allocator(const polymorphic_allocator& other)
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
   polymorphic_allocator& operator=(const polymorphic_allocator& other)
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
   void deallocate(T* p, size_t n)
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
   polymorphic_allocator select_on_container_copy_construction() const
   {  return polymorphic_allocator();  }

   //! <b>Returns</b>:
   //!   m_resource.
   memory_resource* resource() const
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
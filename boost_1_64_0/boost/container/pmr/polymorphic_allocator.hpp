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
0exgNJ/Y1qFNBLMQu+GD3Ra0jCztOnPBaC3imBatgIkrkezyvxy+Da0SzEbs6qMxC9Aapbhr+m6tRGuTall1T189Wqc0LukFuU+jmef6W+HGkEloE8FoPvGef2jpYDRfREHojWhZYHZiNYPGDkMrluyNmGc2o9WBmYl1Dv7VELRmMAux6cO/PobWKdmjf7ujCM04z78PJ3rtWYdmBaNxVzQsOeKxTCUFDOfgZPq36mBOxtIYS2csg7EsxnIkE8fXaC4wlVhPwk/HornBrMSeX/nhcbQKyW4v3mLwGLyui+S7gr6WA6yRsWYwldiArrUT0NpFPmJzF/zJgqbM97eqx176Fs0GRtu0LfzoCY/BsQUY1jKFPicBS2HMyVgaY+lgZmJ7blrfgJYjWWlb5zE0N5iJmHjfQrRSMAux4++lDkWrkewy64cutCamzhYwlZjYZqF1MHGdUh8Oxrz8GJoh278P4jOY0SyMJYLRNsX7AqClMnEZYLROcWyKlsVYjmTi7/HQXIzlS7WI40+04mzt8SyX+pffudCJVivZmb89th6tSR6XqQn3onVItVRNHTsVrRvMSmxa26t1aJYF2svWxpgdzELspj2XH0BLBdPq+2wwWmfG5m+daDlgZmJXl8RnoLmlOPG3A2ilTJ3ljFUSS9XP97NqxmoZ28dYA2NNjLUw1sZYB2OdjJ1hrIcxw+3apjJmZszKWAJjiYwlMTaRsVTGZjI2m7FMxrIZy2Usj7ECxgoZK2aslLFyxioZq2aslrF9YCZidJvcLNnOU21PonWA2YhVrm3ajGZc6B8n/tYSzQqmEvtbzo7DaIlgCcRCP9j9LdpsyRLvnrUcrUDK97ufHxuIVgJG6yz8+PBgtFoprvO119ejNYJZiIlzHmgdYFZiP791bgiaIcff6L4jAczsM/KeOS5lIhguo6n0/CBYKmMzGZvNWCZj2YzlMpbHWAFjhYwVM1bKWDljlYxVM1bL2D7GGhhrYqyFsTbGOhjrZOwMYz2MGe7QNpUxM2NWxhIYS2QsSTLxO2i0iWBmYg+8PPoztNlgFmIl9+7YiuaS7NqVr25CKwYzEXNuvrMBrQLMSky8HgytXqpFvO8BWqtkjp2B/dG6aD58r0BcRov84wKufzsZzQpG+yC2dWgpYCqxZ0Pi70VLA7MRe+HomQfRcsFoLUerk+9Ec0v28zuvuQatVKozuPbSS9GqaRyeZ8cxk/ogfueN1raIWVekNunrYrvBrMTEthzNciepk54vB3OA0TaLH3n2L3hOIBUMx3Oa33tEjlVmg2Gd0+nvx8AyGctmLJexPMYKGCtkrJixUsbKGatkrBpMJXbz14F/Q9sHZiF2YP+0GrRWySL6tX6Mdkayw7NSp3oMXkeS66slTXpfRgtjNsbsjDkYS2HMyVgaY+mMZTCWxVgOYy7G8hlzM1bEWAljZYxVgKnE6Ptg1YCZiNH3v24gbV4J59bE++ujNYGZiVkPrU9A65CsZuOzWWg9Ih+xO99psqKZfuafb4b9ing0C5iZWtMfb0BzSHayvFcEWpqmwWcKknwz6N+8guUw5mIsnzE3Y0WMlTBWxlgFY1WM1TBWx1g9Y42MNTPWylg7Y6cY6wJLILb2gHs6mmUxzE9iQ41VQWiJYDZiqVv63Y6WLlmf+7e4PbZMyQPDWq6irzEDKyA2Uz/XzwoZK2aslLFyxioZq2aslrF9jDUw1sRYi2Riu4TWxlgHmEpMvC4W7QyTr4cxwxJ/E++Fj6aC0Xxiu4tmBTMT6/4y/l20JDALsd8lXu5CSwczEXt2wukr0bLBrMR63vtDM1rhEmYuUZM+Z7KU2NX6sb44sHLGKhmrZqyWsX2MNTA=
*/
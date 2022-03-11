/* Copyright 2003-2020 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_ALLOCATOR_TRAITS_HPP
#define BOOST_MULTI_INDEX_DETAIL_ALLOCATOR_TRAITS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */

#if !defined(BOOST_NO_CXX11_ALLOCATOR)
#include <memory>
#else
#include <boost/detail/workaround.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/multi_index/detail/vartempl_support.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <new>
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* poor man's replacement of std::allocator_traits */

#if !defined(BOOST_NO_CXX11_ALLOCATOR)

template<typename Allocator>
struct allocator_traits:std::allocator_traits<Allocator>
{
  /* wrap std::allocator_traits alias templates for use in C++03 codebase */

  typedef std::allocator_traits<Allocator> super;

  template<typename T>
  struct rebind_alloc
  {
    typedef typename super::template rebind_alloc<T> type;
  };

  template<typename T>
  struct rebind_traits
  {
    typedef typename super::template rebind_traits<T> type;
  };
};

#else

/* not a full std::allocator_traits rewrite (not needed) */

template<typename Allocator>
struct allocator_traits
{
  typedef Allocator                           allocator_type;
  typedef typename Allocator::value_type      value_type;
  typedef typename Allocator::pointer         pointer;
  typedef typename Allocator::const_pointer   const_pointer;

  /* [const_]void_pointer not provided as boost::pointer_traits's
   * rebind_to has been seen to fail with things like
   * boost::interprocess::offset_ptr in relatively old environments.
   */

  typedef typename Allocator::difference_type difference_type;
  typedef typename Allocator::size_type       size_type;

  typedef boost::false_type propagate_on_container_copy_assignment;
  typedef boost::false_type propagate_on_container_move_assignment;
  typedef boost::false_type propagate_on_container_swap;

  template<typename T>
  struct rebind_alloc
  {
    typedef typename Allocator::template rebind<T>::other type;
  };

  template<typename T>
  struct rebind_traits
  {
    typedef allocator_traits<typename rebind_alloc<T>::type> type;
  };

  static pointer   allocate(Allocator& a,size_type n){return a.allocate(n);}
  static pointer   allocate(Allocator& a,size_type n,const_pointer p)
                                   /* should've been const_void_pointer p */
                     {return a.allocate(n,p);} 
  static void      deallocate(Allocator& a,pointer p,size_type n)
                     {a.deallocate(p,n);}
  template<typename T>
  static void      construct(Allocator&,T* p,const T& x)
                     {::new (static_cast<void*>(p)) T(x);}
  template<typename T>
  static void      construct(Allocator&,T* p,BOOST_RV_REF(T) x)
                     {::new (static_cast<void*>(p)) T(boost::move(x));}
 
  template<typename T,BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK>
  static void construct(Allocator&,T* p,BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK)
  {
    vartempl_placement_new(p,BOOST_MULTI_INDEX_FORWARD_PARAM_PACK);
  }

#if BOOST_WORKAROUND(BOOST_MSVC,BOOST_TESTED_AT(1500))
/* MSVC issues spurious warnings about unreferencend formal parameters in
 * destroy<T> when T is a class with trivial dtor.
 */

#pragma warning(push)
#pragma warning(disable:4100)
#endif

  template<typename T>
  static void destroy(Allocator&,T* p){p->~T();}

#if BOOST_WORKAROUND(BOOST_MSVC,BOOST_TESTED_AT(1500))
#pragma warning(pop)
#endif

  static size_type max_size(Allocator& a)BOOST_NOEXCEPT{return a.max_size();}

  static Allocator select_on_container_copy_construction(const Allocator& a)
  {
    return a;
  }
};

#endif

template<typename Allocator,typename T>
struct rebind_alloc_for
{
  typedef typename allocator_traits<Allocator>::
    template rebind_alloc<T>::type               type;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* allocator_traits.hpp
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
*/
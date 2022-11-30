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
#include <boost/type_traits/is_empty.hpp>
#include <memory>
#else
#include <boost/detail/workaround.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/multi_index/detail/vartempl_support.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_empty.hpp>
#include <new>
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* poor man's replacement of std::allocator_traits */

#if !defined(BOOST_NO_CXX11_ALLOCATOR)

template<typename T> struct void_helper{typedef void type;};

template<typename Allocator,typename=void>
struct allocator_is_always_equal:boost::is_empty<Allocator>{};

template<typename Allocator>
struct allocator_is_always_equal<
  Allocator,
  typename void_helper<
    typename std::allocator_traits<Allocator>::is_always_equal
  >::type
>:std::allocator_traits<Allocator>::is_always_equal{};

template<typename Allocator>
struct allocator_traits:std::allocator_traits<Allocator>
{
  /* wrap std::allocator_traits alias templates for use in C++03 codebase */

  typedef std::allocator_traits<Allocator> super;

  /* pre-C++17 compatibilty */

  typedef allocator_is_always_equal<Allocator> is_always_equal;

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

  typedef boost::false_type          propagate_on_container_copy_assignment;
  typedef boost::false_type          propagate_on_container_move_assignment;
  typedef boost::false_type          propagate_on_container_swap;
  typedef boost::is_empty<Allocator> is_always_equal;

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
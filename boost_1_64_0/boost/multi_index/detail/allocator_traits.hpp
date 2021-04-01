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
hIc1DZFQgj/Hy8xUTd4CNJ2KtcdBd9FVpmo9gexvzOhvxo4Bk4YbCQpyl+PJur4v3kXXXQPb6YSg5bhT3TOxSYq7vUx6chJhynaI3oXroJywU721l4dA70HqtJ+nPpEOGW2hJiBfcK89rkVi2sdDeEtjkGugrBD6NjLqwncyLMMup6osThVOavw4K42BIKq+T21oIKU0cRNW0rD/RQKXfTR92nx1BcWEzSJrxt5ig2tZlU+2sm7lF+sX9q3SntaMDe9JK1ViwqLYSqyjIY13kG0mY3z3VV5IfTKW1S+LRhfoI0FeOHoeywYQateHJNvyOuOePQ9vCp8C/ePhXvL6p8TEQphy0bDsu8d+pv0rh+ESH89vjNubY0/LaQPoZHMiXTaXXR1/N8Errq9XapJED0MzveLdvo5tK8etgqwzEkS3iKfAdc7rcdDrnLDSpEWJHpSQUrIUSMaUlyDKrOawbgooXAGYpYUb+rRxwkiCzLUVA8VpLJ4RZj1sJyi9iTCNFsZ6/BFE3+g2r79w6cA2fQPDRyGd4rw4QLPnugeI2FiaGo81EKoGYlOO0A==
*/
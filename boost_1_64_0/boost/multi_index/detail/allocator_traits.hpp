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
LqTisNdabapjJnIPcZTxussbW6uLlasQrNfLigO4cheO4Xcfx3DmZ/s0hqtNNoZf6ofLM6cuhr9gB4bDNhv7njuB4fK9eNVvsQ73qTpc35KW1FVFAkbq7UpdL8CgfefgCGAQysoiI8NwVpZlDAdFR5fUCYazMh4fw3BWxgsYzsv4+HEMxzLiOeOb2FmYG3lR4vm2WGuvbcDBC/iXbW/yc/vPUxnbF4GdhnacRkLpQuVx0zBhckfxIpV3EhGHcLJaXLuN/or8Ef12mlPxyUSxmfrYMxQmM0Zg2A/cvxoHzdqnK4wHnAP/iOMBhGQh6P5tRONdQHV/gEQwvEqtP78dV1gdV9X0iO0bo1j3aesL/Xb+KGLQjchbDjt0eBUXvuWA4aob9fvFhA7ne5bjO3W46l4Y/kkMh+5F5spdOlx1LwzftVuHq+6FZfuGCofawCSw333jjew8NbaCxPJd4UepJw8bN5TdGJ716T099RsiXT+1TzYsjb2LYb22HJGWnnvPUQy+D2vw4kfDx3v3b+R3Rvwg94vyursj2orup/17KozLpIjhDu5M3x/alObegXIfFGVZmkQ+UCeBXh0now0H5T44zlw/8P1QLEHeZNSRltBxH2b5cOw0DcI0EZuSm2r7TfQpR7mHSj/0fbt0RM+0mwkpb8a3kiwvLLG0tCoV/7X7t1if7esx+M430m/RknQO1lHneoflGDx1HM5oi9LL5aMMcu2wurJ+cg5Oeo259k84JkG+j10cYRizr+6NaqxKlc7RX1EYhPI5+sIODGdz9PEJDGdz9N13Yjibo1+A4XyOPrALw9kcvWc3huMcrc/nz7yR26+kYexbblYKoEtLjHZ3YVO+zKMtO+AeAX67sd/zBQXOj0/kbbPYIfr8r8DaDupPhg9+3SEd9HOGPP51b5D5ETjYTkyHdgYxyEG/Dn+gwmWc0EKk7U6NV+HQQuwdFR0OLUTC37mjDlctROatiTq8s8X4b9Th0EIkfG5nFV63ELbPlTeY9sWhFxSFL8BG5gTYZ0+rpVM9mHA+ex6dlzqqWnGdd5y2nVzkzT6tK80h5uQZkYBlZ0uP8cdTXp80t+HLvqHoM9gf3kjWjlBHkCnp+lBMTTZWNecn5joW/GkI5XZqVc+nvzDXsr0NYBzWcVxgOE8HdZr7xkCPB41uue6xJrx+I4PFXbUe8DYchzikJnUT8oF+ELfhyL6qLCrp+wMXtuOqV1oavVy/ccy+BZnwUrt0iuLaDT7qj8Gd6vH1xTfQ8bUIvaG6J1r7EYTMeLOzTd/KovQxla5yXs6Ls4+ZlafecDWi4p6UYTLuKoYmdKyKC4WEskjzqGavjrcjuWlJY6i4J2S4rgBVN0QH+hcYf1Xs5lDHuz7pCOfxoU7mZODhWFfc/v3mUY11m3p40PtEFxRexd9afNIWuJtdeIq6j7Gx1euvm8bHkaev5iO2SjGYOgh2ajdievrAtC8TDE4c13pbzQ15YLhcn8vhXvJGyIMSYtxXSHg9pSB25saI6WkF0/3gHop126zIJI7TN0GenoJwj/2umwJ2gp4nKiMPtGWkc1Qpgti1g8APRT0xTcsBI68AVzMU3bd+i43l5a3e4sZT18UM4NW4+jaOK6fIc8+ZU1WCeDmIq2rPta3kG/jay8my3Auca/fnosYbWVe+mtmE55lXBEUm5Azc3nyKekLezetCrqItMJOxwfjc9kqxvNHtrbfWiIiU0eO6ZOO6rr0OlHvnzd8ox5kaaaBhmfXknSb517CYnYO2lPibEU+LIrmhbDpp5OVzaoy+W2KkstR4fjsZt1HuFyBNzy/+OjJQvYiLERPnPpreo3EI1+UgY/ngqMaxlKh3eZ4=
*/
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_CONTAINER_DETAIL_MPL_HPP
#define BOOST_CONTAINER_CONTAINER_DETAIL_MPL_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/move/detail/type_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>

#include <cstddef>

namespace boost {
namespace container {
namespace dtl {

using boost::move_detail::integral_constant;
using boost::move_detail::true_type;
using boost::move_detail::false_type;
using boost::move_detail::enable_if_c;
using boost::move_detail::enable_if;
using boost::move_detail::enable_if_convertible;
using boost::move_detail::disable_if_c;
using boost::move_detail::disable_if;
using boost::move_detail::disable_if_convertible;
using boost::move_detail::is_convertible;
using boost::move_detail::if_c;
using boost::move_detail::if_;
using boost::move_detail::identity;
using boost::move_detail::bool_;
using boost::move_detail::true_;
using boost::move_detail::false_;
using boost::move_detail::yes_type;
using boost::move_detail::no_type;
using boost::move_detail::bool_;
using boost::move_detail::true_;
using boost::move_detail::false_;
using boost::move_detail::unvoid_ref;
using boost::move_detail::and_;
using boost::move_detail::or_;
using boost::move_detail::not_;
using boost::move_detail::enable_if_and;
using boost::move_detail::disable_if_and;
using boost::move_detail::enable_if_or;
using boost::move_detail::disable_if_or;
using boost::move_detail::remove_const;

template <class FirstType>
struct select1st
{
   typedef FirstType type;

   template<class T>
   BOOST_CONTAINER_FORCEINLINE const type& operator()(const T& x) const
   {  return x.first;   }

   template<class T>
   BOOST_CONTAINER_FORCEINLINE type& operator()(T& x)
   {  return const_cast<type&>(x.first);   }
};


template<typename T>
struct void_t { typedef void type; };

template <class T, class=void>
struct is_transparent_base
{
   static const bool value = false;
};

template <class T>
struct is_transparent_base<T, typename void_t<typename T::is_transparent>::type>
{
   static const bool value = true;
};

template <class T>
struct is_transparent
   : is_transparent_base<T>
{};

template <typename C, class /*Dummy*/, typename R>
struct enable_if_transparent
   : boost::move_detail::enable_if_c<dtl::is_transparent<C>::value, R>
{};

#ifndef BOOST_CONTAINER_NO_CXX17_CTAD

// void_t (void_t for C++11)
template<typename...> using variadic_void_t = void;

// Trait to detect Allocator-like types.
template<typename Allocator, typename = void>
struct is_allocator
{
   static const bool value = false;
};

template <typename T>
T&& ctad_declval();

template<typename Allocator>
struct is_allocator < Allocator,
   variadic_void_t< typename Allocator::value_type
                  , decltype(ctad_declval<Allocator&>().allocate(size_t{})) >>
{
   static const bool value = true;
};

template<class T>
using require_allocator_t = typename enable_if_c<is_allocator<T>::value, T>::type;

template<class T>
using require_nonallocator_t = typename enable_if_c<!is_allocator<T>::value, T>::type;

#endif

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_CONTAINER_DETAIL_MPL_HPP


/* mpl.hpp
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
*/
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
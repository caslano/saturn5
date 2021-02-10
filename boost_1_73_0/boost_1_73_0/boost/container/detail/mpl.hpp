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
+AqxkUBrQephXSgNKwpKVus0UdGR8r8000Vr+oa6t5NBf3g9mk0HwSwIBrPxdEJPqPb9E7pWc8T2dz/WqJYmc758+lfrh6etb7HAn2ZK6u1soUySxTnfNUJKQ2rwhoadm544Ft0Lgv5o2Lys8O4xQQ5hCfeuNQQRC7WygvfD0TjoB6KVxeLvSRamZaToBVvgInL5i7C6whzrZ4bV+RFdLREsqbqsvik+Qwu42xKsZuWaVHvzrMtXV/5T47kQ7StKYpuHmUIghPlqLU0yT9LEbGmD26UKxBceRs4L1nwJJ7ivjZLRM7pq/9/eecj/Au/4Hl71gu6kP55CpBhLxKikdZ5khrMHhEGPPifrUYss2VQnNkma0lyJJEtMItPkPy4nCxV/nTjkKIjJSgnzzMiE806orFwBuSgJAX22cCwQDBj5QhZbBjyiOHfpzpjppfxgGefYGTwWSMM1yhlIlOx6JtOj+HTmlaCAilotk6RbVnygtCWEZQyXH5YW54oticvU2qIeJDJdsV71YArJPqvCJDF7oWweFCtpXE6QFO4ju32vUGAyY6WA2iyBrIs8ZAszVCBdhksuACuZlbD+HjhH0hH/xAMtGIm7+OWgf9Ofdvhug7t4DCdDu0/YpPvMTfwXwWXXtU7nMvygAKV/
*/
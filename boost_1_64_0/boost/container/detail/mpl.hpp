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
4uoRWASZF7NhpwxrYLFkSmanWi5zgyUKY3rdr3cTZiLjtdectu4kLJfMl1n0mB9/h8n6W9Ze5sTSYlOR+TBrc+bwfZiGjM83NKXhVFgEWQVmnf67PAkWT+bEe3vI4yVMR4ZnsQX2U+Wzx2GJZHytA8r+6QYzklVh1sp3WgVYNmpAns+HbIZJkZbb4MWbf2yAqcj4mk3WLpoM05DxMTsmNbgLiyRT8jVTSu1g8cJ8a1peGQ/TC+YetrAe7BiZDVuXg+vP1YalkfFzuP7q7Suwi0Jca9ugijATGe/DNK+2AbBsoYYv/qN0sHwyazbmu0mRt2HSAHo3z8x33d1wmIyM79PN7jXXwoLIeA19W96MgmnIeB8eZqbnwSLJeH2KI823wKLIXFlciz5/P4XFk5Vltkzzc2OYgSyQ2Vvz1fuwbDJPHvc84y+YNNBy+0x8MvEJTEnmwWzw+RtKWBBZFWZNf95VAxZJ5sNsYeUOu2DxZLWYJZ35IwCWQlaBme8b2XRYNhlf657bN9aH5ZG5M4tPuZAAkw2yrL3VPk89TE1Wg5n6fWZtWCQZr29WpKEsTCeMOalp6wUwI5kXs+DxOddhJsGq3WrhAcsj4709e6z9EphysOU2n3E01BOmFqz5mb9vw0LI+Da/yNzIA6YhK8fiMmt/XAKLIvNj5mP87ThMRybnNYyd+xlmIKvNrHNiky6wXDIVM6+r00bC5EMszw+/9r1tDQsj47k0TNlR1Af6GU2G/aiPlbU0puoHa5iWLLgortDmt5xdC2YkC2R2Ri+fBMslUzMbts10AaYcSrUza9Js8htYEFkVZvF9XDbDIslUzGbW/NkNloAxJY1mqFUpqeAHTE8m+2bDrayYWUtGspACo39XEPG4PDL9t3uL2fQHnsOmlUVcyAxbaUJhXFBxHGw3meI7lj3z31zGC5Y36/smzfm+yecyE2pQ/UL2rbcS/YiaqHwAUzMrRb9mbP0YAwsqwUJKMA2zgt+HpV5ZBQsjUzDLSFf1hUUKtmfO5EhYbAmmI5Mz+3HXkb9gW4RcPm5q7QfbLYy5qnndbFi6MGaks48HLJPMj9kV5T8LYeYSTJnwby7W9GtC3W6Pi2yApCJDnI00Rqq4N+c8TEOmYlbK5ng/2GAyObO5FbZ2h8UKcUsuX90BSyJTMLt++l0OLFkYc/HRtl6wDFaDLRnvu4mZnbCdZZZg2cxkWBccQ8jkzI7W+MEelk+mZDa2Qt0yMOU8y7i5jp3qwQIEsxvy4QRMQ6Zg1r1OejQsQrA+vnlNYVphzD8CK8bCZgs2+qBCDksk82M27cL9FFgKGeqzl0pJ+1wfDYTdIFMw+5h9ZQ7sWQlmM//75kfmx0xf+vwvsFAy5OJAv27q4f8cFkHmxOxMWP/DsChmjjRmUseMV7BYMgWzyTfexcN0gt2cXSUdZiCTMbszfH3XQqN/jMycvm1LsJQSLI1MycyzV9m9sLtkCmY2+up3YW/J5Mz2yMtVh8kWWMZdrpi4DaYi43H6l7HPYMGCvejSeycsjMyP2faV54vjooS4NdW2vIXFkfHa26ibVYTNJlMzC08d3QpmFCx/5cN4HAvusvqcpTGF2xLsbQnmtJDWmpnhbtSPMDXZ/42j/9aQoT4XemZdZVn0JlhXMhmzgt7C+ghWcA6ADS4hLroEm1CCxQl59u7QrStMV0JcomAFx0iYvoQ4QwlmLMFSSrC0EiyjBDOVYJklWHYJliusZ+Cl+gZYPpmCWdYDlS1M8atlXNwUO0+YmozHTVr8phlMI5hd1/lhsAhhzIVLLz2CRZM5Mfs9b8Q7WJww5va+ZYttuTCmjfXH3jADGVsXdqyj3gpjdv58aAgsQxg=
*/
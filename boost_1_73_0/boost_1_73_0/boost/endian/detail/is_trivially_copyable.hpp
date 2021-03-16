#ifndef BOOST_ENDIAN_DETAIL_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED

// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/config.hpp>
#include <boost/type_traits/has_trivial_copy.hpp>
#include <boost/type_traits/has_trivial_assign.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
# include <type_traits>
#endif

namespace boost
{
namespace endian
{
namespace detail
{

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)

using std::is_trivially_copyable;

#else

template<class T> struct is_trivially_copyable: boost::integral_constant<bool,
    boost::has_trivial_copy<T>::value && boost::has_trivial_assign<T>::value> {};

#endif

} // namespace detail
} // namespace endian
} // namespace boost

#endif  // BOOST_ENDIAN_DETAIL_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED

/* is_trivially_copyable.hpp
IhQk3BpOKDQZOQq0+ES1AiHyCm3/VVUovPp1n6pY3H2qsXc94IMJkn6XotZvpsIEWsIeTO5LeeswGifpXydCQ0W3y4UCsy5LVUpXo7QJu5tGpEgIL7n4dI6ss06z7D57OgNG+T8pBU84XW1JOW0kNUWCtl48/vHzWAXju1poSLV+BLSL2MSDeoodelAH8vWI4/e6XVAySehIbu4SRGr2bWzkNwPxeYBlhkiSsOZkTSV0JaYRmiZyPWggpndJx3U=
*/
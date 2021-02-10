//
// is_executor.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IS_EXECUTOR_HPP
#define BOOST_ASIO_IS_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/is_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// The is_executor trait detects whether a type T meets the Executor type
/// requirements.
/**
 * Class template @c is_executor is a UnaryTypeTrait that is derived from @c
 * true_type if the type @c T meets the syntactic requirements for Executor,
 * otherwise @c false_type.
 */
template <typename T>
struct is_executor
#if defined(GENERATING_DOCUMENTATION)
  : integral_constant<bool, automatically_determined>
#else // defined(GENERATING_DOCUMENTATION)
  : boost::asio::detail::is_executor<T>
#endif // defined(GENERATING_DOCUMENTATION)
{
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IS_EXECUTOR_HPP

/* is_executor.hpp
BvZbiNxJWNh/OQruOjCupefjwk3ppZJhO9p7I1YK2wMeH/umhAu+gp1ZTQYiTzHR+xZ/oy8Oc7Bv1G+mRhcxQgYhrHXhRDEhylble1kmXP2sdLPw8hUj9tfYAH79zUg18STIuFs+T0HBeCV08NUPq8JLBqEbY/ucSBJMrUkwtcqk6IXIz/vEhFmprfc54kC0ItY7oKV7WYF61ZJW8I2XVEd8d1ZCRcevekOE6UPnAND+hOHOAOLhYJ7NBARE0eb+iH726PkJRBj88YjjgHYcg3AE8EemyK/eCZ0bIzQWBUdJkMbi8AaoIVDSiAPXbRgDa8Aqy0I4zdQ0cVPAmUo77u8Oey6KvyQqfJuV65ratEIfD36gXq/EpxVpZeKxg8bZ3a+08t2wrZT9P4cYxOc1a67BSwLcUL+4DLIfn+9y0njS/RrC6yVo1jkdQIh3jKh5X1jb0nwgL+mAvOLw4Drd8DkxBmh7T4hSq+2Evhu4t4ZXIvu3ipgwfhUUei3+oR1br8W+BaNNAeTudiGBQqqsROQ5ILvE53mxPNxVGZGNQnyXCeNUQxsGpNljdSr3Qd2UHSpDhDGbjEUOaL1MmGAyS2/pH5jcxhXttK+EwEuISimUQqT3169cTU0n3sIKGKYh0m+WFdOkFVO0jXAo
*/
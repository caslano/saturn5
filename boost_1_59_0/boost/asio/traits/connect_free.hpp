//
// traits/connect_free.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_TRAITS_CONNECT_FREE_HPP
#define BOOST_ASIO_TRAITS_CONNECT_FREE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>

#if defined(BOOST_ASIO_HAS_DECLTYPE) \
  && defined(BOOST_ASIO_HAS_NOEXCEPT) \
  && defined(BOOST_ASIO_HAS_WORKING_EXPRESSION_SFINAE)
# define BOOST_ASIO_HAS_DEDUCED_CONNECT_FREE_TRAIT 1
#endif // defined(BOOST_ASIO_HAS_DECLTYPE)
       //   && defined(BOOST_ASIO_HAS_NOEXCEPT)
       //   && defined(BOOST_ASIO_HAS_WORKING_EXPRESSION_SFINAE)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace traits {

template <typename S, typename R, typename = void>
struct connect_free_default;

template <typename S, typename R, typename = void>
struct connect_free;

} // namespace traits
namespace detail {

struct no_connect_free
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = false);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
};

#if defined(BOOST_ASIO_HAS_DEDUCED_CONNECT_FREE_TRAIT)

template <typename S, typename R, typename = void>
struct connect_free_trait : no_connect_free
{
};

template <typename S, typename R>
struct connect_free_trait<S, R,
  typename void_type<
    decltype(connect(declval<S>(), declval<R>()))
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);

  using result_type = decltype(
    connect(declval<S>(), declval<R>()));

  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = noexcept(
    connect(declval<S>(), declval<R>())));
};

#else // defined(BOOST_ASIO_HAS_DEDUCED_CONNECT_FREE_TRAIT)

template <typename S, typename R, typename = void>
struct connect_free_trait :
  conditional<
    is_same<S, typename remove_reference<S>::type>::value
      && is_same<R, typename decay<R>::type>::value,
    typename conditional<
      is_same<S, typename add_const<S>::type>::value,
      no_connect_free,
      traits::connect_free<typename add_const<S>::type, R>
    >::type,
    traits::connect_free<
      typename remove_reference<S>::type,
      typename decay<R>::type>
  >::type
{
};

#endif // defined(BOOST_ASIO_HAS_DEDUCED_CONNECT_FREE_TRAIT)

} // namespace detail
namespace traits {

template <typename S, typename R, typename>
struct connect_free_default :
  detail::connect_free_trait<S, R>
{
};

template <typename S, typename R, typename>
struct connect_free :
  connect_free_default<S, R>
{
};

} // namespace traits
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_TRAITS_CONNECT_FREE_HPP

/* connect_free.hpp
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
*/
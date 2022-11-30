//
// traits/static_require.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_TRAITS_STATIC_REQUIRE_HPP
#define BOOST_ASIO_TRAITS_STATIC_REQUIRE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/traits/static_query.hpp>

#if defined(BOOST_ASIO_HAS_DECLTYPE) \
  && defined(BOOST_ASIO_HAS_NOEXCEPT)
# define BOOST_ASIO_HAS_DEDUCED_STATIC_REQUIRE_TRAIT 1
#endif // defined(BOOST_ASIO_HAS_DECLTYPE)
       //   && defined(BOOST_ASIO_HAS_NOEXCEPT)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace traits {

template <typename T, typename Property, typename = void>
struct static_require_default;

template <typename T, typename Property, typename = void>
struct static_require;

} // namespace traits
namespace detail {

struct no_static_require
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = false);
};

template <typename T, typename Property, typename = void>
struct static_require_trait :
  conditional<
    is_same<T, typename decay<T>::type>::value
      && is_same<Property, typename decay<Property>::type>::value,
    no_static_require,
    traits::static_require<
      typename decay<T>::type,
      typename decay<Property>::type>
  >::type
{
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_REQUIRE_TRAIT)

#if defined(BOOST_ASIO_HAS_WORKING_EXPRESSION_SFINAE)

template <typename T, typename Property>
struct static_require_trait<T, Property,
  typename enable_if<
    decay<Property>::type::value() == traits::static_query<T, Property>::value()
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
};

#else // defined(BOOST_ASIO_HAS_WORKING_EXPRESSION_SFINAE)

false_type static_require_test(...);

template <typename T, typename Property>
true_type static_require_test(T*, Property*,
    typename enable_if<
      Property::value() == traits::static_query<T, Property>::value()
    >::type* = 0);

template <typename T, typename Property>
struct has_static_require
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, value =
    decltype((static_require_test)(
      static_cast<T*>(0), static_cast<Property*>(0)))::value);
};

template <typename T, typename Property>
struct static_require_trait<T, Property,
  typename enable_if<
    has_static_require<typename decay<T>::type,
      typename decay<Property>::type>::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
};

#endif // defined(BOOST_ASIO_HAS_WORKING_EXPRESSION_SFINAE)

#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_REQUIRE_TRAIT)

} // namespace detail
namespace traits {

template <typename T, typename Property, typename>
struct static_require_default : detail::static_require_trait<T, Property>
{
};

template <typename T, typename Property, typename>
struct static_require : static_require_default<T, Property>
{
};

} // namespace traits
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_TRAITS_STATIC_REQUIRE_HPP

/* static_require.hpp
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
*/
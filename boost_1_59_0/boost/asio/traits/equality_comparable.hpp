//
// traits/equality_comparable.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_TRAITS_EQUALITY_COMPARABLE_HPP
#define BOOST_ASIO_TRAITS_EQUALITY_COMPARABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>

#if defined(BOOST_ASIO_HAS_DECLTYPE) \
  && defined(BOOST_ASIO_HAS_NOEXCEPT) \
  && defined(BOOST_ASIO_HAS_WORKING_EXPRESSION_SFINAE)
# define BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT 1
#endif // defined(BOOST_ASIO_HAS_DECLTYPE)
       //   && defined(BOOST_ASIO_HAS_NOEXCEPT)
       //   && defined(BOOST_ASIO_HAS_WORKING_EXPRESSION_SFINAE)

namespace boost {
namespace asio {
namespace traits {

template <typename T, typename = void>
struct equality_comparable_default;

template <typename T, typename = void>
struct equality_comparable;

} // namespace traits
namespace detail {

struct no_equality_comparable
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = false);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
};

#if defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

template <typename T, typename = void>
struct equality_comparable_trait : no_equality_comparable
{
};

template <typename T>
struct equality_comparable_trait<T,
  typename void_type<
    decltype(
      static_cast<void>(
        static_cast<bool>(declval<const T>() == declval<const T>())
      ),
      static_cast<void>(
        static_cast<bool>(declval<const T>() != declval<const T>())
      )
    )
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);

  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
    noexcept(declval<const T>() == declval<const T>())
      && noexcept(declval<const T>() != declval<const T>()));
};

#else // defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

template <typename T, typename = void>
struct equality_comparable_trait :
  conditional<
    is_same<T, typename decay<T>::type>::value,
    no_equality_comparable,
    traits::equality_comparable<typename decay<T>::type>
  >::type
{
};

#endif // defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

} // namespace detail
namespace traits {

template <typename T, typename>
struct equality_comparable_default : detail::equality_comparable_trait<T>
{
};

template <typename T, typename>
struct equality_comparable : equality_comparable_default<T>
{
};

} // namespace traits
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_TRAITS_EQUALITY_COMPARABLE_HPP

/* equality_comparable.hpp
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
*/
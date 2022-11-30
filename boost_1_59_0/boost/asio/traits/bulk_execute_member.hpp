//
// traits/bulk_execute_member.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_TRAITS_BULK_EXECUTE_MEMBER_HPP
#define BOOST_ASIO_TRAITS_BULK_EXECUTE_MEMBER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>

#if defined(BOOST_ASIO_HAS_DECLTYPE) \
  && defined(BOOST_ASIO_HAS_NOEXCEPT) \
  && defined(BOOST_ASIO_HAS_WORKING_EXPRESSION_SFINAE)
# define BOOST_ASIO_HAS_DEDUCED_BULK_EXECUTE_MEMBER_TRAIT 1
#endif // defined(BOOST_ASIO_HAS_DECLTYPE)
       //   && defined(BOOST_ASIO_HAS_NOEXCEPT)
       //   && defined(BOOST_ASIO_HAS_WORKING_EXPRESSION_SFINAE)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace traits {

template <typename T, typename F, typename N, typename = void>
struct bulk_execute_member_default;

template <typename T, typename F, typename N, typename = void>
struct bulk_execute_member;

} // namespace traits
namespace detail {

struct no_bulk_execute_member
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = false);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
};

#if defined(BOOST_ASIO_HAS_DEDUCED_BULK_EXECUTE_MEMBER_TRAIT)

template <typename T, typename F, typename N, typename = void>
struct bulk_execute_member_trait : no_bulk_execute_member
{
};

template <typename T, typename F, typename N>
struct bulk_execute_member_trait<T, F, N,
  typename void_type<
    decltype(declval<T>().bulk_execute(declval<F>(), declval<N>()))
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);

  using result_type = decltype(
    declval<T>().bulk_execute(declval<F>(), declval<N>()));

  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = noexcept(
    declval<T>().bulk_execute(declval<F>(), declval<N>())));
};

#else // defined(BOOST_ASIO_HAS_DEDUCED_BULK_EXECUTE_MEMBER_TRAIT)

template <typename T, typename F, typename N, typename = void>
struct bulk_execute_member_trait :
  conditional<
    is_same<T, typename remove_reference<T>::type>::value
      && is_same<F, typename decay<F>::type>::value
      && is_same<N, typename decay<N>::type>::value,
    typename conditional<
      is_same<T, typename add_const<T>::type>::value,
      no_bulk_execute_member,
      traits::bulk_execute_member<typename add_const<T>::type, F, N>
    >::type,
    traits::bulk_execute_member<
      typename remove_reference<T>::type,
      typename decay<F>::type,
      typename decay<N>::type>
  >::type
{
};

#endif // defined(BOOST_ASIO_HAS_DEDUCED_BULK_EXECUTE_MEMBER_TRAIT)

} // namespace detail
namespace traits {

template <typename T, typename F, typename N, typename>
struct bulk_execute_member_default :
  detail::bulk_execute_member_trait<T, F, N>
{
};

template <typename T, typename F, typename N, typename>
struct bulk_execute_member :
  bulk_execute_member_default<T, F, N>
{
};

} // namespace traits
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_TRAITS_BULK_EXECUTE_MEMBER_HPP

/* bulk_execute_member.hpp
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
*/
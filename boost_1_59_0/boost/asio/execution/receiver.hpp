//
// execution/receiver.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_RECEIVER_HPP
#define BOOST_ASIO_EXECUTION_RECEIVER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/detail/variadic_templates.hpp>
#include <boost/asio/execution/set_done.hpp>
#include <boost/asio/execution/set_error.hpp>
#include <boost/asio/execution/set_value.hpp>

#if defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
# include <exception>
#else // defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
# include <boost/system/error_code.hpp>
#endif // defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)

#if defined(BOOST_ASIO_HAS_DEDUCED_SET_DONE_FREE_TRAIT) \
  && defined(BOOST_ASIO_HAS_DEDUCED_SET_DONE_MEMBER_TRAIT) \
  && defined(BOOST_ASIO_HAS_DEDUCED_SET_ERROR_FREE_TRAIT) \
  && defined(BOOST_ASIO_HAS_DEDUCED_SET_ERROR_MEMBER_TRAIT) \
  && defined(BOOST_ASIO_HAS_DEDUCED_SET_VALUE_FREE_TRAIT) \
  && defined(BOOST_ASIO_HAS_DEDUCED_SET_VALUE_MEMBER_TRAIT) \
  && defined(BOOST_ASIO_HAS_DEDUCED_RECEIVER_OF_FREE_TRAIT) \
  && defined(BOOST_ASIO_HAS_DEDUCED_RECEIVER_OF_MEMBER_TRAIT)
# define BOOST_ASIO_HAS_DEDUCED_EXECUTION_IS_RECEIVER_TRAIT 1
#endif // defined(BOOST_ASIO_HAS_DEDUCED_SET_DONE_FREE_TRAIT)
       //   && defined(BOOST_ASIO_HAS_DEDUCED_SET_DONE_MEMBER_TRAIT)
       //   && defined(BOOST_ASIO_HAS_DEDUCED_SET_ERROR_FREE_TRAIT)
       //   && defined(BOOST_ASIO_HAS_DEDUCED_SET_ERROR_MEMBER_TRAIT)
       //   && defined(BOOST_ASIO_HAS_DEDUCED_SET_VALUE_FREE_TRAIT)
       //   && defined(BOOST_ASIO_HAS_DEDUCED_SET_VALUE_MEMBER_TRAIT)
       //   && defined(BOOST_ASIO_HAS_DEDUCED_RECEIVER_OF_FREE_TRAIT)
       //   && defined(BOOST_ASIO_HAS_DEDUCED_RECEIVER_OF_MEMBER_TRAIT)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace execution {
namespace detail {

template <typename T, typename E>
struct is_receiver_base :
  integral_constant<bool,
    is_move_constructible<typename remove_cvref<T>::type>::value
      && is_constructible<typename remove_cvref<T>::type, T>::value
  >
{
};

} // namespace detail

#if defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
# define BOOST_ASIO_EXECUTION_RECEIVER_ERROR_DEFAULT = std::exception_ptr
#else // defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
# define BOOST_ASIO_EXECUTION_RECEIVER_ERROR_DEFAULT \
  = ::boost::system::error_code
#endif // defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)

/// The is_receiver trait detects whether a type T satisfies the
/// execution::receiver concept.
/**
 * Class template @c is_receiver is a type trait that is derived from @c
 * true_type if the type @c T meets the concept definition for a receiver for
 * error type @c E, otherwise @c false_type.
 */
template <typename T, typename E BOOST_ASIO_EXECUTION_RECEIVER_ERROR_DEFAULT>
struct is_receiver :
#if defined(GENERATING_DOCUMENTATION)
  integral_constant<bool, automatically_determined>
#else // defined(GENERATING_DOCUMENTATION)
  conditional<
    can_set_done<typename remove_cvref<T>::type>::value
      && is_nothrow_set_done<typename remove_cvref<T>::type>::value
      && can_set_error<typename remove_cvref<T>::type, E>::value
      && is_nothrow_set_error<typename remove_cvref<T>::type, E>::value,
    detail::is_receiver_base<T, E>,
    false_type
  >::type
#endif // defined(GENERATING_DOCUMENTATION)
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename E BOOST_ASIO_EXECUTION_RECEIVER_ERROR_DEFAULT>
BOOST_ASIO_CONSTEXPR const bool is_receiver_v = is_receiver<T, E>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

#if defined(BOOST_ASIO_HAS_CONCEPTS)

template <typename T, typename E BOOST_ASIO_EXECUTION_RECEIVER_ERROR_DEFAULT>
BOOST_ASIO_CONCEPT receiver = is_receiver<T, E>::value;

#define BOOST_ASIO_EXECUTION_RECEIVER ::boost::asio::execution::receiver

#else // defined(BOOST_ASIO_HAS_CONCEPTS)

#define BOOST_ASIO_EXECUTION_RECEIVER typename

#endif // defined(BOOST_ASIO_HAS_CONCEPTS)

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES) \
  || defined(GENERATING_DOCUMENTATION)

/// The is_receiver_of trait detects whether a type T satisfies the
/// execution::receiver_of concept for some set of value arguments.
/**
 * Class template @c is_receiver_of is a type trait that is derived from @c
 * true_type if the type @c T meets the concept definition for a receiver for
 * value arguments @c Vs, otherwise @c false_type.
 */
template <typename T, typename... Vs>
struct is_receiver_of :
#if defined(GENERATING_DOCUMENTATION)
  integral_constant<bool, automatically_determined>
#else // defined(GENERATING_DOCUMENTATION)
  conditional<
    is_receiver<T>::value,
    can_set_value<typename remove_cvref<T>::type, Vs...>,
    false_type
  >::type
#endif // defined(GENERATING_DOCUMENTATION)
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename... Vs>
BOOST_ASIO_CONSTEXPR const bool is_receiver_of_v =
  is_receiver_of<T, Vs...>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

#if defined(BOOST_ASIO_HAS_CONCEPTS)

template <typename T, typename... Vs>
BOOST_ASIO_CONCEPT receiver_of = is_receiver_of<T, Vs...>::value;

#define BOOST_ASIO_EXECUTION_RECEIVER_OF_0 \
  ::boost::asio::execution::receiver_of

#define BOOST_ASIO_EXECUTION_RECEIVER_OF_1(v) \
  ::boost::asio::execution::receiver_of<v>

#else // defined(BOOST_ASIO_HAS_CONCEPTS)

#define BOOST_ASIO_EXECUTION_RECEIVER_OF_0 typename
#define BOOST_ASIO_EXECUTION_RECEIVER_OF_1(v) typename

#endif // defined(BOOST_ASIO_HAS_CONCEPTS)

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
      //   || defined(GENERATING_DOCUMENTATION)

template <typename T, typename = void,
    typename = void, typename = void, typename = void, typename = void,
    typename = void, typename = void, typename = void, typename = void>
struct is_receiver_of;

template <typename T>
struct is_receiver_of<T> :
  conditional<
    is_receiver<T>::value,
    can_set_value<typename remove_cvref<T>::type>,
    false_type
  >::type
{
};

#define BOOST_ASIO_PRIVATE_RECEIVER_OF_TRAITS_DEF(n) \
  template <typename T, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct is_receiver_of<T, BOOST_ASIO_VARIADIC_TARGS(n)> : \
    conditional< \
      conditional<true, is_receiver<T>, void>::type::value, \
      can_set_value< \
        typename remove_cvref<T>::type, \
        BOOST_ASIO_VARIADIC_TARGS(n)>, \
      false_type \
    >::type \
  { \
  }; \
  /**/
BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_RECEIVER_OF_TRAITS_DEF)
#undef BOOST_ASIO_PRIVATE_RECEIVER_OF_TRAITS_DEF

#define BOOST_ASIO_EXECUTION_RECEIVER_OF_0 typename
#define BOOST_ASIO_EXECUTION_RECEIVER_OF_1(v) typename

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
       //   || defined(GENERATING_DOCUMENTATION)

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES) \
  || defined(GENERATING_DOCUMENTATION)

/// The is_nothrow_receiver_of trait detects whether a type T satisfies the
/// execution::receiver_of concept for some set of value arguments, with a
/// noexcept @c set_value operation.
/**
 * Class template @c is_nothrow_receiver_of is a type trait that is derived
 * from @c true_type if the type @c T meets the concept definition for a
 * receiver for value arguments @c Vs, and the expression
 * <tt>execution::set_value(declval<T>(), declval<Ts>()...)</tt> is noexcept,
 * otherwise @c false_type.
 */
template <typename T, typename... Vs>
struct is_nothrow_receiver_of :
#if defined(GENERATING_DOCUMENTATION)
  integral_constant<bool, automatically_determined>
#else // defined(GENERATING_DOCUMENTATION)
  integral_constant<bool,
    is_receiver_of<T, Vs...>::value
      && is_nothrow_set_value<typename remove_cvref<T>::type, Vs...>::value
  >
#endif // defined(GENERATING_DOCUMENTATION)
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename... Vs>
BOOST_ASIO_CONSTEXPR const bool is_nothrow_receiver_of_v =
  is_nothrow_receiver_of<T, Vs...>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
      //   || defined(GENERATING_DOCUMENTATION)

template <typename T, typename = void,
    typename = void, typename = void, typename = void, typename = void,
    typename = void, typename = void, typename = void, typename = void>
struct is_nothrow_receiver_of;

template <typename T>
struct is_nothrow_receiver_of<T> :
  integral_constant<bool,
    is_receiver_of<T>::value
      && is_nothrow_set_value<typename remove_cvref<T>::type>::value
  >
{
};

#define BOOST_ASIO_PRIVATE_NOTHROW_RECEIVER_OF_TRAITS_DEF(n) \
  template <typename T, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct is_nothrow_receiver_of<T, BOOST_ASIO_VARIADIC_TARGS(n)> : \
    integral_constant<bool, \
      is_receiver_of<T, BOOST_ASIO_VARIADIC_TARGS(n)>::value \
        && is_nothrow_set_value<typename remove_cvref<T>::type, \
          BOOST_ASIO_VARIADIC_TARGS(n)>::value \
    > \
  { \
  }; \
  /**/
BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_NOTHROW_RECEIVER_OF_TRAITS_DEF)
#undef BOOST_ASIO_PRIVATE_NOTHROW_RECEIVER_OF_TRAITS_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
       //   || defined(GENERATING_DOCUMENTATION)

} // namespace execution
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_RECEIVER_HPP

/* receiver.hpp
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
*/
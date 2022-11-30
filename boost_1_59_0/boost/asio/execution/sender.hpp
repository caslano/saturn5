//
// execution/sender.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_SENDER_HPP
#define BOOST_ASIO_EXECUTION_SENDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/detail/as_invocable.hpp>
#include <boost/asio/execution/detail/void_receiver.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution/receiver.hpp>

#include <boost/asio/detail/push_options.hpp>

#if defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES) \
  && defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES) \
  && defined(BOOST_ASIO_HAS_DECLTYPE) \
  && !defined(BOOST_ASIO_MSVC) || (_MSC_VER >= 1910)
# define BOOST_ASIO_HAS_DEDUCED_EXECUTION_IS_TYPED_SENDER_TRAIT 1
#endif // defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)
       //   && defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
       //   && defined(BOOST_ASIO_HAS_DECLTYPE)
       //   && !defined(BOOST_ASIO_MSVC) || (_MSC_VER >= 1910)

namespace boost {
namespace asio {
namespace execution {
namespace detail {

namespace sender_base_ns { struct sender_base {}; }

template <typename S, typename = void>
struct sender_traits_base
{
  typedef void asio_execution_sender_traits_base_is_unspecialised;
};

template <typename S>
struct sender_traits_base<S,
    typename enable_if<
      is_base_of<sender_base_ns::sender_base, S>::value
    >::type>
{
};

template <typename S, typename = void, typename = void, typename = void>
struct has_sender_types : false_type
{
};

#if defined(BOOST_ASIO_HAS_DEDUCED_EXECUTION_IS_TYPED_SENDER_TRAIT)

template <
    template <
      template <typename...> class Tuple,
      template <typename...> class Variant
    > class>
struct has_value_types
{
  typedef void type;
};

template <
  template <
    template <typename...> class Variant
  > class>
struct has_error_types
{
  typedef void type;
};

template <typename S>
struct has_sender_types<S,
    typename has_value_types<S::template value_types>::type,
    typename has_error_types<S::template error_types>::type,
    typename conditional<S::sends_done, void, void>::type> : true_type
{
};

template <typename S>
struct sender_traits_base<S,
    typename enable_if<
      has_sender_types<S>::value
    >::type>
{
  template <
      template <typename...> class Tuple,
      template <typename...> class Variant>
  using value_types = typename S::template value_types<Tuple, Variant>;

  template <template <typename...> class Variant>
  using error_types = typename S::template error_types<Variant>;

  BOOST_ASIO_STATIC_CONSTEXPR(bool, sends_done = S::sends_done);
};

#endif // defined(BOOST_ASIO_HAS_DEDUCED_EXECUTION_IS_TYPED_SENDER_TRAIT)

template <typename S>
struct sender_traits_base<S,
    typename enable_if<
      !has_sender_types<S>::value
        && detail::is_executor_of_impl<S,
          as_invocable<void_receiver, S> >::value
    >::type>
{
#if defined(BOOST_ASIO_HAS_DEDUCED_EXECUTION_IS_TYPED_SENDER_TRAIT) \
  && defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)

  template <
      template <typename...> class Tuple,
      template <typename...> class Variant>
  using value_types = Variant<Tuple<>>;

  template <template <typename...> class Variant>
  using error_types = Variant<std::exception_ptr>;

  BOOST_ASIO_STATIC_CONSTEXPR(bool, sends_done = true);

#endif // defined(BOOST_ASIO_HAS_DEDUCED_EXECUTION_IS_TYPED_SENDER_TRAIT)
       //   && defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
};

} // namespace detail

/// Base class used for tagging senders.
#if defined(GENERATING_DOCUMENTATION)
typedef unspecified sender_base;
#else // defined(GENERATING_DOCUMENTATION)
typedef detail::sender_base_ns::sender_base sender_base;
#endif // defined(GENERATING_DOCUMENTATION)

/// Traits for senders.
template <typename S>
struct sender_traits
#if !defined(GENERATING_DOCUMENTATION)
  : detail::sender_traits_base<S>
#endif // !defined(GENERATING_DOCUMENTATION)
{
};

namespace detail {

template <typename S, typename = void>
struct has_sender_traits : true_type
{
};

template <typename S>
struct has_sender_traits<S,
    typename enable_if<
      is_same<
        typename boost::asio::execution::sender_traits<
          S>::asio_execution_sender_traits_base_is_unspecialised,
        void
      >::value
    >::type> : false_type
{
};

} // namespace detail

/// The is_sender trait detects whether a type T satisfies the
/// execution::sender concept.

/**
 * Class template @c is_sender is a type trait that is derived from @c
 * true_type if the type @c T meets the concept definition for a sender,
 * otherwise @c false_type.
 */
template <typename T>
struct is_sender :
#if defined(GENERATING_DOCUMENTATION)
  integral_constant<bool, automatically_determined>
#else // defined(GENERATING_DOCUMENTATION)
  conditional<
    detail::has_sender_traits<typename remove_cvref<T>::type>::value,
    is_move_constructible<typename remove_cvref<T>::type>,
    false_type
  >::type
#endif // defined(GENERATING_DOCUMENTATION)
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T>
BOOST_ASIO_CONSTEXPR const bool is_sender_v = is_sender<T>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

#if defined(BOOST_ASIO_HAS_CONCEPTS)

template <typename T>
BOOST_ASIO_CONCEPT sender = is_sender<T>::value;

#define BOOST_ASIO_EXECUTION_SENDER ::boost::asio::execution::sender

#else // defined(BOOST_ASIO_HAS_CONCEPTS)

#define BOOST_ASIO_EXECUTION_SENDER typename

#endif // defined(BOOST_ASIO_HAS_CONCEPTS)

template <typename S, typename R>
struct can_connect;

/// The is_sender_to trait detects whether a type T satisfies the
/// execution::sender_to concept for some receiver.
/**
 * Class template @c is_sender_to is a type trait that is derived from @c
 * true_type if the type @c T meets the concept definition for a sender
 * for some receiver type R, otherwise @c false.
 */
template <typename T, typename R>
struct is_sender_to :
#if defined(GENERATING_DOCUMENTATION)
  integral_constant<bool, automatically_determined>
#else // defined(GENERATING_DOCUMENTATION)
  integral_constant<bool,
    is_sender<T>::value
      && is_receiver<R>::value
      && can_connect<T, R>::value
  >
#endif // defined(GENERATING_DOCUMENTATION)
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename R>
BOOST_ASIO_CONSTEXPR const bool is_sender_to_v =
  is_sender_to<T, R>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

#if defined(BOOST_ASIO_HAS_CONCEPTS)

template <typename T, typename R>
BOOST_ASIO_CONCEPT sender_to = is_sender_to<T, R>::value;

#define BOOST_ASIO_EXECUTION_SENDER_TO(r) \
  ::boost::asio::execution::sender_to<r>

#else // defined(BOOST_ASIO_HAS_CONCEPTS)

#define BOOST_ASIO_EXECUTION_SENDER_TO(r) typename

#endif // defined(BOOST_ASIO_HAS_CONCEPTS)

/// The is_typed_sender trait detects whether a type T satisfies the
/// execution::typed_sender concept.
/**
 * Class template @c is_typed_sender is a type trait that is derived from @c
 * true_type if the type @c T meets the concept definition for a typed sender,
 * otherwise @c false.
 */
template <typename T>
struct is_typed_sender :
#if defined(GENERATING_DOCUMENTATION)
  integral_constant<bool, automatically_determined>
#else // defined(GENERATING_DOCUMENTATION)
  integral_constant<bool,
    is_sender<T>::value
      && detail::has_sender_types<
        sender_traits<typename remove_cvref<T>::type> >::value
  >
#endif // defined(GENERATING_DOCUMENTATION)
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T>
BOOST_ASIO_CONSTEXPR const bool is_typed_sender_v = is_typed_sender<T>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

#if defined(BOOST_ASIO_HAS_CONCEPTS)

template <typename T>
BOOST_ASIO_CONCEPT typed_sender = is_typed_sender<T>::value;

#define BOOST_ASIO_EXECUTION_TYPED_SENDER \
  ::boost::asio::execution::typed_sender

#else // defined(BOOST_ASIO_HAS_CONCEPTS)

#define BOOST_ASIO_EXECUTION_TYPED_SENDER typename

#endif // defined(BOOST_ASIO_HAS_CONCEPTS)

} // namespace execution
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/execution/connect.hpp>

#endif // BOOST_ASIO_EXECUTION_SENDER_HPP

/* sender.hpp
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
*/
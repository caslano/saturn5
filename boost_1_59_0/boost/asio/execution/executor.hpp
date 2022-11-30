//
// execution/executor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_EXECUTOR_HPP
#define BOOST_ASIO_EXECUTION_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/execute.hpp>
#include <boost/asio/execution/invocable_archetype.hpp>
#include <boost/asio/traits/equality_comparable.hpp>

#if defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_FREE_TRAIT) \
  && defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT) \
  && defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)
# define BOOST_ASIO_HAS_DEDUCED_EXECUTION_IS_EXECUTOR_TRAIT 1
#endif // defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_FREE_TRAIT)
       //   && defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)
       //   && defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace execution {
namespace detail {

template <typename T, typename F,
    typename = void, typename = void, typename = void, typename = void,
    typename = void, typename = void, typename = void, typename = void>
struct is_executor_of_impl : false_type
{
};

template <typename T, typename F>
struct is_executor_of_impl<T, F,
  typename enable_if<
    can_execute<typename add_const<T>::type, F>::value
  >::type,
  typename void_type<
    typename result_of<typename decay<F>::type&()>::type
  >::type,
  typename enable_if<
    is_constructible<typename decay<F>::type, F>::value
  >::type,
  typename enable_if<
    is_move_constructible<typename decay<F>::type>::value
  >::type,
#if defined(BOOST_ASIO_HAS_NOEXCEPT)
  typename enable_if<
    is_nothrow_copy_constructible<T>::value
  >::type,
  typename enable_if<
    is_nothrow_destructible<T>::value
  >::type,
#else // defined(BOOST_ASIO_HAS_NOEXCEPT)
  typename enable_if<
    is_copy_constructible<T>::value
  >::type,
  typename enable_if<
    is_destructible<T>::value
  >::type,
#endif // defined(BOOST_ASIO_HAS_NOEXCEPT)
  typename enable_if<
    traits::equality_comparable<T>::is_valid
  >::type,
  typename enable_if<
    traits::equality_comparable<T>::is_noexcept
  >::type> : true_type
{
};

template <typename T, typename = void>
struct executor_shape
{
  typedef std::size_t type;
};

template <typename T>
struct executor_shape<T,
    typename void_type<
      typename T::shape_type
    >::type>
{
  typedef typename T::shape_type type;
};

template <typename T, typename Default, typename = void>
struct executor_index
{
  typedef Default type;
};

template <typename T, typename Default>
struct executor_index<T, Default,
    typename void_type<
      typename T::index_type
    >::type>
{
  typedef typename T::index_type type;
};

} // namespace detail

/// The is_executor trait detects whether a type T satisfies the
/// execution::executor concept.
/**
 * Class template @c is_executor is a UnaryTypeTrait that is derived from @c
 * true_type if the type @c T meets the concept definition for an executor,
 * otherwise @c false_type.
 */
template <typename T>
struct is_executor :
#if defined(GENERATING_DOCUMENTATION)
  integral_constant<bool, automatically_determined>
#else // defined(GENERATING_DOCUMENTATION)
  detail::is_executor_of_impl<T, invocable_archetype>
#endif // defined(GENERATING_DOCUMENTATION)
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T>
BOOST_ASIO_CONSTEXPR const bool is_executor_v = is_executor<T>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

#if defined(BOOST_ASIO_HAS_CONCEPTS)

template <typename T>
BOOST_ASIO_CONCEPT executor = is_executor<T>::value;

#define BOOST_ASIO_EXECUTION_EXECUTOR ::boost::asio::execution::executor

#else // defined(BOOST_ASIO_HAS_CONCEPTS)

#define BOOST_ASIO_EXECUTION_EXECUTOR typename

#endif // defined(BOOST_ASIO_HAS_CONCEPTS)

/// The is_executor_of trait detects whether a type T satisfies the
/// execution::executor_of concept for some set of value arguments.
/**
 * Class template @c is_executor_of is a type trait that is derived from @c
 * true_type if the type @c T meets the concept definition for an executor
 * that is invocable with a function object of type @c F, otherwise @c
 * false_type.
 */
template <typename T, typename F>
struct is_executor_of :
#if defined(GENERATING_DOCUMENTATION)
  integral_constant<bool, automatically_determined>
#else // defined(GENERATING_DOCUMENTATION)
  integral_constant<bool,
    is_executor<T>::value && detail::is_executor_of_impl<T, F>::value
  >
#endif // defined(GENERATING_DOCUMENTATION)
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename F>
BOOST_ASIO_CONSTEXPR const bool is_executor_of_v =
  is_executor_of<T, F>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

#if defined(BOOST_ASIO_HAS_CONCEPTS)

template <typename T, typename F>
BOOST_ASIO_CONCEPT executor_of = is_executor_of<T, F>::value;

#define BOOST_ASIO_EXECUTION_EXECUTOR_OF(f) \
  ::boost::asio::execution::executor_of<f>

#else // defined(BOOST_ASIO_HAS_CONCEPTS)

#define BOOST_ASIO_EXECUTION_EXECUTOR_OF typename

#endif // defined(BOOST_ASIO_HAS_CONCEPTS)

/// The executor_shape trait detects the type used by an executor to represent
/// the shape of a bulk operation.
/**
 * Class template @c executor_shape is a type trait with a nested type alias
 * @c type whose type is @c T::shape_type if @c T::shape_type is valid,
 * otherwise @c std::size_t.
 */
template <typename T>
struct executor_shape
#if !defined(GENERATING_DOCUMENTATION)
  : detail::executor_shape<T>
#endif // !defined(GENERATING_DOCUMENTATION)
{
#if defined(GENERATING_DOCUMENTATION)
 /// @c T::shape_type if @c T::shape_type is valid, otherwise @c std::size_t.
 typedef automatically_determined type;
#endif // defined(GENERATING_DOCUMENTATION)
};

#if defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

template <typename T>
using executor_shape_t = typename executor_shape<T>::type;

#endif // defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

/// The executor_index trait detects the type used by an executor to represent
/// an index within a bulk operation.
/**
 * Class template @c executor_index is a type trait with a nested type alias
 * @c type whose type is @c T::index_type if @c T::index_type is valid,
 * otherwise @c executor_shape_t<T>.
 */
template <typename T>
struct executor_index
#if !defined(GENERATING_DOCUMENTATION)
  : detail::executor_index<T, typename executor_shape<T>::type>
#endif // !defined(GENERATING_DOCUMENTATION)
{
#if defined(GENERATING_DOCUMENTATION)
 /// @c T::index_type if @c T::index_type is valid, otherwise
 /// @c executor_shape_t<T>.
 typedef automatically_determined type;
#endif // defined(GENERATING_DOCUMENTATION)
};

#if defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

template <typename T>
using executor_index_t = typename executor_index<T>::type;

#endif // defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

} // namespace execution
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_EXECUTOR_HPP

/* executor.hpp
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
*/
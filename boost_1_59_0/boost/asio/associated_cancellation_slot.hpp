//
// associated_cancellation_slot.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_ASSOCIATED_CANCELLATION_SLOT_HPP
#define BOOST_ASIO_ASSOCIATED_CANCELLATION_SLOT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associator.hpp>
#include <boost/asio/cancellation_signal.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

template <typename T, typename CancellationSlot>
struct associated_cancellation_slot;

namespace detail {

template <typename T, typename = void>
struct has_cancellation_slot_type : false_type
{
};

template <typename T>
struct has_cancellation_slot_type<T,
  typename void_type<typename T::cancellation_slot_type>::type>
    : true_type
{
};

template <typename T, typename S, typename = void, typename = void>
struct associated_cancellation_slot_impl
{
  typedef void asio_associated_cancellation_slot_is_unspecialised;

  typedef S type;

  static type get(const T&, const S& s = S()) BOOST_ASIO_NOEXCEPT
  {
    return s;
  }
};

template <typename T, typename S>
struct associated_cancellation_slot_impl<T, S,
  typename void_type<typename T::cancellation_slot_type>::type>
{
  typedef typename T::cancellation_slot_type type;

  static type get(const T& t, const S& = S()) BOOST_ASIO_NOEXCEPT
  {
    return t.get_cancellation_slot();
  }
};

template <typename T, typename S>
struct associated_cancellation_slot_impl<T, S,
  typename enable_if<
    !has_cancellation_slot_type<T>::value
  >::type,
  typename void_type<
    typename associator<associated_cancellation_slot, T, S>::type
  >::type> : associator<associated_cancellation_slot, T, S>
{
};

} // namespace detail

/// Traits type used to obtain the cancellation_slot associated with an object.
/**
 * A program may specialise this traits type if the @c T template parameter in
 * the specialisation is a user-defined type. The template parameter @c
 * CancellationSlot shall be a type meeting the CancellationSlot requirements.
 *
 * Specialisations shall meet the following requirements, where @c t is a const
 * reference to an object of type @c T, and @c s is an object of type @c
 * CancellationSlot.
 *
 * @li Provide a nested typedef @c type that identifies a type meeting the
 * CancellationSlot requirements.
 *
 * @li Provide a noexcept static member function named @c get, callable as @c
 * get(t) and with return type @c type.
 *
 * @li Provide a noexcept static member function named @c get, callable as @c
 * get(t,s) and with return type @c type.
 */
template <typename T, typename CancellationSlot = cancellation_slot>
struct associated_cancellation_slot
#if !defined(GENERATING_DOCUMENTATION)
  : detail::associated_cancellation_slot_impl<T, CancellationSlot>
#endif // !defined(GENERATING_DOCUMENTATION)
{
#if defined(GENERATING_DOCUMENTATION)
  /// If @c T has a nested type @c cancellation_slot_type,
  /// <tt>T::cancellation_slot_type</tt>. Otherwise
  /// @c CancellationSlot.
  typedef see_below type;

  /// If @c T has a nested type @c cancellation_slot_type, returns
  /// <tt>t.get_cancellation_slot()</tt>. Otherwise returns @c s.
  static type get(const T& t,
      const CancellationSlot& s = CancellationSlot()) BOOST_ASIO_NOEXCEPT;
#endif // defined(GENERATING_DOCUMENTATION)
};

/// Helper function to obtain an object's associated cancellation_slot.
/**
 * @returns <tt>associated_cancellation_slot<T>::get(t)</tt>
 */
template <typename T>
BOOST_ASIO_NODISCARD inline typename associated_cancellation_slot<T>::type
get_associated_cancellation_slot(const T& t) BOOST_ASIO_NOEXCEPT
{
  return associated_cancellation_slot<T>::get(t);
}

/// Helper function to obtain an object's associated cancellation_slot.
/**
 * @returns <tt>associated_cancellation_slot<T,
 * CancellationSlot>::get(t, st)</tt>
 */
template <typename T, typename CancellationSlot>
BOOST_ASIO_NODISCARD inline
typename associated_cancellation_slot<T, CancellationSlot>::type
get_associated_cancellation_slot(const T& t,
    const CancellationSlot& st) BOOST_ASIO_NOEXCEPT
{
  return associated_cancellation_slot<T, CancellationSlot>::get(t, st);
}

#if defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

template <typename T, typename CancellationSlot = cancellation_slot>
using associated_cancellation_slot_t =
  typename associated_cancellation_slot<T, CancellationSlot>::type;

#endif // defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

namespace detail {

template <typename T, typename S, typename = void>
struct associated_cancellation_slot_forwarding_base
{
};

template <typename T, typename S>
struct associated_cancellation_slot_forwarding_base<T, S,
    typename enable_if<
      is_same<
        typename associated_cancellation_slot<T,
          S>::asio_associated_cancellation_slot_is_unspecialised,
        void
      >::value
    >::type>
{
  typedef void asio_associated_cancellation_slot_is_unspecialised;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_ASSOCIATED_CANCELLATION_SLOT_HPP

/* associated_cancellation_slot.hpp
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
*/
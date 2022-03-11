//
// associated_allocator.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_ASSOCIATED_ALLOCATOR_HPP
#define BOOST_ASIO_ASSOCIATED_ALLOCATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <memory>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename>
struct associated_allocator_check
{
  typedef void type;
};

template <typename T, typename E, typename = void>
struct associated_allocator_impl
{
  typedef E type;

  static type get(const T&, const E& e) BOOST_ASIO_NOEXCEPT
  {
    return e;
  }
};

template <typename T, typename E>
struct associated_allocator_impl<T, E,
  typename associated_allocator_check<typename T::allocator_type>::type>
{
  typedef typename T::allocator_type type;

  static type get(const T& t, const E&) BOOST_ASIO_NOEXCEPT
  {
    return t.get_allocator();
  }
};

} // namespace detail

/// Traits type used to obtain the allocator associated with an object.
/**
 * A program may specialise this traits type if the @c T template parameter in
 * the specialisation is a user-defined type. The template parameter @c
 * Allocator shall be a type meeting the Allocator requirements.
 *
 * Specialisations shall meet the following requirements, where @c t is a const
 * reference to an object of type @c T, and @c a is an object of type @c
 * Allocator.
 *
 * @li Provide a nested typedef @c type that identifies a type meeting the
 * Allocator requirements.
 *
 * @li Provide a noexcept static member function named @c get, callable as @c
 * get(t) and with return type @c type.
 *
 * @li Provide a noexcept static member function named @c get, callable as @c
 * get(t,a) and with return type @c type.
 */
template <typename T, typename Allocator = std::allocator<void> >
struct associated_allocator
{
  /// If @c T has a nested type @c allocator_type, <tt>T::allocator_type</tt>.
  /// Otherwise @c Allocator.
#if defined(GENERATING_DOCUMENTATION)
  typedef see_below type;
#else // defined(GENERATING_DOCUMENTATION)
  typedef typename detail::associated_allocator_impl<T, Allocator>::type type;
#endif // defined(GENERATING_DOCUMENTATION)

  /// If @c T has a nested type @c allocator_type, returns
  /// <tt>t.get_allocator()</tt>. Otherwise returns @c a.
  static type get(const T& t,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return detail::associated_allocator_impl<T, Allocator>::get(t, a);
  }
};

/// Helper function to obtain an object's associated allocator.
/**
 * @returns <tt>associated_allocator<T>::get(t)</tt>
 */
template <typename T>
inline typename associated_allocator<T>::type
get_associated_allocator(const T& t) BOOST_ASIO_NOEXCEPT
{
  return associated_allocator<T>::get(t);
}

/// Helper function to obtain an object's associated allocator.
/**
 * @returns <tt>associated_allocator<T, Allocator>::get(t, a)</tt>
 */
template <typename T, typename Allocator>
inline typename associated_allocator<T, Allocator>::type
get_associated_allocator(const T& t, const Allocator& a) BOOST_ASIO_NOEXCEPT
{
  return associated_allocator<T, Allocator>::get(t, a);
}

#if defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

template <typename T, typename Allocator = std::allocator<void> >
using associated_allocator_t
  = typename associated_allocator<T, Allocator>::type;

#endif // defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_ASSOCIATED_ALLOCATOR_HPP

/* associated_allocator.hpp
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
*/
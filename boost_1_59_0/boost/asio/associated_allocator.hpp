//
// associated_allocator.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/associator.hpp>
#include <boost/asio/detail/functional.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

template <typename T, typename Allocator>
struct associated_allocator;

namespace detail {

template <typename T, typename = void>
struct has_allocator_type : false_type
{
};

template <typename T>
struct has_allocator_type<T,
  typename void_type<typename T::allocator_type>::type>
    : true_type
{
};

template <typename T, typename E, typename = void, typename = void>
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
  typename void_type<typename T::allocator_type>::type>
{
  typedef typename T::allocator_type type;

  static type get(const T& t, const E&) BOOST_ASIO_NOEXCEPT
  {
    return t.get_allocator();
  }
};

template <typename T, typename E>
struct associated_allocator_impl<T, E,
  typename enable_if<
    !has_allocator_type<T>::value
  >::type,
  typename void_type<
    typename associator<associated_allocator, T, E>::type
  >::type> : associator<associated_allocator, T, E>
{
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
BOOST_ASIO_NODISCARD inline typename associated_allocator<T>::type
get_associated_allocator(const T& t) BOOST_ASIO_NOEXCEPT
{
  return associated_allocator<T>::get(t);
}

/// Helper function to obtain an object's associated allocator.
/**
 * @returns <tt>associated_allocator<T, Allocator>::get(t, a)</tt>
 */
template <typename T, typename Allocator>
BOOST_ASIO_NODISCARD inline typename associated_allocator<T, Allocator>::type
get_associated_allocator(const T& t, const Allocator& a) BOOST_ASIO_NOEXCEPT
{
  return associated_allocator<T, Allocator>::get(t, a);
}

#if defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

template <typename T, typename Allocator = std::allocator<void> >
using associated_allocator_t
  = typename associated_allocator<T, Allocator>::type;

#endif // defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

#if defined(BOOST_ASIO_HAS_STD_REFERENCE_WRAPPER) \
  || defined(GENERATING_DOCUMENTATION)

/// Specialisation of associated_allocator for @c std::reference_wrapper.
template <typename T, typename Allocator>
struct associated_allocator<reference_wrapper<T>, Allocator>
{
  /// Forwards @c type to the associator specialisation for the unwrapped type
  /// @c T.
  typedef typename associated_allocator<T, Allocator>::type type;

  /// Forwards the request to get the allocator to the associator specialisation
  /// for the unwrapped type @c T.
  static type get(reference_wrapper<T> t,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<T, Allocator>::get(t.get(), a);
  }
};

#endif // defined(BOOST_ASIO_HAS_STD_REFERENCE_WRAPPER)
       //   || defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_ASSOCIATED_ALLOCATOR_HPP

/* associated_allocator.hpp
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
*/
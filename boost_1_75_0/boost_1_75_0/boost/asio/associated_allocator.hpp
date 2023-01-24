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
uB8t7VJIoaXxhDgOD3JH4wlhCoY94aTvWXToX5g+pCg4KvrLDkCUf4/28PCD0NivzVfogWAPe6trHxLuX1ckfE94YMQBwaTa05YEFzgtTG27yml1lTvFFaisaZPa9QxDUOONTGIIeMNMv6r3y8+Merz5LFi43iKXw/9nEr0fjlxU2jF3mZ1w6jJsDrej1t4pvFcRwwDayIdokpGNzhNycSTA7ZaO4/bIKBAXo2dgSwuNT7vYcjZO+myGx9D10d/QmtTQ2CbeQAyaSgjxCRImIwbMeBMoFGQLXyF/uIgzeI2XToVn3qGyfmNcFUoC+XMFJ5CpElr5InqzrUprbvl7YqaLM6Omc1XaCcNxVB+GjKicKcBQPkwro3GNcRrXiALUdjzs0C4iZZdFk8bwFBOTSgIe68h4ppAExC+Ma1Vjk1pW++mD9bDf0Xgjrbk8Gins67SeInTTK+CCidsegqU70TKobPvtfuhhKJiYkoimINzD8I/8HDtTn3ue/X2R/X2Z/UXecfdz+9jfN1jKOfxbYW/b1Q8f+hH/t/SpV7bR0Rjd/ZNGGd1vNnzr3DJFjWdL7GQXwlA5vRB2p+wdWgrIWBjIcyq+uSAuNfyS3RjnuMoGzA0BJJMFjiIa94DqsiSUIK/1ux8zZ45pUt0Ampqan2zZbfRjRh7IPqEaUhDtIhG469jWhcnQrNiOTfopfQD15eggYwtlj9Qp+naV
*/
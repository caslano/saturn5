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
UTZJNJ+UtAXrHT4bGX2juXSIJDqXZ9FBF210PMhiW34n0wPVPxRmmks3ROZS2PvdOFPniYiSWKp6HcrG3/mIGzO3EEnfgUddPCups6GVw+7Ro2WbSS0tGuemetOinmw+cfkJzA0u4P/KhankYBBTTG+iuN35iBpIgUbQZEGfaRXCi5z4+UvC1HH2Ff67cJLMo4v48OUpGLycRJ3rFpDEkoUkW2uDH3fH0KsXlRCb28ul1rQgaK8kyz4IuLkfYgHDBinUN57tWRaCjXO+UMeXr/TinS9P8N5OeV5tUNrbAoMRiyjgxDGk1xvwzIsFaK77wrs/r0CuiAfbmLAIB7wnImHXZlLtdOBxQe+xj1L43KfvcE52PetL9UGsXRxN1vhMkeLnMC8iieSO3sVT41Zy962ka0HN9M6jGK1d0vinMZzcdqrQpBcxlH0iiyYPEWIRfhY0OOEyW6k7FeecJuD2A11alKNDLoYLqFjUlyLqt1DdpGg6JZ5D/XEv0a5UTuvPd7MdKyuwa10GdpxLp+gTP9jDxyewf4MPix4agthITXp66Dc6D6zmYhsn0BGfNpLTeAiFyksUG5CEW8IKbKmVHMlsNqZbX91x0sCWH/xiAJeuFTxq3wakZLRT414nKujWp7smBK1Xd2j+7Dv0tusSM1y7DXFyErSz0gTXn32lmNnyaMxci0mdT3CqaRszeqQKN+8trLHBDz6Ll9CQ4uvgMmN56L1XOE+/SBrJkIr8zKy+VsGqWJcvPl5CpfI68OlwpttXO1jwYYEfEzenoovz6YKNFsylcrApfjNuhR1BcvJwmlReh7icbsR65cE0LoPHjHene6bfWJ22F0lONoe0z1G6JhzBE8f4UexTScTbnsBwaUmWMGcAQsrdhI8F0Mr4wl61DoFW/gnufX8klbodpXsyL9Ay5QM2rNsDsUBfOv98OUJMfPjfpBJ6dy4IUQuTSfb7VkxSjkEdjyTpC7fJ56YkU7SXog+Hm6n1yhho5Y3hXfuHk/DI8Xzq1r1wLn6OEeFy8A38SkfuydEB+wCeHDAZDivmYWR3B+Vq6iDAdydpzOzh4XUlgtybzYPOlVLInEUsSreRLFfHsefp+dgQNZ9sTraQzEMdaqi4Q2vev+XD3LPpgqAXKyDJ2H1xFQtujKGcL+O5bYMVHZx4jQ/rX4e/a2+QpsUwwm13rLrBsHTEK5ZxvA55i4/Tu9H2KJpRjuspv0i85Q6L/JSHP2l2LOn0H5rvGcF2/VWH7orpfEr2UxwZ/olrO5kgtzWOBtfIwL1gGUK2aVKtTRJX1tPEK52DNL+9n9YIz2S+MR3kOPMLvPL1SCj5J192LZ0kP9yiyaWD+OfSgxIfLTg/siWNgx2Q9eqh0kWz8FjgmtbaTqFrUs187pJ/kFHqJ0GjCVeqrJhSxQ/0zNrCf2wqpSrRi7zK4Sh9tB/PT6d3IrXUj84WplFHVCF7v1senXpJfIhQN8SfZ/GsF+KI8H3LZ4yWJ1z24lemHKCEDSW4GDUaMYHr2IcFg1DZdRx7qovwL9WYa2ZPhoSAM5GyLTnpBnH7l320pM+DPHXe0IHbC/nWzT8QUWXMFq1WhVlxJKwrrmDFyxz6ZamIiTI3cfhQDdRT5rIWtoTGFgVCqGI2BemUIWX7OsyvM0KersDRJHuzgDHxpJehiCcrzuHo/Ids9rx10GrTYCQuR702YTD9egy66+oJtpV0IbMdlyetxu2DT7l/gyMoJRCXR7iS5/LHdPNpMbmrpJJ1GoNryU62RoJDLGQoP7N4Cfyz88k4LpY8zBJxrTyMyo/H0PlYbUrw/MYH38bi51gF2Kj5I/uaK4JNo2ihxyYWLN1JF5SWsfbMuVg=
*/
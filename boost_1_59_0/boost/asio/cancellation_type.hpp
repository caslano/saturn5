//
// cancellation_type.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_CANCELLATION_TYPE_HPP
#define BOOST_ASIO_CANCELLATION_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

# if defined(GENERATING_DOCUMENTATION)

/// Enumeration representing the different types of cancellation that may
/// be requested from or implemented by an asynchronous operation.
enum cancellation_type
{
  /// Bitmask representing no types of cancellation.
  none = 0,

  /// Requests cancellation where, following a successful cancellation, the only
  /// safe operations on the I/O object are closure or destruction.
  terminal = 1,

  /// Requests cancellation where a successful cancellation may result in
  /// partial side effects or no side effects. Following cancellation, the I/O
  /// object is in a well-known state, and may be used for further operations.
  partial = 2,

  /// Requests cancellation where a successful cancellation results in no
  /// apparent side effects. Following cancellation, the I/O object is in the
  /// same observable state as it was prior to the operation.
  total = 4,

  /// Bitmask representing all types of cancellation.
  all = 0xFFFFFFFF
};

/// Portability typedef.
typedef cancellation_type cancellation_type_t;

#elif defined(BOOST_ASIO_HAS_ENUM_CLASS)

enum class cancellation_type : unsigned int
{
  none = 0,
  terminal = 1,
  partial = 2,
  total = 4,
  all = 0xFFFFFFFF
};

typedef cancellation_type cancellation_type_t;

#else // defined(BOOST_ASIO_HAS_ENUM_CLASS)

namespace cancellation_type {

enum cancellation_type_t
{
  none = 0,
  terminal = 1,
  partial = 2,
  total = 4,
  all = 0xFFFFFFFF
};

} // namespace cancellation_type

typedef cancellation_type::cancellation_type_t cancellation_type_t;

#endif // defined(BOOST_ASIO_HAS_ENUM_CLASS)

/// Negation operator.
/**
 * @relates cancellation_type
 */
inline BOOST_ASIO_CONSTEXPR bool operator!(cancellation_type_t x)
{
  return static_cast<unsigned int>(x) == 0;
}

/// Bitwise and operator.
/**
 * @relates cancellation_type
 */
inline BOOST_ASIO_CONSTEXPR cancellation_type_t operator&(
    cancellation_type_t x, cancellation_type_t y)
{
  return static_cast<cancellation_type_t>(
      static_cast<unsigned int>(x) & static_cast<unsigned int>(y));
}

/// Bitwise or operator.
/**
 * @relates cancellation_type
 */
inline BOOST_ASIO_CONSTEXPR cancellation_type_t operator|(
    cancellation_type_t x, cancellation_type_t y)
{
  return static_cast<cancellation_type_t>(
      static_cast<unsigned int>(x) | static_cast<unsigned int>(y));
}

/// Bitwise xor operator.
/**
 * @relates cancellation_type
 */
inline BOOST_ASIO_CONSTEXPR cancellation_type_t operator^(
    cancellation_type_t x, cancellation_type_t y)
{
  return static_cast<cancellation_type_t>(
      static_cast<unsigned int>(x) ^ static_cast<unsigned int>(y));
}

/// Bitwise negation operator.
/**
 * @relates cancellation_type
 */
inline BOOST_ASIO_CONSTEXPR cancellation_type_t operator~(cancellation_type_t x)
{
  return static_cast<cancellation_type_t>(~static_cast<unsigned int>(x));
}

/// Bitwise and-assignment operator.
/**
 * @relates cancellation_type
 */
inline cancellation_type_t& operator&=(
    cancellation_type_t& x, cancellation_type_t y)
{
  x = x & y;
  return x;
}

/// Bitwise or-assignment operator.
/**
 * @relates cancellation_type
 */
inline cancellation_type_t& operator|=(
    cancellation_type_t& x, cancellation_type_t y)
{
  x = x | y;
  return x;
}

/// Bitwise xor-assignment operator.
/**
 * @relates cancellation_type
 */
inline cancellation_type_t& operator^=(
    cancellation_type_t& x, cancellation_type_t y)
{
  x = x ^ y;
  return x;
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_CANCELLATION_TYPE_HPP

/* cancellation_type.hpp
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
*/
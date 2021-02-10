//
// completion_condition.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_COMPLETION_CONDITION_HPP
#define BOOST_ASIO_COMPLETION_CONDITION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

namespace detail {

// The default maximum number of bytes to transfer in a single operation.
enum default_max_transfer_size_t { default_max_transfer_size = 65536 };

// Adapt result of old-style completion conditions (which had a bool result
// where true indicated that the operation was complete).
inline std::size_t adapt_completion_condition_result(bool result)
{
  return result ? 0 : default_max_transfer_size;
}

// Adapt result of current completion conditions (which have a size_t result
// where 0 means the operation is complete, and otherwise the result is the
// maximum number of bytes to transfer on the next underlying operation).
inline std::size_t adapt_completion_condition_result(std::size_t result)
{
  return result;
}

class transfer_all_t
{
public:
  typedef std::size_t result_type;

  template <typename Error>
  std::size_t operator()(const Error& err, std::size_t)
  {
    return !!err ? 0 : default_max_transfer_size;
  }
};

class transfer_at_least_t
{
public:
  typedef std::size_t result_type;

  explicit transfer_at_least_t(std::size_t minimum)
    : minimum_(minimum)
  {
  }

  template <typename Error>
  std::size_t operator()(const Error& err, std::size_t bytes_transferred)
  {
    return (!!err || bytes_transferred >= minimum_)
      ? 0 : default_max_transfer_size;
  }

private:
  std::size_t minimum_;
};

class transfer_exactly_t
{
public:
  typedef std::size_t result_type;

  explicit transfer_exactly_t(std::size_t size)
    : size_(size)
  {
  }

  template <typename Error>
  std::size_t operator()(const Error& err, std::size_t bytes_transferred)
  {
    return (!!err || bytes_transferred >= size_) ? 0 :
      (size_ - bytes_transferred < default_max_transfer_size
        ? size_ - bytes_transferred : std::size_t(default_max_transfer_size));
  }

private:
  std::size_t size_;
};

} // namespace detail

/**
 * @defgroup completion_condition Completion Condition Function Objects
 *
 * Function objects used for determining when a read or write operation should
 * complete.
 */
/*@{*/

/// Return a completion condition function object that indicates that a read or
/// write operation should continue until all of the data has been transferred,
/// or until an error occurs.
/**
 * This function is used to create an object, of unspecified type, that meets
 * CompletionCondition requirements.
 *
 * @par Example
 * Reading until a buffer is full:
 * @code
 * boost::array<char, 128> buf;
 * boost::system::error_code ec;
 * std::size_t n = boost::asio::read(
 *     sock, boost::asio::buffer(buf),
 *     boost::asio::transfer_all(), ec);
 * if (ec)
 * {
 *   // An error occurred.
 * }
 * else
 * {
 *   // n == 128
 * }
 * @endcode
 */
#if defined(GENERATING_DOCUMENTATION)
unspecified transfer_all();
#else
inline detail::transfer_all_t transfer_all()
{
  return detail::transfer_all_t();
}
#endif

/// Return a completion condition function object that indicates that a read or
/// write operation should continue until a minimum number of bytes has been
/// transferred, or until an error occurs.
/**
 * This function is used to create an object, of unspecified type, that meets
 * CompletionCondition requirements.
 *
 * @par Example
 * Reading until a buffer is full or contains at least 64 bytes:
 * @code
 * boost::array<char, 128> buf;
 * boost::system::error_code ec;
 * std::size_t n = boost::asio::read(
 *     sock, boost::asio::buffer(buf),
 *     boost::asio::transfer_at_least(64), ec);
 * if (ec)
 * {
 *   // An error occurred.
 * }
 * else
 * {
 *   // n >= 64 && n <= 128
 * }
 * @endcode
 */
#if defined(GENERATING_DOCUMENTATION)
unspecified transfer_at_least(std::size_t minimum);
#else
inline detail::transfer_at_least_t transfer_at_least(std::size_t minimum)
{
  return detail::transfer_at_least_t(minimum);
}
#endif

/// Return a completion condition function object that indicates that a read or
/// write operation should continue until an exact number of bytes has been
/// transferred, or until an error occurs.
/**
 * This function is used to create an object, of unspecified type, that meets
 * CompletionCondition requirements.
 *
 * @par Example
 * Reading until a buffer is full or contains exactly 64 bytes:
 * @code
 * boost::array<char, 128> buf;
 * boost::system::error_code ec;
 * std::size_t n = boost::asio::read(
 *     sock, boost::asio::buffer(buf),
 *     boost::asio::transfer_exactly(64), ec);
 * if (ec)
 * {
 *   // An error occurred.
 * }
 * else
 * {
 *   // n == 64
 * }
 * @endcode
 */
#if defined(GENERATING_DOCUMENTATION)
unspecified transfer_exactly(std::size_t size);
#else
inline detail::transfer_exactly_t transfer_exactly(std::size_t size)
{
  return detail::transfer_exactly_t(size);
}
#endif

/*@}*/

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_COMPLETION_CONDITION_HPP

/* completion_condition.hpp
QGRRYFwbZzPYWF1VsEdKRnPetvORup5Ow7El16+FCMPnK76gJVEZ/SaBhFTxNZNQ1n2OodPcSSTkKEVqK3L/N37/joPHXrxg6UsyOiGzwDxb+pBFdSOAGdU5sU94GsqzSQFfHUO5vjiJnQJQk4ul722QMJdMsjLCXh8dOT892UOUPjsBebff//P2+f6fZ96uXdqTGumkZh+JF0SE42jqL7dS/yccfsZB0SlKxsExJRwQgoS9Z4HkDCapxnO6BVmjIfh1WTayBW88524R7U2qfL0Y1VU+KjlJ2NjGNct0Nd5GD2sK1oFxN0ADOCjcbrVUkENQXwNJvM24EY4GQdi3ga0nERHKfemo6sr0FlAC1Lim9Ra868qEECKsHAoM5UI10AL2r4xVlDYkoJVAiY8nsh+XZT0AtvSFDvaej8Oc10y0fQyuP1MIbwJMvTkS410uSXswKX1rSz6EQAA74UDV9/opAj5sGCSLhV2Y3s970Y+Wkg/8+VIuVoer7DQbTftFpD2/arlj5Hqz2eGxv/IBTOSMSrlzV5CkKBhlv7lRAbrRhPhRJ0CvFiQRYt5KEU1DF0uovgiJbICJE5UIK+a7XaW0VqfJ6/7CVzl35qxnpzByFd/w9L75G54STMUihhO4QWSlFJuzPPJii4B5
*/
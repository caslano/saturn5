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
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
*/
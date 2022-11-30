//
// completion_condition.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
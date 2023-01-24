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
YSWNVHN0su2yUkQn2JCbJ2eg1odKbTodnIZW6uqxoj7QRvJTgCz5524BIhG6heRnEM9/T5ryGWnyAAws89PiG6HsEPnOmEyB/CFyVyF9AvvBp3xHRhXN2RzNwXGZAh5I9NE1I4lsZKnqyCYTg5K+j+ZCpqcUh/YvdWh3TcOhpU4bGVonDs0xZmgm0lJC8lLIpqSPLhfMqjPxPhjhnOZQAcnLIJnpfm2IgjrEGm2I6Xvx8maSDAyg25R2ImB6GwkJRjpiL4eKkyqHA/nG5fgYoYql5RW4tEG9zphgGSMYYQLKHXumjpE7RvKXHFLzK6fGCk7WaQmWGw+xNxmVGiP1Qia6l7ixUGlMdO1mUrEJqHBP/VXope8PFGTQ5GFc/wtbvgQhtCLgV8rlyZqwZMV6ZX3ZwHMy30Y89M5rPO5fSvEldjXuwuF4jIUG7KcWGRSE2XIjxnPQHoHD9w9DGBrBTLxWP/3jN9ihaNryT+IFOqTIk8u1119U+j+J1FmyeK+p/iqSm1ni9xXSt5g6DxqYUIIPxhXSl7R45Cbd9hYM9iC5dObGMzNRdo4GFVPDtmoNqw9CP5kU8yC0beyD5Enai9BAKtal6lkgeHx/wwH/Oem/pjB2Aukmvv0M5PlmJiax4ZfQV1fA6bgT4YDla0uwyDY5k5OXGwlwKHHkAmlDI9XvvPy9dxWs2eMH1Dc3F4HcnvVntn70RozNuDZD
*/
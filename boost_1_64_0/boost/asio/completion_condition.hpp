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
jfftPoD3I/wS4fUID0F4FPcTzDvFZfB6DmDegDh791UYvxrhNQivRXgdwksRXobwcoRXILwS4akI9+0DOI3xvTkPALwH019C+DzClxF+j/BehC8gfLFP3JH8Ad5vkf6GCFfj7YDpa2B8TYRrcR0Qrj4gztl9EPdl/PvBfQBnEF4JAPsB4L68zph2MO9TGN8R4w9i/BOEZ3Lfw/gWiPsMws0QSgifQ/g8Qg7hVwh7ED6N8Bs+niLcHGEB4Q8If0T4Hbcdwp/42DogzkR/AYgz0K83IM42vz63UR/AqxFew/0Q4QcIX0H4LMIqbw+ML4/xfoQDCLdCuDXCMMJBhNsgHEIYQbglwu0RphCmEW6HMIMwi3Ac4QjCEMJhhFGEMYQCwjjCBMIkwm0RjiLMIcwjFBHy3JcQ9iLcBOEYwi6ExQFx5vrleB/n9kSoIFQRHovAEGp94nzeM0hzP4QrI9wf4YEID0C4Ch8bER7C2wnhqggPRbh4H8B9uH4YTyJMIIxzX0bcoxAezcdyTLsId0eoI9weAF7aD3CJPtQf4U4It0MoIswjlBAWEKYQpjk9wgne/gh3QDiKcAzhOMIiwizCEYQZhCsNANxoG8BT+wD+ivCXPnFH7B6EmyLckvsMws0R9iGMIAwj7EfIIexFuBnCEEIeYQf30T5xHvPVMb4iwlUQro1wBYRr8TIRroxwTYSrIlyN+zrCJXndkP/OGF8K4SSCjXAXhDLCXbk/AcAltgFcrA+gH+Gy3I8QLsfLRnhyP8BTEZ6B8DSESyNuCWEA4YUA8CIAONAHcBuE2yIcQjiIcBjh1gi3QhhDGO0T5+IDH6Mw+hIAfBUAvgEA5wHgKwDwTQD4OgD8CAB+DAC/AICfA8BPAOC7APBDAPgZAPwAAH4KAN8BgO8DwPcA4GsA8EW6j/rzAPAFAPglAHwLAM7RgV8XAcBv6E79PwDA7wDgV/9k77zj4ijTOD6zs8BCSEI6KUQ0iZKiIYkm2LFjR80qp96JGg1qVDQW1HhibJwVO5ZT9CyoUbFjx9jQRMVyivVQo6JGD+uhZ7nnZb7PDnk+7PX73P1xfHz2+y6/L7O7M++8M/PumpX6UuprqcekeqQekXpJ6mWpdqkXPHnuUhPccTyQcUX4oidjgtRyqcelfpbyfBkTPNnmUj9I/ST1MP8O/JNSz0otk2qTekbqaamnpJZKfS/1nVtmIM9ZqlPqXakXpd6R+ljqPanfS3W545PUp1IrpD6U+kjqA6m3pN6WelPqJXcckOqQel3qDXf8iclr8WU9Cg/wZB9ylN+f6475vjxnt+8Ki1z/dttG7sekVsr9h4UPSj0kdYlku7nt58tjSv3WrWfhcqnPpF6Wct+j8JrUZKlDpO71pK9LneTLepb6Xuo7qS43ZrvnInW61JlSt0j9xpPfx4RS74pzqyfHWXd8k/aFUmVyfwcv/I7mDaR2ltpGaiepDaW2l9pW6iypHaVuisk682XdSC1w61R4jFS16xfCj6TapfZx53fC+6TulfqDVJvU/VIPSbVIPe3Whx9+33C2lCzae0BqrCfriH+vfoTUaKkxUqPc/is10h1rpaZLne/L85E//FUg+6LUxTF53VJV0j5IqtitZ3d+IXW51BXuuOPWtdRVUldLnSw115PXEchy5W9/csd9qfFSz0gtlTrQnWsJDxW2Cl+QynTHPfGPk7bv9iW3fNfH3XFTaqJbvidjh/sbdx0gtVTqcaknpJ6Uekrqaak2qWeknpVaJrVc6nK3f7t9PiZ9WuoFqXapF6VeknpZ6hWp30u9KvWaVIfU61JvSL0p9ZbU21LvSPluHUstlmUeFkgfEWbI/UypuFQgdZAn60M=
*/
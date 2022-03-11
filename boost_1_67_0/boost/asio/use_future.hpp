//
// use_future.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_USE_FUTURE_HPP
#define BOOST_ASIO_USE_FUTURE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/future.hpp>

#if defined(BOOST_ASIO_HAS_STD_FUTURE_CLASS) \
  || defined(GENERATING_DOCUMENTATION)

#include <memory>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Function, typename Allocator>
class packaged_token;

template <typename Function, typename Allocator, typename Result>
class packaged_handler;

} // namespace detail

/// Class used to specify that an asynchronous operation should return a future.
/**
 * The use_future_t class is used to indicate that an asynchronous operation
 * should return a std::future object. A use_future_t object may be passed as a
 * handler to an asynchronous operation, typically using the special value @c
 * boost::asio::use_future. For example:
 *
 * @code std::future<std::size_t> my_future
 *   = my_socket.async_read_some(my_buffer, boost::asio::use_future); @endcode
 *
 * The initiating function (async_read_some in the above example) returns a
 * future that will receive the result of the operation. If the operation
 * completes with an error_code indicating failure, it is converted into a
 * system_error and passed back to the caller via the future.
 */
template <typename Allocator = std::allocator<void> >
class use_future_t
{
public:
  /// The allocator type. The allocator is used when constructing the
  /// @c std::promise object for a given asynchronous operation.
  typedef Allocator allocator_type;

  /// Construct using default-constructed allocator.
  BOOST_ASIO_CONSTEXPR use_future_t()
  {
  }

  /// Construct using specified allocator.
  explicit use_future_t(const Allocator& allocator)
    : allocator_(allocator)
  {
  }

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use rebind().) Specify an alternate allocator.
  template <typename OtherAllocator>
  use_future_t<OtherAllocator> operator[](const OtherAllocator& allocator) const
  {
    return use_future_t<OtherAllocator>(allocator);
  }
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Specify an alternate allocator.
  template <typename OtherAllocator>
  use_future_t<OtherAllocator> rebind(const OtherAllocator& allocator) const
  {
    return use_future_t<OtherAllocator>(allocator);
  }

  /// Obtain allocator.
  allocator_type get_allocator() const
  {
    return allocator_;
  }

  /// Wrap a function object in a packaged task.
  /**
   * The @c package function is used to adapt a function object as a packaged
   * task. When this adapter is passed as a completion token to an asynchronous
   * operation, the result of the function object is retuned via a std::future.
   *
   * @par Example
   *
   * @code std::future<std::size_t> fut =
   *   my_socket.async_read_some(buffer,
   *     use_future([](boost::system::error_code ec, std::size_t n)
   *       {
   *         return ec ? 0 : n;
   *       }));
   * ...
   * std::size_t n = fut.get(); @endcode
   */
  template <typename Function>
#if defined(GENERATING_DOCUMENTATION)
  unspecified
#else // defined(GENERATING_DOCUMENTATION)
  detail::packaged_token<typename decay<Function>::type, Allocator>
#endif // defined(GENERATING_DOCUMENTATION)
  operator()(BOOST_ASIO_MOVE_ARG(Function) f) const;

private:
  // Helper type to ensure that use_future can be constexpr default-constructed
  // even when std::allocator<void> can't be.
  struct std_allocator_void
  {
    BOOST_ASIO_CONSTEXPR std_allocator_void()
    {
    }

    operator std::allocator<void>() const
    {
      return std::allocator<void>();
    }
  };

  typename conditional<
    is_same<std::allocator<void>, Allocator>::value,
    std_allocator_void, Allocator>::type allocator_;
};

/// A special value, similar to std::nothrow.
/**
 * See the documentation for boost::asio::use_future_t for a usage example.
 */
#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr use_future_t<> use_future;
#elif defined(BOOST_ASIO_MSVC)
__declspec(selectany) use_future_t<> use_future;
#endif

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/use_future.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_FUTURE_CLASS)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_USE_FUTURE_HPP

/* use_future.hpp
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
*/
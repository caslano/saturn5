//
// use_future.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

/// A @ref completion_token type that causes an asynchronous operation to return
/// a future.
/**
 * The use_future_t class is a completion token type that is used to indicate
 * that an asynchronous operation should return a std::future object. A
 * use_future_t object may be passed as a completion token to an asynchronous
 * operation, typically using the special value @c boost::asio::use_future. For
 * example:
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

/// A @ref completion_token object that causes an asynchronous operation to
/// return a future.
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
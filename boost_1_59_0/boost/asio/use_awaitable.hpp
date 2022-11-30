//
// use_awaitable.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_USE_AWAITABLE_HPP
#define BOOST_ASIO_USE_AWAITABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CO_AWAIT) || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/awaitable.hpp>
#include <boost/asio/detail/handler_tracking.hpp>

#if defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
# if defined(BOOST_ASIO_HAS_SOURCE_LOCATION)
#  include <boost/asio/detail/source_location.hpp>
# endif // defined(BOOST_ASIO_HAS_SOURCE_LOCATION)
#endif // defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// A @ref completion_token that represents the currently executing coroutine.
/**
 * The @c use_awaitable_t class, with its value @c use_awaitable, is used to
 * represent the currently executing coroutine. This completion token may be
 * passed as a handler to an asynchronous operation. For example:
 *
 * @code awaitable<void> my_coroutine()
 * {
 *   std::size_t n = co_await my_socket.async_read_some(buffer, use_awaitable);
 *   ...
 * } @endcode
 *
 * When used with co_await, the initiating function (@c async_read_some in the
 * above example) suspends the current coroutine. The coroutine is resumed when
 * the asynchronous operation completes, and the result of the operation is
 * returned.
 */
template <typename Executor = any_io_executor>
struct use_awaitable_t
{
  /// Default constructor.
  BOOST_ASIO_CONSTEXPR use_awaitable_t(
#if defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
# if defined(BOOST_ASIO_HAS_SOURCE_LOCATION)
      detail::source_location location = detail::source_location::current()
# endif // defined(BOOST_ASIO_HAS_SOURCE_LOCATION)
#endif // defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
    )
#if defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
# if defined(BOOST_ASIO_HAS_SOURCE_LOCATION)
    : file_name_(location.file_name()),
      line_(location.line()),
      function_name_(location.function_name())
# else // defined(BOOST_ASIO_HAS_SOURCE_LOCATION)
    : file_name_(0),
      line_(0),
      function_name_(0)
# endif // defined(BOOST_ASIO_HAS_SOURCE_LOCATION)
#endif // defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
  {
  }

  /// Constructor used to specify file name, line, and function name.
  BOOST_ASIO_CONSTEXPR use_awaitable_t(const char* file_name,
      int line, const char* function_name)
#if defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
    : file_name_(file_name),
      line_(line),
      function_name_(function_name)
#endif // defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
  {
#if !defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
    (void)file_name;
    (void)line;
    (void)function_name;
#endif // !defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
  }

  /// Adapts an executor to add the @c use_awaitable_t completion token as the
  /// default.
  template <typename InnerExecutor>
  struct executor_with_default : InnerExecutor
  {
    /// Specify @c use_awaitable_t as the default completion token type.
    typedef use_awaitable_t default_completion_token_type;

    /// Construct the adapted executor from the inner executor type.
    template <typename InnerExecutor1>
    executor_with_default(const InnerExecutor1& ex,
        typename constraint<
          conditional<
            !is_same<InnerExecutor1, executor_with_default>::value,
            is_convertible<InnerExecutor1, InnerExecutor>,
            false_type
          >::type::value
        >::type = 0) BOOST_ASIO_NOEXCEPT
      : InnerExecutor(ex)
    {
    }
  };

  /// Type alias to adapt an I/O object to use @c use_awaitable_t as its
  /// default completion token type.
#if defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES) \
  || defined(GENERATING_DOCUMENTATION)
  template <typename T>
  using as_default_on_t = typename T::template rebind_executor<
      executor_with_default<typename T::executor_type> >::other;
#endif // defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)
       //   || defined(GENERATING_DOCUMENTATION)

  /// Function helper to adapt an I/O object to use @c use_awaitable_t as its
  /// default completion token type.
  template <typename T>
  static typename decay<T>::type::template rebind_executor<
      executor_with_default<typename decay<T>::type::executor_type>
    >::other
  as_default_on(BOOST_ASIO_MOVE_ARG(T) object)
  {
    return typename decay<T>::type::template rebind_executor<
        executor_with_default<typename decay<T>::type::executor_type>
      >::other(BOOST_ASIO_MOVE_CAST(T)(object));
  }

#if defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
  const char* file_name_;
  int line_;
  const char* function_name_;
#endif // defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
};

/// A @ref completion_token object that represents the currently executing
/// coroutine.
/**
 * See the documentation for boost::asio::use_awaitable_t for a usage example.
 */
#if defined(GENERATING_DOCUMENTATION)
constexpr use_awaitable_t<> use_awaitable;
#elif defined(BOOST_ASIO_HAS_CONSTEXPR)
constexpr use_awaitable_t<> use_awaitable(0, 0, 0);
#elif defined(BOOST_ASIO_MSVC)
__declspec(selectany) use_awaitable_t<> use_awaitable(0, 0, 0);
#endif

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/use_awaitable.hpp>

#endif // defined(BOOST_ASIO_HAS_CO_AWAIT) || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_USE_AWAITABLE_HPP

/* use_awaitable.hpp
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
*/
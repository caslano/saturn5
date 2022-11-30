//
// experimental/use_coro.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2021-2022 Klemens D. Morgenstern
//                         (klemens dot morgenstern at gmx dot net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_USE_CORO_HPP
#define BOOST_ASIO_EXPERIMENTAL_USE_CORO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <optional>
#include <boost/asio/bind_cancellation_slot.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/experimental/detail/partial_promise.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

class any_io_executor;

namespace experimental {

/// A @ref completion_token that represents the currently executing resumable
/// coroutine.
/**
 * The @c use_coro_t class, with its value @c use_coro, is used to represent an
 * operation that can be awaited by the current resumable coroutine. This
 * completion token may be passed as a handler to an asynchronous operation.
 * For example:
 *
 * @code coro<void> my_coroutine(tcp::socket my_socket)
 * {
 *   std::size_t n = co_await my_socket.async_read_some(buffer, use_coro);
 *   ...
 * } @endcode
 *
 * When used with co_await, the initiating function (@c async_read_some in the
 * above example) suspends the current coroutine. The coroutine is resumed when
 * the asynchronous operation completes, and the result of the operation is
 * returned.
 */
template <typename Executor = any_io_executor>
struct use_coro_t
{
  /// Default constructor.
  BOOST_ASIO_CONSTEXPR use_coro_t(
#if defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
# if defined(BOOST_ASIO_HAS_SOURCE_LOCATION)
      boost::asio::detail::source_location location =
        boost::asio::detail::source_location::current()
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
  BOOST_ASIO_CONSTEXPR use_coro_t(const char* file_name,
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

  /// Adapts an executor to add the @c use_coro_t completion token as the
  /// default.
  template <typename InnerExecutor>
  struct executor_with_default : InnerExecutor
  {
    /// Specify @c use_coro_t as the default completion token type.
    typedef use_coro_t default_completion_token_type;

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

  /// Type alias to adapt an I/O object to use @c use_coro_t as its
  /// default completion token type.
#if defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES) \
  || defined(GENERATING_DOCUMENTATION)
  template <typename T>
  using as_default_on_t = typename T::template rebind_executor<
      executor_with_default<typename T::executor_type> >::other;
#endif // defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)
       //   || defined(GENERATING_DOCUMENTATION)

  /// Function helper to adapt an I/O object to use @c use_coro_t as its
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
/// resumable coroutine.
/**
 * See the documentation for boost::asio::use_coro_t for a usage example.
 */
#if defined(GENERATING_DOCUMENTATION)
constexpr use_coro_t<> use_coro;
#elif defined(BOOST_ASIO_HAS_CONSTEXPR)
constexpr use_coro_t<> use_coro(0, 0, 0);
#elif defined(BOOST_ASIO_MSVC)
__declspec(selectany) use_coro_t<> use_coro(0, 0, 0);
#endif

} // namespace experimental
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/experimental/impl/use_coro.hpp>
#include <boost/asio/experimental/coro.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_USE_CORO_HPP

/* use_coro.hpp
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
*/
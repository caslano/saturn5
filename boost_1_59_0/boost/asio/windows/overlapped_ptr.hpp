//
// windows/overlapped_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_OVERLAPPED_PTR_HPP
#define BOOST_ASIO_WINDOWS_OVERLAPPED_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_OVERLAPPED_PTR) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/win_iocp_overlapped_ptr.hpp>
#include <boost/asio/io_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Wraps a handler to create an OVERLAPPED object for use with overlapped I/O.
/**
 * A special-purpose smart pointer used to wrap an application handler so that
 * it can be passed as the LPOVERLAPPED argument to overlapped I/O functions.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
class overlapped_ptr
  : private noncopyable
{
public:
  /// Construct an empty overlapped_ptr.
  overlapped_ptr()
    : impl_()
  {
  }

  /// Construct an overlapped_ptr to contain the specified handler.
  template <typename ExecutionContext, typename Handler>
  explicit overlapped_ptr(ExecutionContext& context,
      BOOST_ASIO_MOVE_ARG(Handler) handler,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : impl_(context.get_executor(), BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }

  /// Construct an overlapped_ptr to contain the specified handler.
  template <typename Executor, typename Handler>
  explicit overlapped_ptr(const Executor& ex,
      BOOST_ASIO_MOVE_ARG(Handler) handler,
      typename constraint<
        execution::is_executor<Executor>::value
          || is_executor<Executor>::value
      >::type = 0)
    : impl_(ex, BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }

  /// Destructor automatically frees the OVERLAPPED object unless released.
  ~overlapped_ptr()
  {
  }

  /// Reset to empty.
  void reset()
  {
    impl_.reset();
  }

  /// Reset to contain the specified handler, freeing any current OVERLAPPED
  /// object.
  template <typename ExecutionContext, typename Handler>
  void reset(ExecutionContext& context, BOOST_ASIO_MOVE_ARG(Handler) handler,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
  {
    impl_.reset(context.get_executor(), BOOST_ASIO_MOVE_CAST(Handler)(handler));
  }

  /// Reset to contain the specified handler, freeing any current OVERLAPPED
  /// object.
  template <typename Executor, typename Handler>
  void reset(const Executor& ex, BOOST_ASIO_MOVE_ARG(Handler) handler,
      typename constraint<
        execution::is_executor<Executor>::value
          || is_executor<Executor>::value
      >::type = 0)
  {
    impl_.reset(ex, BOOST_ASIO_MOVE_CAST(Handler)(handler));
  }

  /// Get the contained OVERLAPPED object.
  OVERLAPPED* get()
  {
    return impl_.get();
  }

  /// Get the contained OVERLAPPED object.
  const OVERLAPPED* get() const
  {
    return impl_.get();
  }

  /// Release ownership of the OVERLAPPED object.
  OVERLAPPED* release()
  {
    return impl_.release();
  }

  /// Post completion notification for overlapped operation. Releases ownership.
  void complete(const boost::system::error_code& ec,
      std::size_t bytes_transferred)
  {
    impl_.complete(ec, bytes_transferred);
  }

private:
  detail::win_iocp_overlapped_ptr impl_;
};

} // namespace windows
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_WINDOWS_OVERLAPPED_PTR)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_OVERLAPPED_PTR_HPP

/* overlapped_ptr.hpp
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
*/
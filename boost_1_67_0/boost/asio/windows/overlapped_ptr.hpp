//
// windows/overlapped_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context.get_executor(), BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }

  /// Construct an overlapped_ptr to contain the specified handler.
  template <typename Executor, typename Handler>
  explicit overlapped_ptr(const Executor& ex,
      BOOST_ASIO_MOVE_ARG(Handler) handler,
      typename enable_if<
        is_executor<Executor>::value
      >::type* = 0)
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
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
  {
    impl_.reset(context.get_executor(), BOOST_ASIO_MOVE_CAST(Handler)(handler));
  }

  /// Reset to contain the specified handler, freeing any current OVERLAPPED
  /// object.
  template <typename Executor, typename Handler>
  void reset(const Executor& ex, BOOST_ASIO_MOVE_ARG(Handler) handler,
      typename enable_if<
        is_executor<Executor>::value
      >::type* = 0)
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
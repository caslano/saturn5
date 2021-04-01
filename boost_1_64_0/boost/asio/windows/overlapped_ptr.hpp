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
p4LE0fhN5Kq0e0tWxM0ELNy4P46SWKTaa69H5rs65q3DNQ1mN4HMcxJQNOfuC+B7wHsgF1NK3LhjIxkCf2oYpzeR2gHFsP38KsSZz5cqpgHwpVLodKnHV+AW/i4281wv+aPGH8uBlR+vTFG0VwbD3PpaXSilJ3GSYKcd8tomXHDKWkmhw5SQ5T5M6MBM9d4SdUwcFLu3NXn9k+IS2LaFIDjEnZKz83/46Hp2gbmzetRWen1INlWYIj92jJAplGa517yTmohp8RrYgVKsVGg/XkAHlg1w+p1CxiuOk11o4QaswgOvqUswGCHeytWYJawQrleyZI0Rn/U4ISP8wkNb1YRzAdERcUJTT4z/KrfhV6gAYqfjAICRitzT8WwnEoYBZhUxBaIN9zeIFB3xBeAf9Y+KvPZcPL+b+mwwPaZewecsR1N1f8rp2oB9WDjyU+ghuuRIn9Krl0QD1MRKwpxjy+X+QnRZygLoxHbCKqCwKEldixwLkWHh/Ot8UPNj7D/666z4rsPF4L+0kzrj2xKA2mKfrewaLOR6oSmjy/T+WJoBKn472bKS5P5jog==
*/
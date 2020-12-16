//
// detail/reactive_socket_sendto_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SENDTO_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SENDTO_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/socket_ops.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename ConstBufferSequence, typename Endpoint>
class reactive_socket_sendto_op_base : public reactor_op
{
public:
  reactive_socket_sendto_op_base(socket_type socket,
      const ConstBufferSequence& buffers, const Endpoint& endpoint,
      socket_base::message_flags flags, func_type complete_func)
    : reactor_op(&reactive_socket_sendto_op_base::do_perform, complete_func),
      socket_(socket),
      buffers_(buffers),
      destination_(endpoint),
      flags_(flags)
  {
  }

  static status do_perform(reactor_op* base)
  {
    reactive_socket_sendto_op_base* o(
        static_cast<reactive_socket_sendto_op_base*>(base));

    buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs(o->buffers_);

    status result = socket_ops::non_blocking_sendto(o->socket_,
          bufs.buffers(), bufs.count(), o->flags_,
          o->destination_.data(), o->destination_.size(),
          o->ec_, o->bytes_transferred_) ? done : not_done;

    BOOST_ASIO_HANDLER_REACTOR_OPERATION((*o, "non_blocking_sendto",
          o->ec_, o->bytes_transferred_));

    return result;
  }

private:
  socket_type socket_;
  ConstBufferSequence buffers_;
  Endpoint destination_;
  socket_base::message_flags flags_;
};

template <typename ConstBufferSequence, typename Endpoint,
    typename Handler, typename IoExecutor>
class reactive_socket_sendto_op :
  public reactive_socket_sendto_op_base<ConstBufferSequence, Endpoint>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_socket_sendto_op);

  reactive_socket_sendto_op(socket_type socket,
      const ConstBufferSequence& buffers, const Endpoint& endpoint,
      socket_base::message_flags flags, Handler& handler,
      const IoExecutor& io_ex)
    : reactive_socket_sendto_op_base<ConstBufferSequence, Endpoint>(socket,
        buffers, endpoint, flags, &reactive_socket_sendto_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_socket_sendto_op* o(static_cast<reactive_socket_sendto_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, o->ec_, o->bytes_transferred_);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      w.complete(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SENDTO_OP_HPP

/* reactive_socket_sendto_op.hpp
P52GEJHuW6HPOoDDvM397Yd5u9MpTJ53c5pOPfZ6OubH923WzX0M2OPp/vbj+67TJQ93OM0P807W3X0O33N/+2He5XTJw91Oi/Nwj2OID/r3C33hQLHntT0xRtu+Sf+B1WnHCvUZpP9Q67z7j+L+kdaxC86m9ceOddyZivdajT+6cQRI030BM5HQMz/xdY4Ecfy0YMNmX2N1olbpZe1nWpuDOTGt1SYaWZOqPrH7NSu232dtYjQ3plmXw39Aa9ij/iC0JXN6cU4Z5sO0jrNRVle6JhbmD4XcYZxLq7m6o/LXWlffnH9jdfT59JtrkNnDPpvDjPum34Lhe02zOF9ifBCX1CPsR9gGixZ5ONDI2jwnlmaVOYj7UXD9TWQc7PfMKNvm8pS6Hj88VrClgyU5yxTn2yq90WHtCdHc2pQ/WI1+PTTqlQGzUmdeadjm6Y8hr+Y1y54MWXeiZcd5f3JMyvrPVqNcxnE9pXkQ1180C+J62jGZs33GaVL2zxptZEG5MrekDoKDH5/zmfvt+nyhlyu9fX2Lh3v7lrlzZF8IdD2X+KLP+LNMo9Zu5cxfSvKJiQb4XxM8z8x8bz3nuS6fy3m0gZ4H8f4jySXef4Zc4qV34F/EqUmyRYffT7T/iOe+2MadTt/Jq/b0et5zKZymRrBQm9jLKZYzW2sjn+nfNWsL41n1mvktVa25b56v8DkHi9++rwzZRKtYd1ksQinGO8VMesMYU/7X8W1xRIl5Xek8Ek7Lq7QNv8vFVE+jhr0j62ou7zo+qXJ61xMbNZvPe5rWD1iW5+54N3MIS6OJdGwQ2LXa9YzGYOAb+pzT2JB1CBv5HEsw+NlXa+ZWWMja9I2THNlA/JskbWRd+Ws0Rz3Sd5S9lvnC8rzKwMKhYVMd6dUktmnEZG52s5iZakprR4m/Ls0n83EOe/OIy3nLW0RMXg93d2Jsk+v4t0xyiX8r5uYcRQnbtmFvYKaOceZnthZdjpdEO7mNY3IGzRtFM4bkO7Ld1ukyd7OdaON4tYoj4Sic7T0mZ1ruEOl2BQPzHZPcZBm/E3cCTx/nzGG8ydmkzxXfOeS81J7SvUvEcgpzV9FRJyqNSfWbfTef42xETs/uHkOTYF5aN48nXP+0Jb/v4ZjMfe3pNF0PmO0lLFdlQunYW7FUHvZRPMzDvoql8rCf4pIHfnaGY1i8g1XR5phgatd6LC8PFRpvRqk2JsyvWF66hTTMjO340w/SsH+CT9b52VkxQyb42QMCrvv0A31GhYSjD6lOzk7wTt7xziA5yLdx548eHOi6D7PxHxLZoB/DXsi3+Px/9mVvje11X0Vl8rbYRj5lVOjOPz7HNrZDf2GMYHNobKP7DYqvN20jfQfCmpO2Q//BNn2xDT5GUJFQ39+/ZptKMfKx/i+FtvheYnJIfK5wjPHdaYn0Ds9TvI7z2+aL5tW1AaWP+2mienpYwDutFZnt9w8XFtZBSscC4e5b2ULRovHcoLDQP8QXae7HR3xIOL6POr/wHsiIx2dsDkc2LsuU/jJzvkWBlhvJWGAkYuRqKv/FMcM0tm53sO8xbQt/YN9j2oZ/3SOtSyMbGT8si5gUh9vvGNtIsSCOo8jGLY/07nQ4OmAyIOA26hjHnSN5rtLXZWCAOCsB1/sojg3YeGKMXo1s5C6I0YjFd0HUIpv4Loh6ZJO+CyKL7fQAgvwxlrSR/Xrjae72ty+Pue6MKYxGaCMdMs9txlzG+bBZEdtIx428TIQ2wXh/MsE7DRmLN1M8r9KzrZAF35KnfO5+yx7v9OBFQL7aPvf7TNjkkU3s405oE/i4G/HYxysjm9jHJ4Q2gY9XhTzw8eqIi49PDJn4mPi7iMuIqyw=
*/
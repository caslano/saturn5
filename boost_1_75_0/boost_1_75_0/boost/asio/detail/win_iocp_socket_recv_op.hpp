//
// detail/win_iocp_socket_recv_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECV_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECV_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/operation.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class win_iocp_socket_recv_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_socket_recv_op);

  win_iocp_socket_recv_op(socket_ops::state_type state,
      socket_ops::weak_cancel_token_type cancel_token,
      const MutableBufferSequence& buffers, Handler& handler,
      const IoExecutor& io_ex)
    : operation(&win_iocp_socket_recv_op::do_complete),
      state_(state),
      cancel_token_(cancel_token),
      buffers_(buffers),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& result_ec,
      std::size_t bytes_transferred)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_socket_recv_op* o(static_cast<win_iocp_socket_recv_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

#if defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
    // Check whether buffers are still valid.
    if (owner)
    {
      buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::validate(o->buffers_);
    }
#endif // defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)

    socket_ops::complete_iocp_recv(o->state_, o->cancel_token_,
        buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::all_empty(o->buffers_),
        ec, bytes_transferred);

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, ec, bytes_transferred);
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
  socket_ops::state_type state_;
  socket_ops::weak_cancel_token_type cancel_token_;
  MutableBufferSequence buffers_;
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECV_OP_HPP

/* win_iocp_socket_recv_op.hpp
kDtqYaXHnjQXnkVbRLirtIlJtNt0zFrm0OQ/Ry2zBhfr6vKGbq80Mdq/suzzvckcYE4psjzVBJXWUeBxZtderLvhumuOHCi2i+D32NQVFFdmjrOPjU70yY+nigs6yyg1Piw5XayO0c4uCoMF83sGF2bNw9flGt2Ze18Yx//ctEMvGpoQW+dwJh3r2qxCfrTnJi0+sfzZV6COZwd0NzVgmf6rqLj7sk1GTPd6f4jlhOPhYnTf0yhH0lHJS101woDsWaT0mPpqB4nArlmheLYIa2DHkEUc4pjhsLJB5jVSgdU8Ex2A+VJDpE0sxr+h6trbVsNsQaa5sfWgTCXs1tfGEZalINq8/optkWVffr4faQCF+ySLWPeibIcdl0PaltpB2yO8RR8wtFV8Z6VRJqs4LirantyKfyM4OuwxR76COJaT4Cow2q3hx2HY+5drQAIH/luroXCrCmvjl+lCcbNjEoWeLGqER0WLfskhhTmvi3IKyvDcLcJn2X7auUu7uB37KXXr1/Hp6VqDz2d8BZewJeWk4qyxYtyiPMYBdPUXGlVRkt7Y+EiCU3M+jojcyUHpkH9w6hWefs9oCmmXRRe/4ch9l1f3WvqmmUbexK2KMUim0eDrfytzdsxDG0a+PsBIyVrr9eCmLFlvjd1d4OEknk+vcmovik7Ba1Rl6Wn5y3ZJ6Ux5nFhaQCXrcLrq93xljgr4lZeBu1f9N1aT
*/
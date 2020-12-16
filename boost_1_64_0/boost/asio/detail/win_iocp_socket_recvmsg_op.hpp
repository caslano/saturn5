//
// detail/win_iocp_socket_recvmsg_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVMSG_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVMSG_OP_HPP

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
#include <boost/asio/socket_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class win_iocp_socket_recvmsg_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_socket_recvmsg_op);

  win_iocp_socket_recvmsg_op(
      socket_ops::weak_cancel_token_type cancel_token,
      const MutableBufferSequence& buffers,
      socket_base::message_flags& out_flags,
      Handler& handler, const IoExecutor& io_ex)
    : operation(&win_iocp_socket_recvmsg_op::do_complete),
      cancel_token_(cancel_token),
      buffers_(buffers),
      out_flags_(out_flags),
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
    win_iocp_socket_recvmsg_op* o(
        static_cast<win_iocp_socket_recvmsg_op*>(base));
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

    socket_ops::complete_iocp_recvmsg(o->cancel_token_, ec);
    o->out_flags_ = 0;

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
  socket_ops::weak_cancel_token_type cancel_token_;
  MutableBufferSequence buffers_;
  socket_base::message_flags& out_flags_;
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVMSG_OP_HPP

/* win_iocp_socket_recvmsg_op.hpp
PdI4FdlqvzSaHXQs7Tfc6SSs2UNnl/ceOsjUfw+dLI89dHbVsofOy4nuPE4hjv1+eZSRbt/7QLhax7k5X/9x7glRjHObvewaes/NWTfWb26OcLXNzXG+/u0mmrm5mC2VcFsq8UNDx0c2fKF0xB//9IcJncaddvTudhP8xpJjNlb+U22s1GZLRe3i8gyW+RIz7p6p4+W7+V3A7wTcc47fv7B/q40Sy35f0/fEJFx7fh91jM12hxmwv46hDdTjQ2A7OFSPj4WdYCHsDBfArnCdjpXdC/vomPgA+AwcBHfDIfB5OBzuUf9L8Az4uh5/G47QsfEz4WE4Cn4IR8P4kD4pJA+Sjgw4HnaEk2FfOBVOgd3gOXCSGQPV57v2ixtqsd1R5ZAriJCjXI1cdZRy+6OUox9VOfweY7lZUa7RLNhYs04zfhN+XO7Guo1fFjjGMEs2/nvWbl6xMbZ+c+3Guq/hfIgw1RujW8v52sYTj6Xa6zkPboxuTWfLTfa6To5vOvm1nS/D/E2nZm1n4aa6r++sIIy9xnPNplOzzrNqU93Wem7f9L+x3tO51vPoppNf75k3n7WbuDW4rbh9uPhLY2O9sb/YX+wv9hf7i/3F/mJ/sb/YX+wv9hf7+7Ln/0vnzT5F8/9P9mEs1F7/r/ZGh+ncziDcEDwp35L5HZncUSWAmjXSlxRX5MgaS5ctAF1bqWGJMdtqRLrM/JXOXZnzZq57WkDXHYRWKSadcM0qc7/e68Wbhs9lEU+iyecOtds5WvM5AjecsIU++dTltQuXlFX42TzQsD2c+2CafUEq5Vyy+llFKv6GlqyXDnC+ga6vTshxzLX6r3tZJeGbqN+OL1jvsnKWzTQd5miigYK4PGSr3WUjpSJVQJdhR66dNfOzmt5Q2qwTpC0pfF1oWNoOa9rsSJrhRpK2vbWkTQ/4pU3DptQ7bWNtmwLx7rSNGkaaa0vb15YUlc67eF7xosW+6Tt8kumzy26Gzru300BtcWNDbXu1K32sV9L01VQPSduYYa69STRsO892reeiTjfxk26Nn2Mp4W3XlPOxBHf9zCdsXm35kAPzWF3kmxfC162OmvRqOY+3+1Cd+0/XQK01fQW1pE+2bjeJ9E2jxpFe7zTadSG3oZadBkrGjUO23CeNUg20//NJm4YN1jttto7BvoY+azRX13ON5ur667AM9dFh2ZHkvZaxanX91zIStjYdD87XX8cjmrWMMV2IcF2IoaILMbx8Q+LCt3/Zb+ZFUxq23d/1vZjOw3+qzkN99pXRZ6HvfjC6NkjfUalDshYqfG3QOF1DNh6mwgmwJTwHtoETYWc4CXaDU2APOBVmq1yO+gep397joVCvO9py7/Fwul53uF53hF53LMyCozXeMXAIPAuO0PP2XifVGj/xuPY6KUEuxHkwAc6HDWEpTFLb9UH12/Ht1fhSPOL7isY3Q+ObqfFdoPGdD5up347vcC3xFWp8RRrfbI1vrsY3R+Oba+LTdxLYziO+9hpfB9gUZsJ02EnvY0fYVv0aH+8M/uXXTePrrunroenrpenrCYPqPyL50ec7TNf4GsFpGl8/jS9H4+uv8Q3W+AZouk+DqXq8BRwEW6vfTne5Xifoke5Wep00vU5rvU4bvU46TFa/0X9ZHeUeKCeQOxAfnR7KqVg392Xpm/y/65rUVc8kGv2SaHVLotEridkK/8+1Ff5F643Ubie8bjoj2eiHzMCtxG3F7cMFS7H1jSvB3YnbjTtcGtMjif3F/mJ/sb/YX+wv9hf7i/3F/v4X/r68+f/QGvVTY///MYf9/50BXf+Pa6FsEFq3ep1Z/6/XlhW5bnv+umb+Y5HP17kNO3yama8esSrkDxg=
*/
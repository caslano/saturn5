//
// detail/win_iocp_socket_send_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_SEND_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_SEND_OP_HPP

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

template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
class win_iocp_socket_send_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_socket_send_op);

  win_iocp_socket_send_op(socket_ops::weak_cancel_token_type cancel_token,
      const ConstBufferSequence& buffers, Handler& handler,
      const IoExecutor& io_ex)
    : operation(&win_iocp_socket_send_op::do_complete),
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
    win_iocp_socket_send_op* o(static_cast<win_iocp_socket_send_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

#if defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
    // Check whether buffers are still valid.
    if (owner)
    {
      buffer_sequence_adapter<boost::asio::const_buffer,
          ConstBufferSequence>::validate(o->buffers_);
    }
#endif // defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)

    socket_ops::complete_iocp_send(o->cancel_token_, ec);

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
  ConstBufferSequence buffers_;
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_SEND_OP_HPP

/* win_iocp_socket_send_op.hpp
t07TvfaGa3qH4LqR3sJrve0Uz9N1K6mJsmfjEsrApHuRhOlltTLp1ni0L82TfNr79dGXmvM5Zlz+FvEnm3b+WB3aNGkif5omHaPMkzzLNcPaeUvdjy9Lx1/b4j4cSp26NnJeQrYylfv0wdCwvUxVtoU5Z/YyNedS6rWXKXE59zJV/+yw+7bdYz/BZqHn4LXhY8gyfuywTdvEvV6GMPVf19PEZ++1dUF3+loha13nSp9rfJt+xpVGwpnx7Qne49vI1H98m2u6xrcnuMe3TfmXeOzV13wYsXrlT6qfb/kTptb1Spyv/3qlJlGsV7LvWV5Tb5u0edf52aSVVyw/m7SEq9UmLefrv69iNDZp7Xwd8shXMuEL/fNl5iKPDvXcV5Gw9d9XkTgj91U0c0N7Pfb2a01aK33TalqP732odLSduGHebafyJNpOgodNZ67ja9N5c4p3Pau6rn62j6tqr2ec/2JtH9v3bmVzd746Eb7aN1/haxk7uvNG2BPsy3gSfUPHKPqG2Hxe+Hze/TKf131z3rUvlty+7anh88+/6GdLfxKz6/zfNs/nP59n1iMyfqP6NBb5cvze5Pj9sMPe833md7gd6Acdvzc6fh/BHbR03A1O1Dm6DH7vw1k6l5cCO8IOMBPmws5Q9mSAM2BXeDHsDitgD7gc9oQ3wl7wVtgP3gdz4ENwINwGB8GnYS58SePZD8+Ah2AePApHwtakcRRsC0fD3nAMPA2OhYPg2fAMOBieCc80azFl/MR3LWa1rrl7BraGu2BX+DPYCz4Ls+FuOAD+HA5X/xH53tLxBDhO428Ix2j8DyIX4hbYQv1p8CEt34dhX/h9OBo+ovHm2t/vOjZAvPLtkA0tXbMq47ywFTxH4zsXdoIbYQ84DY6A0+FoPT4FztE50mK4BV4MH4Ml8Ak4Hz4HS+HrcCF8Dy6FAdJwOUyEV8Lm8CqYBq+GveC1cAC8Hp4NV8OJ8AZ4LrwJTodr4Vx4MyyB34aVcD28Bm6Aa+Dt8C54N9wE74WPwPvgE/B+uBduNGsy9RsWnucx5/2orjHdDtvBx7S8Hoc58Al4BnxSy20nHKf+AvVr/dJvSr5pPerXr7R+vaT162WYCV+BneFret1XtX79Bg7R4/Y+mFs1/iyJP3wfzBd0LfGLsC3cAzuq39gav9bf1vhnx+V4qEQnlxmlXJ6Rw1/LPpSFUcpVRilXFaVc9QnkJv4P2Fbf+VL08+8x++ox++ox++ox++r+c/j4y9hXE7cfZy2MszJxebi5uJW4+3Ev4A7j0ss5hyvFrSv/z5nr95v/n//Fzv9fuGxWCEUnPfffmd37n0nnOfePBL6Z5Rt/9FnnTJs1cvoMxsy/NquiwhL9gHW8+5v5tIDayrD3S8O9ybdlzjdkrCAsEh0blXHmJm3CxqBVvr35/r+0DuPMxCXjzM75i/2ariQN0BC3g8QVeqVrXkVtNqp0zCvYfDfh8z4NlU3pwjlFpQQLn1uc2MBdFu9SFuVe15SROcvkt6z2/JKG8PnjbNXLuE3nMW/EHeJaVY5rFc2d23/WouL5xXMqZlE3gEs3Q+Y7HpcwI/Re2HGk6fkA/UfI38wxj0xs9riUke+AX+4rf0VLGHcx8R+V891c8aWatQXEVzNVa3QanpIwX2d/+wSxA1lA2V5o7xPYsCyYYM8t67lKs/ag0Ipce5ChMruQ2UDdjeuWfFZifLBhZ52/Xsnxatx3RJdgkPOeSHjn/OyhKNctNGUOTvLJ63XxokWuuavw9QvkP+L+5ug89UN6f+/R+1t4ecT9rVi0ZLG5vZ66Nxom3cydLhP/aPUHrE/E39Lv/mr4rlaGzm3dIP5FzDUFSW8Sdooaue8=
*/
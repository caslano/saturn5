//
// detail/win_iocp_socket_recvfrom_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVFROM_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVFROM_OP_HPP

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

template <typename MutableBufferSequence, typename Endpoint,
    typename Handler, typename IoExecutor>
class win_iocp_socket_recvfrom_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_socket_recvfrom_op);

  win_iocp_socket_recvfrom_op(Endpoint& endpoint,
      socket_ops::weak_cancel_token_type cancel_token,
      const MutableBufferSequence& buffers, Handler& handler,
      const IoExecutor& io_ex)
    : operation(&win_iocp_socket_recvfrom_op::do_complete),
      endpoint_(endpoint),
      endpoint_size_(static_cast<int>(endpoint.capacity())),
      cancel_token_(cancel_token),
      buffers_(buffers),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  int& endpoint_size()
  {
    return endpoint_size_;
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& result_ec,
      std::size_t bytes_transferred)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_socket_recvfrom_op* o(
        static_cast<win_iocp_socket_recvfrom_op*>(base));
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

    socket_ops::complete_iocp_recvfrom(o->cancel_token_, ec);

    // Record the size of the endpoint returned by the operation.
    o->endpoint_.resize(o->endpoint_size_);

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
  Endpoint& endpoint_;
  int endpoint_size_;
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

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVFROM_OP_HPP

/* win_iocp_socket_recvfrom_op.hpp
0LXqaLuSMLXZO+J8/e0dRWO70rbbkuthV3DmMP7dwvU9bSaevB24lKD7mi2GIel7TbE/5vdOo+HS9N3TZX+M8/W3P8b1XGXJNTzt/h30sWeYd0vLetkzJFxtdtU4/+XYM1znYbdvBuELffMlzyh5P9oiz9I5fI7wGHfajItI+/Qo0m7bnyJO0qlxRqQ1t6m3jcHKW+pnY7Dylvr3I8a+W2T997G/V3VL/ezvVZ2gnlSdRP2Ppp7YfcmhZt7296pvqb/9PcLW1k9yvv79ZHT291JqVm2H/qv+INkkz9Rhwu+/xej513xOEJ25T6qHb6+7TLy15h2pOf81fxq+m+c3wQT7vL4zHJN3hjKxC0Fa5djncqxUjmWG2aaXPBg7Dcly7dZWQyRl7QaZOJBi68Hnutdyq0wQ/6vyLdgmmNDEctmPC5V14QneDcpNPdLy4Niy8Pd4835MHkNyIb/k53Pxlxq9+A2BuutHe+t3++mt++m/112vfI/ore987dXG43/1m78FHl1xILFL0jl+etl++uZ+evd+etZ++uZ++vJ+et9+6wP89dY/Vn0ZS/W1X4Oqr21+b1Y9aFtHexlUHW3ze6/j9x7H71cdv1+y41H7YZv1G+FX+rsMp/oXOg6EbEDOhelfjNR9usfAsyBO9HXOhlNhPpwOx8Hz4Xg4H06AX4OT4BI4GX4dFsDlcCq8EZ4D18Np8D44E26G58NH4AVwB7wQPgW/Cl+EJfAtOA++DWfDv8A58H1YDD+A8+ERWG7p+IGOdWzGJePmaj5zkOsJT4N91I8Tfx4cqPkeBKfBwfASPb8UDoPL4OnwVjgE2vsdyvcx7CXXDd/vMBU5eb+DnWBL2FX9dvhyDd/eI3xrDZ8OW8I2MB3iTPgqDd/JI/wCDV+m4RbCduq39Q73avjHJHy43uEyDbdc68lKLa9r4AR4LTxfj8+D18NL4Wp4ObwOVqp/LbwK3ql+ow98s9EHpp3464Xvj1LOusXI0Ub89L1xUcrlGTkpD3996ijlKqOUq4pSrjoKuXLcfpXLd7cP6h56i7Cz1rMusA3sCjuov5v6e8Nu2n66wwGwN8yFPeEo9e+Ks06JzlO4vpNb1+kQzq3j5KPfFKbPdGp0mUSPKUyHyaW/5NBdwuU59ZW8dZU248L0k1y6SW69JLdOUrg+0rSlJ9ZBcugf1ap7VII/UueoOiSv+kWqW+TQKaqbLpFbj8hPh8ilN6Q6Q+H6QldcFqEnVEf9oNr0gSYaPaAvZl9J1f9RnZ9wfR+3jk+4fs8Yfm+/hLqIO4oLlrC/I64AV45bh9uBO4ALzmPvRNyFuJW4h3Avz4vp6cT+Yn+xvy97/h/7ejL9f/Lz/z/vY5l9xaq0O5sVsqOh7BEao1ntnFMRewghQ8OhVJQToW2/DpllOnZhh+lvbNJ8IP6+gfaBGvugWTIGQgyLdTzDhBlibN98Iv4egRaBBE9bpmkw9QYzZ40fSzlrxOaf515kyXLuZeLHb2TzeE9M8bV1MVtklhm7e5ni/9waxbFfW+0k3I9bqc1D67idkT4i9zDh8DvCNeHYAStZwsW1MbYYzbzu+zXlFujAQqM0nXOvCK114T6Jod4kt62+Diq32ciNFVsalT+u3a7vDv1efk7sYBe6x3lU5qh+mxPj88FGTd17CahcOvXnFyG5Zis6uvZjU5kzkPk8S+xufxgZTwb+BLXRG3IPEdeWE9u0N3OqefAtGTdaZnQAqGf4pZ6FzddUxLvGI9GNt1gg5zFfI0OsXENsuLjGITVMmtpqcY2xcr7+Y6xczzUOyTU8x+LTE9x5mkT+q0yedHh10siCgnGTz9ZpMkn3BPf4KuHqP749wWcPnU8=
*/
//
// detail/reactive_socket_recvmsg_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECVMSG_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECVMSG_OP_HPP

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
#include <boost/asio/socket_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence>
class reactive_socket_recvmsg_op_base : public reactor_op
{
public:
  reactive_socket_recvmsg_op_base(socket_type socket,
      const MutableBufferSequence& buffers, socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags, func_type complete_func)
    : reactor_op(&reactive_socket_recvmsg_op_base::do_perform, complete_func),
      socket_(socket),
      buffers_(buffers),
      in_flags_(in_flags),
      out_flags_(out_flags)
  {
  }

  static status do_perform(reactor_op* base)
  {
    reactive_socket_recvmsg_op_base* o(
        static_cast<reactive_socket_recvmsg_op_base*>(base));

    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(o->buffers_);

    status result = socket_ops::non_blocking_recvmsg(o->socket_,
        bufs.buffers(), bufs.count(),
        o->in_flags_, o->out_flags_,
        o->ec_, o->bytes_transferred_) ? done : not_done;

    BOOST_ASIO_HANDLER_REACTOR_OPERATION((*o, "non_blocking_recvmsg",
          o->ec_, o->bytes_transferred_));

    return result;
  }

private:
  socket_type socket_;
  MutableBufferSequence buffers_;
  socket_base::message_flags in_flags_;
  socket_base::message_flags& out_flags_;
};

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class reactive_socket_recvmsg_op :
  public reactive_socket_recvmsg_op_base<MutableBufferSequence>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_socket_recvmsg_op);

  reactive_socket_recvmsg_op(socket_type socket,
      const MutableBufferSequence& buffers, socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags, Handler& handler,
      const IoExecutor& io_ex)
    : reactive_socket_recvmsg_op_base<MutableBufferSequence>(socket, buffers,
        in_flags, out_flags, &reactive_socket_recvmsg_op::do_complete),
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
    reactive_socket_recvmsg_op* o(
        static_cast<reactive_socket_recvmsg_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECVMSG_OP_HPP

/* reactive_socket_recvmsg_op.hpp
0hztB6ev39jwNWAm3pH55d65tOKCWEnYnN55Ze837dyANew5s77u5kXni17sBJIVGvDTQMzdnO1hMXO/lQ93jI/Vrdf5mQW+btZSNFaO47vJQmFFfm366Z0ZjBgmcsy80GzzQ9LOISxag92KWj7b1rWh6exoioptjpjepj2B9254OhuODluQuNzKka3MI4xEjKdpcAwf2Sxeg00OmyVJGzgJNkembTjFsFk6jU1eHctsXMvSNvwzHDbvSNr4c+9HTWeD+6KOTnIzRzdODSCFcUzSRu5JemfEZS1JJWIyD3OsY7Q0xMySFVsoi6kEfq+qHqds8Rywr4+1G1mzPrG6iYfJpja9TfENkOpzfQ02/I2Q05F5drJGaczXJ1rmg4yBbs37uMepeMkny2M9t3E1HENdhx+Pc7rbmZebuOh3wgrH5BvyhGjFgWOTVfh00ulcnwwgvenpVO0p3lasV+z5j1M+0/6jdB3vOE1rkNZ2muw3y7WWTSKDspa7E3CzzAjvPteHbsCnzDcx8qqpxbatXSk2xm3kE1NVmJ0QM1NFmK2KGFUNYquFGTdWportps0O/3Y70TFZl/0uT5uq5hgznuR0Tnq121lOlQJpPzngUwfSJgR69t0RM54hzHGeonk7d33PqUofzSrentLTHMPsN/z0Hk/vTjHB3lFh3aafC+LvizhygeffH3LJCcX9Acex2oIiZ19/0LLKwnlzZ3AePgRtlusisX/U6bqLZPYRx/gLdYU2LuOc2BSrlOf3Ir6POW7cSf7B3GukVxor7dxrzHIuCA7zk5oXGM+dHur7FZtVWm49xBmKr6iPcWrw7KccW+mPEtCnnKk4UiMmCP8s2BxY6R0ZGaZVgubFw95Rny0pDQ/MXVZRZ8I63j8wz66xRn7PCRnGZJ/RerAO+VzHSoN03a5aB3pexCQd50dM1rtdoFmxkXKkhO2zzC9MctnffFGSyzrTixVfYlZsDql1mZ+NmPSll0RM1mV+zjHcqtk72I+bNXHOCdtdOr2dt4fh89PbmQSxzWXT27gx8OXOZrhk5hcqbt0s4rkixcdRpZHvKxM2br9rwMK1tVeleJ65enC15VSNS/26Pl4TMtTHLwa6ju9anw1LhnGWa8R1hrmtvD5pI/XrhiSX+vulJJf248tpLme4ejyopAjjprSNawduTnN3J8wtjpu2mYfZjVFKQ3FkC63R4H212m4G7FyN5jr9VW0Dk2JRSCdr2vNA+W7TlF0+aeKqVe3ega8nbLrY2/0NYRiONsYatar7Nnurz92dD7d5ejurNaYaJml8f2maYf4O95dqG1mGR89/K2KZSjb21sY27nfPdyyj/Jgibk3CgpLA89FiA6eaUkTfe4ewjskw2d/ptKL75tvp3Hy0x+Tesbs8Xe4du9vTl3h7c+9xDCNG1IfvW53rCedKnJKvhbT/QOy6Uwjzh07DCBO2P7I63xhE2o+dJn3OvVajdxquzJndp5lLD5fjTzSzK3WrxWpQk2Xs0/qptonKGveJxjYoScxba+4qP+fxfsfk/I5fOE3WDjxgNd4fUdxJRnE/6PTc/lTlU2jQZvxSc10eSNtDjssVtpb9SjNbD8F+rRnK3Nbv3whL+CznuWtlgwaD9+g6XfaLP+Jp+oVi/jvL5T3lSgv+qOKTUxOZKgI+v9Xy4LvzY07vtCojZfPfiDcv/LjlGB7b/D9BevS10mvL/5C2cW35H9Pc7TN50nH8PKZFjpivtsy9o6z/2elZU+tPWd29I5yPvzh9ykQQ3Y7DZ7t6NvQCUvqfiXV6Nkecz/o8N5z056xOUjHYxvmupLvzrobMiGdRvxofvpDk0n+/mOTyfr1U8EULBvqWuaI=
*/
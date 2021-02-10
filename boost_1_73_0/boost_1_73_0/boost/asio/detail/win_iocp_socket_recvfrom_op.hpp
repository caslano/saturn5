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
PKonCf5jrEd0ii0pi6CnHf4peeeXzobIPhb9HLlmY+NwLWqLBHuOXzeK9kPH9TO9iN0COzIM88OfGK4vf/vX5cfh7zC24xaUeEmLeHIImYzMh7/+B1BLAwQKAAAACAAtZ0pSK4kvetsAAAA3AQAAKwAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2Z0cC1hY2NvdW50LmRVVAUAAbZIJGBNjsFqw0AMRO/7FSLn2LTkUDClYAylhRxyCPSseLX2kvXKrOSE/n1l+9KTQDNvZs6chwaCzhX2PS9ZXVvs8e5R8cN9UZobaHcF1h+IlpgHdyms3HOSBj6vF9d6T76Bt/r1VL+4DpUGLr9bMOCio6uqyv2MlAHzCoBQeVABlLtA4AIH/FdyAAxq6mIuyDiRUR5mFHly8TCiuBtZ1lz4Ea34CDpG2ffZFbIcDsF4m2oaQdt1V+h5miyodu477ATPGjmvjFV5A20TJtA4kRw3MKFYViZ4xpTgRpuxdn9QSwMECgAAAAgALWdKUkGJ9CcIAQAAgAEAADcACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9mdHAtYWx0ZXJuYXRpdmUtdG8tdXNlci5kVVQFAAG2SCRgTZBBS8QwEIXv+RXD
*/
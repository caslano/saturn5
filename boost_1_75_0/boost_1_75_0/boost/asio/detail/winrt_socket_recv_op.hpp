//
// detail/winrt_socket_recv_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINRT_SOCKET_RECV_OP_HPP
#define BOOST_ASIO_DETAIL_WINRT_SOCKET_RECV_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/winrt_async_op.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class winrt_socket_recv_op :
  public winrt_async_op<Windows::Storage::Streams::IBuffer^>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(winrt_socket_recv_op);

  winrt_socket_recv_op(const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
    : winrt_async_op<Windows::Storage::Streams::IBuffer^>(
          &winrt_socket_recv_op::do_complete),
      buffers_(buffers),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code&, std::size_t)
  {
    // Take ownership of the operation object.
    winrt_socket_recv_op* o(static_cast<winrt_socket_recv_op*>(base));
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

    std::size_t bytes_transferred = o->result_ ? o->result_->Length : 0;
    if (bytes_transferred == 0 && !o->ec_ &&
        !buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::all_empty(o->buffers_))
    {
      o->ec_ = boost::asio::error::eof;
    }

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, o->ec_, bytes_transferred);
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
  MutableBufferSequence buffers_;
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_WINRT_SOCKET_RECV_OP_HPP

/* winrt_socket_recv_op.hpp
2j+jQV828PQcH6RvBpKbB2ZyYUbY5vgfN3IITKu06/gBLsx+rlZQ6Iv4PdKfNeo5F+T0l8nBiG8EtupOU0ADF7Y47Um3quogsGZJi7kaMSDV2XW6TRW1b4nPgkSbGEhylPR6LoP068exkztexsD2KaXLuP2ofmuTbSK8GDgfEqAjEdxNYP6umQ/nxsLUJwvHt277SWDme5s22MaCpSLHZKbfAIG1PUzpDY2FYEX3a9s/fySw94l2IS2x0PleyjbVvp3AfPb2W2nFwbt7U9+IGKHxqgR3VbWLA0O/5O49IxD/EmW/KsPj4MY7ZcewcETfmjkXn7XHweoghS3SHYj/mXUbHZnx0Hiqb46OP6qf3aS76mg8bBheVHWyDfWXiMk+k97FQ4XE/ug3HW0E1ntUvaczHkKuuzSNnYLac1/T/KKFCYD5wOQPH3oIjLiSGOOcACuflx2aVNGM9Ptk7Yv3CRDntFs3uROVX1ETFvgrAb6s7B4w+Ir043bbvGtEIhj9GP6VrYDk0VTretk9ER7erNL0fo7GlxCle9c+JkJhat8OHW8kDwne26CBRHikqPnw4tUYAgtKTw/RSYK7cjLV85RQ/eWMjnivJDj+ZM6OCYao/MlhK0pjk+D26itPTrej8Snr+ycR8WTozksa/q4ii8C4++/OWJEMG+X6Xz+P6Uf6J51jfDIZjK9rfts9A/F7/rzD2aRk6L93uXqE
*/
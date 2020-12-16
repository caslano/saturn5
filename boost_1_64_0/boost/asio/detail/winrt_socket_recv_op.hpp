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
5ocf1AAVhStL8pebnoFkPq2lsDNcfD/zsbIsn0Emyf2Z8l5aRf5UdbmyWfbDv9JDbKt3jFaOqqwhaPlskiOPlyHbyJXkz1PJj+t2XxL1R9h+Y8kj+yKXZbvL99USsilw2bW7YdymF5JdG2e88qFDW4/+m0Sqz3CnBXjt4LuK7I45ojG6KILs0FqT3TbHQKy+8Ia6W7TlVB+Xku1Cl3FeeITQ2ad97zu3Kan6Nlvm7Xu0/4hzM1bwsWy3uT4oIrv5rqba7WVkt8BF/ebdSdSM29hhpjZKs9mZyG1mtOdlq/Y6gu3qErn9DfBsdgeZ+9fj2M7VU2sXq66FnTtgXTJgM9+cwyT15GO3qdouj2uwqe6pxXNdfBNtO7dVIF2zvyvhqPPfxRWm7T7X8ja6llK3kescdhbPi/688wW035uk6/Pn+z7P8E7BOo6mdr/Mt92ndUOniPuN1t7w+qcm+vp/bfC/b/BP6+nrv9vgX57k679H+n3HNO1MNveZZok+oGSpJdMwrom/GQ8w6KfAtlENGey315Ch/S3XkBlwBhoyu1LMaR+M48WnyLSbv43w+3qiIQ8QptE8wH77PKD9Lc+DxBbkgey3SjXnwTAcL8c6D8oVTv8QQ/pzmkh/ThPpzzmD9A9pQfq1bwbbe5nTn43jefTp15X94YZ0e5pIt6eJdHvOIN3DW5Bu7X3iMK+xfxP3U10JFy2+S3nTjYpqZf6SCvGoS4+xxmc22U/1V7JfpkyR/VTaMbpSmHL5PYLzRO6Pk23mfvKXY6RuoC4MnVa+071ANpco53EfXo48Tiznnb91uX5MKaeF86/c0HeeLbdRXHzqzV1p5nIzUowFTZX6U4Z60zwmFrb2ulO0v+W6UzhX47pTnI7KPuZ0jEY6amQ67OpA89ihmibSU3MG6cG5GkuPrM/Gp5vTM1b05Vmnp1yx+fZc10Ra6s4gLThXY2mRdZO7rzkt45EWpZdMi6ybzN9z2c4+Ddjf8jTc0WT58tYzB/t5Az/IY/nvBSeKfgstDSstyxfFeVuojDOnSQvXSb63TCb/NvSkOWzHik2S4aJlnTOB/L9WO1D/uNTRKinQ9ZUUyXARFK4U/rEynEu39vqK8qUcZroMM9Y0ZkzUs7+mfW3VMB5ftqs3vUvhaDFkX0Y6YeWyfu1L+y9Bn09b2ef3Ph1jmnxP3k3+ZLx/fY7IxPA3XO3YSTh2F+M3W3n8xyhsDc7Yhbdp4XpTOHoHQDkM6qeNTypCt57b5fkOsNOc4jC9+tn3G6TBHwz/rci/zeFe5tNv0zbQ/z43lBlZDiPo3dw8LifCp9+Nr7n2/C7XKMc1NWi4Lc/0nvASbjOL4dbipbA+yLIsy364k9ZaZxyur48+nzPQ9C2A7brKsqu29o7/HomQhvtEtpc/UpiFykStvZTHibMq71L37CTZzFRGcXteLMPFymt9SRqcH9+KNI2/kzYaf0irz/rw2RbXb7zxOhnql6EDzLp6ncW3wjRNV08/LaMAk6sqqAxwH6dRW4/DRch7V5XjPXX75Lhk/3X1vP1DfC5fXT2fMnbYIj1JSI/HlB4eysJlrMirkVe6QnRN6dLjMcR5th9agNp1wzERPz6m4V5YP9Acz47iucE6nqtWcJ6HDzHlOcK0XG8Rx7PUW5yXZY5fCmz3WcavbFV5kW2Z4DARumfgsoqV8v5s2C/HiTQj/jifUW+Rn91wDkOavrVIUyTSVG+ZpvLSlRX2aao3xPm2FsZZH78XB5njFyueV/pYxY+0/OzKBMI0sb5Ln5ZrXIYPaVrjUtb5g611ReP7NF9XNL5Py8u5na5o9hBrXdHsPs3XFc1uIs+zzyDP/dEVzdCeGS3SdFQ=
*/
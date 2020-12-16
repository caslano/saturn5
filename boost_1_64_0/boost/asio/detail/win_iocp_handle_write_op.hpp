//
// detail/win_iocp_handle_write_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Rep Invariant Systems, Inc. (info@repinvariant.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_HANDLE_WRITE_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_HANDLE_WRITE_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/error.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
class win_iocp_handle_write_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_handle_write_op);

  win_iocp_handle_write_op(const ConstBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
    : operation(&win_iocp_handle_write_op::do_complete),
      buffers_(buffers),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& ec, std::size_t bytes_transferred)
  {
    // Take ownership of the operation object.
    win_iocp_handle_write_op* o(static_cast<win_iocp_handle_write_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

#if defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
    if (owner)
    {
      // Check whether buffers are still valid.
      buffer_sequence_adapter<boost::asio::const_buffer,
          ConstBufferSequence>::validate(o->buffers_);
    }
#endif // defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)

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
  ConstBufferSequence buffers_;
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_HANDLE_WRITE_OP_HPP

/* win_iocp_handle_write_op.hpp
9BNH0MYRn6Y19Jvw5OnudP0VWeujkHRpOUdLm8pHL2f8G17On6TWXc5OfraUB2IY3Ai9dzAVziVzuwJ6TOf1Ka7/+rhAmO6yfmCr5n1AcujeujFG7iSR26HjzBSR0zPA9btxuc17bFl/ow46f5gk9qfiniAXn6Cb5RjPC77GsVW6T86Ju7fl6H5JecC2/+DJIMZr9PtzeZwlJdJB073mXtEhGGN/DTnOSuErxEGr2BPvU71AznugWR/RUeemO0haHogr88ywFninW6m+Kz0HY66xbox9w+qgc6mnVtsyw9Gbs9o6yRNrXek52/J723tS7DhM+n7EZxDpa2Z9aT1rzrzf+qDtl2aXhbTJ7e4R2bgwPUUy/54jfrPizrIyYx6PedDTQtyd+LeT/2Ue4pFvEEtE9vo4pyzirTlm/9zfpCzai3aeFF2/mHCffIeKOeg9xjrNl2/dF5NsdVC9S1USV6+48cznFnl+9M6MOcWKj23B6sJh9hor+WsqaajiWbnSCriLh6btQ9K2RNYdzLXMWkQp49bwRYl/b6wXver9cE31LbO+8y2yfhUzSdLQ2tYAcL8t87T3WL613kD9+5ISO8fTKRCn3GuZQzf7856UOJvHjYoZpt8JnXxkxnWwRsXcFWOnx5RxH9Hdq9/crpay8MWsY355lOc31keeVZ5tvvYST7L9BU3SMtTTnpbsbGuN6F5LS7TLOLCVngOZ5kjedd58gJT3EvLXyDrZs8O7NOYNs+dwj8QV742x0tEcMgtdIs+Sh2Fyv0U3qKS5s9VD3AJlulXcUuNm8HyUk8ZbPfO87WPSrVNil1vfx/qkLjEdpPm9OC6SzqcOuvczW9I2PdbRg/mgb5gVQ7l3tP1NmY2MW8+1NmI2Wb/z3cUu06axTYN0U8l8sjzr82GEb4lGt9G7UrZDfH2sv3udufrHHzi0puph+dZDG2FZ5tyRhyUNreMm6L08x6RrYFyyNUHvpUlL3nxNy3J46B4z5CieqfqsGJ9IOn7w9WXP9Z+sZM8X3OPrfJN0Hax5Zqm3s+R51bqr9SxH4s+WPoK97/QXu2mJe8m3y47+pkH6UCY5+xpVrk1J4Ox3v2+2P7a3P3Zpsd/XCHV7EdfuaZhMwnyVJHpIavy+Y9x7+1WuoMTRv1TIXj+/7vULlVnuyCx5wiXTVWW2zuRa6bbM13ExKAX0+o5NGMGvdnEx/uZUzDB9pe7vfFrvP5V2sUTruvMM/0ae4WutvpTrMo9rTYS2u71EtqPqhq1dl+sBuU5Ply7X8RJHS/k+uIJ8L53pfA9emutaq6Mya2c6ulyXjnTpclWZLTOdPZUJrj2VweVYU0qbkG7LraLkGrfyJYE2re1SXPSQFVqOCe5yNN9HL5N8fOvJtG7UPsUpy2ekLOdaZ0tZRltj8LDIbvEcQ3jdky5lso18rC51ymSZW7+tymwsNWXycniZiJzzDCC3QuK6NNvMX6rcVOwkTfZdnpgeatYnBUwcv/Pwv7anXW7I6m8o7k3V37a/GUz9VrehjjWGq81ZMLFJxz0Q+t1+a5T10TvggGSzr1Nkd8EUcQt6l9F1ruXyPb+COu9P+tDeWyVnwc3rF9QziN9H+GUG/E4K8pNr2te5M+w73XJ1C9bPmw3nSp6kTZK9nwukPbcsmjex/1rtPTIC9ufD7MUIBtsXh9nfxB4cX1Z1qP8MYw8dW62a5dZdtLsV9sA79Lx+kU6wQkZ0AoTu/dEwrY2f0bFl/A7pZvqqV33WbQTeoYkrWAeT2qeF5GPK7Mj5yNJ8nHQY+ciqJR9Z/6J87Me+x8t6kVjWwnuefWXyp3eWtNvz49VVw9/o9OAX1KkY270i5bKvFk244fw=
*/
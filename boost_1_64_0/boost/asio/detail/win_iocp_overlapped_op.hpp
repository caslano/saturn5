//
// detail/win_iocp_overlapped_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_OVERLAPPED_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_OVERLAPPED_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/error.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename IoExecutor>
class win_iocp_overlapped_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_overlapped_op);

  win_iocp_overlapped_op(Handler& handler, const IoExecutor& io_ex)
    : operation(&win_iocp_overlapped_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& ec, std::size_t bytes_transferred)
  {
    // Take ownership of the operation object.
    win_iocp_overlapped_op* o(static_cast<win_iocp_overlapped_op*>(base));
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
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_OVERLAPPED_OP_HPP

/* win_iocp_overlapped_op.hpp
KWBCHXk99EQoE8xiv6LzYqeBBqyheUjYUk8dqdtesLuQFMUkr2hK8yTCs2n7tYjU6Tdup574D7i/JugOASagLSHsZoJa0Yk+0VSbO1aNQj+DSlDfLA983pwAm/VcgROhcWXwtm2wQEr14pQJsXgTxhC3cF4LSBw/XhIE0WyntLJdX7qxf/UJ62QfxMKNSJ6RSANYHaepbmxlQ/XXaueNW1cyUmQeHwjrdCPirTwut9gRGpACC8FDRZw5b5VjK9tWuRjtkiEQdZxaqoxdwbrrZYlrqK2vnChpRP//xdIE+QnUrrqE8zdXNjLO0tRv3YglKBi+LDpIScsX5S4hMsKGKFxQznYpzXQTwmmAkHXuKO65xr/xSBm64U2gwnwE7it/TR4PiYs+i019DG1crteYReWL1iUNkz06sLEiCMc/IhLSNrftdmb2HbVmR7q9nws/9eNYS5g1oZxljiTpqA3VjJ43l/ISoOKjEs+LFUMuzp91CmMzkWscgC9OY9O4QXH8Z5qEAg2crnj+mCe/LVn4J8eRKaALbIyUwl/wjVaO12r8yKQLzPb9iNDUnw==
*/
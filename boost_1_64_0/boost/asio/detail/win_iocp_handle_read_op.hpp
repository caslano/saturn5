//
// detail/win_iocp_handle_read_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Rep Invariant Systems, Inc. (info@repinvariant.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_HANDLE_READ_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_HANDLE_READ_OP_HPP

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

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class win_iocp_handle_read_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_handle_read_op);

  win_iocp_handle_read_op(const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
    : operation(&win_iocp_handle_read_op::do_complete),
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
    win_iocp_handle_read_op* o(static_cast<win_iocp_handle_read_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

#if defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
    if (owner)
    {
      // Check whether buffers are still valid.
      buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::validate(o->buffers_);
    }
#endif // defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)

    // Map non-portable errors to their portable counterparts.
    if (ec.value() == ERROR_HANDLE_EOF)
      ec = boost::asio::error::eof;

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
  MutableBufferSequence buffers_;
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_HANDLE_READ_OP_HPP

/* win_iocp_handle_read_op.hpp
fojqddR5mlsx19hr7wP5p0GanZdfYQ+BZMgT/k3drLXJFvklzPMkaJk4cXSO+N18jPirLkn9bj5B7BNtLaPm2/kr4tbCvWZI39nGif+1XNkjYbJMvB2iziO0hmNE5hprkbPOx4RrF2ncW++xjvs7t/ubdmaEb9ojw8erYfV02xB3PX3N3vu13ZxX5Gqn3XtEVT76eUX4N/y8Iq4V/byi4L16p7jz8hd7raTJi6vNjbiHMKuOvGQdQV7yW9UvLyWnuvPyOnmpNHlxtZ8R9/JU1pGXyiPIS8963peBp7nz8qa97tedF20LI6+5rq4jL9VHkJdl0fIS1q5tPN2yhPZeSeV8wmbcqXmZnRO8l1vaiu8i61nWMD3MvKHMk8S55pdVrq8Zt+aL/TLvO544CXNDoikL037liswK706PX9svJ56MoParuLQgaM612Mj0MmPvC8V+lfcjT0z4NySZCygU/196X/Akm3VOlq5zStbvTPeJzCleLyVZ4emi7pSWuN/DjGcCuSv3hH3fl7mEK0Qmx3udp4u6aTi0NTflJF977DGE+hUz1BlHdfPHNvOz7a/2MRxh0POmY5GuF4a4Zw7VcUDTLNd46FTszbCvSQyYdi1qNUYmLd1m3e/8zSx/4Pm/mzwG2Ufadh0T3HGX/O48dlyfPpa6XXfIrbfjdukhtwzHrcK49R7kuOUfchvouE085DbAcRt6yO0kx63XIbf+VtA6qu8i6OudDH1xZjxixjI3JOqzpuGLTJ+l9TNMZ3zqCEv+BnHh45Vv2Trjt5tn0LXfDjH3s6LvGDF/kXV2nu+tlvpsOnF11jlP97NyjOXIZEg8ZYRJlHgaezyeGLnWVYPNnj7zDaOpyPg93+r3pSxzrV4R1wkWG/9u5plsJHG08Pg9Xtcz2drOl/g38nyr31x7Ba9h1vZhqMjssB62Oph1MKnitp8yxZUaX0NbN2W4802hm0y5VL4a/blK1jBLh+v8fZNMv6+De92HnE+hz1B3fS6Cuaae604zI9SdkWa+19wvMxfP/QjZtzQ5bK1g8Lx7xZmBi72sunKfgO8QvnyHqWN5gRrmrldah5DV/RB671eLfa0nynpQlR+hdmrEGzJHFz5/Lu3nZBN/iSeXFYNPWTepO7On4j7Lk0D97Wv18ITN85u29VqRW+r5i/axE0ycXcy+7baShq5B9azUctasZb+u+zt0TnaY2JOwB++RN3vnI65B+Eaut53Zmtt0bZiT/smebriOsc5Bc/s8qyt1Jj6o3f26V3D7q3atN0X13Kdt14HKsDqkesVda0hXhn4vELfVYd8bWrj2b4e+O8SMDCSkbQAyLrrCXgstZVwZeEFnz1nZTFkHHbE9IKvI12/ts52e+OC8hOl9oHDlb6gnkJae8Fa7HQ2kZyYnL4S/MEdbi6lhOpu6HvOmbW8dra6r/FlR94EE++8arDr2Lcvshf1B/Dt5ItWpNLn2q9ZsXVMiLe5O+YYQvm5W2v8bbHmRjjXt46ni9gQp+Imzf8nEkaztZW+R2WU1RaqY8M57laSVuxk8LkwW2SaeOFkPwFpo6sL6Uc6c50i/b1It7ysqvwP5L2R/yKJ2Zg42TOYgMj0Cc+1esz8kTCZ1NPOtdjz+yj+avXxhMsOR2S/Xqrw7mkzRaOc9aULk9So6F/oQlTYuqe423db9/92bRvf/Ee2hc+R2SZvP/Qir+zvGBi78I6YTZjfmTmQrd5q67zTwWc6euhZmfgrnuSXBaxU0XD/zDWy92J+K+E12jJHvYXRP3CX2bRH3xulcjoaZFFTPphVXaD1z9lfdKzItwvcume+AO8S/Sr7zxIzhmaccvpX7PMpy3WeVyRpr9iVdHl4=
*/
//
// detail/winrt_socket_connect_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINRT_SOCKET_CONNECT_OP_HPP
#define BOOST_ASIO_DETAIL_WINRT_SOCKET_CONNECT_OP_HPP

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

template <typename Handler, typename IoExecutor>
class winrt_socket_connect_op :
  public winrt_async_op<void>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(winrt_socket_connect_op);

  winrt_socket_connect_op(Handler& handler, const IoExecutor& io_ex)
    : winrt_async_op<void>(&winrt_socket_connect_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code&, std::size_t)
  {
    // Take ownership of the operation object.
    winrt_socket_connect_op* o(static_cast<winrt_socket_connect_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder1<Handler, boost::system::error_code>
      handler(o->handler_, o->ec_);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_));
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

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_WINRT_SOCKET_CONNECT_OP_HPP

/* winrt_socket_connect_op.hpp
Vuyvome2RBr3LOtC2W7n0zH6qOmKd9xzPRI0ryMcjXv27HIHuU3jnsPYrhJ2xfTc77lCs5ltsKmBzWJqp2bYHuepjtr7Q1WqLOsGmyOwuYCOU9VBs5nHNhxvWkNnqTfer7gD2pjPB7+T29LnhfOjf06MlV4Wq9PS963PUG6M4/KpbNC2bKkXwtcf28bLbbi+hjbpeKT3xNt53eVfw/US7w2x1mW5pKgQGv225ZjDnSPL8WWdhN9pV47ZfjT7NfsIq/Ijn30dZPMrxS1G+sOJ67UL12FrpHbds0zXgZ6j+Do8EN70NfA3z33WkecFKUZxXg6D64007OtkzEvZWWfMR6ml8QqFSce6ISrnJR8HFlpa5qcJ5/+6bPq06OOdHe01TuZASRzv+M6mePP1L7e7/hwmucm6nNZqNsdJlstT0dZ5mWeOk/5l0TY/V3Y25SeO5ZufuWlwP0F+BvF6+jtZ/+h6uD6iHJjjjoXUsa6577OPjPM7ZH8xdGxDOM7aMeJ09otp3yTep1+v6S3yb1TW8D2ixHjX/V0h7pHY3vr6ibaVCefHvC3D8xX5s6R/sU9buZvzIl7h9ezgenZFHR1nygtM7CguyMdqzGX5FUXa3Ky4rqb10TlsvLzHL0xr+hlFu2Y4njavhOI5keM5ixO8xwFbcCeYKdYsbiSeKwu9n/fE0vRafBPCvP0U+fLdUTtGrHzH/zv5r0dfLvTzHE4us75r/kyS4aLkuq1HyH+TIwwx/wFq1RmOTPR0dFci+N33wy7e9/Z+ikO9ADpBMbLOzV++vHSNdvPmlywplH3zH9Ixb3FECDUspQv1LxfJc3dUtqHc7MU1fLCLN5/dznMDWzsjQxJDSgMTnd0C2zudgaFwLmdcSFJgsDM4ZHVgW6crJJl/R2GfwxkakhbogEUv2IWFjMH/rtgfFRjkbI3fsXjrbNcKG9rDtQ2ZEBjo7IgVqaY4QwKznBGBSU4XAkeH9AqZAsMOgYHQ83GKRzCej8TfwWT5xW/rvp324NeUrtbCT+mfS3kW5xDtTeeB3vYG32hxpRW5Jtd4solwRMhjck7CSvtGMQ+cQnbJDkM/Ea11+1m82BeKOMMvr9VKNUgNxZWMVsT1EuHe9z41y3VlLye7T1Rj/FYWFDesH042nS3iBytO+wrYzSS7UId4djkAoZUX4/D+HU3X1B3QSzH3Z7Pdt7AroWvvucsdF2ioL7kPg22TuvAxg6oC3M6qMHdAoPWcNLafDPtzYY/ejo6mfgK22duFz9+1qsBwbnN9z/dKVLz3GWEdap0Y0/3xMrSzO4s8p/PQubicH9LiH5Bpyg/2o670f73bBFqrj+oDObcN8ZVrIsX5rHdrvk/1a865u/PafqyFswnsizoqvRvVUVQ5YZJhBc5F5ZLLDPaV5a/EG6au35TD9JTffOaSfxXeDwKUBSp09WRYKm/y+84ssitTk5GvF0AZe6waz/WVdszu8nvPtgRak47nZ+rX2irTvo9R+Z1P4dbQ+8BChNPsgoSdyDe+F3aTXbDqUh20/lckZ/h02j5QiaNtqrevmbaNUf+Ms7+EejYFYRruyyVyfbNbyS4O92GYbn+Z1D27mfZ3VQPVSF38l4h4yfp8IdmsVFNxnrmq08eO0sn9qrlkt0ztjve6HLUV6ZXNQ7uT1437wZy5eIVwB3jq3UFBdt+BOExdN60P77om+/C0dzXV8K72GMVnJD9XYwNdr4eVzpi3eheuL90XfL7j3bgfrq1p7qiMU0GCFqfPWhynzhSHAr/itCGB49TGU2+Ik7TZlcB5G+SpM97P3vz1f9yENme1M/XxyXuK72ttO90vPt/yd/GDyTUu2ICrwX6iv6A73bc=
*/
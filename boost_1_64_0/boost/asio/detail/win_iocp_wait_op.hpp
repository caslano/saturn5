//
// detail/win_iocp_wait_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_WAIT_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_WAIT_OP_HPP

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
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename IoExecutor>
class win_iocp_wait_op : public reactor_op
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_wait_op);

  win_iocp_wait_op(socket_ops::weak_cancel_token_type cancel_token,
      Handler& handler, const IoExecutor& io_ex)
    : reactor_op(&win_iocp_wait_op::do_perform,
        &win_iocp_wait_op::do_complete),
      cancel_token_(cancel_token),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static status do_perform(reactor_op*)
  {
    return done;
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& result_ec,
      std::size_t /*bytes_transferred*/)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_wait_op* o(static_cast<win_iocp_wait_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // The reactor may have stored a result in the operation object.
    if (o->ec_)
      ec = o->ec_;

    // Map non-portable errors to their portable counterparts.
    if (ec.value() == ERROR_NETNAME_DELETED)
    {
      if (o->cancel_token_.expired())
        ec = boost::asio::error::operation_aborted;
      else
        ec = boost::asio::error::connection_reset;
    }
    else if (ec.value() == ERROR_PORT_UNREACHABLE)
    {
      ec = boost::asio::error::connection_refused;
    }

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder1<Handler, boost::system::error_code>
      handler(o->handler_, ec);
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
  socket_ops::weak_cancel_token_type cancel_token_;
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_WAIT_OP_HPP

/* win_iocp_wait_op.hpp
eg78H26BTas17st8bPmPI1t1lU77Pvj3nVvQBdv2SXpCtn3euRds22fGcIiPTf4rMR3h4UHHMOBe0dAMLw3nwAt1BfJit5t6Tf3bjVY/TuQVu6mTjfeXytLyVc3aTTXS9tE4ntBE/6V47KiULzs9caX32lCpvZSh17jSB9tPqa2UPR9xyee1naKf+MXYPGs71UboBoYy1XYquwMyTj+9s2fM3+fZe80bzfujelttoSz7vuUdvfZ9DbEGVTm+oTRx/vy50yctmD/lrCukxH0htfrVsdtfvf12VnliT/X5J3vuebFT+sB377j/4Zlb+7YNsvsKsqcKsr/637WbCrBPE3sqfUCS+VxHuYuMTZQ+v6tuX+OyIRhrt7GIqo2OD12ujS4aZ3l1SpflQzfZbhvURHmTbHShyuD25dltJirjKy8vTrpoZZz8xlleQxzlFVj3IHC00tn9wFykNh2DwTRwCNgDvATMAoeCF4EjwGHgcDBH46Y/q4xtCTLjbAfyI/47UjclhbI3xWejMRO6MoLdNgO7DPY8m/Hp8alWvx6tfj3O3Tbh+f9gvx6RTfH59jj+UHz+PYJ9exCYgwcIzxNOE1I3M4cJ0wjFhFpCHeEQ4Rjh9OZWm4DWX+uv9df6a/21/lp/rb/WX+uv9ffv/7UllL/t+//RDSv4SIuYAJyjDYC1j99w2uzT5y+YNGPK4kYzANnHH5vJH2+6040pgOzjl9r8+u302cdvN5BzP8W6d2kKkS1c2Zcp7ubYl4E2of1bx5l8ynLv4Ztv9Q0n6Nmi0NSerCF624S7MMoybaKjzZl7pVcfVkftPoZ03+JPkt49ZPkT6DaMvfzM5v0JpDnaLnU62j9KX3lv0D4t0/Znlfi1Pyeo/Up/mcbDoR0Sb+/lR30gjZb0pSHrGzdr6cCYL4VPpTXylNuMn7o8J0/mGnVxTepyfutJ973Ha0HjCJPhc78/n4XRosqi9aHGvbGDwm80uk683xmeNW+W4fmYxLvafVGtM/u2hn68lFndTsu0+aPIP0sjZUxSP39W+hx7uhkH5qymzyP9i5KeK/tgQ6T9U7rO5jp/a95ws34AM9QP4EHpX8O3+gI0fp+M/4ZM810o5Udps8BJ6jfQujbEjJu02zmXkgNsIVZ5xojNs/jtIfLeDPaTecDHVuGxmP8Mb53srMVtC0P9znrW6N74X9Vf0snY3wNom7eeKuvbOn8e4LSHgdb4TJpJfLHEj4Ui1PM+gjXXkAkmhcqdyZdhfC0tlPiJkHwdkWDJUoh89u8n3ip0n8WHfar4oTlIXz3AOJeJH5phkQ6RkOf7PWlKdxi6j/cSX2QvGl3ronnN0GwIuWlUz4mOW6Z74zlN6oTkrr1WG59lFZU232P0o/F/M83oCKuPxnStEz6x/Rjj1BkFun9+q+p2yEP7BsYO+/qNmdEZvnOT8dN8aebbpHdKvAyNEbZ9S6WIu6+OncnTy+bbMFp9U7REbT2c6UntnPvxc1zpWY3pJeLHRcf4UUmfYdMTmof/0CHq083UTV6Z4IY+x0VfQNwau77wUxTHN8uc9yj6zPPtF+kT13fLpB9s++fOffZ844dK+BU9VWDyGj4c4/2qz/cA8y+lnDVOf636mFS4orS6qrrS1+cneRL7HqCPL1XjI+67ujd1iDA6Zju5xtgTTZ43UUVQ7VBGZTqed5R2WChNdcY6id/LmfxwkM9EzTNQ8iwkvlLiD3BePynQb+Iak+8KKXeIbKDJFDPy/qSm94VLt6/EWaQflPRJYtUxAh0Rs19JjXCv7sX4ZrRrE2mf1C4pktwxZUjKpXxNr01SJteSu/BZveROZ3VYjSgxq86bpcw7QtOp114nzyE=
*/
//
// detail/resolve_endpoint_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_RESOLVER_ENDPOINT_OP_HPP
#define BOOST_ASIO_DETAIL_RESOLVER_ENDPOINT_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/ip/basic_resolver_results.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/resolve_op.hpp>
#include <boost/asio/detail/socket_ops.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_io_context.hpp>
#else // defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/scheduler.hpp>
#endif // defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Protocol, typename Handler, typename IoExecutor>
class resolve_endpoint_op : public resolve_op
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(resolve_endpoint_op);

  typedef typename Protocol::endpoint endpoint_type;
  typedef boost::asio::ip::basic_resolver_results<Protocol> results_type;

#if defined(BOOST_ASIO_HAS_IOCP)
  typedef class win_iocp_io_context scheduler_impl;
#else
  typedef class scheduler scheduler_impl;
#endif

  resolve_endpoint_op(socket_ops::weak_cancel_token_type cancel_token,
      const endpoint_type& endpoint, scheduler_impl& sched,
      Handler& handler, const IoExecutor& io_ex)
    : resolve_op(&resolve_endpoint_op::do_complete),
      cancel_token_(cancel_token),
      endpoint_(endpoint),
      scheduler_(sched),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the operation object.
    resolve_endpoint_op* o(static_cast<resolve_endpoint_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    if (owner && owner != &o->scheduler_)
    {
      // The operation is being run on the worker io_context. Time to perform
      // the resolver operation.
    
      // Perform the blocking endpoint resolution operation.
      char host_name[NI_MAXHOST];
      char service_name[NI_MAXSERV];
      socket_ops::background_getnameinfo(o->cancel_token_, o->endpoint_.data(),
          o->endpoint_.size(), host_name, NI_MAXHOST, service_name, NI_MAXSERV,
          o->endpoint_.protocol().type(), o->ec_);
      o->results_ = results_type::create(o->endpoint_, host_name, service_name);

      // Pass operation back to main io_context for completion.
      o->scheduler_.post_deferred_completion(o);
      p.v = p.p = 0;
    }
    else
    {
      // The operation has been returned to the main io_context. The completion
      // handler is ready to be delivered.

      // Take ownership of the operation's outstanding work.
      handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

      BOOST_ASIO_HANDLER_COMPLETION((*o));

      // Make a copy of the handler so that the memory can be deallocated
      // before the upcall is made. Even if we're not about to make an upcall,
      // a sub-object of the handler may be the true owner of the memory
      // associated with the handler. Consequently, a local copy of the handler
      // is required to ensure that any owning sub-object remains valid until
      // after we have deallocated the memory here.
      detail::binder2<Handler, boost::system::error_code, results_type>
        handler(o->handler_, o->ec_, o->results_);
      p.h = boost::asio::detail::addressof(handler.handler_);
      p.reset();

      if (owner)
      {
        fenced_block b(fenced_block::half);
        BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, "..."));
        w.complete(handler, handler.handler_);
        BOOST_ASIO_HANDLER_INVOCATION_END;
      }
    }
  }

private:
  socket_ops::weak_cancel_token_type cancel_token_;
  endpoint_type endpoint_;
  scheduler_impl& scheduler_;
  Handler handler_;
  IoExecutor io_executor_;
  results_type results_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_RESOLVER_ENDPOINT_OP_HPP

/* resolve_endpoint_op.hpp
dop/t4A9rhe79iH+QfwD1j7roMFvIFeO9SVu4rb57C6hMfwmXzUu5X5Gl1xj89E48R9Pu5Pee793nJ0Opj2aN+8qVf7XW3FukDizHfoT7NOS3Np93xQJk27vK4/4Dvc1uPSwF0mYhT41FoxEf1Uy0ZRpDjQr0yj6rSb9uhEton/aor++Wb2uoj9u0q8/o0Xx95xk0n/WZPxD4RbP9tvJNlzf13gzMeUU5inmXr9BJbJ+6tfy1kLj1zirkuv7nfQLuc2sKybqdUUZo6Teka2Sqkr2Qzg/tNS735jj0W/McfQbQcpfoLP288W597TLHNmw6Mhj7GOeL3avRZ5e4ravLXGPi3+i/T72OT1K3etgr5S6/Ucsdct+P1xK+sj51nRdYls537rIr/uoXRdGjKsqR2U4Fx57bGWYvtbY+qqyI8YYfRTpe1tj6x/Fvhz0bJecb3FuwTHRe+373mX6XGUy9Y+JYm/nvwVukf1CMudLfqFJ9Xfz5XIOBQ3CRXq8XoQ2cHAyymea3lcfKJTt5omBvsDO4bhA63CHQK/4TNhSsWG2U+twt0BufG9YO8XPwr/Dwu0DCbLjpWPAH58ZPxXtZ/Aw8ALaSqvovS9i57wkZt94f5lKWxnTivoqc425THtyVF5izfFKJP+zfZSbWWbp/jzjIc/5XTbPyp+covb68az8+tFyWD7irHzMs/AjzfOajGfTNLOPiWu2D1P0j5j0655qtg9T9Ict+o1Nxh9xxob7z1reV5lzw1FSJ1dBah6Oc+9jpI/Kb0bHN81x50Gjh9yyyUNuyXKvT0kbH7vMPb/bFGGPL3P3CXeWed8vUDdLJ/B27hP4Acw7UMwevcjqE3hzck3ZyqbXphjG3nfYermsRhi5wqnm/h1Ewvt/TJk2LHRLIJG2ZX9hxpViyaizhaaVxPNWHxVPfRlvUqL8bYbpKbyHscLxLnNxUXn5kiLc+1xSVFck9PMi6FFvMeerHeTb8zDDHB29Dsw8LBOazKj0xlrfWi3+aYbMJdEv75hJ3u3blN6QfMt9IgNAPwSmTwt1Gqa8c8byls71XPM6qWvqgrnfzK7LFMrXqBu423WTpnUf3IvmqgfXOa41C/SHf4sM9wM+ATyKuPYsj+BDNbMvLi8rrZTpXyy9BMONM5K5XlhfoexfQKMblPpuZH1/ILyESO2ximGzhG4T6T4UumIc/Kkkv5EOLSmNY9o/xP49n9IZ/9noiJWssbzPACuhlSLT4+sjJN4tjHffGaJrlKykkZc+1/H4p8nq33vGS7455FnzmyMsPqsul35c4tzGONNTJU69Xkoebit0SVb5nCfpaefY88C4uedhO8fgj/pIXFV1y+SpJos+K4J+J+kj2qZFPzKCflfs9mmFyYkI84hXG+W6pl/yt8E/EpRRbZRlMFXyHG+12b3CE3OsOycOSBx5qDm/kWbNnRzMVkCZgvtLrpLw7xh3G0G6ueq5yXl913L2Z+S5DuW6v2sDt6h5PPuM84Vmss/UNW+X7x9Ar7laz5mSzTC1RjLlsuNSftf7ZyBPrjMALIPNEufz1jfulThXR/GX1zfb2PoB67xBF8l/W2uuOV/C9/Ali78Z/jBCt+X9ImaZTZYyc5xFsO7TSbbKo7RBSsRRpyck/g5eugdrj8RAoTnP307qaXZSA8a8uHkY+ztjHh+/7lxz7TOfd0CZNANAk6Ro4tbNM2k+IU1X0hSC5jxFE1j3bEIonBBovDIhFLL77vuSYCLi3Ygw56swbdcdYrzwcdPsBE2+fHv9MpMmJ9n97QOg6UN5ynnYxn3Whue1OGYMypKzFCL3nAkzq7Ps25RzEhsGalxvI8YXcY+4z8l7L2KjUwdIWeY=
*/
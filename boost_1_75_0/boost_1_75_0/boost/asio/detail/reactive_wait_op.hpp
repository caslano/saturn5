//
// detail/reactive_wait_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_WAIT_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_WAIT_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/reactor_op.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename IoExecutor>
class reactive_wait_op : public reactor_op
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_wait_op);

  reactive_wait_op(Handler& handler, const IoExecutor& io_ex)
    : reactor_op(&reactive_wait_op::do_perform,
        &reactive_wait_op::do_complete),
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
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_wait_op* o(static_cast<reactive_wait_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_REACTIVE_WAIT_OP_HPP

/* reactive_wait_op.hpp
uu9e/hxhmMADmgfzcTbQXr0mWNEvoCJvKuA5jyM6C5fRQvY/b2kEcmKeNpPzF2soGsKuee577McZGs1U/hCo96KHOc3MsyhyY3HydDEhV9g/yL5scXHK12sGSx0PwvjVNBe7BoGcV5x8vePTxUuCBDR/a/8MVGr4fXRPAGKnMikf3T+alQcbsOOniGFPJOrEOBW8ACjQSLYoWORBKOL5GKchZnMFbmhm8Nnin2rcEJq/VJy/9CzndbQpGw9TlnXt7lFy2bsvaoQR3bw5TcwlSmZjFx2H11oQtZiw4YNnNRLGeY1bUs6uvw6g9qV+7G+NgRfFBvnt+TDAl80TXjYIxS7DAnGs9yzQ1TjoldlSXeyKYRXPapRVo4tWP1rF5Pol/dDFP2p00a5jqNEq4CiNp53E6M5klpOs9n+wwwzGsAI/uwbciDdStnYp4oFx7JIPsXF4dfUBNhIuIuvciyMim+YWFEhKzKom9yy9zVXoZ9FICvwF0NQ7ZJ/lpIzfn/PXR1+vXL1tjtyQWJ8WWYOy+Ieq0dyRlcsaTqE84I9E6FhS3DYupOgDVBRZusty2XYoGtkyq0DqjFm1C7ifinWt1PEW6ngDddxSbcN/bF+lTncsvLfjtN6eht6+83vs7ekGaxdyHVqXW91l05U1SewqqEm5Tm5hk0+pfS2IbFIyuwrc6w2Oj7C3bOxzWldXydZWablfJ1WXyD4X70Vp
*/
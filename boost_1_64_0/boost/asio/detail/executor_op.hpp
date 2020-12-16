//
// detail/executor_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_EXECUTOR_OP_HPP
#define BOOST_ASIO_DETAIL_EXECUTOR_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/scheduler_operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename Alloc,
    typename Operation = scheduler_operation>
class executor_op : public Operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_ALLOCATOR_PTR(executor_op);

  template <typename H>
  executor_op(BOOST_ASIO_MOVE_ARG(H) h, const Alloc& allocator)
    : Operation(&executor_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(H)(h)),
      allocator_(allocator)
  {
  }

  static void do_complete(void* owner, Operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    executor_op* o(static_cast<executor_op*>(base));
    Alloc allocator(o->allocator_);
    ptr p = { detail::addressof(allocator), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    Handler handler(BOOST_ASIO_MOVE_CAST(Handler)(o->handler_));
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN(());
      boost_asio_handler_invoke_helpers::invoke(handler, handler);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  Handler handler_;
  Alloc allocator_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_EXECUTOR_OP_HPP

/* executor_op.hpp
6Otv2dutsf/jQevKpj26FAh4JLi34+479HbdbK63pXLcpISEbOGV8Na9HeF9+7Q4KhHb7rzZllvie+zdPOrvuMViB4PYeY/t0hePuG6c6ZLB2gdPbCEy+QAM9lZB3LO0bYEtQuewglPo3bYd7LSwa6pZhvFITo/WLQ4fjw6JdAVGU7f5tvUmZeR22JlUnlPkNDe23ae35Rw2MAqCPI5tN9uAlMtsEjvuvv32ilhewHFPNbI7A85ttvn2vQKV+a0PF8Iu9ns32TlPzG24Th7SJ3Fu750baPcsHWB23BazC7vFTNh9bgsf0+wDtdzTHtvutm2ufKOAd8cHCbtuOyf7RWu1yCQwxLbVoppOxqxsidocdWGL5j7HMzZ9crHtVttugUJOi9+27SmPrVu3kH25t8WHpDW36/CQ4Wh+sqvsf2G01da0IntLbFOHlXR2Cx5aJeD4Jtp2VxT1Trvu3Ug0gu+8/WZ7z2HFcsKMLoPSIMH5c64ik7SL7KHzRrINKqFWbQYZDylGMls8YdeNJPa2aMiyQ7SUCoRPDIiYFpAhKeCoOBH1JmMBtkTvtevc3nVOok7pZtNbGtYTIPT0h5pFinZEkSXfiUwrzLfEgpR662/QrvcMhNY16IBH6rCq2HGR2+og7DN1gue04/Nkg4LCUC2vOeUDx7xot52322yLQG2bGPnSdNfeVgml865Tm0LfvzOp1KC29Fi2vyCHVtL0stOOiHUXYoBZG3fE7ugXGgRuuTmayG6emh145RncxmG0/h4ZXULkb4Zy3gPp3H6nLRocCjttS0aKp/Qnrj6qNqH6qFlDBDwwNmHZBHNdXsqRX8Q8yotcfbxTk0Ilb0DU8BptxCs954WEnuFCpnkuC1meuEIqHo3SkPEEE5J6PklO7FryVrofUkjUTODGef8QeXoPZw+08Ywqylx03iNF2REAieUm/wly+35SbTveU6rBEsEOL+vtsq4u61MLORYzyz0X3NF7ZGI8YGNUIENsYbBH0oV0e7PXHPaNDRTzgrAZeZYntqmsAOxLyCvrw+a4u59gt+FagUq3izRuaSx6s8Zl0z+g87fbzs1r5xO49ur2FzIKnW4RMxZyFhP3E0hwZp/YhX4hnMHdasxPXxvU7nsRpArtGdyaCM8EB2rlyUBzR0BtYjaTSFFNPoaBml/8kGMlqidJHMgUYxGScIrpQ4YEujcCvEQncPEgDsyhpElBnUap0nfpo3UPKhlFoIPRAs5bHCCcjQHcNPeAD67NN1znvQQo7RPIDMrKDJyFBhwttEhXicktNHC00EjFxA6KFloQ5HHAQiOV59egYaEB+dwDjhYa2NxCixT9Rgutyc6RcBYaKZ9EWGhEwR6DwNtjIII9Bs7ZYzmNYtejgZRjEZdtNEiCjQauYJCBLRpk4INBBq5gkNU0tOS10zjYaOBoowk4nijYaOCcjQbM6HIo/Q04b3tFxhSONhpIb6OBaFhgGWQ8pBhJ6nv0mkls2GhAmY2mVCB8YoKNRtInhTaYR40wXm1vo4FwNhpwwUYDG200kCUbDbQzyXJCql+w0cAFGw1csNE8Sapgo4Fus9Egymy0QG2bGNpoQLmNBsrZaMDBRgPXtNEAnY0G7G00EN5GA5HbaKC8jeYZuU1mo4GJNhrIYKOBy200UMFGA9ew0YBooxmqgbPRgM1Gw6Wz0YCDjQYut9FIWSWnjVajjeyKNhqIzEYDE200srSZSEUbjbIdt5R6Ek02kM5ky4ldS94Kt3cJBmJHTFIyIbfXZn08Q0dZS7C2IG3e8cKeQaKMwYIF2MYzuihz0XmPFOVWI9im1QiYW42g2q1GSjVYItgFZ/1v1vlmvXwho2MeuyeVswY=
*/
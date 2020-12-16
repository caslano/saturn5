//
// detail/wait_handler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WAIT_HANDLER_HPP
#define BOOST_ASIO_DETAIL_WAIT_HANDLER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/wait_op.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename IoExecutor>
class wait_handler : public wait_op
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(wait_handler);

  wait_handler(Handler& h, const IoExecutor& ex)
    : wait_op(&wait_handler::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(h)),
      io_executor_(ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    wait_handler* h(static_cast<wait_handler*>(base));
    ptr p = { boost::asio::detail::addressof(h->handler_), h, h };
    handler_work<Handler, IoExecutor> w(h->handler_, h->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*h));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder1<Handler, boost::system::error_code>
      handler(h->handler_, h->ec_);
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

#endif // BOOST_ASIO_DETAIL_WAIT_HANDLER_HPP

/* wait_handler.hpp
0z2Tn/NjXfWyj+tkciHzjHvdpcTw/M4ypQg/5ubFXm54ZmaZWoRvcXPjvmpY42EZPC/zOtCyZ6xkjkmZmk1WMucgg7SEzBdWz96zeW0ISM/bR/h5+3s4XCP3hW69yOHn2RttRH32luPWqibw76bFmdvVys0y2i14W3zzm6PaLRg1fXL/fFiPGXvJ2GkeWytHIGOwyTAneNsRSE/aJNDeX6f+xvs7BFmX+f1JWyTRRpsRHCeR15cMtkgQHrwtkmgTmx3Iw9QWyRkTnd4Rc4q5TmyLxLLcEc+P3Z45wduKODLCv60Ita7WDLCw0TYnCBttzWhLVjbaqgda2GibE6SNtjkB2GibE7wNkqbaaMsdZGGjrTAIG22FPtsUwoNvU02x0bZHrxOfw7BLnTzbRM6HjbaZg435tR6OvmySn7YNxw43lCHiBN+GkZ5pG84eYry/dpB1mtyfbMNy74LxHhFPtuGJ5m0YMsG3YeRpaMMTfbThmKFG/X4jxntT/TDa+9DNpWnDuWY22gqDH++Rn6EN51rYaGs00SkedVZnohP3S6s2hTh+xvpm9MvY4f775cWsU162UadfCRvKWp1421Nz+6ba9s+a5PmK2L9rkae2f74EOcP43Yz+ifTM7YAOM97jW5BViszvkdswrwUZ7xHxZH1/ZGzDCA++DSM/Q31/ZGE/betwo16vinHYXC9ux5Zlj3g+2zHCg2/HLwXwzEJc/KH/evsTt3UX17uFbb38ldgTqRPumJ+78PWZj7XYpQjWLsUesktRVHNo/JN9lowPTVz//RNdvv9Li12K5tilYC5UfAODPkj3N2yj4qDGRsVBaaNC/o39gfwtGW6T5u8t8m/3u/IuyGcrqDv+e5ziXjNsxN9Pw72j+btB8zfWkvFD/nBvav5+W/P3rzV/Yx1D5ntM8/czmnt4XnMP+/nvS8WecP47T3CI89+L4Q7x36vhJB+vg3lRTXiF+2v5blku0kSun0auIcD0lKnWcnkaOZePfKdp5LICTM/pQy5bI+fwke8QjVxtgOnV+kjvIo1cvY/0xmn18JHeGI3c6QDTs0+zlrtUI1fhI9+J2vILID2XcCz3Bstp7R08aXPz0T8F7Ah8GjgI+Cwwh/n0pwCfA97KfPq3M5/+GubPf4T9W5lX/xm+/ir7cR/Yw8dn1/j8mxg3IoAj4RS2fyHwN8AQtoMRC/wtsD3wOPPLf6DRf9f0wPpB4/TA2m1cXmDtLCcvsPquyPNfP5DDOZDA9GjIC0wPZUZgemTNCEwP5wz/etQqvOec99Hv0tmLKEI7aAcsASaxvyv7xwKvBTqA84GF7J/H/lJgKfAG5o3+KbCM+aDLRTybO51FwOuANwErVfs2ct8u7Sum+xogvu8Bxe8b3H8P5ufuw/4B7B8N/AdwBvN1FwgAzgWGsp2ECGANMBx4K/vXAC9gXupI4Cb2b2X/PmAr5veOBuJv5WJgBnAscDhwHHAk8BLgbOCFQJW3+wZgPPN2twHeC2wPfIR5ux8FJgNPMW93SAjqERgF7ArsBkwF9gD2BPYH9gJeDOwLnAzMBM5k/xXszwf2A84DRgAXA7OB9wOHA7cB04CvA9NFvijv3sB4YAYwETgAOAQ4EFgOHASsBl7E9bVI4b2AwFe4vcUAS9UPdpBLBTqA/YFTgSOA04CTgZcBr+Lw+WzPpAJYwPUzm3nXrwJuAE4Hvgh0cv5r5R4y2vNG+WeJPercXh5hezDbgIPYP5T9uWzHwAncwbzvjwGvY381+5cDdwLXAp8G1rH9DDiyk/EC8Dm2l/A825nYB/wrEGHUXl4GdgQeAE4FvgacD3wduAj4K+BPgQ3AVcB3gRuA7wG3A48BdwM=
*/
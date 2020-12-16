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
ruR3DWyPfQ8cCP0/I52YXH5XYkbyuwqWwI3I78DswazHrRq3A/zeDHdi3wsTF5KuO3DHnrEQe3+ef0wGZiT2TFgO9yPTciRlxO9c2w3jX8vzhX0I7jvhFFiBqbT9LkGW39WYldiHY99Ee7gbE38u7SQmC1OBWY3ZiNmFiZnss9IwYzHlmDWYGswuTMx5hMNkY+Zj1mBqMLsx8ef7rAxMNmYhZh1mM2Y3JpGOth9mMmYhpgpTg9mNiZ9CnJgsTDlmFaYasxWzH9PmQp81EDMFsxRzG2YzZh+mDRPQmZgizErMRsxujJ8PZEMwBZgVmA2Y3Rh/LunATMGswKzH7MQcwLTMww8zBXP07+jf0b+jf0f//nl/MfLN15Mk37oHTykrLywNHIwb+DmnpNe0uZzj16t3eu/0jOm95s3pk9F7gPGbf1K/XnOK2Nlc0Gs2GhXy5hQ6EvmzF5RXlE2ZL2fvTinPX5BTgQ6Y9LJpF9nfsIYkWbn2XLq9l+jxPMvwrOL82WVzyqZXpKZN7J46vryieGbxxcWlM1KHsYG6uKRwNt/qxia93ssy50hMiQnkI12/23eGawYyfrlG1sfLRtnyspJiEpBfVJj/E6PzfaDsebcTpevjNYzqrj4X+zlib+mRs3rjRJ5jNYmruELj1P2mJmwns/coX+wz1I5muFW2/Zjgsx0LZ1fMMToJzxP57mLPMvG1lb19X7Wx5TUXZcUFc3Sf0gQjlyH2bOzlYj+o+8VEx09J3gx77+WIpPHy7c8J45G9TeXYw850NHvl/qJpQnu30QfqlXyMMnruxog93uj9/ELCFFGvJkm8J4qe5tKygsJDeR2oYWz/eaJtTm6DKbvnJY6VlrOXtEjscZ4WJp3FpdwCSWyypnWxyExiXNqIvROxJn0Fq1Q/s0lL3lwUakuCsJi9ijMDZeKx9xJtsGQdpPWG6KuvfCf8TDdHJhuZJwPnzR4IPw/R0U3+Jv5/P4H5AeVb8G3MJrHXffaDrUuPMnb2Cum+KtXzOVD1J1B4HVTHJ/UUN1c9VX2f5jw4qXspqu+T+oVbSP0S+XKzv0frkF6Xe4Zb4J6l6HUpW9yCy1b34+hzejA2kKknMK2Vw0l/zSrXc2pHrJqsLFNHPFpH9FnVcCmmzrwh9lvNeX8Lr5X7KeH7yn3Pn8tWK7O/zxL/n7r0Qdpp84pfuexRy6V9GULa37Hvc2IvK3xfWbLKFMRqfYk5Ts4pdNUZlVuO3J0S15zwuIzMOnO98e7rYY/BfmxLvgUhk5eIqYeuSNm3H3bvgnUhrIoLCPfXfUa27AYe+GopC87msu9qkH6xItk/hKO5J45sf5PmvHrosHXSRXykS+IL0aXYr5FbF0KqncjrHF0IQ88e1ztn/OmjRwzLDtLT1qF/BH0I1zVcVwPxRdT1GB/vTl9HZFMjpU9VNkROn4aJrq8B/4bra+jQv259Dc6es3UR8lRq7xe8LkT/RNb4saOGnZczfGj20EM6Mo6LoO8j8wjK/bgo+vFWNnansTWyuVHTaBTkSTpjXenUsKofxjc4on48ZBquH49ruvTDcJ1w/XgmjyVN3Hk8HvnK6HlUnSDR70VlHXWs8gjq2HH10L3i5C0zwZ23csJXRczbuPHDR4Tq7DrRnTfCRtXZhV/DdXZxrag6u4KfmzZ+d54m2bpyouZJFJBGzU9N0L0qcuszxL/h+kdPjHCviqLoM9wYIV/TCL8rar7kOYuWL8I1XP/oiVHag4ym7jSeg6x1fbQ0Hrm+tG0RrnnaYCSjX9O0k4Pc5UK4hreTg6KUy4Zm7jSW2G159DRqOxn9/hHWtJOPJkdsJ5FpeDt5YoR2kutE1SO6snnk5y43ah4=
*/
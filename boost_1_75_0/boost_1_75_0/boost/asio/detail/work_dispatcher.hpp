//
// detail/work_dispatcher.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WORK_DISPATCHER_HPP
#define BOOST_ASIO_DETAIL_WORK_DISPATCHER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/executor_work_guard.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler>
class work_dispatcher
{
public:
  template <typename CompletionHandler>
  explicit work_dispatcher(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler)
    : work_((get_associated_executor)(handler)),
      handler_(BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler))
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  work_dispatcher(const work_dispatcher& other)
    : work_(other.work_),
      handler_(other.handler_)
  {
  }

  work_dispatcher(work_dispatcher&& other)
    : work_(BOOST_ASIO_MOVE_CAST(executor_work_guard<
        typename associated_executor<Handler>::type>)(other.work_)),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  void operator()()
  {
    typename associated_allocator<Handler>::type alloc(
        (get_associated_allocator)(handler_));
    work_.get_executor().dispatch(
        BOOST_ASIO_MOVE_CAST(Handler)(handler_), alloc);
    work_.reset();
  }

private:
  executor_work_guard<typename associated_executor<Handler>::type> work_;
  Handler handler_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WORK_DISPATCHER_HPP

/* work_dispatcher.hpp
uXWCW6+5dYVbn7l1iFuPuXWLW3+5dY5bb7l1kVtfuXWUQ86d88eF4+Lh4uXS4dLl8sHli8snl2+uHFy5/lrf/u5flBSfkQrPSMXPSKXPSOWPkco/I1U+Rqr8jFT9MFL1x0jVLyNV/4xU+zBS7cdIte8/5nOu3ByfKzcXnis3Fz9Xbi59rtxc/rhyc/nnys2Vjys3h5w7548Lx8XDxculw6XL5YPLF5dPLt9cObhy/TW/UX+vY1J8kAoPUvGDVPoglT+Qyj9IlQ+kyg9S9QNS9QdS9QtS9Q9S7QNS7QdS7cvKx3/3gPum7u5RNSM2Ujy8j4/aLD3vc/M9N/9z875/S79xYjfedPYskpYAX+geLhRb7YQJ/3ynwFBbIHbVFbKIt6L4JUD0ITTrDxEah6DFRlnI3lXBV/O/wL53x7M63ugatqANeRbeveO76cvY8HjHb2gsYp/xZn1nc2CKfznElcvFNXcMRJvvhWhqNDxM5bCey/D5G7Ih/0Tm4jS0g851U1s3ks9GUvoLP4ewz/m/8Kv4oShAEvKIAuLPJWrjQHG+8TvZY0TbFShqc2fxgaF49kCO/yfNMyXb9dXdAu3Rf75plKzbfi39EiP9QGFO8xAhjt2Tjf1tnXy7LKtXKMarkRmKvt43njhV4LUJOXWR038tp4/QW1/x9QR9xVepb+IQpY9d36SizbqbmqacfomHvrp/Yu8ES/aQ0JBA
*/
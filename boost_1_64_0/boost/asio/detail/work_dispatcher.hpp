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
3+OzOJjCWy/czbixuFF8+TbK9ivZNOAWYIaRKxqeF4j/90q/S8m2ZaKG245b7au8Ba57Yktrxyved1b+iZHO+eXrdoOcGroKWnZ8gr/Z970WP13uqDHkvepX9d8Nyp8Cg+7jGkWh6oLu7V6az4/uJwnGkhDwAPoGAaDjpdUgySaM/Kf/tRD+pPCvUA1hp39jpl2C0+D6wGckPGBTnoVi7iCYJC8mXnJ8K+Ayorx6PTwaQx/zwe5kfUM4YZP0ySoA5AMqyO8ImywVzAzBM3SZX2VW5WwrY2+8tYblM17Rb2UZJ8ubpenT0xLFDxYZesqngUOYB/222Gg7tfPCITHfIDpgA/CD1JvWYugwkB5xSR968xUEvMqqN0VsIOLC8ZWcnUwvT6A0zKowCXBt/jvrNqPQBASDpF25T/sme+tz+oDTGHxOXLTzk5MOabp+6P+gvby1xSWD+9BmfvUdY2seXyBRWeovXWQyZlpy+FtEa0AZoDcCOXolN9DbNqoSDpkxAV6xsSyMWj5h8/mJs35uWS2bjndrglS4daogRZXC2DBmOxL2hhA20KD+QA==
*/
//
// detail/base_from_completion_cond.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_BASE_FROM_COMPLETION_COND_HPP
#define BOOST_ASIO_DETAIL_BASE_FROM_COMPLETION_COND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/completion_condition.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename CompletionCondition>
class base_from_completion_cond
{
protected:
  explicit base_from_completion_cond(CompletionCondition& completion_condition)
    : completion_condition_(
        BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition))
  {
  }

  std::size_t check_for_completion(
      const boost::system::error_code& ec,
      std::size_t total_transferred)
  {
    return detail::adapt_completion_condition_result(
        completion_condition_(ec, total_transferred));
  }

private:
  CompletionCondition completion_condition_;
};

template <>
class base_from_completion_cond<transfer_all_t>
{
protected:
  explicit base_from_completion_cond(transfer_all_t)
  {
  }

  static std::size_t check_for_completion(
      const boost::system::error_code& ec,
      std::size_t total_transferred)
  {
    return transfer_all_t()(ec, total_transferred);
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_BASE_FROM_COMPLETION_COND_HPP

/* base_from_completion_cond.hpp
HgPOH7TpbPnJCrrSFWCqiSrOq1uTvLCHAxcaFLz/dH7vIVEjxPi6vRoOS95KrKYJfSg9S8jiZgHUbiBmbotCkw+FjStxqC1p6l+msJ4A/XH6s3IozChwNc5Mpr1Cfeskw3pzOA3rLaQMPgKygD2XVGegrDhz/bAsUYhk237K8QpjDwCQ6OJI22ClhIlHG21KJbJ6MiaFrfjBbukCMOiyv2T8tPg8YMGH2CVzaxIoo3rJ3xeCRwDYdm7e7YYogUGl8auKjYq6AbHYt8Vxx6YccjGgg2NS0yEAe2abw2wRSvpbiSrTonXxJoIm+R6pmqQetZQM6WtvwY63Ln9VBPIPTG8gD644u3PfqNDvMHehuL0+XRn65rZawDTwxmgBIdCbyqLGcVfSafd2JD4e0NEEjax2Rxs5vDlRAG0aV6sUx2IHd1HOoS6aweabe/jGw6MlGr/fC0IgpNsDHVqe7j9ePjP7ql7ltb+SXMvR6TpGdklOQLS0YXFIhcD2fEaA/DtrA3B9jVA/QRACDiwB8FimXGpZiotHugs96gUREstDTDERYXVED5pMfeeeQQ==
*/
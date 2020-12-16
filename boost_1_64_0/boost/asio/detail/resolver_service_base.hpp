//
// detail/resolver_service_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_RESOLVER_SERVICE_BASE_HPP
#define BOOST_ASIO_DETAIL_RESOLVER_SERVICE_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/resolve_op.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/scoped_ptr.hpp>
#include <boost/asio/detail/thread.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_io_context.hpp>
#else // defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/scheduler.hpp>
#endif // defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class resolver_service_base
{
public:
  // The implementation type of the resolver. A cancellation token is used to
  // indicate to the background thread that the operation has been cancelled.
  typedef socket_ops::shared_cancel_token_type implementation_type;

  // Constructor.
  BOOST_ASIO_DECL resolver_service_base(execution_context& context);

  // Destructor.
  BOOST_ASIO_DECL ~resolver_service_base();

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void base_shutdown();

  // Perform any fork-related housekeeping.
  BOOST_ASIO_DECL void base_notify_fork(
      execution_context::fork_event fork_ev);

  // Construct a new resolver implementation.
  BOOST_ASIO_DECL void construct(implementation_type& impl);

  // Destroy a resolver implementation.
  BOOST_ASIO_DECL void destroy(implementation_type&);

  // Move-construct a new resolver implementation.
  BOOST_ASIO_DECL void move_construct(implementation_type& impl,
      implementation_type& other_impl);

  // Move-assign from another resolver implementation.
  BOOST_ASIO_DECL void move_assign(implementation_type& impl,
      resolver_service_base& other_service,
      implementation_type& other_impl);

  // Cancel pending asynchronous operations.
  BOOST_ASIO_DECL void cancel(implementation_type& impl);

protected:
  // Helper function to start an asynchronous resolve operation.
  BOOST_ASIO_DECL void start_resolve_op(resolve_op* op);

#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)
  // Helper class to perform exception-safe cleanup of addrinfo objects.
  class auto_addrinfo
    : private boost::asio::detail::noncopyable
  {
  public:
    explicit auto_addrinfo(boost::asio::detail::addrinfo_type* ai)
      : ai_(ai)
    {
    }

    ~auto_addrinfo()
    {
      if (ai_)
        socket_ops::freeaddrinfo(ai_);
    }

    operator boost::asio::detail::addrinfo_type*()
    {
      return ai_;
    }

  private:
    boost::asio::detail::addrinfo_type* ai_;
  };
#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)

  // Helper class to run the work scheduler in a thread.
  class work_scheduler_runner;

  // Start the work scheduler if it's not already running.
  BOOST_ASIO_DECL void start_work_thread();

  // The scheduler implementation used to post completions.
#if defined(BOOST_ASIO_HAS_IOCP)
  typedef class win_iocp_io_context scheduler_impl;
#else
  typedef class scheduler scheduler_impl;
#endif
  scheduler_impl& scheduler_;

private:
  // Mutex to protect access to internal data.
  boost::asio::detail::mutex mutex_;

  // Private scheduler used for performing asynchronous host resolution.
  boost::asio::detail::scoped_ptr<scheduler_impl> work_scheduler_;

  // Thread used for running the work io_context's run loop.
  boost::asio::detail::scoped_ptr<boost::asio::detail::thread> work_thread_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/resolver_service_base.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_RESOLVER_SERVICE_BASE_HPP

/* resolver_service_base.hpp
b04RyqmEw17ntID+iO8cCq+OY+jN7765hPuokLiXcZDxXUlcUZ6vMzdYlu39+K6gAVoZz3MWEU4xSEUe3sr+54XecnIC+Sift9pv519ifrBuSi6dH4y6/R5zv6S+qjftS3Wxmw/cv+1h+aSkYaGTuZ2Fv4YV6MyJxzrjh8zrkdQaPDNfuyJf1zOvsFmac2foL6HZShmUV5ncNlwG34bySbt4zPkzt7Ol1IcWH4l2s+zgYwYu/3SPv/Gbg9roXf5Oj79pKvM7BuY2Se4+j3vabQed2+Ty247zwt5hnTelcqd63NOmHFK8qzz+6Tc3yr+eZEMd0WeUcf8h5t526IWxA8V1IlkqxiykE3bjbalUbw4X4wpwmMMrr8lpMqyuQ6gdwLhEyzTDP/qyuwbTWFTPQ+vHhqAfO6qY9bzmrahu30Ca6Xv0zi0KnRl6t1nUOTrp00MaqyhVxipuLVX6Obo/oVSf940xCej+3EewbLuqVwfGI0TDhnUPmFuN9+OQ5XhH0B8OLhb93Xb0f4/Ie01HX4WJM90xj7kTXc8jzvIlWv8nTaGJdXT46SHHIG26OfMwnxh9Sj3fJ4f60v+nsWUpZOrl/lzoncx9jL58Wjp3k9P7GWlnOpN5n4t2YTyhE1D/Sw6hXSD+lR5/485G3xfv+6DsJ85r9vSsBzmeYdKzCg+qZx3qdwX0L6Vuwca0RLchJS/FvVEn9k/BU5uJsbF3iVRDnF1LlTpxiPOjhJ9Jvn7xDd8/wd8KOzoH5keBP8zXDT7g+2fEtwXbWKELou68x/gjoTx6U0eF8sU3CoeDecvQx8ctY/2cxltWirDUuSLor79iP/dznxj1wxiv1DEqQuUbZRSHOZ92523tzw3odAzsl8zxnruGnjuZmENCqcwz42OfI3Upc9qFRN0PhpVAx+I6/0/2rjy+quIK37cSSJAkQAghYtjDHiACskjYdwgQMCo1CUmQSDayQBTQsFixRUWLFa222KLiWrS4VW2xaqUW61Ja0WJLXVFRkaLSlmq/OfPd7b37kqC/tn/U6PC9mTkzd5YzM2fObOUj0c5GkYcv5ZQjFs+TfotJ3/h6s2OKot9j0q8raXJOI+sL1DWncFwpStS/qXeGX8vaTQrbzSQpi4/RbhZhxnZpU/tlZzSnowUf2vtqOB9RvMZ5R8RcBDzj2X9THybpgjw2lv0w7f3Stf2TCP9/2v4ufUDj2TrxB/1ad/IsMKcjzAV2G+RxTq/9O6TrbulTl4j9Uf8ivy/mHs7KQtG1Q6qcYt1nXStuYZGbu/UUbQ4OFlvnZW39WoHsY+QagRnuRujp4iVsONMKW2OF5XdfkbSFrbheF3sX32muuEZH7je09nBtFPptsj//KPqu/LHmHvFhTfLxSrilK914V9sEkM4uMP1g0mD6wmTC9IHpBNMbJhmmG0x3mP6ZOlwCIsqG6QszHGYQTC+YoTAZMANhuov+sGV8bq5BXFzY0jWIUJKUU8QZtJyIvdDTrP0O9p6/dwrdc2dfUcRcmbrL7PG8Gxae3YBBYB1oDhXZPFleVqsVerUxxwTST7Tmaj2WSB/vvW5KeucY0lno33CcgaU+mrweJ/5XcCwww2daupk/in9v154/+R7P1YTE/7hD3yNLAy7dUYLQtLLWxNqLvdaYjtI1+fYtcQtFr0kwzGLxBz3TfY3Yp9LfTGf7JtLN8Yvj0bfFP5d2O3xTaxxjheYhe4+5Y90gU68DA1ui8w4lqe9RNj7ltXvZ2+hYV1i1xL0ugLy51rv2Rtj/RHvCcLcsc2CyTuRaCGnwgsyP2kaY3GKuf5FnRaNXhOPDNbWx+JZhZlpl9wOxZwRi8C3px1pz7qvEPjwQi+8=
*/
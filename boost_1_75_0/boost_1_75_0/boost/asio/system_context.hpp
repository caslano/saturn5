//
// system_context.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SYSTEM_CONTEXT_HPP
#define BOOST_ASIO_SYSTEM_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/scheduler.hpp>
#include <boost/asio/detail/thread_group.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

class system_executor;

/// The executor context for the system executor.
class system_context : public execution_context
{
public:
  /// The executor type associated with the context.
  typedef system_executor executor_type;

  /// Destructor shuts down all threads in the system thread pool.
  BOOST_ASIO_DECL ~system_context();

  /// Obtain an executor for the context.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT;

  /// Signal all threads in the system thread pool to stop.
  BOOST_ASIO_DECL void stop();

  /// Determine whether the system thread pool has been stopped.
  BOOST_ASIO_DECL bool stopped() const BOOST_ASIO_NOEXCEPT;

  /// Join all threads in the system thread pool.
  BOOST_ASIO_DECL void join();

#if defined(GENERATING_DOCUMENTATION)
private:
#endif // defined(GENERATING_DOCUMENTATION)
  // Constructor creates all threads in the system thread pool.
  BOOST_ASIO_DECL system_context();

private:
  friend class system_executor;

  struct thread_function;

  // Helper function to create the underlying scheduler.
  BOOST_ASIO_DECL detail::scheduler& add_scheduler(detail::scheduler* s);

  // The underlying scheduler.
  detail::scheduler& scheduler_;

  // The threads in the system thread pool.
  detail::thread_group threads_;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/system_context.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/impl/system_context.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_SYSTEM_CONTEXT_HPP

/* system_context.hpp
ugOB3sTqWH/iSs39tl7QUuw11H3LjCQZAdzX7UY5hvSiK5tRTam798Ic7ulw792Ni/Qr2DtV6cLG1Nvh3kMr9/cTBg1+ZEaUBdljvLgrkHktTHX50KUas8yyEuZ4+RAJxtiYJj8Hm9NI57sGzTzFxaQR0t29FE/ivoRLQklu9/LgJTLao8WS/b8vCZ6bKLQSF0i1BNZIlnK0CXsZN8LWv/UZFN/+iwFhB4Y/cPYIhLOgGy+GQPSjws6/BJQ28DfBKEJtQFa/Fe5DgcxGlHeho4+w/sRFgf5/HgnhqIGOxrKRWpQ2qiKU3NmSZQVpVJxQcCLR+RWY0YDU74WqR82TJTCfHqhjjbn4LHyIRZcbp5wt5WFNRxWqmt9d/yjeApWWNE1WdExso5ugTB9Qgfkz4S+sUinzGjWKXUQFKl7TlZSAjINrpXwAOOitl9AwceNSVtAb6DM25uqOH7qObpi/jD/1VsiBIj2UU5ee8Zb6+AxiITFz/gsOqijZh0DYIywWnM0ghpQMCf3M7SBwp8B0OKnsHRarYD/RGwI1wlp6oEXS3LiXYnbGNcV6jGi8wZMb7pimjibTn8db8tAYXd43LTjXiA6ngz/uSWh7nMdLYi/RuWmLeJ230z0JWJMJtKbUX8xLVaR5I9SXMM5hu8fA+BSBdcmWhjtg+/weWrQzzkwRnRc8T08xgLvwcpa1OYH9krbChkgnlsiGHlvg
*/
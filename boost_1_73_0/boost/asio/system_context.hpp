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
fZZSdZo05yuNQigkfSt7L3EpreMi7d+lth8tHicX3D0zYPp7p85IbPKCv5sKqQ/k7u4uK7onEm3VxUarPdRNPbSTzj42lKNT7wC3sE4VGkDtJ1CaBTmYHbScJFTSeIgSQqjCqFC+53RGlqmAKsKcT3O7VgX00k6cvbh8Ma8KXCG/Iu2cLe3sk3a+LhMvPAe3M6Obn9eZCJ7RSIkIHBUFiDB5EyE0tSpwkb/bDHkLP0x+6X0P
*/
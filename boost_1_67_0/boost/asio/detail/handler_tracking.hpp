//
// detail/handler_tracking.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_HANDLER_TRACKING_HPP
#define BOOST_ASIO_DETAIL_HANDLER_TRACKING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

namespace boost {
namespace asio {

class execution_context;

} // namespace asio
} // namespace boost

#if defined(BOOST_ASIO_CUSTOM_HANDLER_TRACKING)
# include BOOST_ASIO_CUSTOM_HANDLER_TRACKING
#elif defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
# include <boost/system/error_code.hpp>
# include <boost/asio/detail/cstdint.hpp>
# include <boost/asio/detail/static_mutex.hpp>
# include <boost/asio/detail/tss_ptr.hpp>
#endif // defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_CUSTOM_HANDLER_TRACKING)

// The user-specified header must define the following macros:
// - BOOST_ASIO_INHERIT_TRACKED_HANDLER
// - BOOST_ASIO_ALSO_INHERIT_TRACKED_HANDLER
// - BOOST_ASIO_HANDLER_TRACKING_INIT
// - BOOST_ASIO_HANDLER_CREATION(args)
// - BOOST_ASIO_HANDLER_COMPLETION(args)
// - BOOST_ASIO_HANDLER_INVOCATION_BEGIN(args)
// - BOOST_ASIO_HANDLER_INVOCATION_END
// - BOOST_ASIO_HANDLER_OPERATION(args)
// - BOOST_ASIO_HANDLER_REACTOR_REGISTRATION(args)
// - BOOST_ASIO_HANDLER_REACTOR_DEREGISTRATION(args)
// - BOOST_ASIO_HANDLER_REACTOR_READ_EVENT
// - BOOST_ASIO_HANDLER_REACTOR_WRITE_EVENT
// - BOOST_ASIO_HANDLER_REACTOR_ERROR_EVENT
// - BOOST_ASIO_HANDLER_REACTOR_EVENTS(args)
// - BOOST_ASIO_HANDLER_REACTOR_OPERATION(args)

# if !defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)
#  define BOOST_ASIO_ENABLE_HANDLER_TRACKING 1
# endif /// !defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)

#elif defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)

class handler_tracking
{
public:
  class completion;

  // Base class for objects containing tracked handlers.
  class tracked_handler
  {
  private:
    // Only the handler_tracking class will have access to the id.
    friend class handler_tracking;
    friend class completion;
    uint64_t id_;

  protected:
    // Constructor initialises with no id.
    tracked_handler() : id_(0) {}

    // Prevent deletion through this type.
    ~tracked_handler() {}
  };

  // Initialise the tracking system.
  BOOST_ASIO_DECL static void init();

  // Record the creation of a tracked handler.
  BOOST_ASIO_DECL static void creation(
      execution_context& context, tracked_handler& h,
      const char* object_type, void* object,
      uintmax_t native_handle, const char* op_name);

  class completion
  {
  public:
    // Constructor records that handler is to be invoked with no arguments.
    BOOST_ASIO_DECL explicit completion(const tracked_handler& h);

    // Destructor records only when an exception is thrown from the handler, or
    // if the memory is being freed without the handler having been invoked.
    BOOST_ASIO_DECL ~completion();

    // Records that handler is to be invoked with no arguments.
    BOOST_ASIO_DECL void invocation_begin();

    // Records that handler is to be invoked with one arguments.
    BOOST_ASIO_DECL void invocation_begin(const boost::system::error_code& ec);

    // Constructor records that handler is to be invoked with two arguments.
    BOOST_ASIO_DECL void invocation_begin(
        const boost::system::error_code& ec, std::size_t bytes_transferred);

    // Constructor records that handler is to be invoked with two arguments.
    BOOST_ASIO_DECL void invocation_begin(
        const boost::system::error_code& ec, int signal_number);

    // Constructor records that handler is to be invoked with two arguments.
    BOOST_ASIO_DECL void invocation_begin(
        const boost::system::error_code& ec, const char* arg);

    // Record that handler invocation has ended.
    BOOST_ASIO_DECL void invocation_end();

  private:
    friend class handler_tracking;
    uint64_t id_;
    bool invoked_;
    completion* next_;
  };

  // Record an operation that is not directly associated with a handler.
  BOOST_ASIO_DECL static void operation(execution_context& context,
      const char* object_type, void* object,
      uintmax_t native_handle, const char* op_name);

  // Record that a descriptor has been registered with the reactor.
  BOOST_ASIO_DECL static void reactor_registration(execution_context& context,
      uintmax_t native_handle, uintmax_t registration);

  // Record that a descriptor has been deregistered from the reactor.
  BOOST_ASIO_DECL static void reactor_deregistration(execution_context& context,
      uintmax_t native_handle, uintmax_t registration);

  // Record a reactor-based operation that is associated with a handler.
  BOOST_ASIO_DECL static void reactor_events(execution_context& context,
      uintmax_t registration, unsigned events);

  // Record a reactor-based operation that is associated with a handler.
  BOOST_ASIO_DECL static void reactor_operation(
      const tracked_handler& h, const char* op_name,
      const boost::system::error_code& ec);

  // Record a reactor-based operation that is associated with a handler.
  BOOST_ASIO_DECL static void reactor_operation(
      const tracked_handler& h, const char* op_name,
      const boost::system::error_code& ec, std::size_t bytes_transferred);

  // Write a line of output.
  BOOST_ASIO_DECL static void write_line(const char* format, ...);

private:
  struct tracking_state;
  BOOST_ASIO_DECL static tracking_state* get_state();
};

# define BOOST_ASIO_INHERIT_TRACKED_HANDLER \
  : public boost::asio::detail::handler_tracking::tracked_handler

# define BOOST_ASIO_ALSO_INHERIT_TRACKED_HANDLER \
  , public boost::asio::detail::handler_tracking::tracked_handler

# define BOOST_ASIO_HANDLER_TRACKING_INIT \
  boost::asio::detail::handler_tracking::init()

# define BOOST_ASIO_HANDLER_CREATION(args) \
  boost::asio::detail::handler_tracking::creation args

# define BOOST_ASIO_HANDLER_COMPLETION(args) \
  boost::asio::detail::handler_tracking::completion tracked_completion args

# define BOOST_ASIO_HANDLER_INVOCATION_BEGIN(args) \
  tracked_completion.invocation_begin args

# define BOOST_ASIO_HANDLER_INVOCATION_END \
  tracked_completion.invocation_end()

# define BOOST_ASIO_HANDLER_OPERATION(args) \
  boost::asio::detail::handler_tracking::operation args

# define BOOST_ASIO_HANDLER_REACTOR_REGISTRATION(args) \
  boost::asio::detail::handler_tracking::reactor_registration args

# define BOOST_ASIO_HANDLER_REACTOR_DEREGISTRATION(args) \
  boost::asio::detail::handler_tracking::reactor_deregistration args

# define BOOST_ASIO_HANDLER_REACTOR_READ_EVENT 1
# define BOOST_ASIO_HANDLER_REACTOR_WRITE_EVENT 2
# define BOOST_ASIO_HANDLER_REACTOR_ERROR_EVENT 4

# define BOOST_ASIO_HANDLER_REACTOR_EVENTS(args) \
  boost::asio::detail::handler_tracking::reactor_events args

# define BOOST_ASIO_HANDLER_REACTOR_OPERATION(args) \
  boost::asio::detail::handler_tracking::reactor_operation args

#else // defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)

# define BOOST_ASIO_INHERIT_TRACKED_HANDLER
# define BOOST_ASIO_ALSO_INHERIT_TRACKED_HANDLER
# define BOOST_ASIO_HANDLER_TRACKING_INIT (void)0
# define BOOST_ASIO_HANDLER_CREATION(args) (void)0
# define BOOST_ASIO_HANDLER_COMPLETION(args) (void)0
# define BOOST_ASIO_HANDLER_INVOCATION_BEGIN(args) (void)0
# define BOOST_ASIO_HANDLER_INVOCATION_END (void)0
# define BOOST_ASIO_HANDLER_OPERATION(args) (void)0
# define BOOST_ASIO_HANDLER_REACTOR_REGISTRATION(args) (void)0
# define BOOST_ASIO_HANDLER_REACTOR_DEREGISTRATION(args) (void)0
# define BOOST_ASIO_HANDLER_REACTOR_READ_EVENT 0
# define BOOST_ASIO_HANDLER_REACTOR_WRITE_EVENT 0
# define BOOST_ASIO_HANDLER_REACTOR_ERROR_EVENT 0
# define BOOST_ASIO_HANDLER_REACTOR_EVENTS(args) (void)0
# define BOOST_ASIO_HANDLER_REACTOR_OPERATION(args) (void)0

#endif // defined(BOOST_ASIO_ENABLE_HANDLER_TRACKING)

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/handler_tracking.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_HANDLER_TRACKING_HPP

/* handler_tracking.hpp
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
*/
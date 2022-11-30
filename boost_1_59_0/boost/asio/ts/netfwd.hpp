//
// ts/netfwd.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_TS_NETFWD_HPP
#define BOOST_ASIO_TS_NETFWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CHRONO)
# include <boost/asio/detail/chrono.hpp>
#endif // defined(BOOST_ASIO_HAS_CHRONO)

#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
# include <boost/asio/detail/date_time_fwd.hpp>
#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)

#if !defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)
#include <boost/asio/execution/blocking.hpp>
#include <boost/asio/execution/outstanding_work.hpp>
#include <boost/asio/execution/relationship.hpp>
#endif // !defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)

#if !defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

class execution_context;

template <typename T, typename Executor>
class executor_binder;

#if !defined(BOOST_ASIO_EXECUTOR_WORK_GUARD_DECL)
#define BOOST_ASIO_EXECUTOR_WORK_GUARD_DECL

template <typename Executor, typename = void, typename = void>
class executor_work_guard;

#endif // !defined(BOOST_ASIO_EXECUTOR_WORK_GUARD_DECL)

template <typename Blocking, typename Relationship, typename Allocator>
class basic_system_executor;

#if defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)

class executor;

typedef executor any_io_executor;

#else // defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)

namespace execution {

#if !defined(BOOST_ASIO_EXECUTION_ANY_EXECUTOR_FWD_DECL)
#define BOOST_ASIO_EXECUTION_ANY_EXECUTOR_FWD_DECL

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename... SupportableProperties>
class any_executor;

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename = void, typename = void, typename = void,
    typename = void, typename = void, typename = void,
    typename = void, typename = void, typename = void>
class any_executor;

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#endif // !defined(BOOST_ASIO_EXECUTION_ANY_EXECUTOR_FWD_DECL)

template <typename U>
struct context_as_t;

template <typename Property>
struct prefer_only;

} // namespace execution

class any_io_executor;

#endif // defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)

template <typename Executor>
class strand;

class io_context;

template <typename Clock>
struct wait_traits;

#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)

template <typename Time>
struct time_traits;

#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)

#if !defined(BOOST_ASIO_BASIC_WAITABLE_TIMER_FWD_DECL)
#define BOOST_ASIO_BASIC_WAITABLE_TIMER_FWD_DECL

template <typename Clock,
    typename WaitTraits = wait_traits<Clock>,
    typename Executor = any_io_executor>
class basic_waitable_timer;

#endif // !defined(BOOST_ASIO_BASIC_WAITABLE_TIMER_FWD_DECL)

#if defined(BOOST_ASIO_HAS_CHRONO)

typedef basic_waitable_timer<chrono::system_clock> system_timer;

typedef basic_waitable_timer<chrono::steady_clock> steady_timer;

typedef basic_waitable_timer<chrono::high_resolution_clock>
  high_resolution_timer;

#endif // defined(BOOST_ASIO_HAS_CHRONO)

#if !defined(BOOST_ASIO_BASIC_SOCKET_FWD_DECL)
#define BOOST_ASIO_BASIC_SOCKET_FWD_DECL

template <typename Protocol, typename Executor = any_io_executor>
class basic_socket;

#endif // !defined(BOOST_ASIO_BASIC_SOCKET_FWD_DECL)

#if !defined(BOOST_ASIO_BASIC_DATAGRAM_SOCKET_FWD_DECL)
#define BOOST_ASIO_BASIC_DATAGRAM_SOCKET_FWD_DECL

template <typename Protocol, typename Executor = any_io_executor>
class basic_datagram_socket;

#endif // !defined(BOOST_ASIO_BASIC_DATAGRAM_SOCKET_FWD_DECL)

#if !defined(BOOST_ASIO_BASIC_STREAM_SOCKET_FWD_DECL)
#define BOOST_ASIO_BASIC_STREAM_SOCKET_FWD_DECL

// Forward declaration with defaulted arguments.
template <typename Protocol, typename Executor = any_io_executor>
class basic_stream_socket;

#endif // !defined(BOOST_ASIO_BASIC_STREAM_SOCKET_FWD_DECL)

#if !defined(BOOST_ASIO_BASIC_SOCKET_ACCEPTOR_FWD_DECL)
#define BOOST_ASIO_BASIC_SOCKET_ACCEPTOR_FWD_DECL

template <typename Protocol, typename Executor = any_io_executor>
class basic_socket_acceptor;

#endif // !defined(BOOST_ASIO_BASIC_SOCKET_ACCEPTOR_FWD_DECL)

#if !defined(BOOST_ASIO_BASIC_SOCKET_STREAMBUF_FWD_DECL)
#define BOOST_ASIO_BASIC_SOCKET_STREAMBUF_FWD_DECL

// Forward declaration with defaulted arguments.
template <typename Protocol,
#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME) \
  || defined(GENERATING_DOCUMENTATION)
    typename Clock = boost::posix_time::ptime,
    typename WaitTraits = time_traits<Clock> >
#else
    typename Clock = chrono::steady_clock,
    typename WaitTraits = wait_traits<Clock> >
#endif
class basic_socket_streambuf;

#endif // !defined(BOOST_ASIO_BASIC_SOCKET_STREAMBUF_FWD_DECL)

#if !defined(BOOST_ASIO_BASIC_SOCKET_IOSTREAM_FWD_DECL)
#define BOOST_ASIO_BASIC_SOCKET_IOSTREAM_FWD_DECL

// Forward declaration with defaulted arguments.
template <typename Protocol,
#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME) \
  || defined(GENERATING_DOCUMENTATION)
    typename Clock = boost::posix_time::ptime,
    typename WaitTraits = time_traits<Clock> >
#else
    typename Clock = chrono::steady_clock,
    typename WaitTraits = wait_traits<Clock> >
#endif
class basic_socket_iostream;

#endif // !defined(BOOST_ASIO_BASIC_SOCKET_IOSTREAM_FWD_DECL)

namespace ip {

class address;

class address_v4;

class address_v6;

template <typename Address>
class basic_address_iterator;

typedef basic_address_iterator<address_v4> address_v4_iterator;

typedef basic_address_iterator<address_v6> address_v6_iterator;

template <typename Address>
class basic_address_range;

typedef basic_address_range<address_v4> address_v4_range;

typedef basic_address_range<address_v6> address_v6_range;

class network_v4;

class network_v6;

template <typename InternetProtocol>
class basic_endpoint;

template <typename InternetProtocol>
class basic_resolver_entry;

template <typename InternetProtocol>
class basic_resolver_results;

#if !defined(BOOST_ASIO_IP_BASIC_RESOLVER_FWD_DECL)
#define BOOST_ASIO_IP_BASIC_RESOLVER_FWD_DECL

template <typename InternetProtocol, typename Executor = any_io_executor>
class basic_resolver;

#endif // !defined(BOOST_ASIO_IP_BASIC_RESOLVER_FWD_DECL)

class tcp;

class udp;

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_TS_NETFWD_HPP

/* netfwd.hpp
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
*/
//
// ts/netfwd.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

#if !defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

class execution_context;

template <typename T, typename Executor>
class executor_binder;

template <typename Executor>
class executor_work_guard;

class system_executor;

class executor;

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
    typename Executor = executor>
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

template <typename Protocol, typename Executor = executor>
class basic_socket;

#endif // !defined(BOOST_ASIO_BASIC_SOCKET_FWD_DECL)

#if !defined(BOOST_ASIO_BASIC_DATAGRAM_SOCKET_FWD_DECL)
#define BOOST_ASIO_BASIC_DATAGRAM_SOCKET_FWD_DECL

template <typename Protocol, typename Executor = executor>
class basic_datagram_socket;

#endif // !defined(BOOST_ASIO_BASIC_DATAGRAM_SOCKET_FWD_DECL)

#if !defined(BOOST_ASIO_BASIC_STREAM_SOCKET_FWD_DECL)
#define BOOST_ASIO_BASIC_STREAM_SOCKET_FWD_DECL

// Forward declaration with defaulted arguments.
template <typename Protocol, typename Executor = executor>
class basic_stream_socket;

#endif // !defined(BOOST_ASIO_BASIC_STREAM_SOCKET_FWD_DECL)

#if !defined(BOOST_ASIO_BASIC_SOCKET_ACCEPTOR_FWD_DECL)
#define BOOST_ASIO_BASIC_SOCKET_ACCEPTOR_FWD_DECL

template <typename Protocol, typename Executor = executor>
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

template <typename InternetProtocol, typename Executor = executor>
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
PjsG7GFuxvzVzmejisePnjxNbPnaeIf8RvoL9Xg8If6Hg/zAPu2laa+h31ADPxWb1SZvSj0j8BvTtNH89pj4t1vyn6XPFTwqcb3If4G0LRkfKM8h5S22yymrHV2mo91GG910TdcshK7cZn+xl+ajTUKzwwjyJ+1vBuxUSPxLxplkkvGJSTPAEL9uRxVly9PC85lCf5Gd52lnc6uU94y9Pi2VnhMPMl7sREMWfeAh36eVfRjK9z3hTzkD39cF3z8MbG+XoZwH4XOh41nmQp1P7XOhxML7dl7vLP6ykLmwWPtniX9ZiIwu1/7ptrnyXQzvf+UenRvYC312+lP7XMF5MhiEDJ0rnThXAvTN9FzJ+Qx+7LiGys5emraJHpcaQvtnGy9yjpC2oZaz2UL7edjz4XJNW1/Pp0yh/do+t8lHl0rcA9a5IenJ89K/Z5LlIyX9Esu86KfnRbrE/Smch8nzqRL/vWoIHoshj2neishPFZOnb30WTZ52CpGnM0J4bHoIj40M4bHetuf4qdiQc5VcLw3/3M4z01UkXiEdUkeSo4wLt0Nmi+NcrcC9ImY7moX0Q17IXOoYpZ2+RCU/bGeqOsTLzOdISDvt8r2U7SQd+DyVc+Ih8RuOXsoVZiuY7WeahtpG0Ebxuxx9lDPUXrC2B/SA0Hgd/VB79hXzqW+/4yhoT4u8SZvaJq9zXrwt6fYZNdVCw7SfncHOXCfhF6oMCZONfNK+DlpD8svxyHklZBeUuU1Oi71xI+ROJW0v7Zjk8RrO8mXK+bgPYsV+f8g9RnFnvMdoi5RxXlQbUJskvpH/HiOWkZug7zF63X+PUWyF7jEaKHk1iFpWP4lvLmX1BZ+aTU5P0Ta4w+4U4r1CDNf2uq1x2lZrBs8T50fmd22zLM9y19DVX0R7rpT67QKrcFvBZToMfBbpjiFltwH5amIEmy+Qmx2/DN43YRoTnl3YqXDSlKLC3pHlAunD534vWxzvgfrFc7+3rQ1deDJtLd8Bl7ANw8Pa0DlCGzqzDQH6evo5uOjLqO+CpD1PP5OuFX+p5ZlijhnlgMS15xk7u53JdGCZxF9OP2al+HPO+AwrF5pRtA8cfA49DnyZz55vK3A/hslnUh75zN7vnSP1u7a1vlj+he4sXBr1KnubZ0S/0v0OOzyjJhbK67vYBR4xdcSkSPd8MU1VLct6iH+RmoLywvqf9Fa7at3Efwv0ggyhP0/sbY7XsrhE4gdDClaRuwWy2AmFEp6isiVMZKOmPV8lmfTa9uOBDNNVpE+tfTj2jLw7j3ePXA3nFn0o0LTEP1+nKIutXFzUMGJ6sd9EaJgNzIzAu6GkKVbmv2Pg2LfMy2ftF4nra/ajxF0mfTLB4HpSwtJUhoRJoKZrqKpU+Cxo0M6l/Yx8blpk24FrUEZFbQeC9oy2A9d+nfKr2A78gHWtStmYDNfdtBGD/GmvQdYRE1XE91DSVY1ot5VxFV0T9Qznrd4hvDXWVvcsLgDaIPPzgDWB5lrvdEjdZ9neC2ax7qSzyMOMb0x/nOUddzbbEqC9QMunWkLrstAGbZtXlbirxF+g0zZgPPj2W3n/tshLmFfpHTyT3FrSf6pSreuj0ThyzDVSs/A1kpbTn0naNsq6PmogYS8yTPhd03FtFHwPYBtukvjrwurM+wJkHdAhQ5ysHbyZ4mStcCP8z1vsHRecZU2Qb1kTSL0oq+3r/Fkh75KzQ94le9N2sl4LsM+C569L/g/OX/9a56w3yTnrHc99M+EfdWceuW/GrXc/mv5TUuU563/HOWs+B2RNn8dz1ua3HR/vcOF5I35Dl2/9iLOfN8JZlbL6wNU8x7MWOMWkpX75OuBs4HrgAuADPEc=
*/
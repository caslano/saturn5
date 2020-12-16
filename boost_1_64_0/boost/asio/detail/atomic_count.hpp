//
// detail/atomic_count.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_ATOMIC_COUNT_HPP
#define BOOST_ASIO_DETAIL_ATOMIC_COUNT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
// Nothing to include.
#elif defined(BOOST_ASIO_HAS_STD_ATOMIC)
# include <atomic>
#else // defined(BOOST_ASIO_HAS_STD_ATOMIC)
# include <boost/detail/atomic_count.hpp>
#endif // defined(BOOST_ASIO_HAS_STD_ATOMIC)

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS)
typedef long atomic_count;
inline void increment(atomic_count& a, long b) { a += b; }
#elif defined(BOOST_ASIO_HAS_STD_ATOMIC)
typedef std::atomic<long> atomic_count;
inline void increment(atomic_count& a, long b) { a += b; }
#else // defined(BOOST_ASIO_HAS_STD_ATOMIC)
typedef boost::detail::atomic_count atomic_count;
inline void increment(atomic_count& a, long b) { while (b > 0) ++a, --b; }
#endif // defined(BOOST_ASIO_HAS_STD_ATOMIC)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_ATOMIC_COUNT_HPP

/* atomic_count.hpp
7efBT8i/Nh090uDjlaoqpb7YrdnMmdB8oxyeSdjdrM8yiAOr1NPJXEgs1E5ALmQPH0oK3/tHIBv1druk8dBOgV81duwD/5c4r4TXfuxyYRXy024z7T4D42k3AR3LiYlo6J9F+RSQPJ/8gfgUm905k2PsngT2Mc60cP52s7QF2cYZm4OMFvS3SBUpjBvF0M5AZ8r3eFgjNlLewBxFepJXakD+qdCyJKAj9tqFnW/DF5MrkQ/7v06cbID/DUPQAXusoHxwEfEIPbfpByOxMfyWNSEL7d5iDD4O3Z6E5qf4pmcF9iBev5tKvCBHiY01BnG7Az/PKaH/48ed6HAJsRiWwBqC+BsJv2nY9EH4fZjL/DcI/4Bn8PFryNjUCM0y1tuTGf/gdym2uw9bLGqVeF2t5kO/rBIdx2Jf6p8PrZ4FUv0I/EfbZSPhD5/n4onfevowfNKwc0014y08licwnkDr4cHEvBdfc/wRbe5NYa0LX4dd7FFDNg/jB2UvULYJXZJboV/K2IJdjmtFD6tUOJF2NuIfZMLrXWSzIMfp1Lkb2Trwz6gWxgInNm4ihmkXhz12Qf9R7PgAtmglvdFLHTc0XVIYfnkVvRvIGz8LP4HTCmlDXl9skoR/Gql3jQfbxOOvDHin4WeOi/DfZHg+P472xNpQ2pxObLnwb9Uw4hkfFiPfTuMn5NmODcfRdj9yraPswn7YlPZJtZIXu67CZpPM57p9Yi8f8YosNXPRE5vchEwbKX8pFV60fSpZ6jmVNRp23ZzCOoI2cyZAM09a0kbf9eFz6s7FH/EV0i110lL8cR74PrDS/vfQuxjaM5G7LVHyQm8/cj5bhd+gYTXjJ77PSZfqEmkPzb3o+YhD+uEY1htmnY+v8tFxeM43n6SLgdakCnSPp7+UExceqRp6J+Cj9EJ8zvEfc6UCsA/Zx7rQwUl8IPvGYmKb8gmUjUfexWZ8pZ/GYoMFcfgLWVc101/ipK3o2Yz9VlO3lvZ1yPmHBPRDtmtd+Id2qdX0V2xbUsQ6Ad1izRqC9G34PF4qvnFJvMzGV8j5BjbJTER29MqAnq2FeLFKpfPx7yD6bjIyY/efwLM3MTMCOSYWsv4E5lMmy4jNsHHoQBxmD6Ut9oiF7inQTG/F1tT/M/7oY64jiKt24kQOUnzXl3aLqP9pPmuLRPyGXB0cb01ANs7b0WEFcj2B7KX4os1HjBTjuyZ4k95I+QLKe9cxVnA8eTR9Fxr3TqIOsZgG/eR0ZIBWC7bYgs9inNJ22h/AJnkOaGQwP9BXbMczx1G/GD2jhkKHdAW+GUn7H6DDftJfQONK6J+IHcIofzIDPmZun0mZF1kK0IfY6TkG+abgL7OGg0YSOpvXRGaQ76P9GvhYXfirlTUQeUvrmXdbaEfdB5B7ILZaTp1SaJVA+yvqJGYSa+nQMzGdJ+2mTNj8DrABGX6NPDuQc7MXW6KbrwzfDZDikekDu1RI283Q+j68LqxjPqqWlsHrNurfCo3eVcwNNsaqUcR5MbaA35w47O2AJ2mmWd/ORy7a5kFjHH7yNoj3iBJzXmyUDy1zHZjNOML49AVxn0P9/SCNNn8YgZzJ0mboX08cpCDXu7S9DtpnIeu2RHw1Fn/ksq4ZyfqSMcYGrd+jy+z+9Hvkr6+DbyI8nFIC6dugP/V2xSHvIGLeBt0k8rDXbnSbCJ1obHMGaXMe4zztbi+U9lHneOS4p4428JtC+iwy/QWbv1eBbXxSG/aZZ6MO+dtpn0y7nvTxgiL6tJe60GvJwC/YvQx7bUKOVch6Ev0vzMwr4ExonYsvt5n5A/9ejn9/Rfnp4Ox45ifKIikbNJp6BcQkx083MB/AKxxbxhD3mRY=
*/
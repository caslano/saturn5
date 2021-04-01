//
// detail/reactor_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTOR_FWD_HPP
#define BOOST_ASIO_DETAIL_REACTOR_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_IOCP) || defined(BOOST_ASIO_WINDOWS_RUNTIME)
typedef class null_reactor reactor;
#elif defined(BOOST_ASIO_HAS_IOCP)
typedef class select_reactor reactor;
#elif defined(BOOST_ASIO_HAS_EPOLL)
typedef class epoll_reactor reactor;
#elif defined(BOOST_ASIO_HAS_KQUEUE)
typedef class kqueue_reactor reactor;
#elif defined(BOOST_ASIO_HAS_DEV_POLL)
typedef class dev_poll_reactor reactor;
#else
typedef class select_reactor reactor;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_REACTOR_FWD_HPP

/* reactor_fwd.hpp
2tnPnJvu59TROLqCE87xqL64MLv0LZUTX+rI4g0L28/dDaB7FySZM++DarGq5Evdv8qhmEoZl9Sa1iL+leUPBoIV3ezhuoFr8DNwFNk3DxsA2uJWlIbfg9QnSwxexVJFzOeo6LwwUGrSXuJGJttRY8XgD7SgcgRqDK86DmzhaSsF+dTP+rf8Q3jyqngwoHXaR+IBmQg4PBgqeyIB0StDJSSBrB2f/DQMHUrxtJkLc8a4I0o7WUdp6wwaQxHK9aX2AajO6dcgXFWY5Xg+u1maPBPxw83Wi1l8K5gIXsYN/fkDYV6510/FNqfVirx1I2/cG9/vQpxVat3BuKTBjL/Ytcad4Y/ASZVL5zLHPge7oiyxwt6GUSdyKYSpdiM23bIsRiT4V07oQ5/L6w94E0rqmTVISGJA6FtaUl7+rCcjDVjZ7VSiqvgNt7wnzeeftZkvun5ZhPAp/2MTOEibmq41NlaXU5CnH1DYqRIF+06ZUwVcpG9eb/jcdnKB6crG7QeOre+2K1o1cIInAJJBmrUabnkI08L/wF/dcbbrvr67IxOGLpDyrEExFcTmXw==
*/
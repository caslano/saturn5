//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_SERVICE_BASE_HPP
#define BOOST_BEAST_DETAIL_SERVICE_BASE_HPP

#include <boost/asio/execution_context.hpp>

namespace boost {
namespace beast {
namespace detail {

template<class T>
struct service_base : net::execution_context::service
{
    static net::execution_context::id const id;

    explicit
    service_base(net::execution_context& ctx)
        : net::execution_context::service(ctx)
    {
    }
};

template<class T>
net::execution_context::id const service_base<T>::id;

} // detail
} // beast
} // boost

#endif

/* service_base.hpp
MD5DK9e0tSF9bzjgDvj7A5v6wy72SrYMox5SWOn+p8FL/2Ylf4QEIRqnVEVLdeNcXtHHKstOJBShWSAnnT1g0z7kwgjTt+hwUyaHVlHaVfGQFadiZDIcM/vQtRRMJWMxtMDabuPgkFOB9zO8nPdzEycLEw1L1KQaiaMjwvZxCZMAbzMDtzgfo8WdeSst5F2hCtQWoY2g8ZjHFJAY6RgakTDGGEIiBjc3U3Rk51O+07wcm02R
*/
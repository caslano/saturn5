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
cNNntcOkwgSr161PmjCghy8RW/sn3IgcT9y+/NIonJUY4cCZ9zg3HOPR627ZB2IkfF9pPQnr0X7qQLnsADRDc3GIUmP1qcwx42LSt4XuTT7TCbw7ng6Qy8M4lA75peRwd8PbwYcsJZae5+NA18BdZ1KjLfTxHmaD4Ye2JEvIi66B/5TvmAoqe2bSLjE8qCYQwrv1ZoGQvFfAbbe1b4kAQt/9OqdAMyzpq44jG4XnebL4GJB+wotB3qIFzPq24HOtt+HThxsUn5p4WCxj+6f3QboySz1aquKwCECLfxi5VBPxY8G31p/ZA1Bgb2p2vrUWKXGc/wsSEquq8Y4MXbQqVGW/6YwvcF2lmEKiPztA3C+71icD3Ydbiylg0Hdo+yZpHaugOoHgC3mW7+cb+14Qao7IMX5XysTs1nkF0vu5C8QI/9qFBiCE5F7cVdwkKrewuPR27b9xI9P1OWUPRMt7/ARyVl5g/dLY0LbocZLKkp/EauN/z/D5S/+GcJzABgD3r1/mCdW8SQBWWAD4Sl7j97BzrO4SBmctsp0Th9eKN8zm51X4+522CZ1DCg==
*/
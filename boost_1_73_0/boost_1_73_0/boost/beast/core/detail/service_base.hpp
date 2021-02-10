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
iJxy4QVaEEsiVKeo9C1nbiZnxi7xxXkJMaw4b6zSU0KB0LJilU/a77e+9Dudn5TOyiqXtO98rkyvOHy4VKr06zW2ymsbi9yTdWPyOkQq8MwfwaVR/fKpQ3BWWNqpPd3Du1P/ysSH217nyx4rCq+yZr1zxampjRw1+eneGZXTTmY0htqjzBsmVi8aCGlMtSgSaOdR59MazkrMFh7pIKwgIUEhOPSI4+wvRLuPfouCeXjeBjf3FsIMUZqsC9WXh3W8PHJ4CYgv1j68oFcRI6tJN6ge0PDy7CwK6QLH7pCp/Lq8z7hk/GGOGvhJd0sbT1Kbalq0DdBtsAHhMXPonmDwRm8FHGrWaZffvrDjG07CdXixVy9m82X3580Q/lxF8FfEfNLWoA0m2mut1aEdrL7sPYTZMATE3ZC+xq21BnxDjKAxpUPV6xoeXV6cof7otKQAA5XBNC9mJmeydcHYY7UKk9JUCk+9VcSzulaoQ0j4QpUlT97UYuSYtbWUOdKYLsO8tukVqQG7h3LU9pqW2t1rCqdNPatg7sD3c8Ph8MhBg/2fliYVZaK08l2OIHl/dv7b4CwZoFzBTxjhjwGWNUDJzjE31KjrHAA2vEnhlrW9lQE3lxkInzht4Iyp9BvaQd5Jj22iu2EuDgk9/zhO
*/
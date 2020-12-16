//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_TEST_TCP_HPP
#define BOOST_BEAST_TEST_TCP_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/detail/get_io_context.hpp>
#include <boost/beast/_experimental/unit_test/suite.hpp>
#include <boost/beast/_experimental/test/handler.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <chrono>

namespace boost {
namespace beast {
namespace test {

/** Connect two TCP sockets together.
*/
template<class Executor>
bool
connect(
    net::basic_stream_socket<net::ip::tcp, Executor>& s1,
    net::basic_stream_socket<net::ip::tcp, Executor>& s2)

{
    auto ioc1 = beast::detail::get_io_context(s1);
    auto ioc2 = beast::detail::get_io_context(s2);
    if(! BEAST_EXPECT(ioc1 != nullptr))
        return false;
    if(! BEAST_EXPECT(ioc2 != nullptr))
        return false;
    if(! BEAST_EXPECT(ioc1 == ioc2))
        return false;
    auto& ioc = *ioc1;
    try
    {
        net::basic_socket_acceptor<
            net::ip::tcp, Executor> a(s1.get_executor());
        auto ep = net::ip::tcp::endpoint(
            net::ip::make_address_v4("127.0.0.1"), 0);
        a.open(ep.protocol());
        a.set_option(
            net::socket_base::reuse_address(true));
        a.bind(ep);
        a.listen(0);
        ep = a.local_endpoint();
        a.async_accept(s2, test::success_handler());
        s1.async_connect(ep, test::success_handler());
        run(ioc);
        if(! BEAST_EXPECT(
            s1.remote_endpoint() == s2.local_endpoint()))
            return false;
        if(! BEAST_EXPECT(
            s2.remote_endpoint() == s1.local_endpoint()))
            return false;
    }
    catch(std::exception const& e)
    {
        beast::unit_test::suite::this_suite()->fail(
            e.what(), __FILE__, __LINE__);
        return false;
    }
    return true;
}

} // test
} // beast
} // boost

#endif

/* tcp.hpp
m+k4eYXE8WpgA8fDjq+orZHORx1prrEBYeJvpWM96b3H/r6Nuf7Ok/i31BzvbCh11CcOb7PuR3lr38+TeDq6+pHPCDlmxf1poDuPp/hqXZgpK9LIJ0Imjiur48YcSd0vcznyjptfJRL2d4FBjkucC5xNnW9RX/0DAh0rAibKvKW/pENGN3NPv0Ti2MoMsZsjTo7Z4qEv3Yafd1xP0jc6ENNWvY67eRL5Vt1Xxni+k8N+HvHfiLwf4VuGE+Z5/F9BtiM7kBHa7zKRdMTaOzSS41epH2GgZzjcnBe646zmXCNC3y2dVMk15Ghj/Waz3it8h1yPfsjHfvurfdIgbWGGV39tIv3ViuMdZq4h7J3ozrdXu+haBK1B/Fpydx/q3XdN/xsnOuMc7XQd8hITLsbvfOBq8a/laEl91sI9SuvxXMqtI3KF0iq/blWUXwqc4aP8rHut+ZEV77XmoJ92SMvPtoirt57Sv27wvPdE/7ffe95gv9/XtcXTkb7vPWf7SNeZrC+G5Pq/78yNqlgWvydti32cU247f8N9Zy/N35Eo3/krLZVzVfbAocr13Sbk9VPiXyPPIvIm0tAnkl2CevadxU0q5ncu+d1yqPI02Nd9+ni1gy1n1g562dtBH20H9nIKaeq7nA5UXk5ntAaUkm1vE55zorlNK5bRPNJ5tPIy+k3rQVbbP+knzwm79ZzmIY4kt8r2YOXzQI6Ptq/nLI72fc6jWs7eD6Ac1Tiv1Q4PZPtshya/h32fm4lzxXOT8CrPa54l+MjvhVa9xlSs15up19hP9JxeDw7tY19/zzZPmN/e5vt7rLvp2Bfj57lKqe+0ncn4dyDLf5nkN6tYJvNJX5qfMvmtY2AXa7xtXvF8Cznf7LLzZSflpZvnKNZ4s8Cz7FVXr6eh+NHOzL2dlz9zNn6zLqP+uepvr7uCkOrX3QKtuzB9BsL5cXP+8vsO6D4m5/S81sRWzPttxFdiz7t9nVPzv8gr/+j7z7/6+88//meWf4/r9qJ/IP8rW5ZFWFe/of0jcgfxHfDKv5mpaf5v98y/6nc091T1P5U5G0+8avkrEw0TZ+b8NSXMIcco/vdTThrmfF0r8rbFoPc5Es9LaAWTVmOzwaxX1hX/A7b5oue6RZH4j3NEsGaTT/vY0II+6V6zqRUd3IBEldeRru2o3r4WurZTP8t7/cfonEZH1382+dOJbWl0PvDWkWdSOh+9OsbNM7M9f7utraT6aCtpXm2lvupRhhwr9Bg3wvVD5GFOfeYOO/Mj4TN72zEtR+oiMdKj3ahuC9NuBov7qCOX//20G8J4PnsdJO6vWe2v6d1uRCcCDhCdLxzZ+nw318TTVMLEh1e8b5gk/n/CJnmIsf1fR8t8gjKymusfVvknRp5Z+dvLm6Ux+WOLt6wLtYTu8l582F7ek/OmZBbnDMiZ7qu8Vbed6XObxO1y9eRMfspbw8RKmCtxl4g7yNXXUcNfP9Uwyd5la9biQj53+z/o9Oqfsi62UcLWcoXp/Q1+ZCp9PFkydb5ddI47E7WdpISKnuhYzxWulXOcMPZYrvkCN1fZiHJ7LNdmpReMKU4vT3so/FbChXIuTZvq2b8bcUR04tHBTdzdJO5rWX1sKONGZGt02nAtlnEjwve4oXoh5HG09Pffu7z6u9FJNjpzSip71lBHv0VxNVI3DDdSwO9CtS+CW46HWu23WmNHYOjsL8yzBn2+7dmWh/toyxneY4nq6VgitkM6Sry8TxPneV2iiVa4Lt+FTtqXpq173Ada85I7Pa9Lqu//uqz+/tox/r/9unznb7oul809+ZCq/F0QQN5hAsyO43hZ/nUjX5kBpCQx1eL3uYuGaW36zkpxhwc=
*/
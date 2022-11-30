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
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
*/
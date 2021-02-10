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
9rF1pQHCU1P7uwu2E8T4l1307/Z+NV9GWq4szo32NnCHBU5CMfmxAKK2zauMa9Pr17RqkLO36bg/lf4XXk/90/4xUA7xA8UNer6oFFUfdOckRyag/guK5RxbC1IEBc/xqUaoJGBD7xsalLp5tHaWDple/VOM1o5Wj3ldOeW4tpccCTx+vout0rlZwzYBMl/Kn49l3J4g76/Qkz9ew7Aj1rrbd+jV4wf9xbt++y/1wN5Wd6vSXSEp7gX22BLPDu8YwpYPJBzyIBN0FzPIymxp3hhdqn0fwt1nIWxi9DKMuz+A8defg/GxVfLQ97bu4q2ahuw6SGE5Yd3gqWEY5XrqVVR9rEopV67ZcgwgfOmd3F5f0PYU/Ip4k0dhHqs4TLgwE3+thWmtpAbCiBdrKj4W9m30D1nq6up68bYVweNpbTtrv/rpTLK+YYd9kDDaT2YpNvWMsIvH2LPs3ob6jCLrTz221gHsC402AI4NL8+vxqOzf4z21moVGgfsBRsIyxDO7tGmRlazM0UIoPT8+OJi9OH66vb9Bwcq9iWBrXePH4JfVolLxiS2PQVkZ0mQ+65JQfECF3NdEiuTBj0MuWK+auGHs+PTs+sx2g1nJwODSrJxeEQ3Eok/lQIGbzjTKmasyjg9Hh2/LIFd+/76
*/
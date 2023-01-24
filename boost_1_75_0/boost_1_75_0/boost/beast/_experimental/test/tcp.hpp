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
3FVEkR+4o3V3Xrhb785viZjPD4tTS2z0jaq6wHmxHZg2IkWhb792I33bB9+OPF4RRVbGKeEBdiiYDobPxT4Qg2F+2ARY9NuK6KetnoAWIlJfEV3PLJDzqlGQWJWWLm55ohJ5syKK3EaKeOgTD6GdT2TBaCjYXhHdKAvuh4K1FdF6WfA4FLxTEW2QBc9BwUsVUeQNhubNFIz3yrhpJCWYsgBNcaPO8QtIWAI2uaI3C4GjwEiFA3Zo9jfQBVPM+1CY9/4JMOaP4mInBMRR4Z/FXUV0dauHsInDn+HDNa0ewokhvAQfrm31EMx3w08D2zKDORTHjHMhRjRusdXPgxsCZLRzVD0Rj3xHUegqyT6WYXCAZbh5IUa3waOg8yHxJ42oIdzDWmY9nRDxJ8tekPzJCm6rtcfNwmdiNITSSv4co77BoCxhBqVUPpQawiKzSy+J86p0NR1JuIa8IBkVqmENT4DKLVMvpdRqLjNS7Efz2g/HyX0/L7YCkImr/y2etn7g0Xp+Jx6oOyt+24JEGQhU5W+CKEM/KqM24DeW4HHpbLSYFEzCynNEzTDGgEBmtNPKfCiI48N3GyHi9YH6nm/FP8gsTw65oCb+oVArfKElSiLrzdj8aiMYzMoM+CpmYhbd8PiTV04FX+Spuu1kcqvPb33uT37+8+fl570xn09eeQF8LQ2nQMAorFpBnI6QAJJU4nQpaW9NO1PTqrMx
*/
//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_SERVICE_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_SERVICE_HPP

#include <boost/beast/core/detail/service_base.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <mutex>
#include <vector>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

class service
    : public beast::detail::service_base<service>
{
public:
    class impl_type
        : public boost::enable_shared_from_this<impl_type>
    {
        service& svc_;
        std::size_t index_;

        friend class service;

    public:
        virtual ~impl_type() = default;

        BOOST_BEAST_DECL
        explicit
        impl_type(net::execution_context& ctx);

        BOOST_BEAST_DECL
        void
        remove();

        virtual
        void
        shutdown() = 0;
    };

private:
    std::mutex m_;
    std::vector<impl_type*> v_;

    BOOST_BEAST_DECL
    void
    shutdown() override;

public:
    BOOST_BEAST_DECL
    explicit
    service(net::execution_context& ctx)
        : beast::detail::service_base<service>(ctx)
    {
    }
};

} // detail
} // websocket
} // beast
} // boost

#if BOOST_BEAST_HEADER_ONLY
#include <boost/beast/websocket/detail/service.ipp>
#endif

#endif

/* service.hpp
2056m0tv44iDdjm9ldLb0VfwbRq9bae3Cnq7hd5IvGi5kN7m09urS/Ctit5up7fF9HYZva2gt6bF+Laa3hbRWyO6h7Q46U2ht30v49tBeiugtxZ6O4PeJNJfOfASvtnobRa9pdDbTfSWSm/n0lsavW1/Ed8y6G0ivWXS22n0lk1vG1HjeXoevfnozUNvZ9NbIb6tWY3KKZaBi8iZRciSgr+mV1P6K/+ghQG1ElcmgoGaZIIoR/IjqFpSvhtA5/kW0s6NYTdABNt6xfMxhsXRTcmaTo8FhToNJpczSGn65luASdZQh+ftogXyPrL6Oc37yNhnNUjavVCDpOcWapB0w0INkpY8bYSkoU8bIem8p42QVLvACEmPLDBC0sgFRkj691NGSNrwlBGSXE8ZIenofCMkbZ5vhKSp842QlDPfCEmvPmmEpLFPGiHpsyeMkPT6E0ZICjxhhKQuTxgh6cd5RkhaM88ISSPnGSEpaZ4RkpY/boSkmx43QtKXjxkh6c3HDJBkmfgojY8A5/JHjWC09RENjBj81GQmS02Nu1RVg4VByxksfPQ1h4UpcyNgIX2OBgv7Z2uwcO1sDRYSZmuwUC1rsOB82AgLtUEjLDwSNMJCVtAIC8cqjLBQX2GEhVsrjLDQrcIIC8tmGWHhjllGWLh8lhEWmmcaYeHFmUZY6DzTCAv7y42w0K/cCAtdyo2w8GOZERaCZUZYGFpm
*/
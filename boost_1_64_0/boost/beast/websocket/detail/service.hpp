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
JL4WAZVdGn+3aDJb3TubOna62HsEIvvbNOO3g5mH6Sv219ROu5J1Ty2L9L9nmrBtzXi2l9gHuu5znknT9+JW1d0XE/7Y67Nsuddd/PUNuNZjEbZk67EGi7/efuuxjMwZK37qBtxyowfX9NwAIzcmFzyD2YOekAVTzlmF34qSJb/6qd3knxn3LdVvOI558Di+9U5+rGRruI5nDKJruNQefQ3X7du9beizCHvfx7xteAR2dXf2n0TWRt9X0H8/w+j7Dfrvcxh9P0P/fSmj7Yd5/GcmH+8+mdly1vR9iUfrDz/a86NFCTfs2VolJfv490U8UWdx++9XGW3/xuPft9N/H85o+21G36/S7Mmoe4zF2iZij6ck3ftqACwLBzp7xQVVx1d1p+1wPLq1Us9MmxBkTzI4BTaD02FrOAN2htVDVn4/tZ8BZ8JhcBYcC2fDyTAHzlD/C9WeD3PhMjgPPgT/BJ+E8+EeuAi+Dc+HB+AF8Ct4ITwK82E50nwRrAEXw6ZwCTwFXgz7wivhQHgVzIRXw1x4HZwDr4d/gSvgRrgSPgtvhZ/CNfAgXAtj7TkyWAv+DdaBG2FneA8cA++H8+CDcAV8FG6DmPz98Al4EO6ER+EuGKbAnoLV4TOwNnwONoHPwxZwD2wH/w47w5fhGPgqXAjfhMvgW3AlfAfeCt+Ft8P34H3wffgI/ADuhgfgc/Aj+Cn8FNry5yvYBH4D+8Pv4HT4PbwK/gTvhEfhLhigfD+AIfgbjIF1qFdlYXtYDvaE5eGZsAKcCqvAmbAqnAuT4FJYDV4Lq0PZc83oQkreSn1ta8+pQ/t3cph6AJvBlrAlbANbw46wDTwLtofjYAeYBTvBc2FnuBp2g1vhKXAPPBW+BHvAd2FP+AnsA7+CfeEP8DQYJi39YCV4OmwE+8PW8CzYEQ6DQ+AImANHw1w4Bs6DY+EiOA7eAM+GW2A63A4z4OMwEz4JJ8GXYRZ8HU6Gb8Ns+AGcBn+FM6Bdb2fDOjAH1oPnwiYwF54O58CJ8E8wC86H2XAhXAQvhhfDS+CV8FK4Ci6Fdjntc/TAVBeOcmI1PfVXy6lWiHKCdWEt2BB2go1gL9gEDoR3wlGwOZwAW8ILYGu4BLaBy2FbuBp2hPfBTvAR2Bnugl3gi7ArfB92g5/D02A5u5zgyXAA7ALPgD3hEDgEDoWZ8Ey4EA6DN8AR8CE4Cu6BY+DLMB2+DjPg53ACtIKUE6wBJ8N2cCocCKfBqXAGvAjmwqUwD14P58IVcB58GC6AL8AL4ZfwIpgYQu7BVnAZ7Av/DDPhFXAhvBouh9fAu+EK+BS8Cb4LV8Kf4R0wRLmtgVXhWtgE3qntsIvRvaEstL8JQ/0cYtG28yvCs2BDOAw2U7uGV50Sytwn/Cj8VYajYW04Bta17Rp+t6N/oLoghBd9y20a/t4Ae7XCB2B/+CA8C26GZ8OH4GT4KJwOt8LL4GPwSvg4XAd3wvvhk/AZ+DR8Fj4DX4C74XvweXgA7oHfwxfhb3AvrEDa/gErw32wJnwD1oFvBnSvUWetvK7tj43YO/g73bv0MKwHf4C2+4+wGfwJdoQ/w27wKBwHf4VZMKB7cQbhhTAE/wzD8DoYA2+HZeDdsCx8CJbXvXHj4Duwgj5fRfgDTIDxpDER1oU1YVNYC3aAdWAveDJMh3XhAlgfXgkbwztgU/ggbAlfgK3hm7Ad/Ap2hIdgJ3gUdobhIPUIloVdNR8pa137TVitV2Vgd60X5+peq7mwJsyDDeAc2ATOhS3VrnvM6rpqwmh87j1m5+uezgtgc3iehl8Cu8CFcCA8H46H+fyfru5OelcVk95pmt7pmt4Zmt6Zmt5Zer+ZGt9eZ00=
*/
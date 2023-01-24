/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_DELETE_HPP
#define BOOST_PHOENIX_OBJECT_DELETE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/call.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(delete_)
  , (meta_grammar)
)

namespace boost { namespace phoenix
{
    struct delete_eval
    {
        typedef void result_type;

        template <typename P, typename Context>
        result_type
        operator()(P const& p, Context const &ctx) const
        {
            delete boost::phoenix::eval(p, ctx);
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::delete_, Dummy>
        : call<delete_eval>
    {};

    template <typename P>
    inline
    typename expression::delete_<P>::type const
    delete_(P const& p)
    {
        return expression::delete_<P>::make(p);
    }

}}

#endif

/* delete.hpp
awoGXA2dZR1qC8UizpC4mdOIY+uGLh1Gc1HORuA24AjiLNyezzuCm4LebazdjAyc9NDm1To6XubmaShe+yDWaFOjzrMGaqwqxKyZk0s7w7oF4YYDrk6zDrMjhImH2JIi6DM9vCXTsZsTjh2Hcn/RMI0dx1njMi7TljAQ+yi4EWt1xNrIjdz12kFXxNoX+vBougPvHGuQcRGsaRuqdI41KqeUv6zvDtYQtw1EjC2dQI9lTYR1QJlu5gwDNxWN1Oi5up8xWV03ZGRrFHFO1h+urXWVtekDDfNHWnClkjHa/RiYNloDjnMzlIdHd92uEevs7rJrkKF1G2uRdQPidkgE9IYQyFrk4WH2jm5FaRstUUdZOtfQjJWtGYiXWTpSR+08bsj6vob5Y20O1pFEHo7s+j+YtT0bPcvkKccehEZqQVYMfy5y6WYNfgR0seKqIYdpM637f8G0cbw2f6IDlyIaG6KKCpM18OEpKF6jZXeUWujEoSRAJ7ciBANnXGCRvKeKaF020d8UDbvo26dUtNSVA9atsK3JybpBjPUbNutwB0JhQI7o1p4UfpDCjRRiLZbFIe6inI2WsfvBQRnB2g+n6JJxe7ddQZUUuDtv1xZPdOC6QhMjV7SrHkjPvMwtQB5O5GYpkf9xrB1FCqPkQIOOEFOsRXm7DS1Xp1djaKU2ZN2Qsr8xtHEfeuwWD9z6XJ6cC/fHZ+3dTaxBHo5r
*/
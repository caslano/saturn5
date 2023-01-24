/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_LOGICAL_HPP
#define BOOST_PHOENIX_OPERATOR_LOGICAL_HPP

#include <boost/phoenix/operator/detail/define_operator.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    
    BOOST_PHOENIX_UNARY_OPERATORS(
        (logical_not)
    )
    BOOST_PHOENIX_BINARY_OPERATORS(
        (logical_and)
        (logical_or)
    )
    
    using proto::exprns_::operator!;
    using proto::exprns_::operator&&;
    using proto::exprns_::operator||;
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* logical.hpp
4VGZM6zUoq5u00fA7tyVnC7E0zF1oZ1fNmsu7peUvRnyxh0zp2+CQnnhz+NWPG2zmER5WYZo04dHYMhw5fzNqQmjYwGnM/ZKy8O5jLKkCIy1EfGyknTfXGjM0QMY4VKE+HE43Hn6hb/n9ob4vnzx6Zb3Bb+JHisVCXD613zOSvhha027+HNd7rtI9uz3xqTTfg/EM9wAEILuBFJjCJkz9g9Q2Zb/u+5lgEWnHOgQgXjO0lMlH6qmXcrKaH9XaU2z6BehPhGEE6cotNPxsTbJFgHzyC5NQn6n3PrBgR2IUNO6gOkg1JW0LHlnd/RHM6ZVaasq1Vi7sCSBr56veopah7wqlU+dncyfr2rAE9/bNZKWRYlPf0KrcdgBVX8g5rwv17Oe/yt+wGDJsXlNyHQ6ojbiKkI2vAg8/AZSewvc0YXCnA5x1V9/nK8jr4zxN2TDpznQAtGyWFR3xH2JD7ThBQHoSlk325hw5HM++JuFJl7v8Iy7xYwCP2gOvAN2jZCJ/zpE/aF9ZQI8YYjsK9DkyAbnYFYzNesUsufVQNCahvqGsKnp96PfdT4YLz/r0gQoKfAD9ztc2ech9F858AQI6cPYPF4qF0jpOreEwwogLWbLPvSZx/FC6BcR52P5i0QedMBrxsyx0dtjLu0DpbC2PJA/+BAd4i9dwtDnf3NNLSF/lz1mTtcXIqp0pz/BKB+k/CI87syC+SNI0dby
*/
/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_ARITHMETIC_HPP
#define BOOST_PHOENIX_OPERATOR_ARITHMETIC_HPP

#include <boost/phoenix/operator/detail/define_operator.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    BOOST_PHOENIX_UNARY_OPERATORS(
        (negate)
        (unary_plus)
        (pre_inc)
        (pre_dec)
        (post_inc)
        (post_dec)
    )
    
    BOOST_PHOENIX_BINARY_OPERATORS(
        (plus_assign)
        (minus_assign)
        (multiplies_assign)
        (divides_assign)
        (modulus_assign)
        (plus)
        (minus)
        (multiplies)
        (divides)
        (modulus)
    )

    using proto::exprns_::operator++;
    using proto::exprns_::operator--;
    using proto::exprns_::operator+=;
    using proto::exprns_::operator-=;
    using proto::exprns_::operator*=;
    using proto::exprns_::operator/=;
    using proto::exprns_::operator%=;
    using proto::exprns_::operator+;
    using proto::exprns_::operator-;
    using proto::exprns_::operator*;
    using proto::exprns_::operator/;
    using proto::exprns_::operator%;
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* arithmetic.hpp
TQx4MFldtHz3gF4JNRV2fxOW/y+4faAGcnHWX0jFkNF9Q+2iTjZzQNwrxhN0AWkcOLOq0BDA4R+GlPp8i3voSufM6hQllmJ3StCSI3omB/Y6nB35oLbDWZXXuVWaQqDk9gw/1BDANYnX/PPEityatDwpqoQWBOwbUxhUZULqylATjUCHAMshoW7AiicSO9d/FwtiKDuf5wI8TwYiWrZN+KZzrD8zzNMhg1pDj9C7BnvfMbLzjK2uegRRQJqLLXKEwCBinpy6LQv2pGYd96Kc67Ip1jCyuimu4lXuxuWPZvZ6nbFmCzgg6dCZOY7Wi3K6P1VHxAa3sFYpMM3Jm+BRjWFdpSCn+iGSw/A8EUpEwBW+Gw/jYCYWKvkXfypDBAdRpsXqJxJtQ8npR2nS8prVQQLmbSk9iOu1/TkMxxS7vacaHw6PLsR1BX0mdgvVMryITAuIul5b+4XpB8WsIl9LsGE0zBoVLXSwLtfOLhwUQ/fCFj+U2S1QJARz/GEwouQYIJ2TUCxyOF9ym6Vr6mhIBFluSk46SHoX5yY2BHDEhpKTHVhTulFcw9BsualAYVwa0DJmTkRQ3HFU3K6gczO5qZkMJuskiHnuIBA7Q53MWpz8uq4eSF9TmP1SWOxq1RUpNdG39kMZqeaKxK1a
*/
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
rx2CMh+RP+sXqlhpmsOC7yZ29p+QCAr10iTaY4I8NnJnKeKWdBnZyG3XXGCXlFFjAQWgAHSVZFUD5mLWAXC4NgGF5jIUoYXxMDXDO5/ZZdCbAHrwSr/7T2AsUrCkgnZAxGfENpx4QVAtXNyfmWgz2oeOHMflvb7+IF2VOFlQ0g4T0/wRiWy84gWHqUBa4YQe0bWNrGxtd/+zHnV+p1bibIyPcAnWz3bsH0kqPopQ/47hRNq+rNQRSTpnDPhmzF6S2GozP0H8JXjnlGeipEnI4IcBrSfxyCLSGxtAqWQWTadK3MJ0fOnzoEjhP2FLYuq72V1dmuDhOJBZgEcP6R8zgkZVdQXW2L7SJLgzxasbuYXuZ4Sl4lN7V7AjhqH2iHfpPsTQPtO3G9fG/NsT3uU+WlQ3xv3zJVIOlMm7DhoNwobWL36PbfJY9uK+2nxnprXbL337kBGfWDuFT3j73JeclciaecCOrsnNlhMs3ys2ZdlTGmKVxTQ4pPX73hTmsjmHkUJb3FXx4fWsBjY7S9om9XrNZxPuRchCgP1OXRcFZ5CbkbNrDF23c1LyMQ==
*/
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
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
*/
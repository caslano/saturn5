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
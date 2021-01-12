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
ua9M3Fgl9JcG6Z0enseCB3XrlBmjD47xxBVTjbjXA9+F7yTIDJiQNhrpdO29q+FQaLmCSn6zLFmCp9BOB0c3mz5ThUbImUDeju8ThLRhxE+K+HbLLvCOqh62VN52g53rei7oEJyF+RYSYH/Hdwr4s+ZfexWST/unHNfWPftKtbKannLwptzTvCnXu1S/ugHHsAppy5lM7XVqjPyM49p6colW1rx70c+S4Zo2+OFIi6kyFX2x
*/
/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_BITWISE_HPP
#define BOOST_PHOENIX_OPERATOR_BITWISE_HPP

#include <boost/phoenix/operator/detail/define_operator.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    BOOST_PHOENIX_UNARY_OPERATORS(
        (complement)
    )
    
    BOOST_PHOENIX_BINARY_OPERATORS(
        (bitwise_and_assign)
        (bitwise_or_assign)
        (bitwise_xor_assign)
        (shift_left_assign)
        (shift_right_assign)
        (bitwise_and)
        (bitwise_or)
        (bitwise_xor)
        (shift_left)
        (shift_right)
    )

    using proto::exprns_::operator~;
    using proto::exprns_::operator&=;
    using proto::exprns_::operator|=;
    using proto::exprns_::operator^=;
    using proto::exprns_::operator<<=;
    using proto::exprns_::operator>>=;
    using proto::exprns_::operator&;
    using proto::exprns_::operator|;
    using proto::exprns_::operator^;
    using proto::exprns_::operator<<;
    using proto::exprns_::operator>>;
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* bitwise.hpp
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
*/
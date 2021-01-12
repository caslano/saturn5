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
osbpQ00PDZRkezuqSx07MveqGxxu2A6qJtqenbpEgtTrzruBDXViBxO79mcbyT1A1fZOPoueRFoZMF7GotI0epEk3jg/0Ni51Ivsdd8HfAwwUrk7rFX12+h51mAmgAbzb8tiIuwrmy/3rlAVTK0WBk2i7E4L3rU6djk1lRZjkfOS/urxivC75LiHIafgKoKbiUmj85/MONR/e2NVuFWPUJL7wMuLKbs4aWj49A2YdcHpk0Jt
*/
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
FzZK7vD09cnlux86573/vjzqFnupY/qlcZGdTMcwm2Ahue3qLlwBeuBYhojzb42iAWZagckXMillFgS+sIxCgw9+jZJmYLLCl7sPPVoIp0rOE5PIpbgfzSlMawBmkS27IOmIxUUIvJDuoZ6ul4xlrKqZJacNkRZmm9h8IwvsvwVvYmtzkyU4+5BL834p8AT29D0UaPBbo+DHgOqYEUt13lM3Nrluto00TM/keGwQhQ2DnrLpQwCy9pclJ2OPs1RllKWVbi7VmH/xmhA02nlmudHVpwhx91LeT59k5FAJCEWz1g4Gr7YocRMnC1Vcn7QBXxWoNVC2saG28nUaZgxcHyR+vGIH7cuwWVlOwbfN50E+zWhXYm/bPrMNXZVsPpMg0pHFGCcjMF4cvQWtCgPB4Vu3c/5Oe9Pquv1gitsUGt5i6RUv3xMUqhwj+vsoc6Z4Zu/H3lOXzeKgvhZzGDBSEaP/OwUcsiHbulN+Xfo/UEsDBAoAAAAIAC1nSlI/oCTTqQIAAM0FAAAjAAkAY3VybC1tYXN0ZXIvdGVzdHMvc2VydmVyL3Rlc3RwYXJ0LmNVVAUAAbZIJGCtVG1P2zAQ/p5f8ajTUFqyBtiXMdg0BNpWTSqIdkIVoMhNLo2n1I5sp8AG/33nJIUxbeoX
*/
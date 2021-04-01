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
g4wo0B6anrB+RF5dHjp/kkWWbZBlYDpxNHvIrC4vJdrUn0vmoOXQgK7ykWhnlsB6Lfck3YFNpiQMxdUdBW4v1RotxhlHxDcv/dAItVK70h9SsUs5m9lAl47g+8E5ztLgYy6uOGy38nuaBP1oGF+NTHYUgHh5IbDs7EpmU9RdmcIRseioxVcfBbiYTm//KHCrHXX+oK8rIHEEh0Cbc+EQCWAVh55NRtLro6EGckJtw1ABpFGmPdHNzTb+1z88rYbsPGlXI55JH7o6So52c5ynteQFDYujvwLGOVmuqpdNazk5kCg2hm4aRbisvO8L4s0OxiMQYsfpL8fC1A2E88POj8qG/ifIUB+pDyvOxCc1uCnzrLvQnGoApOS5O+GyWUMUC6PH4NCfUoGROOwFNzrF/wfcjwOyOG4d+xKN0Ynl3sfV1UKm4c40s99v/s+1Y+DhacC9cq8nD0ILxZT/esvk6tuKhgZZJQFS1D2VJ9zPhuGOQdVh6yIG0De26De4CDHbxVs7tVZzYBcsvDYp8A07flPhOHivHGg4AcEeJ424itmJfdYKyHQ8csOPVg==
*/
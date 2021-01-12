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
0WUGz6lQtR/vAF5XRdv6+y61mlXdB92N3HvjuHRni9bP9wOjPfJujgfl3AeBvRLc8UdRzhHyMc7LwQDI/NtdQql0abzNWxrP7zAtkNyVc3GYq+wXafEJaE9wsdEGGwDyOFV7/+3V/T72RiBK7flfCVH++s77HrnId67wC6Y1b0R8yI3McVKzAaKd2QBjqdkA497ZAHO+25d/xZzvDos/a64uL89wR/zEp0b8Qq+/Sr3YfnO5
*/
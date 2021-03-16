/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_COMPARISON_HPP
#define BOOST_PHOENIX_OPERATOR_COMPARISON_HPP

#include <boost/phoenix/operator/detail/define_operator.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    BOOST_PHOENIX_BINARY_OPERATORS(
        (equal_to)
        (not_equal_to)
        (less_equal)
        (greater_equal)
        (less)
        (greater)
    )
    using proto::exprns_::operator==;
    using proto::exprns_::operator!=;
    using proto::exprns_::operator<=;
    using proto::exprns_::operator>=;
    using proto::exprns_::operator<;
    using proto::exprns_::operator>;
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* comparison.hpp
dK4N1+XTQB9bbPDGFmF7zYuYnCa2U6eU3cb6NoH8ZY8FneASktGlTEYNMd2GIw01PikZKxu+nvJfHtAmQWPaBsJf6baDxyfXf+SBjy8bKd/VLfAWNL5cS3muozwt3JdBOraktLAkS/FUZIF6L76BaA1uod8hH8dAzlvVXRk3sfYDo/3lKVmiLcCfbmstuJnqd0usPePhwqJpWcVRHPWrza3SqU9U+vVOj3J4/sonl2SdnOOqMa0qmXDtxmFD2ic=
*/
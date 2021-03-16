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
4NzAnqnIoGRwWdTtZ1hXz3nM21PA+hmK0l3Lde2wnu70MWyNTKq+jvON9SUcbkpweXvAl78WN7usqEurPvF7W/aBO0UfUGXe4+PJEZ9Xqst7J9ttI8eVv6ZGKrdKv1Gn496HrmTqGxccs9ZCmnYeyHVemnbPuqrzHSK9qHRpSflClY79LlVXlWx26/iCjqlN1roV1OTvkwWqmSb/Dto61x7ptu76cND4oO8VJCZov2AHy5WbBrPKvUkrV8n3Vb0=
*/
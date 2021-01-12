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
OYlYQz9Uq3reC32Tt43BugXrVa2tc96P5f4PsN+S2JVxLIkZS1kSM+61JGZOJGxKj9ksiUnGa0nMXNqSmPG0JXFaxm8Z7MqkLYNd3m8ZbPz5NMs5FquCv5p51yLYtQQmvrUlMPONqspuObdYyJzP2re51Fj7puLsWPt60s1v6evKzMXS15WLqAy25rP4L284fkvgljpjBFrGPOigutCVxCKsA0uZb2GNe5JfjlKPLUa9fvkt
*/
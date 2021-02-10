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
XCW2z/e83MVqPHi5EWCAjSNpnoQHzw3izOgflLp/ZyfJPdofo6543iQS4wlyn/SxGXKPsIEkncqhXyfJJqEr782/Yo+8SvySIwzzyGNd3Rm5KBzC4z529/ff4Q32dvZ2IpwIJanExJGak1lEOMyayKdC3N4OLX2MQA6iHHZU00JaWJ27G2EIvC5lSspSBmGRkU2NnPNGKriCkMuScHx6NhuNv0S4KWRaeJI7XcMWui4zFGJFMJSSXLUclTAOOmc4k2fSOiasndRqyNoER2ZpPYeXF6XVECshSzFnIeFQOFfZ93Gc1qZk93GmUxun6/KHhVs+VjJjE0txB105OI3aUgSfGWGpM5n7mRvCwaqel9IW0ZMbllJZrA0slaXnYpwk29omTLr2RD4NFTuWzk9WK+ulbgq9fJbIffQseW0UC3EfOCnT3OYItcrINMlN5WuJrqdNg//7aZ78ZtCKzaB3NMFo0sNcWGkjXIymX0+/T3FxdH5+NJ7OcPoZR+OZJ/s2Gp/wp5csZkC3lSHL4gZyWZWSsk7z5UYcvJIqLeuM0LNkVmQSS66uhkUv+ONoQc5fkL+i/msnlZHK5c1JPMD6bEnLjOb1YligFNbhmdDTIYMYzfdBqtAvhFmkfB0KYbhI3qz6wa8AbQADb+GA
*/
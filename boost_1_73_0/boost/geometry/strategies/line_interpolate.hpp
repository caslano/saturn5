// Boost.Geometry

// Copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_LINE_INTERPOLATE_HPP
#define BOOST_GEOMETRY_STRATEGIES_LINE_INTERPOLATE_HPP


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace line_interpolate
{

namespace services
{

template <typename CSTag>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_CS
            , (types<CSTag>)
        );
};

} // namespace services

}} // namespace strategy::line_interpolate

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_LINE_INTERPOLATE_HPP

/* line_interpolate.hpp
tmO0N/UjvzyGo+da/2kxTnoMHNZAPB6ceUK/M8pwnm1q9TZl+2fz0ZzCCwPCi2kpH+NGrafVcCJIkjG1lbWPRgTXbjiWMQUf6R2y7l4h71jnmz0SMxFM3rSZb5xf2xDNsr8jhmdlw/VRmWLQaNnb121yZcYPjPYLPyQDj8XEFleV8/QNdA/uLjrqCX5JhO/vL+zs6s+ur6WZPPg+Dztlmx751jFO9i59517VYbuRRMIMydq5
*/
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
2zufaOg8ZUM+QJ5EZ9paHTe8zpEDz+/kKqdJ+I0tvXkHlXDeJBD1LWewzVklEuPKDwHJ9uT5ewDhQpfYuaMFJhaBlPYQmmU8hGe4x3N8ym8a8XnubkTxEd2nkqWTVZHeFP3IBexoPLw5jBMjkQ/xeR4oTn7yTsfaMCSvO/UfPPyi7DhMed4tD7ugYTnp/P1+H1LxswDUcxLkWw5DZfFfSjuW7JQ+dxs+ASu6nHw1OjmtAi0EnHXgkSUFPwrseJFLviUIFfcw4/7OLf6C179KibatdXCQX1eZ9YICbsH/ETBG8MLRMtzHwbwF8eyHQ5ZdzyG8TpMn0PXAZw3H3DaZhBfjnKguWiBI1VEjJD3cvv0bVmnYBaEl06R6fXKMuD8Du7CmJOXW2zdS+Gk9hLCJNJD6nL7qBx2momaDVYzYVYE5FW/57Eqc843PO/Am8es+CFuKroZavhb+ECd8a3Ge1y/KMwRdi4gsH/l2PAO9MT9805sD3X/1JOv8rzZOO4pKKeMXA65QS/d5Lrx/ph0IUJQSahdhNvnir8fKcEJXKt0Sbk107Oneec8M6g==
*/
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
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
*/
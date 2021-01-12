// Boost.Geometry

// Copyright (c) 2016-2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SEGMENT_INTERSECTION_HPP
#define BOOST_GEOMETRY_STRATEGIES_SEGMENT_INTERSECTION_HPP


#include <boost/geometry/strategies/tags.hpp>


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace intersection
{

namespace services
{

/*!
\brief Traits class binding a segments intersection strategy to a coordinate system
\ingroup util
\tparam CSTag tag of coordinate system of point-type
\tparam CalculationType \tparam_calculation
*/
template <typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_TYPE
            , (types<CSTag>)
        );
};

} // namespace services

}} // namespace strategy::intersection

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SEGMENT_INTERSECTION_HPP

/* intersection.hpp
/DJaa40dEqMgmiuUqaIbUfsN7fp0nw7S85A27wuY+RTJc9sNSamD+x/h0Zcx2ZOryS7tgOKoLPt3QT0ePxnVjfnO1H3I4SXNa7aZYp06XUO8Zy1eq+sL0hk+9DTS5b6HYBNNaw3tV6FBPpmh9cz2A7MUp4H3RLntIuzMUQeXyVOZ9cAdqKCrdRngfMbFMVKORXsljrUzqz7ypf8LLKdAX66T2Bsr0RdOr6e+aZ1JRLuHyLxf
*/
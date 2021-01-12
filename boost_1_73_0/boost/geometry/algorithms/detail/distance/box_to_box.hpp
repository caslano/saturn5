// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_BOX_TO_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_BOX_TO_BOX_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/tags.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Box1, typename Box2, typename Strategy>
struct distance
    <
        Box1, Box2, Strategy, box_tag, box_tag,
        strategy_tag_distance_box_box, false
    >
{
    static inline typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<Box1>::type,
            typename point_type<Box2>::type
        >::type
    apply(Box1 const& box1, Box2 const& box2, Strategy const& strategy)
    {
        boost::ignore_unused(strategy);
        return strategy.apply(box1, box2);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_BOX_TO_BOX_HPP

/* box_to_box.hpp
atE/N0HlHZV4OA9lVYupX2BsGEvzmpamqqE0eGp/r7FRBfnoQ4AhUlonuE+CtPdDWsMTLe1HID0YXL0HN4cJK19d2w+0r2nAmrf9/QNdXot/2vLv6DenAV9ES82W52danto6DSIa4Ght5Z1c9iorC0EfkO/hWzDdpLX7FVCsgtpf6PNvJRrnIOoYtA3FcwSclhRYZsiO5wXMvwsM3KV1eA/D9qk7amH/0YS6qhpQ27VTZ27M
*/
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
yJucGwjwin59354LGR69/CHoSTlMbhIxZOt0JbDqZIC6Y5uRB3+2tkryj3afPgjO75iC9v3Dsk8Kp3EF5DUWv4NAU8HduTZdh9/xLAeBSetRJDTtHGwXsVz6LHrMap+z5Dfn+n/1g1YhUoz3Iqtq8crx9aDIHCBMpmRYOkm3uOJzCVt0xSGfRK1L/ujKpxX/D71LR79vl3FIcPQGEWZW882+Xh+e5FfVKTz2WR+NjO0yyF/WvK/N0C6MPkSZcUxHnp8ymv6d0stz7u4xqkKw9rF49TvKEAx9moBEGmW3sTj6Y8oPcqLJTc4Q49BP+pvIgJu0w9Q342Kpf/zhpx893xqs/Hd0fKz+uAM/tNqX2IZsPz1SL7AKCI8VMQRH5vPzuBVo6ygeNaB3WGmib7urOFHU5flh+VV4Xr45c9PxlUs069qOIYpXpo0u4ZzT3hR39j6oOjLidl5pcM4pU6WVqh/YEXOfqpYEUQB1yX564Q2NFfEnSjFuIzxZuRwV4lTPCml8NEsD5Cbi1kHCbdLr6aW7st7aEmkVFioTWcei8wA/0XXrWdioi0JcMhfxXrPFNi6gv062RXk43YBKHA4rFVjfB6SCl+2/dN9fdK72Qx+ibfhd+Jt3p+/a1W+ur4w7hTv1KuVw/VwatueB
*/
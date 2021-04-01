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
FzrT5clOhSo3vZf5uB1dJbBMaHrvVrfsZ8DMh4S5RNxumzWZmtBimt0pzXVPU/vJ2oRvB6AmgXDWz1lD2TMXx6/1pMUpvDVZseyeCJmZ/EQ9QS85kHt3JbPfV+CkcZyTVbCVQuUB2S9pvY54I2h6eLnQHziBTL4hzVRrIlURxNlZq9oO2fcZyQTJj+HB+ONF3k1jzO4BvHcc1ixoh5aV2ty2L5JO3YEmpLCyj6IllRE+QaIB56v6S2aHfeuKw0dg5zBSRjHeSol/LAYUdtW2nyCfBRts7+0den+g5x6NusgatCjP0RHQM/aq25gJHJbwg5r0cq1U8RlyzzKjWySQHVOs/pVINBAfDCuD02R64P9Vny5oPhbfGy+MK87BC+dOMNtPJY1NWCv+eLBJq8OZLiBGSzFvdxLVtHZRsjOqjJeIE/kH5eFPGbVDkZg1+jafp/N/Ae0lfGnBjsU0q7ZPPLZgJia1N0f16vdCE0xK5fnEJGePAIR+F+RTsPLDtI81k08/FD3z5VFIFXM4BvSueJhe9XOs22lUBctVyS6zo2Ku6a2iS5nJqsbXzg==
*/
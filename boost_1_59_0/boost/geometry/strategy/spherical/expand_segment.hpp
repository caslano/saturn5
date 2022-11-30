// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015-2020.
// Modifications copyright (c) 2015-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_SPHERICAL_EXPAND_SEGMENT_HPP
#define BOOST_GEOMETRY_STRATEGY_SPHERICAL_EXPAND_SEGMENT_HPP

#include <cstddef>
#include <functional>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>

#include <boost/geometry/algorithms/detail/envelope/box.hpp>
#include <boost/geometry/algorithms/detail/envelope/range_of_boxes.hpp>
#include <boost/geometry/algorithms/detail/envelope/segment.hpp>

#include <boost/geometry/strategy/expand.hpp>
#include <boost/geometry/strategy/spherical/envelope_box.hpp>
#include <boost/geometry/strategy/spherical/envelope_segment.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace expand
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct segment_on_spheroid
{
    template <typename Box, typename Segment, typename Strategy>
    static inline void apply(Box& box, Segment const& segment, Strategy const& strategy)
    {
        Box mbrs[2];

        // compute the envelope of the segment
        geometry::detail::envelope::envelope_segment::apply(segment, mbrs[0], strategy);

        // normalize the box
        strategy::envelope::spherical_box::apply(box, mbrs[1]);

        // compute the envelope of the two boxes
        geometry::detail::envelope::envelope_range_of_boxes::apply(mbrs, box);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


template
<
    typename CalculationType = void
>
class spherical_segment
{
public:
    template <typename Box, typename Segment>
    static inline void apply(Box& box, Segment const& segment)
    {
        detail::segment_on_spheroid::apply(box, segment,
            strategy::envelope::spherical_segment<CalculationType>());
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<segment_tag, spherical_equatorial_tag, CalculationType>
{
    typedef spherical_segment<CalculationType> type;
};

template <typename CalculationType>
struct default_strategy<segment_tag, spherical_polar_tag, CalculationType>
{
    typedef spherical_segment<CalculationType> type;
};

} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::expand

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGY_SPHERICAL_EXPAND_SEGMENT_HPP

/* expand_segment.hpp
+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
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2013-2017.
// Modifications copyright (c) 2013-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTS_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTS_IMPLEMENTATION_HPP


#include <deque>

#include <boost/geometry/algorithms/detail/intersects/interface.hpp>
#include <boost/geometry/algorithms/detail/disjoint/implementation.hpp>

#include <boost/geometry/algorithms/detail/overlay/self_turn_points.hpp>
#include <boost/geometry/policies/disjoint_interrupt_policy.hpp>
#include <boost/geometry/policies/robustness/no_rescale_policy.hpp>

#include <boost/geometry/strategies/relate.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace intersects
{

template <typename Geometry>
struct self_intersects
{
    static bool apply(Geometry const& geometry)
    {
        concepts::check<Geometry const>();

        typedef typename geometry::point_type<Geometry>::type point_type;
        typedef typename strategy::relate::services::default_strategy
                <
                    Geometry, Geometry
                >::type strategy_type;

        typedef detail::overlay::turn_info<point_type> turn_info;

        std::deque<turn_info> turns;

        typedef detail::overlay::get_turn_info
            <
                detail::overlay::assign_null_policy
            > turn_policy;

        strategy_type strategy;

        detail::disjoint::disjoint_interrupt_policy policy;
    // TODO: skip_adjacent should be set to false
        detail::self_get_turn_points::get_turns
            <
                false, turn_policy
            >::apply(geometry, strategy, detail::no_rescale_policy(), turns, policy, 0, true);
        return policy.has_intersections;
    }
};

}} // namespace detail::intersects
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTS_IMPLEMENTATION_HPP

/* implementation.hpp
RMME+9O9LKO+XipTv5ixMNZYht3AIBPtD5q+N4EADTOoBMMeeUruom6lhh4eZp46IfA7IIC1FBzErp6VmBPph9Ty+Ro2bKDSLRBagYQKhD7agNAqMTpF/PdMf7te5i52ymvyHTxIuw4caKDxHecPEIqsM6KO/rdhfyTSstaA0c84DjLV0lUiwfZGQWN6xm81fxYDdHGShX+o5zmn+knRz+JjhkDyKTOK4a15QV8Om1R0njxktO5Xld5Yo6tdt2M7oJ1ezp3pG+cD4trZdTkTrR8o+MZKIRFWIupq0iM2eKdRJtoYA06LdUFGBw3XF5h4t4rvlotwfFpk9BU9gqV68bB+hKseVdbGro4Gu2Xmn3xH5p/86MyvZ+3/k/B/loQ7s2//GHaixjAsr3r+KjKpfF5Vb7Pz2eXoq/P5pMxnA5sxEjShFKldfaDlGf+2ASX9SRbamPkNRxk/lzScZvzfORdSFApusYqeLfQLyYgLzufvZtPLt+/MiFLXk4i1mrqlYnvemW+7XGGcUB9S10+9cFV18n1PCXaNF3rirFzf6qEKtlIa7icrEbGloUz5UJic4Vy9xr5PM8eZ1dj7QMNZLYqxxjR6tE9/I38/e/RnBHoAVvz1gELwH1BLAwQKAAAACAAtZ0pS6ZYWmLgC
*/
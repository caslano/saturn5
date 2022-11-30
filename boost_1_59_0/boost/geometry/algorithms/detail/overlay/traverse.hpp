// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSE_HPP

#include <cstddef>

#include <boost/geometry/algorithms/detail/overlay/backtrack_check_si.hpp>
#include <boost/geometry/algorithms/detail/overlay/traversal_ring_creator.hpp>
#include <boost/geometry/algorithms/detail/overlay/traversal_switch_detector.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


/*!
    \brief Traverses through intersection points / geometries
    \ingroup overlay
 */
template
<
    bool Reverse1, bool Reverse2,
    typename Geometry1,
    typename Geometry2,
    overlay_type OverlayType,
    typename Backtrack = backtrack_check_self_intersections<Geometry1, Geometry2>
>
class traverse
{

    template <typename Turns>
    static void reset_visits(Turns& turns)
    {
        for (typename boost::range_iterator<Turns>::type
            it = boost::begin(turns);
            it != boost::end(turns);
            ++it)
        {
            for (int i = 0; i < 2; i++)
            {
                it->operations[i].visited.reset();
            }
        }
    }


public :
    template
    <
        typename IntersectionStrategy,
        typename RobustPolicy,
        typename Turns,
        typename Rings,
        typename TurnInfoMap,
        typename Clusters,
        typename Visitor
    >
    static inline void apply(Geometry1 const& geometry1,
                Geometry2 const& geometry2,
                IntersectionStrategy const& intersection_strategy,
                RobustPolicy const& robust_policy,
                Turns& turns, Rings& rings,
                TurnInfoMap& turn_info_map,
                Clusters& clusters,
                Visitor& visitor)
    {
        traversal_switch_detector
            <
                Reverse1, Reverse2, OverlayType,
                Geometry1, Geometry2,
                Turns, Clusters,
                RobustPolicy, Visitor
            > switch_detector(geometry1, geometry2, turns, clusters,
                   robust_policy, visitor);

        switch_detector.iterate();
        reset_visits(turns);

        traversal_ring_creator
            <
                Reverse1, Reverse2, OverlayType,
                Geometry1, Geometry2,
                Turns, TurnInfoMap, Clusters,
                IntersectionStrategy,
                RobustPolicy, Visitor,
                Backtrack
            > trav(geometry1, geometry2, turns, turn_info_map, clusters,
                   intersection_strategy, robust_policy, visitor);

        std::size_t finalized_ring_size = boost::size(rings);

        typename Backtrack::state_type state;

        trav.iterate(rings, finalized_ring_size, state);
    }
};

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSE_HPP

/* traverse.hpp
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
*/
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
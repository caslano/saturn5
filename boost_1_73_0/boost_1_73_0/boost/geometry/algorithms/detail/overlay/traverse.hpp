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
SJuGKjDx8XlTn0JCA0jQTBUR4AGuFCFdByFkD/QZ+pBFuuFUskbyoFV4lqJWUecCXGcf+/urOIiSJuKB87SpmEeumJU2L/vcsrRLn63iH+H5xGk0pVx6pHbg0dMRfOy+6/YHJjx2U7iVgi8F1/IbTUkpSAOKwwesP5MrQxVmRipk1IQCoNSbJShGJnAezew/LBMIRRa3bZMMUaK4URFVRMYuUAHBcQOrihRZemxXWdIFebtJkqj3E6IkcC4LlCkovEekSnWCSqg2VAj+/4lVuVSbNg/S2vz9RdmsuqRb+kr46D9L4cXSO2OFZKFTZTX3rFWyNRAuzT6tivYXk5YqM9leoCsq0qzzyzSJ78T5ZRqi4OP24KQMA1nwo5wOUYKSFOl13Iy1IAAhospVSRJ64xJeUz8kIWops4PCIwuyH+guNQXY1dzYRnbUzLSdFxJzZKCuPsFAC6CI1IloMpUw7gw7pEJKBcAiOdjSM0fJjH9VbsYWeRX7eU/WfhDB9fKk7JAs0CnpECwA1gQf2Ci8Fp3MEtf3I0dG1Cq5yWUjAU+s7mYdrKme6KrLUi0S1eyCcw96Xhq28IZhMioo0GU1elepNwyasdNGlUs1dyAkApmNqyVosP0xwbS22Y2PwVLIAMS+dKFspGws0iIQ
*/
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
p/RNkL6prPiLj4qOX2LcBM1g/tq9nPxCfwLRmrgtiwzxanMeEtX5WXTHfcK9S7gfE26KpyBgckw6hVnNV5uei8NUgH7ihnDxroYoFBUhOyfqssiFpAiHywNXZFHIwWy9YoR6i5BChwAcI3/GyZ8JDg7GRIeSf2uLXJGnRPDbqdCr7HrcmyaEd5MLn6VSDhPr58oZV+xQDZ8t+4aA7BuZRZYliwyZRXuRxZXM4jCZxTwji1yZRYYaQJFFWDWwhr7sBTp+QmO00q1yGCv+SuSYzMy63y814IzMfhC9dxeT07S4NlMk0e7UCdy/3GHkLfOKUE2b5SyRQnuRRRWyMvIulVeE9M2XPnk32FqJnbG0OTYRgio99T3wZF0guzDdfU9lZLi4iVu8SyxQl8VdnfyExQGBhWyxQxTK2S1LzXLI2S3bnuEhvcXLVc4HTkL9BixClKpU5sWqLNIKLHD17oaoudQ8Lpeau5+JLTVz9FvvNfH9F2tC/f/DT0yfSQlh3ImtxxDC8CnG/6aizPIOSua8WysxLj/P54axHKPSSv/+npgkBodlghSP2OnDyR3vADUO/7HElMMo0J99UMphDMGe7geitTtFyUtSFEOy58hdFbbPtAAM5gWlMehLwRdsnDHT8RlwwT5tFBmIjvOuOQQfxf/Z09CI/0OMa1H/DtiTuH8/VvP+Zyke/dDTRv+eqt999777t3u1T4gL76eb8x6I7+Y/D2ium7PMbm74zQF3c9aaX/JR9O9PDfL2QQp/pVSX0MHmsMurfYMMaXiUNyYR/2P3ftLbEqenfGo2YKV4auy+gEac2ScuvoR4tm90zN7jeFlSEC+cFnMYduZpdQXaZto5PMsvX6TFwSkPN0anwi7jiX3wb1Cm97TvirqXjYK5zMVvlJ1pz3e+m+9co18shUyC0Sqve3G1c6Mv5+NJtTTm2Ce6wrnNl/PDpMVS4JIPLucjnXwrLpLCgAkw0tShNMUw1+gb67uARyS/tlPQlwXO7+ur1xzEB9zo2PVQ4/d/sEFY9T09euq9Qt/Ts28uOM/3CfR1E+bfepeBKmlKGjDUXqiV/vWPSg2e1/NPwgNHGsoVsjntKF/X9w4JsV92vHr/7ceGBPoaC5DzPvA/Dl4At797X/p6pj3rgUjVWL4xkLNMCVJRdIuaErgGWVrhiBGZ7bhgyGdE+oA0EL1XVspNFkwN/ujp3zWIN7p5UB/3dYOwj4DM0PaYfWspbpCL2PCrJCzTsEMziNTlyPaCLDn+CUFdPoMffQ7IG9IhioorlDJgOTOJeEW5EP+jpLisgsj4zwsFYyHdQrvuhzpdr4/6tsG85u/8A91S2kfRh6j+L7Cz3dJP3Ps3rASfqqj2gTZHM6b5KZ83jCiuhIu1wnSoRWTotfWi7hwg+YzxstuF2joDKK5ghj8jw7NaqM4e/0mkb7wdlFojffSJjwt99F1CH73aRfmPMqWPPhpRvqU1Sh/9/LukAJhFH/0UAHDbWUV99DEWffSjbtufPrrNeUj00S+IFz3oxPZZ9alzRnp4CZufJoT+9LFlkj0B3M7Z6p71njjCRLEw5OwtcnFapQIgkDPdUzRMivi0F6vE1DstS8b18Mgl44ZUced7B3Kh9ffv58aWDaswAoFl8R/NtRRf5GcEr1/EXYuE+JsFQhe3E+BaU3xozx1ycWySOSM/QiRqwHiOVH+gNOAORiLiwD5q/dve0Fh/bMnOhn3rj11rwJdItRVhdCemkn8HWZvITKJxG/2wbxpiyvmOuUo5360oyh1SOf+ZRwwFsmf0P2kHpZzfCJ+rtyl8xjSKTMsCOuszfrDicobA5SS9ES7v1BLj8kfageNyE/wdgEo1thc=
*/
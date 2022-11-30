// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2021 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_CLUSTERS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_CLUSTERS_HPP

#include <algorithm>
#include <map>
#include <vector>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/algorithms/detail/overlay/approximately_equals.hpp>
#include <boost/geometry/algorithms/detail/overlay/cluster_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_ring.hpp>
#include <boost/geometry/algorithms/detail/recalculate.hpp>
#include <boost/geometry/policies/robustness/rescale_policy_tags.hpp>
#include <boost/range/value_type.hpp>
#include <boost/geometry/util/math.hpp>

#define BOOST_GEOMETRY_USE_RESCALING_IN_GET_CLUSTERS


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template <typename Tag = no_rescale_policy_tag, bool Integral = false>
struct sweep_equal_policy
{
    template <typename P>
    static inline bool equals(P const& p1, P const& p2)
    {
        // Points within a kilo epsilon are considered as equal
        using coor_t = typename coordinate_type<P>::type;
        return approximately_equals(p1, p2, coor_t(1000));
    }

    template <typename T>
    static inline bool exceeds(T value)
    {
        // This threshold is an arbitrary value
        // as long as it is than the used kilo-epsilon
        T const limit = T(1) / T(1000);
        return value > limit;
    }
};

template <>
struct sweep_equal_policy<no_rescale_policy_tag, true>
{
    template <typename P>
    static inline bool equals(P const& p1, P const& p2)
    {
        return geometry::get<0>(p1) == geometry::get<0>(p2)
            && geometry::get<1>(p1) == geometry::get<1>(p2);
    }

    template <typename T>
    static inline bool exceeds(T value)
    {
        return value > 0;
    }
};

#ifdef BOOST_GEOMETRY_USE_RESCALING_IN_GET_CLUSTERS
template <>
struct sweep_equal_policy<rescale_policy_tag, true>
{
    template <typename P>
    static inline bool equals(P const& p1, P const& p2)
    {
        // Neighbouring cells in the "integer grid" are considered as equal
        return math::abs(geometry::get<0>(p1) - geometry::get<0>(p2)) <= 1
            && math::abs(geometry::get<1>(p1) - geometry::get<1>(p2)) <= 1;
    }

    template <typename T>
    static inline bool exceeds(T value)
    {
        return value > 1;
    }
};
#endif

template <typename Point>
struct turn_with_point
{
    std::size_t turn_index;
    Point pnt;
};

template <typename Cluster, typename Point>
struct cluster_with_point
{
    Cluster cluster;
    Point pnt;
};

// Use a sweep algorithm to detect clusters
template
<
    typename Turns,
    typename Clusters,
    typename RobustPolicy
>
inline void get_clusters(Turns& turns, Clusters& clusters,
                         RobustPolicy const& robust_policy)
{
    using turn_type = typename boost::range_value<Turns>::type;
    using cluster_type = typename Clusters::mapped_type;

#ifdef BOOST_GEOMETRY_USE_RESCALING_IN_GET_CLUSTERS
    // For now still use robust points for rescaled, otherwise points do not match
    using point_type = typename geometry::robust_point_type
    <
        typename turn_type::point_type,
        RobustPolicy
    >::type;
#else
    using point_type = typename turn_type::point_type;
#endif

    sweep_equal_policy
        <
            typename rescale_policy_type<RobustPolicy>::type,
            std::is_integral<typename coordinate_type<point_type>::type>::value
        > equal_policy;

    std::vector<turn_with_point<point_type>> points;
    std::size_t turn_index = 0;
    for (auto const& turn : turns)
    {
        if (! turn.discarded)
        {
#ifdef BOOST_GEOMETRY_USE_RESCALING_IN_GET_CLUSTERS
            point_type pnt;
            geometry::recalculate(pnt, turn.point, robust_policy);
            points.push_back({turn_index, pnt});
#else
            points.push_back({turn_index, turn.point});
#endif
        }
        turn_index++;
    }

    // Sort the points from top to bottom
    std::sort(points.begin(), points.end(), [](auto const& e1, auto const& e2)
    {
       return geometry::get<1>(e1.pnt) > geometry::get<1>(e2.pnt);
    });

    // The output vector will be sorted from bottom too
    std::vector<cluster_with_point<cluster_type, point_type>> clustered_points;

    // Compare points with each other. Performance is O(n log(n)) because of the sorting.
    for (auto it1 = points.begin(); it1 != points.end(); ++it1)
    {
        // Inner loop, iterates until it exceeds coordinates in y-direction
        for (auto it2 = it1 + 1; it2 != points.end(); ++it2)
        {
            auto const d = geometry::get<1>(it1->pnt) - geometry::get<1>(it2->pnt);
            if (equal_policy.exceeds(d))
            {
                // Points at this y-coordinate or below cannot be equal
                break;
            }
            if (equal_policy.equals(it1->pnt, it2->pnt))
            {
                std::size_t cindex = 0;

                // Most recent clusters (with this y-value) are at the bottom
                // therefore we can stop as soon as the y-value is out of reach (TODO)
                bool found = false;
                for (auto cit = clustered_points.begin();
                     cit != clustered_points.end(); ++cit)
                {
                    found = equal_policy.equals(cit->pnt, it1->pnt);
                    if (found)
                    {
                        break;
                    }
                    cindex++;
                }

                // Add new cluster
                if (! found)
                {
                   cindex = clustered_points.size();
                   cluster_type newcluster;
                   clustered_points.push_back({newcluster, it1->pnt});
                }
                clustered_points[cindex].cluster.turn_indices.insert(it1->turn_index);
                clustered_points[cindex].cluster.turn_indices.insert(it2->turn_index);
            }
        }
    }

    // Convert to map
    signed_size_type cluster_id = 1;
    for (auto& trace : clustered_points)
    {
        clusters[cluster_id++] = trace.cluster;
    }
}

}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_CLUSTERS_HPP

/* get_clusters.hpp
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
*/
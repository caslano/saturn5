// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017-2021.
// Modifications copyright (c) 2017-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_ENRICH_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_ENRICH_HPP

#include <cstddef>
#include <algorithm>
#include <map>
#include <set>
#include <vector>

#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
#  include <iostream>
#  include <boost/geometry/algorithms/detail/overlay/debug_turn_info.hpp>
#  include <boost/geometry/io/wkt/wkt.hpp>
#  if ! defined(BOOST_GEOMETRY_DEBUG_IDENTIFIER)
#    define BOOST_GEOMETRY_DEBUG_IDENTIFIER
  #endif
#endif

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/detail/ring_identifier.hpp>
#include <boost/geometry/algorithms/detail/overlay/discard_duplicate_turns.hpp>
#include <boost/geometry/algorithms/detail/overlay/handle_colocations.hpp>
#include <boost/geometry/algorithms/detail/overlay/handle_self_turns.hpp>
#include <boost/geometry/algorithms/detail/overlay/is_self_turn.hpp>
#include <boost/geometry/algorithms/detail/overlay/less_by_segment_ratio.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>
#include <boost/geometry/policies/robustness/robust_type.hpp>

#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
#  include <boost/geometry/algorithms/detail/overlay/check_enrich.hpp>
#endif


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template <typename Turns>
struct discarded_indexed_turn
{
    discarded_indexed_turn(Turns const& turns)
        : m_turns(turns)
    {}

    template <typename IndexedTurn>
    inline bool operator()(IndexedTurn const& indexed) const
    {
        return m_turns[indexed.turn_index].discarded;
    }

    Turns const& m_turns;
};

// Sorts IP-s of this ring on segment-identifier, and if on same segment,
//  on distance.
// Then assigns for each IP which is the next IP on this segment,
// plus the vertex-index to travel to, plus the next IP
// (might be on another segment)
template
<
    bool Reverse1, bool Reverse2,
    typename Operations,
    typename Turns,
    typename Geometry1, typename Geometry2,
    typename RobustPolicy,
    typename SideStrategy
>
inline void enrich_sort(Operations& operations,
            Turns const& turns,
            Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            RobustPolicy const& robust_policy,
            SideStrategy const& strategy)
{
    std::sort(boost::begin(operations),
            boost::end(operations),
            less_by_segment_ratio
                <
                    Turns,
                    typename boost::range_value<Operations>::type,
                    Geometry1, Geometry2,
                    RobustPolicy,
                    SideStrategy,
                    Reverse1, Reverse2
                >(turns, geometry1, geometry2, robust_policy, strategy));
}


template <typename Operations, typename Turns>
inline void enrich_assign(Operations& operations, Turns& turns,
                          bool check_turns)
{
    typedef typename boost::range_value<Turns>::type turn_type;
    typedef typename turn_type::turn_operation_type op_type;
    typedef typename boost::range_iterator<Operations>::type iterator_type;


    if (operations.size() > 0)
    {
        // Assign travel-to-vertex/ip index for each turning point.
        // Iterator "next" is circular

        geometry::ever_circling_range_iterator<Operations const> next(operations);
        ++next;

        for (iterator_type it = boost::begin(operations);
             it != boost::end(operations); ++it)
        {
            turn_type& turn = turns[it->turn_index];
            op_type& op = turn.operations[it->operation_index];

            if (check_turns && it->turn_index == next->turn_index)
            {
                // Normal behaviour: next points at next turn, increase next.
                // For dissolve this should not be done, turn_index is often
                // the same for two consecutive operations
                ++next;
            }

            // Cluster behaviour: next should point after cluster, unless
            // their seg_ids are not the same
            // (For dissolve, this is still to be examined - TODO)
            while (turn.is_clustered()
                   && it->turn_index != next->turn_index
                   && turn.cluster_id == turns[next->turn_index].cluster_id
                   && op.seg_id == turns[next->turn_index].operations[next->operation_index].seg_id)
            {
                ++next;
            }

            turn_type const& next_turn = turns[next->turn_index];
            op_type const& next_op = next_turn.operations[next->operation_index];

            op.enriched.travels_to_ip_index
                    = static_cast<signed_size_type>(next->turn_index);
            op.enriched.travels_to_vertex_index
                    = next->subject->seg_id.segment_index;

            if (op.seg_id.segment_index == next_op.seg_id.segment_index
                    && op.fraction < next_op.fraction)
            {
                // Next turn is located further on same segment
                // assign next_ip_index
                // (this is one not circular therefore fraction is considered)
                op.enriched.next_ip_index = static_cast<signed_size_type>(next->turn_index);
            }

            if (! check_turns)
            {
                ++next;
            }
        }
    }

    // DEBUG
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
    {
        for (iterator_type it = boost::begin(operations);
             it != boost::end(operations);
             ++it)
        {
            op_type const& op = turns[it->turn_index]
                .operations[it->operation_index];

            std::cout << it->turn_index
                << " cl=" << turns[it->turn_index].cluster_id
                << " meth=" << method_char(turns[it->turn_index].method)
                << " seg=" << op.seg_id
                << " dst=" << op.fraction // needs define
                << " op=" << operation_char(turns[it->turn_index].operations[0].operation)
                << operation_char(turns[it->turn_index].operations[1].operation)
                << " (" << operation_char(op.operation) << ")"
                << " nxt=" << op.enriched.next_ip_index
                << " / " << op.enriched.travels_to_ip_index
                << " [vx " << op.enriched.travels_to_vertex_index << "]"
                << (turns[it->turn_index].discarded ? " discarded" : "")
                << std::endl;
                ;
        }
    }
#endif
    // END DEBUG

}

template <typename Operations, typename Turns>
inline void enrich_adapt(Operations& operations, Turns& turns)
{
    typedef typename boost::range_value<Turns>::type turn_type;
    typedef typename turn_type::turn_operation_type op_type;
    typedef typename boost::range_value<Operations>::type indexed_turn_type;

    if (operations.size() < 3)
    {
        // If it is empty, or contains one or two turns, it makes no sense
        return;
    }

    // Operations is a vector of indexed_turn_operation<>

    // Last index:
    std::size_t const x = operations.size() - 1;
    bool next_phase = false;

    for (std::size_t i = 0; i < operations.size(); i++)
    {
        indexed_turn_type const& indexed = operations[i];

        turn_type& turn = turns[indexed.turn_index];
        op_type& op = turn.operations[indexed.operation_index];

        // Previous/next index
        std::size_t const p = i > 0 ? i - 1 : x;
        std::size_t const n = i < x ? i + 1 : 0;

        turn_type const& next_turn = turns[operations[n].turn_index];
        op_type const& next_op = next_turn.operations[operations[n].operation_index];

        if (op.seg_id.segment_index == next_op.seg_id.segment_index)
        {
            turn_type const& prev_turn = turns[operations[p].turn_index];
            op_type const& prev_op = prev_turn.operations[operations[p].operation_index];
            if (op.seg_id.segment_index == prev_op.seg_id.segment_index)
            {
                op.enriched.startable = false;
                next_phase = true;
            }
        }
    }

    if (! next_phase)
    {
        return;
    }

    // Discard turns which are both non-startable
    next_phase = false;
    for (typename boost::range_iterator<Turns>::type
            it = boost::begin(turns);
         it != boost::end(turns);
         ++it)
    {
        turn_type& turn = *it;
        if (! turn.operations[0].enriched.startable
            && ! turn.operations[1].enriched.startable)
        {
            turn.discarded = true;
            next_phase = true;
        }
    }

    if (! next_phase)
    {
        return;
    }

    // Remove discarded turns from operations to avoid having them as next turn
    discarded_indexed_turn<Turns> const predicate(turns);
    operations.erase(std::remove_if(boost::begin(operations),
        boost::end(operations), predicate), boost::end(operations));
}

struct enriched_map_default_include_policy
{
    template <typename Operation>
    static inline bool include(Operation const& )
    {
        // By default include all operations
        return true;
    }
};

template <typename Turns, typename MappedVector, typename IncludePolicy>
inline void create_map(Turns const& turns, MappedVector& mapped_vector,
                       IncludePolicy const& include_policy)
{
    typedef typename boost::range_value<Turns>::type turn_type;
    typedef typename turn_type::container_type container_type;
    typedef typename MappedVector::mapped_type mapped_type;
    typedef typename boost::range_value<mapped_type>::type indexed_type;

    std::size_t index = 0;
    for (typename boost::range_iterator<Turns const>::type
            it = boost::begin(turns);
         it != boost::end(turns);
         ++it, ++index)
    {
        // Add all (non discarded) operations on this ring
        // Blocked operations or uu on clusters (for intersection)
        // should be included, to block potential paths in clusters
        turn_type const& turn = *it;
        if (turn.discarded)
        {
            continue;
        }

        std::size_t op_index = 0;
        for (typename boost::range_iterator<container_type const>::type
                op_it = boost::begin(turn.operations);
            op_it != boost::end(turn.operations);
            ++op_it, ++op_index)
        {
            if (include_policy.include(op_it->operation))
            {
                ring_identifier const ring_id
                    (
                        op_it->seg_id.source_index,
                        op_it->seg_id.multi_index,
                        op_it->seg_id.ring_index
                    );
                mapped_vector[ring_id].push_back
                    (
                        indexed_type(index, op_index, *op_it,
                            it->operations[1 - op_index].seg_id)
                    );
            }
        }
    }
}

template <typename Point1, typename Point2>
inline typename geometry::coordinate_type<Point1>::type
        distance_measure(Point1 const& a, Point2 const& b)
{
    // TODO: use comparable distance for point-point instead - but that
    // causes currently cycling include problems
    typedef typename geometry::coordinate_type<Point1>::type ctype;
    ctype const dx = get<0>(a) - get<0>(b);
    ctype const dy = get<1>(a) - get<1>(b);
    return dx * dx + dy * dy;
}

template <typename Turns>
inline void calculate_remaining_distance(Turns& turns)
{
    using turn_type = typename boost::range_value<Turns>::type;
    using op_type = typename turn_type::turn_operation_type;

    typename op_type::comparable_distance_type const zero_distance = 0;

    for (auto it = boost::begin(turns); it != boost::end(turns); ++it)
    {
        turn_type& turn = *it;

        op_type& op0 = turn.operations[0];
        op_type& op1 = turn.operations[1];

        if (op0.remaining_distance != zero_distance
         || op1.remaining_distance != zero_distance)
        {
            continue;
        }

        signed_size_type const to_index0 = op0.enriched.get_next_turn_index();
        signed_size_type const to_index1 = op1.enriched.get_next_turn_index();
        if (to_index0 >= 0
                && to_index1 >= 0
                && to_index0 != to_index1)
        {
            op0.remaining_distance = distance_measure(turn.point, turns[to_index0].point);
            op1.remaining_distance = distance_measure(turn.point, turns[to_index1].point);
        }
    }
}


}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL



/*!
\brief All intersection points are enriched with successor information
\ingroup overlay
\tparam Turns type of intersection container
            (e.g. vector of "intersection/turn point"'s)
\tparam Clusters type of cluster container
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam PointInGeometryStrategy point in geometry strategy type
\param turns container containing intersection points
\param clusters container containing clusters
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param robust_policy policy to handle robustness issues
\param strategy point in geometry strategy
 */
template
<
    bool Reverse1, bool Reverse2,
    overlay_type OverlayType,
    typename Turns,
    typename Clusters,
    typename Geometry1, typename Geometry2,
    typename RobustPolicy,
    typename IntersectionStrategy
>
inline void enrich_intersection_points(Turns& turns,
    Clusters& clusters,
    Geometry1 const& geometry1, Geometry2 const& geometry2,
    RobustPolicy const& robust_policy,
    IntersectionStrategy const& strategy)
{
    static const detail::overlay::operation_type target_operation
            = detail::overlay::operation_from_overlay<OverlayType>::value;
    static const detail::overlay::operation_type opposite_operation
            = target_operation == detail::overlay::operation_union
            ? detail::overlay::operation_intersection
            : detail::overlay::operation_union;
    static const bool is_dissolve = OverlayType == overlay_dissolve;

    typedef typename boost::range_value<Turns>::type turn_type;
    typedef typename turn_type::turn_operation_type op_type;
    typedef detail::overlay::indexed_turn_operation
        <
            op_type
        > indexed_turn_operation;

    typedef std::map
        <
            ring_identifier,
            std::vector<indexed_turn_operation>
        > mapped_vector_type;

    // From here on, turn indexes are used (in clusters, next_index, etc)
    // and may not be DELETED - they may only be flagged as discarded
    discard_duplicate_start_turns(turns, geometry1, geometry2);

    bool has_cc = false;
    bool const has_colocations
        = detail::overlay::handle_colocations
            <
                Reverse1, Reverse2, OverlayType, Geometry1, Geometry2
            >(turns, clusters, robust_policy);

    // Discard turns not part of target overlay
    for (typename boost::range_iterator<Turns>::type
            it = boost::begin(turns);
         it != boost::end(turns);
         ++it)
    {
        turn_type& turn = *it;

        if (turn.both(detail::overlay::operation_none)
            || turn.both(opposite_operation)
            || turn.both(detail::overlay::operation_blocked)
            || (detail::overlay::is_self_turn<OverlayType>(turn)
                && ! turn.is_clustered()
                && ! turn.both(target_operation)))
        {
            // For all operations, discard xx and none/none
            // For intersections, remove uu to avoid the need to travel
            // a union (during intersection) in uu/cc clusters (e.g. #31,#32,#33)
            // The ux is necessary to indicate impossible paths
            // (especially if rescaling is removed)

            // Similarly, for union, discard ii and ix

            // For self-turns, only keep uu / ii

            turn.discarded = true;
            turn.cluster_id = -1;
            continue;
        }

        if (! turn.discarded
            && turn.both(detail::overlay::operation_continue))
        {
            has_cc = true;
        }
    }

    if (! is_dissolve)
    {
        detail::overlay::discard_closed_turns
            <
                OverlayType,
                target_operation
            >::apply(turns, clusters, geometry1, geometry2,
                     strategy);
        detail::overlay::discard_open_turns
            <
                OverlayType,
                target_operation
            >::apply(turns, clusters, geometry1, geometry2,
                     strategy);
    }

    // Create a map of vectors of indexed operation-types to be able
    // to sort intersection points PER RING
    mapped_vector_type mapped_vector;

    detail::overlay::create_map(turns, mapped_vector,
                                detail::overlay::enriched_map_default_include_policy());

    // No const-iterator; contents of mapped copy is temporary,
    // and changed by enrich
    for (typename mapped_vector_type::iterator mit
        = mapped_vector.begin();
        mit != mapped_vector.end();
        ++mit)
    {
        detail::overlay::enrich_sort<Reverse1, Reverse2>(
                    mit->second, turns,
                    geometry1, geometry2,
                    robust_policy, strategy.side()); // TODO: pass strategy
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
        std::cout << "ENRICH-sort Ring " << mit->first << std::endl;
        for (auto const& op : mit->second)
        {
            std::cout << op.turn_index << " " << op.operation_index << std::endl;
        }
#endif
    }

    if (has_colocations)
    {
        // First gather cluster properties (using even clusters with
        // discarded turns - for open turns), then clean up clusters
        detail::overlay::gather_cluster_properties
            <
                Reverse1,
                Reverse2,
                OverlayType
            >(clusters, turns, target_operation,
              geometry1, geometry2, strategy.side()); // TODO: pass strategy

        detail::overlay::cleanup_clusters(turns, clusters);
    }

    // After cleaning up clusters assign the next turns

    for (typename mapped_vector_type::iterator mit
        = mapped_vector.begin();
        mit != mapped_vector.end();
        ++mit)
    {
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
    std::cout << "ENRICH-assign Ring " << mit->first << std::endl;
#endif
        if (is_dissolve)
        {
            detail::overlay::enrich_adapt(mit->second, turns);
        }

        detail::overlay::enrich_assign(mit->second, turns, ! is_dissolve);
    }

    if (has_cc)
    {
        detail::overlay::calculate_remaining_distance(turns);
    }

#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
    //detail::overlay::check_graph(turns, for_operation);
#endif

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_ENRICH_HPP

/* enrich_intersection_points.hpp
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
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017, 2019.
// Modifications copyright (c) 2017, 2019 Oracle and/or its affiliates.

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

#include <boost/range.hpp>

#include <boost/geometry/algorithms/detail/ring_identifier.hpp>
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
                << std::boolalpha << turns[it->turn_index].discarded
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

template <typename Turns, typename MappedVector>
inline void create_map(Turns const& turns, MappedVector& mapped_vector)
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
    typedef typename boost::range_value<Turns>::type turn_type;
    typedef typename turn_type::turn_operation_type op_type;

    for (typename boost::range_iterator<Turns>::type
            it = boost::begin(turns);
         it != boost::end(turns);
         ++it)
    {
        turn_type& turn = *it;

        op_type& op0 = turn.operations[0];
        op_type& op1 = turn.operations[1];

        if (op0.remaining_distance != 0
         || op1.remaining_distance != 0)
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
    // and may only be flagged as discarded

    bool has_cc = false;
    bool const has_colocations
        = detail::overlay::handle_colocations<Reverse1, Reverse2, OverlayType>(turns,
        clusters, geometry1, geometry2);

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

    detail::overlay::create_map(turns, mapped_vector);

    // No const-iterator; contents of mapped copy is temporary,
    // and changed by enrich
    for (typename mapped_vector_type::iterator mit
        = mapped_vector.begin();
        mit != mapped_vector.end();
        ++mit)
    {
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
    std::cout << "ENRICH-sort Ring "
        << mit->first << std::endl;
#endif
        detail::overlay::enrich_sort<Reverse1, Reverse2>(
                    mit->second, turns,
                    geometry1, geometry2,
                    robust_policy, strategy.get_side_strategy());
    }

    for (typename mapped_vector_type::iterator mit
        = mapped_vector.begin();
        mit != mapped_vector.end();
        ++mit)
    {
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
    std::cout << "ENRICH-assign Ring "
        << mit->first << std::endl;
#endif
        if (is_dissolve)
        {
            detail::overlay::enrich_adapt(mit->second, turns);
        }

        detail::overlay::enrich_assign(mit->second, turns, ! is_dissolve);
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
              geometry1, geometry2, strategy.get_side_strategy());

        detail::overlay::cleanup_clusters(turns, clusters);
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
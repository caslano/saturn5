// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013-2017 Adam Wulkiewicz, Lodz, Poland

// This file was modified by Oracle on 2015-2020.
// Modifications copyright (c) 2015-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_OVERLAY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_OVERLAY_HPP


#include <deque>
#include <map>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/detail/overlay/cluster_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/enrich_intersection_points.hpp>
#include <boost/geometry/algorithms/detail/overlay/enrichment_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turns.hpp>
#include <boost/geometry/algorithms/detail/overlay/is_self_turn.hpp>
#include <boost/geometry/algorithms/detail/overlay/needs_self_turns.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>
#include <boost/geometry/algorithms/detail/overlay/traverse.hpp>
#include <boost/geometry/algorithms/detail/overlay/traversal_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/self_turn_points.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>

#include <boost/geometry/algorithms/detail/recalculate.hpp>

#include <boost/geometry/algorithms/is_empty.hpp>
#include <boost/geometry/algorithms/reverse.hpp>

#include <boost/geometry/algorithms/detail/overlay/add_rings.hpp>
#include <boost/geometry/algorithms/detail/overlay/assign_parents.hpp>
#include <boost/geometry/algorithms/detail/overlay/ring_properties.hpp>
#include <boost/geometry/algorithms/detail/overlay/select_rings.hpp>
#include <boost/geometry/algorithms/detail/overlay/do_reverse.hpp>

#include <boost/geometry/policies/robustness/segment_ratio_type.hpp>

#include <boost/geometry/util/condition.hpp>

#ifdef BOOST_GEOMETRY_DEBUG_ASSEMBLE
#  include <boost/geometry/io/dsv/write.hpp>
#endif


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


//! Default visitor for overlay, doing nothing
struct overlay_null_visitor
{
    void print(char const* ) {}

    template <typename Turns>
    void print(char const* , Turns const& , int) {}

    template <typename Turns>
    void print(char const* , Turns const& , int , int ) {}

    template <typename Turns>
    void visit_turns(int , Turns const& ) {}

    template <typename Clusters, typename Turns>
    void visit_clusters(Clusters const& , Turns const& ) {}

    template <typename Turns, typename Turn, typename Operation>
    void visit_traverse(Turns const& , Turn const& , Operation const& , char const*)
    {}

    template <typename Turns, typename Turn, typename Operation>
    void visit_traverse_reject(Turns const& , Turn const& , Operation const& , traverse_error_type )
    {}

    template <typename Rings>
    void visit_generated_rings(Rings const& )
    {}
};

template
<
    overlay_type OverlayType,
    typename TurnInfoMap,
    typename Turns,
    typename Clusters
>
inline void get_ring_turn_info(TurnInfoMap& turn_info_map, Turns const& turns, Clusters const& clusters)
{
    typedef typename boost::range_value<Turns>::type turn_type;
    typedef typename turn_type::turn_operation_type turn_operation_type;
    typedef typename turn_type::container_type container_type;

    static const operation_type target_operation
            = operation_from_overlay<OverlayType>::value;
    static const operation_type opposite_operation
            = target_operation == operation_union
            ? operation_intersection
            : operation_union;

    for (typename boost::range_iterator<Turns const>::type
            it = boost::begin(turns);
         it != boost::end(turns);
         ++it)
    {
        turn_type const& turn = *it;

        bool cluster_checked = false;
        bool has_blocked = false;

        if (is_self_turn<OverlayType>(turn) && turn.discarded)
        {
            // Discarded self-turns don't count as traversed
            continue;
        }

        for (typename boost::range_iterator<container_type const>::type
                op_it = boost::begin(turn.operations);
            op_it != boost::end(turn.operations);
            ++op_it)
        {
            turn_operation_type const& op = *op_it;
            ring_identifier const ring_id = ring_id_by_seg_id(op.seg_id);

            if (! is_self_turn<OverlayType>(turn)
                && (
                    (BOOST_GEOMETRY_CONDITION(target_operation == operation_union)
                      && op.enriched.count_left > 0)
                  || (BOOST_GEOMETRY_CONDITION(target_operation == operation_intersection)
                      && op.enriched.count_right <= 2)))
            {
                // Avoid including untraversed rings which have polygons on
                // their left side (union) or not two on their right side (int)
                // This can only be done for non-self-turns because of count
                // information
                turn_info_map[ring_id].has_blocked_turn = true;
                continue;
            }

            if (turn.any_blocked())
            {
                turn_info_map[ring_id].has_blocked_turn = true;
            }
            if (turn_info_map[ring_id].has_traversed_turn
                    || turn_info_map[ring_id].has_blocked_turn)
            {
                continue;
            }

            // Check information in colocated turns
            if (! cluster_checked && turn.is_clustered())
            {
                check_colocation(has_blocked, turn.cluster_id, turns, clusters);
                cluster_checked = true;
            }

            // Block rings where any other turn is blocked,
            // and (with exceptions): i for union and u for intersection
            // Exceptions: don't block self-uu for intersection
            //             don't block self-ii for union
            //             don't block (for union) i/u if there is an self-ii too
            if (has_blocked
                || (op.operation == opposite_operation
                    && ! turn.has_colocated_both
                    && ! (turn.both(opposite_operation)
                          && is_self_turn<OverlayType>(turn))))
            {
                turn_info_map[ring_id].has_blocked_turn = true;
            }
        }
    }
}

template
<
    typename GeometryOut, overlay_type OverlayType, bool ReverseOut,
    typename Geometry1, typename Geometry2,
    typename OutputIterator, typename Strategy
>
inline OutputIterator return_if_one_input_is_empty(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            OutputIterator out, Strategy const& strategy)
{
    typedef typename geometry::ring_type<GeometryOut>::type ring_type;
    typedef std::deque<ring_type> ring_container_type;

    typedef ring_properties
        <
            typename geometry::point_type<ring_type>::type,
            typename geometry::area_result<ring_type, Strategy>::type
        > properties;

// Silence warning C4127: conditional expression is constant
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4127)
#endif

    // Union: return either of them
    // Intersection: return nothing
    // Difference: return first of them
    if (OverlayType == overlay_intersection
        || (OverlayType == overlay_difference && geometry::is_empty(geometry1)))
    {
        return out;
    }

#if defined(_MSC_VER)
#pragma warning(pop)
#endif


    std::map<ring_identifier, ring_turn_info> empty;
    std::map<ring_identifier, properties> all_of_one_of_them;

    select_rings<OverlayType>(geometry1, geometry2, empty, all_of_one_of_them, strategy);
    ring_container_type rings;
    assign_parents<OverlayType>(geometry1, geometry2, rings, all_of_one_of_them, strategy);
    return add_rings<GeometryOut>(all_of_one_of_them, geometry1, geometry2, rings, out, strategy);
}


template
<
    typename Geometry1, typename Geometry2,
    bool Reverse1, bool Reverse2, bool ReverseOut,
    typename GeometryOut,
    overlay_type OverlayType
>
struct overlay
{
    template <typename RobustPolicy, typename OutputIterator, typename Strategy, typename Visitor>
    static inline OutputIterator apply(
                Geometry1 const& geometry1, Geometry2 const& geometry2,
                RobustPolicy const& robust_policy,
                OutputIterator out,
                Strategy const& strategy,
                Visitor& visitor)
    {
        bool const is_empty1 = geometry::is_empty(geometry1);
        bool const is_empty2 = geometry::is_empty(geometry2);

        if (is_empty1 && is_empty2)
        {
            return out;
        }

        if (is_empty1 || is_empty2)
        {
            return return_if_one_input_is_empty
                <
                    GeometryOut, OverlayType, ReverseOut
                >(geometry1, geometry2, out, strategy);
        }

        typedef typename geometry::point_type<GeometryOut>::type point_type;
        typedef detail::overlay::traversal_turn_info
        <
            point_type,
            typename segment_ratio_type<point_type, RobustPolicy>::type
        > turn_info;
        typedef std::deque<turn_info> turn_container_type;

        typedef typename geometry::ring_type<GeometryOut>::type ring_type;
        typedef std::deque<ring_type> ring_container_type;

        // Define the clusters, mapping cluster_id -> turns
        typedef std::map
            <
                signed_size_type,
                cluster_info
            > cluster_type;

        turn_container_type turns;

#ifdef BOOST_GEOMETRY_DEBUG_ASSEMBLE
std::cout << "get turns" << std::endl;
#endif
        detail::get_turns::no_interrupt_policy policy;
        geometry::get_turns
            <
                Reverse1, Reverse2,
                assign_policy_only_start_turns
            >(geometry1, geometry2, strategy, robust_policy, turns, policy);

        visitor.visit_turns(1, turns);

#if ! defined(BOOST_GEOMETRY_NO_SELF_TURNS)
        if (! turns.empty() || OverlayType == overlay_dissolve)
        {
            // Calculate self turns if the output contains turns already,
            // and if necessary (e.g.: multi-geometry, polygon with interior rings)
            if (needs_self_turns<Geometry1>::apply(geometry1))
            {
                self_get_turn_points::self_turns<Reverse1, assign_policy_only_start_turns>(geometry1,
                    strategy, robust_policy, turns, policy, 0);
            }
            if (needs_self_turns<Geometry2>::apply(geometry2))
            {
                self_get_turn_points::self_turns<Reverse2, assign_policy_only_start_turns>(geometry2,
                    strategy, robust_policy, turns, policy, 1);
            }
        }
#endif


#ifdef BOOST_GEOMETRY_DEBUG_ASSEMBLE
std::cout << "enrich" << std::endl;
#endif

        cluster_type clusters;
        std::map<ring_identifier, ring_turn_info> turn_info_per_ring;

        geometry::enrich_intersection_points<Reverse1, Reverse2, OverlayType>(
            turns, clusters, geometry1, geometry2, robust_policy, strategy);

        visitor.visit_turns(2, turns);

        visitor.visit_clusters(clusters, turns);

#ifdef BOOST_GEOMETRY_DEBUG_ASSEMBLE
std::cout << "traverse" << std::endl;
#endif
        // Traverse through intersection/turn points and create rings of them.
        // These rings are always in clockwise order.
        // In CCW polygons they are marked as "to be reversed" below.
        ring_container_type rings;
        traverse<Reverse1, Reverse2, Geometry1, Geometry2, OverlayType>::apply
                (
                    geometry1, geometry2,
                    strategy,
                    robust_policy,
                    turns, rings,
                    turn_info_per_ring,
                    clusters,
                    visitor
                );
        visitor.visit_turns(3, turns);

        get_ring_turn_info<OverlayType>(turn_info_per_ring, turns, clusters);

        typedef ring_properties
            <
                point_type,
                typename geometry::area_result<ring_type, Strategy>::type
            > properties;

        // Select all rings which are NOT touched by any intersection point
        std::map<ring_identifier, properties> selected_ring_properties;
        select_rings<OverlayType>(geometry1, geometry2, turn_info_per_ring,
                selected_ring_properties, strategy);

        // Add rings created during traversal
        {
            ring_identifier id(2, 0, -1);
            for (auto const& ring : rings)
            {
                selected_ring_properties[id] = properties(ring, strategy);
                selected_ring_properties[id].reversed = ReverseOut;
                id.multi_index++;
            }
        }

        assign_parents<OverlayType>(geometry1, geometry2,
            rings, selected_ring_properties, strategy);

        // NOTE: There is no need to check result area for union because
        // as long as the polygons in the input are valid the resulting
        // polygons should be valid as well.
        // By default the area is checked (this is old behavior) however this
        // can be changed with #define. This may be important in non-cartesian CSes.
        // The result may be too big, so the area is negative. In this case either
        // it can be returned or an exception can be thrown.
        return add_rings<GeometryOut>(selected_ring_properties, geometry1, geometry2, rings, out,
                                      strategy,
                                      OverlayType == overlay_union ? 
#if defined(BOOST_GEOMETRY_UNION_THROW_INVALID_OUTPUT_EXCEPTION)
                                      add_rings_throw_if_reversed
#elif defined(BOOST_GEOMETRY_UNION_RETURN_INVALID)
                                      add_rings_add_unordered
#else
                                      add_rings_ignore_unordered
#endif
                                      : add_rings_ignore_unordered);
    }

    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(
                Geometry1 const& geometry1, Geometry2 const& geometry2,
                RobustPolicy const& robust_policy,
                OutputIterator out,
                Strategy const& strategy)
    {
        overlay_null_visitor visitor;
        return apply(geometry1, geometry2, robust_policy, out, strategy, visitor);
    }
};


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_OVERLAY_HPP

/* overlay.hpp
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
*/
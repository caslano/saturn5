// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_RING_CREATOR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_RING_CREATOR_HPP

#include <cstddef>

#include <boost/range.hpp>

#include <boost/geometry/algorithms/detail/overlay/backtrack_check_si.hpp>
#include <boost/geometry/algorithms/detail/overlay/copy_segments.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/traversal.hpp>
#include <boost/geometry/algorithms/num_points.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/closure.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template
<
    bool Reverse1,
    bool Reverse2,
    overlay_type OverlayType,
    typename Geometry1,
    typename Geometry2,
    typename Turns,
    typename TurnInfoMap,
    typename Clusters,
    typename IntersectionStrategy,
    typename RobustPolicy,
    typename Visitor,
    typename Backtrack
>
struct traversal_ring_creator
{
    typedef traversal
            <
                Reverse1, Reverse2, OverlayType,
                Geometry1, Geometry2, Turns, Clusters,
                RobustPolicy, typename IntersectionStrategy::side_strategy_type,
                Visitor
            > traversal_type;

    typedef typename boost::range_value<Turns>::type turn_type;
    typedef typename turn_type::turn_operation_type turn_operation_type;

    static const operation_type target_operation
        = operation_from_overlay<OverlayType>::value;

    inline traversal_ring_creator(Geometry1 const& geometry1, Geometry2 const& geometry2,
            Turns& turns, TurnInfoMap& turn_info_map,
            Clusters const& clusters,
            IntersectionStrategy const& intersection_strategy,
            RobustPolicy const& robust_policy, Visitor& visitor)
        : m_trav(geometry1, geometry2, turns, clusters,
                 robust_policy, intersection_strategy.get_side_strategy(),
                 visitor)
        , m_geometry1(geometry1)
        , m_geometry2(geometry2)
        , m_turns(turns)
        , m_turn_info_map(turn_info_map)
        , m_clusters(clusters)
        , m_intersection_strategy(intersection_strategy)
        , m_robust_policy(robust_policy)
        , m_visitor(visitor)
    {
    }

    template <typename Ring>
    inline traverse_error_type travel_to_next_turn(signed_size_type start_turn_index,
                int start_op_index,
                signed_size_type& turn_index,
                int& op_index,
                Ring& current_ring,
                bool is_start)
    {
        int const previous_op_index = op_index;
        signed_size_type const previous_turn_index = turn_index;
        turn_type& previous_turn = m_turns[turn_index];
        turn_operation_type& previous_op = previous_turn.operations[op_index];
        segment_identifier previous_seg_id;

        signed_size_type to_vertex_index = -1;
        if (! m_trav.select_turn_from_enriched(turn_index, previous_seg_id,
                          to_vertex_index, start_turn_index, start_op_index,
                          previous_turn, previous_op, is_start))
        {
            return is_start
                    ? traverse_error_no_next_ip_at_start
                    : traverse_error_no_next_ip;
        }
        if (to_vertex_index >= 0)
        {
            if (previous_op.seg_id.source_index == 0)
            {
                geometry::copy_segments<Reverse1>(m_geometry1,
                        previous_op.seg_id, to_vertex_index,
                        m_intersection_strategy.get_side_strategy(),
                        m_robust_policy, current_ring);
            }
            else
            {
                geometry::copy_segments<Reverse2>(m_geometry2,
                        previous_op.seg_id, to_vertex_index,
                        m_intersection_strategy.get_side_strategy(),
                        m_robust_policy, current_ring);
            }
        }

        if (m_turns[turn_index].discarded)
        {
            return is_start
                ? traverse_error_dead_end_at_start
                : traverse_error_dead_end;
        }

        if (is_start)
        {
            // Register the start
            previous_op.visited.set_started();
            m_visitor.visit_traverse(m_turns, previous_turn, previous_op, "Start");
        }

        if (! m_trav.select_turn(start_turn_index, start_op_index,
                turn_index, op_index,
                previous_op_index, previous_turn_index, previous_seg_id,
                is_start, current_ring.size() > 1))
        {
            return is_start
                ? traverse_error_no_next_ip_at_start
                : traverse_error_no_next_ip;
        }

        {
            // Check operation (TODO: this might be redundant or should be catched before)
            const turn_type& current_turn = m_turns[turn_index];
            const turn_operation_type& op = current_turn.operations[op_index];
            if (op.visited.finalized()
                || m_trav.is_visited(current_turn, op, turn_index, op_index))
            {
                return traverse_error_visit_again;
            }
        }

        // Update registration and append point
        turn_type& current_turn = m_turns[turn_index];
        turn_operation_type& op = current_turn.operations[op_index];
        detail::overlay::append_no_collinear(current_ring, current_turn.point,
            m_intersection_strategy.get_side_strategy(),
            m_robust_policy);

        // Register the visit
        m_trav.set_visited(current_turn, op);
        m_visitor.visit_traverse(m_turns, current_turn, op, "Visit");

        return traverse_error_none;
    }

    template <typename Ring>
    inline traverse_error_type traverse(Ring& ring,
            signed_size_type start_turn_index, int start_op_index)
    {
        turn_type const& start_turn = m_turns[start_turn_index];
        turn_operation_type& start_op = m_turns[start_turn_index].operations[start_op_index];

        detail::overlay::append_no_collinear(ring, start_turn.point,
            m_intersection_strategy.get_side_strategy(),
            m_robust_policy);

        signed_size_type current_turn_index = start_turn_index;
        int current_op_index = start_op_index;

        traverse_error_type error = travel_to_next_turn(start_turn_index,
                    start_op_index,
                    current_turn_index, current_op_index,
                    ring, true);

        if (error != traverse_error_none)
        {
            // This is not necessarily a problem, it happens for clustered turns
            // which are "build in" or otherwise point inwards
            return error;
        }

        if (current_turn_index == start_turn_index)
        {
            start_op.visited.set_finished();
            m_visitor.visit_traverse(m_turns, m_turns[current_turn_index], start_op, "Early finish");
            return traverse_error_none;
        }

        if (start_turn.is_clustered())
        {
            turn_type& turn = m_turns[current_turn_index];
            turn_operation_type& op = turn.operations[current_op_index];
            if (turn.cluster_id == start_turn.cluster_id
                && op.enriched.get_next_turn_index() == start_turn_index)
            {
                op.visited.set_finished();
                m_visitor.visit_traverse(m_turns, m_turns[current_turn_index], start_op, "Early finish (cluster)");
                return traverse_error_none;
            }
        }

        std::size_t const max_iterations = 2 + 2 * m_turns.size();
        for (std::size_t i = 0; i <= max_iterations; i++)
        {
            // We assume clockwise polygons only, non self-intersecting, closed.
            // However, the input might be different, and checking validity
            // is up to the library user.

            // Therefore we make here some sanity checks. If the input
            // violates the assumptions, the output polygon will not be correct
            // but the routine will stop and output the current polygon, and
            // will continue with the next one.

            // Below three reasons to stop.
            error = travel_to_next_turn(start_turn_index, start_op_index,
                    current_turn_index, current_op_index,
                    ring, false);

            if (error != traverse_error_none)
            {
                return error;
            }

            if (current_turn_index == start_turn_index
                    && current_op_index == start_op_index)
            {
                start_op.visited.set_finished();
                m_visitor.visit_traverse(m_turns, start_turn, start_op, "Finish");
                return traverse_error_none;
            }
        }

        return traverse_error_endless_loop;
    }

    template <typename Rings>
    void traverse_with_operation(turn_type const& start_turn,
            std::size_t turn_index, int op_index,
            Rings& rings, std::size_t& finalized_ring_size,
            typename Backtrack::state_type& state)
    {
        typedef typename boost::range_value<Rings>::type ring_type;

        turn_operation_type const& start_op = start_turn.operations[op_index];

        if (! start_op.visited.none()
            || ! start_op.enriched.startable
            || start_op.visited.rejected()
            || ! (start_op.operation == target_operation
                || start_op.operation == detail::overlay::operation_continue))
        {
            return;
        }

        ring_type ring;
        traverse_error_type traverse_error = traverse(ring, turn_index, op_index);

        if (traverse_error == traverse_error_none)
        {
            std::size_t const min_num_points
                    = core_detail::closure::minimum_ring_size
                            <
                                geometry::closure<ring_type>::value
                            >::value;

            if (geometry::num_points(ring) >= min_num_points)
            {
                clean_closing_dups_and_spikes(ring,
                                              m_intersection_strategy.get_side_strategy(),
                                              m_robust_policy);
                rings.push_back(ring);

                m_trav.finalize_visit_info(m_turn_info_map);
                finalized_ring_size++;
            }
        }
        else
        {
            Backtrack::apply(
                finalized_ring_size,
                rings, ring, m_turns, start_turn,
                m_turns[turn_index].operations[op_index],
                traverse_error,
                m_geometry1, m_geometry2,
                m_intersection_strategy, m_robust_policy,
                state, m_visitor);
        }
    }

    int get_operation_index(turn_type const& turn) const
    {
        // When starting with a continue operation, the one
        // with the smallest (for intersection) or largest (for union)
        // remaining distance (#8310b)
        // Also to avoid skipping a turn in between, which can happen
        // in rare cases (e.g. #130)
        static const bool is_union
            = operation_from_overlay<OverlayType>::value == operation_union;

        turn_operation_type const& op0 = turn.operations[0];
        turn_operation_type const& op1 = turn.operations[1];
        return op0.remaining_distance <= op1.remaining_distance
                ? (is_union ? 1 : 0)
                : (is_union ? 0 : 1);
    }

    template <typename Rings>
    void iterate(Rings& rings, std::size_t& finalized_ring_size,
                 typename Backtrack::state_type& state)
    {
        for (std::size_t turn_index = 0; turn_index < m_turns.size(); ++turn_index)
        {
            turn_type const& turn = m_turns[turn_index];

            if (turn.discarded || turn.blocked())
            {
                // Skip discarded and blocked turns
                continue;
            }

            if (turn.both(operation_continue))
            {
                traverse_with_operation(turn, turn_index,
                        get_operation_index(turn),
                        rings, finalized_ring_size, state);
            }
            else
            {
                for (int op_index = 0; op_index < 2; op_index++)
                {
                    traverse_with_operation(turn, turn_index, op_index,
                            rings, finalized_ring_size, state);
                }
            }
        }
    }

    template <typename Rings>
    void iterate_with_preference(std::size_t phase,
                 Rings& rings, std::size_t& finalized_ring_size,
                 typename Backtrack::state_type& state)
    {
        for (std::size_t turn_index = 0; turn_index < m_turns.size(); ++turn_index)
        {
            turn_type const& turn = m_turns[turn_index];

            if (turn.discarded || turn.blocked())
            {
                // Skip discarded and blocked turns
                continue;
            }

            turn_operation_type const& op0 = turn.operations[0];
            turn_operation_type const& op1 = turn.operations[1];

            if (phase == 0)
            {
                if (! op0.enriched.prefer_start && ! op1.enriched.prefer_start)
                {
                    // Not preferred, take next one
                    continue;
                }
            }

            if (turn.both(operation_continue))
            {
                traverse_with_operation(turn, turn_index,
                        get_operation_index(turn),
                        rings, finalized_ring_size, state);
            }
            else
            {
                bool const forward = op0.enriched.prefer_start;

                int op_index = forward ? 0 : 1;
                int const increment = forward ? 1 : -1;

                for (int i = 0; i < 2; i++, op_index += increment)
                {
                    traverse_with_operation(turn, turn_index, op_index,
                            rings, finalized_ring_size, state);
                }
            }
        }
    }

private:
    traversal_type m_trav;

    Geometry1 const& m_geometry1;
    Geometry2 const& m_geometry2;
    Turns& m_turns;
    TurnInfoMap& m_turn_info_map; // contains turn-info information per ring
    Clusters const& m_clusters;
    IntersectionStrategy const& m_intersection_strategy;
    RobustPolicy const& m_robust_policy;
    Visitor& m_visitor;
};

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_RING_CREATOR_HPP

/* traversal_ring_creator.hpp
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
*/
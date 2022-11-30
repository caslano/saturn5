// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_RING_CREATOR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_RING_CREATOR_HPP

#include <cstddef>

#include <boost/range/value_type.hpp>

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
    typename Strategy,
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
                RobustPolicy,
                decltype(std::declval<Strategy>().side()),
                Visitor
            > traversal_type;

    typedef typename boost::range_value<Turns>::type turn_type;
    typedef typename turn_type::turn_operation_type turn_operation_type;

    static const operation_type target_operation
        = operation_from_overlay<OverlayType>::value;

    inline traversal_ring_creator(Geometry1 const& geometry1, Geometry2 const& geometry2,
            Turns& turns, TurnInfoMap& turn_info_map,
            Clusters const& clusters,
            Strategy const& strategy,
            RobustPolicy const& robust_policy, Visitor& visitor)
        : m_trav(geometry1, geometry2, turns, clusters,
                 robust_policy, strategy.side(), visitor)
        , m_geometry1(geometry1)
        , m_geometry2(geometry2)
        , m_turns(turns)
        , m_turn_info_map(turn_info_map)
        , m_clusters(clusters)
        , m_strategy(strategy)
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
                        m_strategy, m_robust_policy, current_ring);
            }
            else
            {
                geometry::copy_segments<Reverse2>(m_geometry2,
                        previous_op.seg_id, to_vertex_index,
                        m_strategy, m_robust_policy, current_ring);
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
                                             m_strategy, m_robust_policy);

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
                                             m_strategy, m_robust_policy);

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
                clean_closing_dups_and_spikes(ring, m_strategy, m_robust_policy);
                rings.push_back(ring);

                m_trav.finalize_visit_info(m_turn_info_map);
                finalized_ring_size++;
            }
        }
        else
        {
            Backtrack::apply(finalized_ring_size,
                             rings, ring, m_turns, start_turn,
                             m_turns[turn_index].operations[op_index],
                             traverse_error,
                             m_geometry1, m_geometry2,
                             m_strategy, m_robust_policy,
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
    Strategy const& m_strategy;
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
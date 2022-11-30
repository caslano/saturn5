// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_HPP

#include <cstddef>
#include <set>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/detail/overlay/cluster_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/cluster_exits.hpp>
#include <boost/geometry/algorithms/detail/overlay/is_self_turn.hpp>
#include <boost/geometry/algorithms/detail/overlay/sort_by_side.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/util/condition.hpp>

#if defined(BOOST_GEOMETRY_DEBUG_INTERSECTION) \
    || defined(BOOST_GEOMETRY_OVERLAY_REPORT_WKT) \
    || defined(BOOST_GEOMETRY_DEBUG_TRAVERSE)
#  include <string>
#  include <boost/geometry/algorithms/detail/overlay/debug_turn_info.hpp>
#  include <boost/geometry/io/wkt/wkt.hpp>
#endif

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template <typename Turn, typename Operation>
#ifdef BOOST_GEOMETRY_DEBUG_TRAVERSE
inline void debug_traverse(Turn const& turn, Operation op,
                std::string const& header, bool condition = true)
{
    if (! condition)
    {
        return;
    }
    std::cout << " " << header
        << " at " << op.seg_id
        << " meth: " << method_char(turn.method)
        << " op: " << operation_char(op.operation)
        << " vis: " << visited_char(op.visited)
        << " of:  " << operation_char(turn.operations[0].operation)
        << operation_char(turn.operations[1].operation)
        << " " << geometry::wkt(turn.point)
        << std::endl;

    if (boost::contains(header, "Finished"))
    {
        std::cout << std::endl;
    }
}
#else
inline void debug_traverse(Turn const& , Operation, const char*, bool = true)
{
}
#endif

template
<
    bool Reverse1,
    bool Reverse2,
    overlay_type OverlayType,
    typename Geometry1,
    typename Geometry2,
    typename Turns,
    typename Clusters,
    typename RobustPolicy,
    typename SideStrategy,
    typename Visitor
>
struct traversal
{
private :

    static const operation_type target_operation = operation_from_overlay<OverlayType>::value;

    typedef typename sort_by_side::side_compare<target_operation>::type side_compare_type;
    typedef typename boost::range_value<Turns>::type turn_type;
    typedef typename turn_type::turn_operation_type turn_operation_type;

    typedef typename geometry::point_type<Geometry1>::type point_type;
    typedef sort_by_side::side_sorter
        <
            Reverse1, Reverse2, OverlayType,
            point_type, SideStrategy, side_compare_type
        > sbs_type;

public :
    inline traversal(Geometry1 const& geometry1, Geometry2 const& geometry2,
            Turns& turns, Clusters const& clusters,
            RobustPolicy const& robust_policy, SideStrategy const& strategy,
            Visitor& visitor)
        : m_geometry1(geometry1)
        , m_geometry2(geometry2)
        , m_turns(turns)
        , m_clusters(clusters)
        , m_robust_policy(robust_policy)
        , m_strategy(strategy)
        , m_visitor(visitor)
    {
    }

    template <typename TurnInfoMap>
    inline void finalize_visit_info(TurnInfoMap& turn_info_map)
    {
        for (typename boost::range_iterator<Turns>::type
            it = boost::begin(m_turns);
            it != boost::end(m_turns);
            ++it)
        {
            turn_type& turn = *it;
            for (int i = 0; i < 2; i++)
            {
                turn_operation_type& op = turn.operations[i];
                if (op.visited.visited()
                    || op.visited.started()
                    || op.visited.finished() )
                {
                   ring_identifier const ring_id = ring_id_by_seg_id(op.seg_id);
                   turn_info_map[ring_id].has_traversed_turn = true;

                   if (op.operation == operation_continue)
                   {
                       // Continue operations should mark the other operation
                       // as traversed too
                       turn_operation_type& other_op = turn.operations[1 - i];
                       ring_identifier const other_ring_id
                               = ring_id_by_seg_id(other_op.seg_id);
                       turn_info_map[other_ring_id].has_traversed_turn = true;
                   }
                }
                op.visited.finalize();
            }
        }
    }

    //! Sets visited for ALL turns traveling to the same turn
    inline void set_visited_in_cluster(signed_size_type cluster_id,
                                       signed_size_type rank)
    {
        typename Clusters::const_iterator mit = m_clusters.find(cluster_id);
        BOOST_ASSERT(mit != m_clusters.end());

        cluster_info const& cinfo = mit->second;
        std::set<signed_size_type> const& ids = cinfo.turn_indices;

        for (typename std::set<signed_size_type>::const_iterator it = ids.begin();
             it != ids.end(); ++it)
        {
            signed_size_type const turn_index = *it;
            turn_type& turn = m_turns[turn_index];

            for (int i = 0; i < 2; i++)
            {
                turn_operation_type& op = turn.operations[i];
                if (op.visited.none()
                    && op.enriched.rank == rank)
                {
                    op.visited.set_visited();
                }
            }
        }
    }
    inline void set_visited(turn_type& turn, turn_operation_type& op)
    {
        if (op.operation == detail::overlay::operation_continue)
        {
            // On "continue", all go in same direction so set "visited" for ALL
            for (int i = 0; i < 2; i++)
            {
                turn_operation_type& turn_op = turn.operations[i];
                if (turn_op.visited.none())
                {
                    turn_op.visited.set_visited();
                }
            }
        }
        else
        {
            op.visited.set_visited();
        }
        if (turn.is_clustered())
        {
            set_visited_in_cluster(turn.cluster_id, op.enriched.rank);
        }
    }

    inline bool is_visited(turn_type const& , turn_operation_type const& op,
                         signed_size_type , int) const
    {
        return op.visited.visited();
    }

    template <signed_size_type segment_identifier::*Member>
    inline bool select_source_generic(turn_type const& turn,
            segment_identifier const& current,
            segment_identifier const& previous) const
    {
        turn_operation_type const& op0 = turn.operations[0];
        turn_operation_type const& op1 = turn.operations[1];

        bool const switch_source = op0.enriched.region_id != -1
                && op0.enriched.region_id == op1.enriched.region_id;

#if defined(BOOST_GEOMETRY_DEBUG_TRAVERSAL_SWITCH_DETECTOR)
        if (switch_source)
        {
            std::cout << "Switch source at " << &turn << std::endl;
        }
        else
        {
            std::cout << "DON'T SWITCH SOURCES at " << &turn << std::endl;
        }
#endif
        return switch_source
                ? current.*Member != previous.*Member
                : current.*Member == previous.*Member;
    }

    inline bool select_source(turn_type const& turn,
                              segment_identifier const& candidate_seg_id,
                              segment_identifier const& previous_seg_id) const
    {
        // For uu/ii, only switch sources if indicated

        if (BOOST_GEOMETRY_CONDITION(OverlayType == overlay_buffer))
        {
            // Buffer does not use source_index (always 0).
            return select_source_generic<&segment_identifier::multi_index>(
                        turn, candidate_seg_id, previous_seg_id);
        }

        if (is_self_turn<OverlayType>(turn))
        {
            // Also, if it is a self-turn, stay on same ring (multi/ring)
            return select_source_generic<&segment_identifier::multi_index>(
                        turn, candidate_seg_id, previous_seg_id);
        }

        // Use source_index
        return select_source_generic<&segment_identifier::source_index>(
                    turn, candidate_seg_id, previous_seg_id);
    }

    inline bool traverse_possible(signed_size_type turn_index) const
    {
        if (turn_index == -1)
        {
            return false;
        }

        turn_type const& turn = m_turns[turn_index];

        // It is not a dead end if there is an operation to continue, or of
        // there is a cluster (assuming for now we can get out of the cluster)
        return turn.is_clustered()
            || turn.has(target_operation)
            || turn.has(operation_continue);
    }

    inline std::size_t get_shortcut_level(turn_operation_type const& op,
                             signed_size_type start_turn_index,
                             signed_size_type origin_turn_index,
                             std::size_t level = 1) const
    {
        signed_size_type next_turn_index = op.enriched.get_next_turn_index();
        if (next_turn_index == -1)
        {
            return 0;
        }
        if (next_turn_index == start_turn_index)
        {
            // This operation finishes the ring
            return 0;
        }
        if (next_turn_index == origin_turn_index)
        {
            // This operation travels to itself
            return level;
        }
        if (level > 10)
        {
            // Avoid infinite recursion
            return 0;
        }

        turn_type const& next_turn = m_turns[next_turn_index];
        for (int i = 0; i < 2; i++)
        {
            turn_operation_type const& next_op = next_turn.operations[i];
            if (next_op.operation == target_operation
                && ! next_op.visited.finished()
                && ! next_op.visited.visited())
            {
                // Recursively continue verifying
                if (get_shortcut_level(next_op, start_turn_index,
                                       origin_turn_index, level + 1))
                {
                    return level + 1;
                }
            }
        }
        return 0;
    }

    inline
    bool select_cc_operation(turn_type const& turn,
                signed_size_type start_turn_index,
                int& selected_op_index) const
    {
        // For "cc", take either one, but if there is a starting one,
        //           take that one. If next is dead end, skip that one.
        // If both are valid candidates, take the one with minimal remaining
        // distance (important for #mysql_23023665 in buffer).

        signed_size_type next[2] = {0};
        bool possible[2] = {0};
        bool close[2] = {0};

        for (int i = 0; i < 2; i++)
        {
            next[i] = turn.operations[i].enriched.get_next_turn_index();
            possible[i] = traverse_possible(next[i]);
            close[i] = possible[i] && next[i] == start_turn_index;
        }

        if (close[0] != close[1])
        {
            // One of the operations will finish the ring. Take that one.
            selected_op_index = close[0] ? 0 : 1;
            debug_traverse(turn, turn.operations[selected_op_index], "Candidate cc closing");
            return true;
        }

        if (BOOST_GEOMETRY_CONDITION(OverlayType == overlay_buffer)
            && possible[0] && possible[1])
        {
            // Buffers sometimes have multiple overlapping pieces, where remaining
            // distance could lead to the wrong choice. Take the matching operation.

            bool is_target[2] = {0};
            for (int i = 0; i < 2; i++)
            {
                turn_operation_type const& next_op = m_turns[next[i]].operations[i];
                is_target[i] = next_op.operation == target_operation;
            }

            if (is_target[0] != is_target[1])
            {
                // Take the matching operation
                selected_op_index = is_target[0] ? 0 : 1;
                debug_traverse(turn, turn.operations[selected_op_index], "Candidate cc target");
                return true;
            }
        }

        static bool const is_union = target_operation == operation_union;

        typename turn_operation_type::comparable_distance_type
                best_remaining_distance = 0;

        bool result = false;

        for (int i = 0; i < 2; i++)
        {
            if (!possible[i])
            {
                continue;
            }

            turn_operation_type const& op = turn.operations[i];

            if (! result
                || (is_union && op.remaining_distance > best_remaining_distance)
                || (!is_union && op.remaining_distance < best_remaining_distance))
            {
                debug_traverse(turn, op, "First candidate cc", ! result);
                debug_traverse(turn, op, "Candidate cc override (remaining)",
                    result && op.remaining_distance < best_remaining_distance);

                selected_op_index = i;
                best_remaining_distance = op.remaining_distance;
                result = true;
            }
        }

        return result;
    }

    inline
    bool select_noncc_operation(turn_type const& turn,
                segment_identifier const& previous_seg_id,
                int& selected_op_index) const
    {
        bool result = false;

        for (int i = 0; i < 2; i++)
        {
            turn_operation_type const& op = turn.operations[i];

            if (op.operation == target_operation
                && ! op.visited.finished()
                && ! op.visited.visited()
                && (! result || select_source(turn, op.seg_id, previous_seg_id)))
            {
                selected_op_index = i;
                debug_traverse(turn, op, "Candidate");
                result = true;
            }
        }

        return result;
    }

    inline
    bool select_preferred_operation(turn_type const& turn,
                signed_size_type turn_index,
                signed_size_type start_turn_index,
                int& selected_op_index) const
    {
        bool option[2] = {0};
        bool finishing[2] = {0};
        bool preferred[2] = {0};
        std::size_t shortcut_level[2] = {0};
        for (int i = 0; i < 2; i++)
        {
            turn_operation_type const& op = turn.operations[i];

            if (op.operation == target_operation
                && ! op.visited.finished()
                && ! op.visited.visited())
            {
                option[i] = true;
                if (op.enriched.get_next_turn_index() == start_turn_index)
                {
                    finishing[i] = true;
                }
                else
                {
                    shortcut_level[i] = get_shortcut_level(op, start_turn_index,
                                                           turn_index);
                }

                if (op.enriched.prefer_start)
                {
                    preferred[i] = true;
                }
            }
        }

        if (option[0] != option[1])
        {
            // Only one operation is acceptable, take that one
            selected_op_index = option[0] ? 0 : 1;
            return true;
        }

        if (option[0] && option[1])
        {
            // Both operations are acceptable
            if (finishing[0] != finishing[1])
            {
                // Prefer operation finishing the ring
                selected_op_index = finishing[0] ? 0 : 1;
                return true;
            }

            if (shortcut_level[0] != shortcut_level[1])
            {
                // If a turn can travel to itself again (without closing the
                // ring), take the shortest one
                selected_op_index = shortcut_level[0] < shortcut_level[1] ? 0 : 1;
                return true;
            }

            if (preferred[0] != preferred[1])
            {
                // Only one operation is preferred (== was not intersection)
                selected_op_index = preferred[0] ? 0 : 1;
                return true;
            }
        }

        for (int i = 0; i < 2; i++)
        {
            if (option[i])
            {
                selected_op_index = 0;
                return true;
            }
        }

        return false;
    }

    inline
    bool select_operation(const turn_type& turn,
                signed_size_type turn_index,
                signed_size_type start_turn_index,
                segment_identifier const& previous_seg_id,
                int& selected_op_index) const
    {
        bool result = false;
        selected_op_index = -1;
        if (turn.both(operation_continue))
        {
            result = select_cc_operation(turn, start_turn_index,
                                         selected_op_index);
        }
        else if (BOOST_GEOMETRY_CONDITION(OverlayType == overlay_dissolve))
        {
            result = select_preferred_operation(turn, turn_index,
                start_turn_index, selected_op_index);
        }
        else
        {
            result = select_noncc_operation(turn, previous_seg_id,
                selected_op_index);
        }
        if (result)
        {
           debug_traverse(turn, turn.operations[selected_op_index], "Accepted");
        }

        return result;
    }

    inline int starting_operation_index(const turn_type& turn) const
    {
        for (int i = 0; i < 2; i++)
        {
            if (turn.operations[i].visited.started())
            {
                return i;
            }
        }
        return -1;
    }

    inline bool both_finished(const turn_type& turn) const
    {
        for (int i = 0; i < 2; i++)
        {
            if (! turn.operations[i].visited.finished())
            {
                return false;
            }
        }
        return true;
    }

    inline int priority_of_turn_in_cluster_union(sort_by_side::rank_type selected_rank,
            typename sbs_type::rp const& ranked_point,
            std::set<signed_size_type> const& cluster_indices,
            signed_size_type start_turn_index, int start_op_index) const
    {
        // Returns 0: not OK
        // Returns 1: OK but next turn is in same cluster
        // Returns 2: OK
        // Returns 3: OK and start turn matches
        // Returns 4: OK and start turn and start op both match
        if (ranked_point.rank != selected_rank
            || ranked_point.direction != sort_by_side::dir_to)
        {
            return 0;
        }

        auto const& turn = m_turns[ranked_point.turn_index];
        auto const& op = turn.operations[ranked_point.operation_index];

        // Check finalized: TODO: this should be finetuned, it is not necessary
        if (op.visited.finalized())
        {
            return 0;
        }

        if (BOOST_GEOMETRY_CONDITION(OverlayType != overlay_dissolve)
            && (op.enriched.count_left != 0 || op.enriched.count_right == 0))
        {
            // Check counts: in some cases interior rings might be generated with
            // polygons on both sides. For dissolve it can be anything.
            return 0;
        }

        bool const to_start = ranked_point.turn_index == start_turn_index;
        bool const to_start_index = ranked_point.operation_index == start_op_index;

        bool const next_in_same_cluster
                = cluster_indices.count(op.enriched.get_next_turn_index()) > 0;

        return to_start && to_start_index ? 4
            : to_start ? 3
            : next_in_same_cluster ? 1
            : 2
            ;
    }

    template <typename RankedPoint>
    inline turn_operation_type const& operation_from_rank(RankedPoint const& rp) const
    {
        return m_turns[rp.turn_index].operations[rp.operation_index];
    }

    inline sort_by_side::rank_type select_rank(sbs_type const& sbs) const
    {
        static bool const is_intersection
                = target_operation == operation_intersection;

        // Take the first outgoing rank corresponding to incoming region,
        // or take another region if it is not isolated
        auto const& in_op = operation_from_rank(sbs.m_ranked_points.front());

        for (std::size_t i = 0; i < sbs.m_ranked_points.size(); i++)
        {
            auto const& rp = sbs.m_ranked_points[i];
            if (rp.rank == 0 || rp.direction == sort_by_side::dir_from)
            {
                continue;
            }
            auto const& out_op = operation_from_rank(rp);

            if (out_op.operation != target_operation
                && out_op.operation != operation_continue)
            {
                continue;
            }

            if (in_op.enriched.region_id == out_op.enriched.region_id
                || (is_intersection && ! out_op.enriched.isolated))
            {
                // Region corresponds to incoming region, or (for intersection)
                // there is a non-isolated other region which should be taken
                return rp.rank;
            }
        }
        return -1;
    }

    inline bool select_from_cluster_union(signed_size_type& turn_index,
        std::set<signed_size_type> const& cluster_indices,
        int& op_index, sbs_type const& sbs,
        signed_size_type start_turn_index, int start_op_index) const
    {
        sort_by_side::rank_type const selected_rank = select_rank(sbs);

        int current_priority = 0;
        for (std::size_t i = 1; i < sbs.m_ranked_points.size(); i++)
        {
            typename sbs_type::rp const& ranked_point = sbs.m_ranked_points[i];

            if (ranked_point.rank > selected_rank)
            {
                break;
            }

            int const priority = priority_of_turn_in_cluster_union(selected_rank,
                ranked_point, cluster_indices, start_turn_index, start_op_index);

            if (priority > current_priority)
            {
                current_priority = priority;
                turn_index = ranked_point.turn_index;
                op_index = ranked_point.operation_index;
            }
        }
        return current_priority > 0;
    }

    inline bool analyze_cluster_intersection(signed_size_type& turn_index,
                int& op_index, sbs_type const& sbs) const
    {
        // Select the rank based on regions and isolation
        sort_by_side::rank_type const selected_rank = select_rank(sbs);

        if (selected_rank <= 0)
        {
            return false;
        }

        // From these ranks, select the index: the first, or the one with
        // the smallest remaining distance
        typename turn_operation_type::comparable_distance_type
                min_remaining_distance = 0;

        std::size_t selected_index = sbs.m_ranked_points.size();
        for (std::size_t i = 0; i < sbs.m_ranked_points.size(); i++)
        {
            auto const& ranked_point = sbs.m_ranked_points[i];

            if (ranked_point.rank > selected_rank)
            {
                break;
            }
            else if (ranked_point.rank == selected_rank)
            {
                auto const& op = operation_from_rank(ranked_point);

                if (op.visited.finalized())
                {
                    // This direction is already traveled,
                    // it cannot be traveled again
                    continue;
                }

                if (selected_index == sbs.m_ranked_points.size()
                        || op.remaining_distance < min_remaining_distance)
                {
                    // It was unassigned or it is better
                    selected_index = i;
                    min_remaining_distance = op.remaining_distance;
                }
            }
        }

        if (selected_index == sbs.m_ranked_points.size())
        {
            // Should not happen, there must be points with the selected rank
            return false;
        }

        auto const& ranked_point = sbs.m_ranked_points[selected_index];
        turn_index = ranked_point.turn_index;
        op_index = ranked_point.operation_index;
        return true;
    }

    inline bool fill_sbs(sbs_type& sbs,
                         signed_size_type turn_index,
                         std::set<signed_size_type> const& cluster_indices,
                         segment_identifier const& previous_seg_id) const
    {

        for (auto cluster_turn_index : cluster_indices)
        {
            turn_type const& cluster_turn = m_turns[cluster_turn_index];
            if (cluster_turn.discarded)
            {
                // Defensive check, discarded turns should not be in cluster
                continue;
            }

            for (int i = 0; i < 2; i++)
            {
                sbs.add(cluster_turn,
                        cluster_turn.operations[i],
                        cluster_turn_index, i, previous_seg_id,
                        m_geometry1, m_geometry2,
                        cluster_turn_index == turn_index);
            }
        }

        if (! sbs.has_origin())
        {
            return false;
        }
        turn_type const& turn = m_turns[turn_index];
        sbs.apply(turn.point);
        return true;
    }


    inline bool select_turn_from_cluster(signed_size_type& turn_index,
            int& op_index,
            signed_size_type start_turn_index, int start_op_index,
            segment_identifier const& previous_seg_id) const
    {
        bool const is_union = target_operation == operation_union;

        turn_type const& turn = m_turns[turn_index];
        BOOST_ASSERT(turn.is_clustered());

        typename Clusters::const_iterator mit = m_clusters.find(turn.cluster_id);
        BOOST_ASSERT(mit != m_clusters.end());

        cluster_info const& cinfo = mit->second;
        std::set<signed_size_type> const& cluster_indices = cinfo.turn_indices;

        sbs_type sbs(m_strategy);


        if (! fill_sbs(sbs, turn_index, cluster_indices, previous_seg_id))
        {
            return false;
        }

        cluster_exits<OverlayType, Turns, sbs_type> exits(m_turns, cluster_indices, sbs);

        if (exits.apply(turn_index, op_index))
        {
            return true;
        }

        bool result = false;

        if (is_union)
        {
            result = select_from_cluster_union(turn_index, cluster_indices,
                                               op_index, sbs,
                                               start_turn_index, start_op_index);
            if (! result)
            {
               // There no way out found, try second pass in collected cluster exits
               result = exits.apply(turn_index, op_index, false);
            }
        }
        else
        {
            result = analyze_cluster_intersection(turn_index, op_index, sbs);
        }
        return result;
    }

    // Analyzes a non-clustered "ii" intersection, as if it is clustered.
    inline bool analyze_ii_intersection(signed_size_type& turn_index, int& op_index,
                    turn_type const& current_turn,
                    segment_identifier const& previous_seg_id)
    {
        sbs_type sbs(m_strategy);

        // Add this turn to the sort-by-side sorter
        for (int i = 0; i < 2; i++)
        {
            sbs.add(current_turn,
                    current_turn.operations[i],
                    turn_index, i, previous_seg_id,
                    m_geometry1, m_geometry2,
                    true);
        }

        if (! sbs.has_origin())
        {
            return false;
        }

        sbs.apply(current_turn.point);

        bool result = analyze_cluster_intersection(turn_index, op_index, sbs);

        return result;
    }

    inline void change_index_for_self_turn(signed_size_type& to_vertex_index,
                turn_type const& start_turn,
                turn_operation_type const& start_op,
                int start_op_index) const
    {
        if (BOOST_GEOMETRY_CONDITION(OverlayType != overlay_buffer
                                     && OverlayType != overlay_dissolve))
        {
            return;
        }

        const bool allow_uu = OverlayType != overlay_buffer;

        // It travels to itself, can happen. If this is a buffer, it can
        // sometimes travel to itself in the following configuration:
        //
        // +---->--+
        // |       |
        // |   +---*----+ *: one turn, with segment index 2/7
        // |   |   |    |
        // |   +---C    | C: closing point (start/end)
        // |            |
        // +------------+
        //
        // If it starts on segment 2 and travels to itself on segment 2, that
        // should be corrected to 7 because that is the shortest path
        //
        // Also a uu turn (touching with another buffered ring) might have this
        // apparent configuration, but there it should
        // always travel the whole ring

        turn_operation_type const& other_op
                = start_turn.operations[1 - start_op_index];

        bool const correct
                = (allow_uu || ! start_turn.both(operation_union))
                  && start_op.seg_id.source_index == other_op.seg_id.source_index
                  && start_op.seg_id.multi_index == other_op.seg_id.multi_index
                  && start_op.seg_id.ring_index == other_op.seg_id.ring_index
                  && start_op.seg_id.segment_index == to_vertex_index;

#if defined(BOOST_GEOMETRY_DEBUG_TRAVERSE)
        std::cout << " WARNING: self-buffer "
                  << " correct=" << correct
                  << " turn=" << operation_char(start_turn.operations[0].operation)
                  << operation_char(start_turn.operations[1].operation)
                  << " start=" << start_op.seg_id.segment_index
                  << " from=" << to_vertex_index
                  << " to=" << other_op.enriched.travels_to_vertex_index
                  << std::endl;
#endif

        if (correct)
        {
            to_vertex_index = other_op.enriched.travels_to_vertex_index;
        }
    }

    bool select_turn_from_enriched(signed_size_type& turn_index,
            segment_identifier& previous_seg_id,
            signed_size_type& to_vertex_index,
            signed_size_type start_turn_index,
            int start_op_index,
            turn_type const& previous_turn,
            turn_operation_type const& previous_op,
            bool is_start) const
    {
        to_vertex_index = -1;

        if (previous_op.enriched.next_ip_index < 0)
        {
            // There is no next IP on this segment
            if (previous_op.enriched.travels_to_vertex_index < 0
                || previous_op.enriched.travels_to_ip_index < 0)
            {
                return false;
            }

            to_vertex_index = previous_op.enriched.travels_to_vertex_index;

            if (is_start &&
                    previous_op.enriched.travels_to_ip_index == start_turn_index)
            {
                change_index_for_self_turn(to_vertex_index, previous_turn,
                    previous_op, start_op_index);
            }

            turn_index = previous_op.enriched.travels_to_ip_index;
            previous_seg_id = previous_op.seg_id;
        }
        else
        {
            // Take the next IP on this segment
            turn_index = previous_op.enriched.next_ip_index;
            previous_seg_id = previous_op.seg_id;
        }
        return true;
    }

    bool select_turn(signed_size_type start_turn_index, int start_op_index,
                     signed_size_type& turn_index,
                     int& op_index,
                     int previous_op_index,
                     signed_size_type previous_turn_index,
                     segment_identifier const& previous_seg_id,
                     bool is_start, bool has_points)
    {
        turn_type const& current_turn = m_turns[turn_index];

        if (BOOST_GEOMETRY_CONDITION(target_operation == operation_intersection))
        {
            if (has_points)
            {
                bool const back_at_start_cluster
                        = current_turn.is_clustered()
                        && m_turns[start_turn_index].cluster_id == current_turn.cluster_id;

                if (turn_index == start_turn_index || back_at_start_cluster)
                {
                    // Intersection can always be finished if returning
                    turn_index = start_turn_index;
                    op_index = start_op_index;
                    return true;
                }
            }

            if (! current_turn.is_clustered()
                && current_turn.both(operation_intersection))
            {
                if (analyze_ii_intersection(turn_index, op_index,
                            current_turn, previous_seg_id))
                {
                    return true;
                }
            }
        }

        if (current_turn.is_clustered())
        {
            if (! select_turn_from_cluster(turn_index, op_index,
                    start_turn_index, start_op_index, previous_seg_id))
            {
                return false;
            }

            if (is_start && turn_index == previous_turn_index)
            {
                op_index = previous_op_index;
            }
        }
        else
        {
            op_index = starting_operation_index(current_turn);
            if (op_index == -1)
            {
                if (both_finished(current_turn))
                {
                    return false;
                }

                if (! select_operation(current_turn, turn_index,
                                start_turn_index,
                                previous_seg_id,
                                op_index))
                {
                    return false;
                }
            }
        }
        return true;
    }

private :
    Geometry1 const& m_geometry1;
    Geometry2 const& m_geometry2;
    Turns& m_turns;
    Clusters const& m_clusters;
    RobustPolicy const& m_robust_policy;
    SideStrategy m_strategy;
    Visitor& m_visitor;
};



}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_HPP

/* traversal.hpp
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
*/
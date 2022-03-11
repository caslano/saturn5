// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_HPP

#include <cstddef>
#include <set>

#include <boost/range.hpp>

#include <boost/geometry/algorithms/detail/overlay/cluster_info.hpp>
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
    struct linked_turn_op_info
    {
        explicit linked_turn_op_info(signed_size_type ti = -1, int oi = -1,
                    signed_size_type nti = -1)
            : turn_index(ti)
            , op_index(oi)
            , next_turn_index(nti)
            , rank_index(-1)
        {}

        signed_size_type turn_index;
        int op_index;
        signed_size_type next_turn_index;
        signed_size_type rank_index;
    };

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


    template <typename RankedPoint>
    inline turn_operation_type const& operation_from_rank(RankedPoint const& rp) const
    {
        return m_turns[rp.turn_index].operations[rp.operation_index];
    }

    inline int select_turn_in_cluster_union(sort_by_side::rank_type selected_rank,
            typename sbs_type::rp const& ranked_point,
            signed_size_type start_turn_index, int start_op_index) const
    {
        // Returns 0 if it not OK
        // Returns 1 if it OK
        // Returns 2 if it OK and start turn matches
        // Returns 3 if it OK and start turn and start op both match
        if (ranked_point.rank != selected_rank
            || ranked_point.direction != sort_by_side::dir_to)
        {
            return 0;
        }

        turn_operation_type const& op = operation_from_rank(ranked_point);

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

        return ranked_point.turn_index == start_turn_index
                && ranked_point.operation_index == start_op_index ? 3
            : ranked_point.turn_index == start_turn_index ? 2
            : 1
            ;
    }

    inline sort_by_side::rank_type select_rank(sbs_type const& sbs,
                                        bool skip_isolated) const
    {
        // Take the first outgoing rank corresponding to incoming region,
        // or take another region if it is not isolated
        turn_operation_type const& incoming_op
                = operation_from_rank(sbs.m_ranked_points.front());

        for (std::size_t i = 0; i < sbs.m_ranked_points.size(); i++)
        {
            typename sbs_type::rp const& rp = sbs.m_ranked_points[i];
            if (rp.rank == 0 || rp.direction == sort_by_side::dir_from)
            {
                continue;
            }
            turn_operation_type const& op = operation_from_rank(rp);

            if (op.operation != target_operation
                && op.operation != operation_continue)
            {
                continue;
            }

            if (op.enriched.region_id == incoming_op.enriched.region_id
                || (skip_isolated && ! op.enriched.isolated))
            {
                // Region corresponds to incoming region, or (for intersection)
                // there is a non-isolated other region which should be taken
                return rp.rank;
            }
        }
        return -1;
    }

    inline bool select_from_cluster_union(signed_size_type& turn_index,
        int& op_index, sbs_type const& sbs,
        signed_size_type start_turn_index, int start_op_index) const
    {
        sort_by_side::rank_type const selected_rank = select_rank(sbs, false);

        int best_code = 0;
        bool result = false;
        for (std::size_t i = 1; i < sbs.m_ranked_points.size(); i++)
        {
            typename sbs_type::rp const& ranked_point = sbs.m_ranked_points[i];

            if (ranked_point.rank > selected_rank)
            {
                // Sorted on rank, so it makes no sense to continue
                break;
            }

            int const code
                = select_turn_in_cluster_union(selected_rank, ranked_point,
                    start_turn_index, start_op_index);

            if (code > best_code)
            {
                // It is 1 or higher and matching better than previous
                best_code = code;
                turn_index = ranked_point.turn_index;
                op_index = ranked_point.operation_index;
                result = true;
            }
        }
        return result;
    }

    inline bool analyze_cluster_intersection(signed_size_type& turn_index,
                int& op_index, sbs_type const& sbs) const
    {
        sort_by_side::rank_type const selected_rank = select_rank(sbs, true);

        if (selected_rank > 0)
        {
            typename turn_operation_type::comparable_distance_type
                    min_remaining_distance = 0;

            std::size_t selected_index = sbs.m_ranked_points.size();
            for (std::size_t i = 0; i < sbs.m_ranked_points.size(); i++)
            {
                typename sbs_type::rp const& ranked_point = sbs.m_ranked_points[i];

                if (ranked_point.rank == selected_rank)
                {
                    turn_operation_type const& op = operation_from_rank(ranked_point);

                    if (op.visited.finalized())
                    {
                        // This direction is already traveled before, the same
                        // cannot be traveled again
                        continue;
                    }

                    // Take turn with the smallest remaining distance
                    if (selected_index == sbs.m_ranked_points.size()
                            || op.remaining_distance < min_remaining_distance)
                    {
                        selected_index = i;
                        min_remaining_distance = op.remaining_distance;
                    }
                }
            }

            if (selected_index < sbs.m_ranked_points.size())
            {
                typename sbs_type::rp const& ranked_point = sbs.m_ranked_points[selected_index];
                turn_index = ranked_point.turn_index;
                op_index = ranked_point.operation_index;
                return true;
            }
        }

        return false;
    }

    inline signed_size_type get_rank(sbs_type const& sbs,
            linked_turn_op_info const& info) const
    {
        for (std::size_t i = 0; i < sbs.m_ranked_points.size(); i++)
        {
            typename sbs_type::rp const& rp = sbs.m_ranked_points[i];
            if (rp.turn_index == info.turn_index
                    && rp.operation_index == info.op_index
                    && rp.direction == sort_by_side::dir_to)
            {
                return rp.rank;
            }
        }
        return -1;
    }

    // Function checks simple cases, such as a cluster with two turns,
    // arriving at the first turn, first turn points to second turn,
    // second turn points further.
    inline bool select_turn_from_cluster_linked(signed_size_type& turn_index,
            int& op_index,
            std::set<signed_size_type> const& ids,
            segment_identifier const& previous_seg_id) const
    {
        typedef typename std::set<signed_size_type>::const_iterator sit_type;

        std::vector<linked_turn_op_info> possibilities;
        std::vector<linked_turn_op_info> blocked;
        for (sit_type it = ids.begin(); it != ids.end(); ++it)
        {
            signed_size_type cluster_turn_index = *it;
            turn_type const& cluster_turn = m_turns[cluster_turn_index];
            if (cluster_turn.discarded)
            {
                continue;
            }
            if (cluster_turn.both(target_operation))
            {
                // Not (yet) supported, can be cluster of u/u turns
                return false;
            }
            for (int i = 0; i < 2; i++)
            {
                turn_operation_type const& op = cluster_turn.operations[i];
                turn_operation_type const& other_op = cluster_turn.operations[1 - i];
                signed_size_type const ni = op.enriched.get_next_turn_index();
                if (op.operation == target_operation
                    || op.operation == operation_continue)
                {
                    if (ni == cluster_turn_index)
                    {
                        // Not (yet) supported, traveling to itself, can be
                        // hole
                        return false;
                    }
                    possibilities.push_back(
                        linked_turn_op_info(cluster_turn_index, i, ni));
                }
                else if (op.operation == operation_blocked
                         && ! (ni == other_op.enriched.get_next_turn_index())
                         && ids.count(ni) == 0)
                {
                    // Points to turn, not part of this cluster,
                    // and that way is blocked. But if the other operation
                    // points at the same turn, it is still fine.
                    blocked.push_back(
                        linked_turn_op_info(cluster_turn_index, i, ni));
                }
            }
        }

        typedef typename std::vector<linked_turn_op_info>::const_iterator const_it_type;

        if (! blocked.empty())
        {
            sbs_type sbs(m_strategy);

            if (! fill_sbs(sbs, turn_index, ids, previous_seg_id))
            {
                return false;
            }

            for (typename std::vector<linked_turn_op_info>::iterator it = possibilities.begin();
                 it != possibilities.end(); ++it)
            {
                linked_turn_op_info& info = *it;
                info.rank_index = get_rank(sbs, info);
            }
            for (typename std::vector<linked_turn_op_info>::iterator it = blocked.begin();
                 it != blocked.end(); ++it)
            {
                linked_turn_op_info& info = *it;
                info.rank_index = get_rank(sbs, info);
            }


            for (const_it_type it = possibilities.begin();
                 it != possibilities.end(); ++it)
            {
                linked_turn_op_info const& lti = *it;
                for (const_it_type bit = blocked.begin();
                     bit != blocked.end(); ++bit)
                {
                    linked_turn_op_info const& blti = *bit;
                    if (blti.next_turn_index == lti.next_turn_index
                            && blti.rank_index == lti.rank_index)
                    {
                        return false;
                    }
                }
            }
        }

        // Traversal can either enter the cluster in the first turn,
        // or it can start halfway.
        // If there is one (and only one) possibility pointing outside
        // the cluster, take that one.
        linked_turn_op_info target;
        for (const_it_type it = possibilities.begin();
             it != possibilities.end(); ++it)
        {
            linked_turn_op_info const& lti = *it;
            if (ids.count(lti.next_turn_index) == 0)
            {
                if (target.turn_index >= 0
                    && target.next_turn_index != lti.next_turn_index)
                {
                    // Points to different target
                    return false;
                }
                if (BOOST_GEOMETRY_CONDITION(OverlayType == overlay_buffer)
                    && target.turn_index > 0)
                {
                    // Target already assigned, so there are more targets
                    // or more ways to the same target
                    return false;
                }

                target = lti;
            }
        }
        if (target.turn_index < 0)
        {
            return false;
        }

        turn_index = target.turn_index;
        op_index = target.op_index;

        return true;
    }

    inline bool fill_sbs(sbs_type& sbs,
                         signed_size_type turn_index,
                         std::set<signed_size_type> const& ids,
                         segment_identifier const& previous_seg_id) const
    {
        for (typename std::set<signed_size_type>::const_iterator sit = ids.begin();
             sit != ids.end(); ++sit)
        {
            signed_size_type cluster_turn_index = *sit;
            turn_type const& cluster_turn = m_turns[cluster_turn_index];
            bool const departure_turn = cluster_turn_index == turn_index;
            if (cluster_turn.discarded)
            {
                // Defensive check, discarded turns should not be in cluster
                continue;
            }

            for (int i = 0; i < 2; i++)
            {
                sbs.add(cluster_turn.operations[i],
                        cluster_turn_index, i, previous_seg_id,
                        m_geometry1, m_geometry2,
                        departure_turn);
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
        std::set<signed_size_type> const& ids = cinfo.turn_indices;

        if (select_turn_from_cluster_linked(turn_index, op_index, ids, previous_seg_id))
        {
            return true;
        }

        sbs_type sbs(m_strategy);

        if (! fill_sbs(sbs, turn_index, ids, previous_seg_id))
        {
            return false;
        }

        bool result = false;

        if (is_union)
        {
            result = select_from_cluster_union(turn_index, op_index, sbs,
                start_turn_index, start_op_index);
        }
        else
        {
            result = analyze_cluster_intersection(turn_index, op_index, sbs);
        }
        return result;
    }

    inline bool analyze_ii_intersection(signed_size_type& turn_index, int& op_index,
                    turn_type const& current_turn,
                    segment_identifier const& previous_seg_id)
    {
        sbs_type sbs(m_strategy);

        // Add this turn to the sort-by-side sorter
        for (int i = 0; i < 2; i++)
        {
            sbs.add(current_turn.operations[i],
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
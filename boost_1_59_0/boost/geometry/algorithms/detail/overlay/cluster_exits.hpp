// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2020 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CLUSTER_EXITS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CLUSTER_EXITS_HPP

#include <cstddef>
#include <set>
#include <vector>

#include <boost/range/value_type.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>
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

// Structure to check relatively simple cluster cases
template <overlay_type OverlayType,
          typename Turns,
          typename Sbs>
struct cluster_exits
{
private :
    static const operation_type target_operation = operation_from_overlay<OverlayType>::value;
    typedef typename boost::range_value<Turns>::type turn_type;
    typedef typename turn_type::turn_operation_type turn_operation_type;

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

    typedef typename std::vector<linked_turn_op_info>::const_iterator const_it_type;
    typedef typename std::vector<linked_turn_op_info>::iterator it_type;
    typedef typename std::set<signed_size_type>::const_iterator sit_type;

    inline signed_size_type get_rank(Sbs const& sbs,
            linked_turn_op_info const& info) const
    {
        for (std::size_t i = 0; i < sbs.m_ranked_points.size(); i++)
        {
            typename Sbs::rp const& rp = sbs.m_ranked_points[i];
            if (rp.turn_index == info.turn_index
                    && rp.operation_index == info.op_index
                    && rp.direction == sort_by_side::dir_to)
            {
                return rp.rank;
            }
        }
        return -1;
    }

    std::set<signed_size_type> const& m_ids;
    std::vector<linked_turn_op_info> possibilities;
    std::vector<linked_turn_op_info> blocked;

    bool m_valid;

    bool collect(Turns const& turns)
    {
        for (sit_type it = m_ids.begin(); it != m_ids.end(); ++it)
        {
            signed_size_type cluster_turn_index = *it;
            turn_type const& cluster_turn = turns[cluster_turn_index];
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
                         && m_ids.count(ni) == 0)
                {
                    // Points to turn, not part of this cluster,
                    // and that way is blocked. But if the other operation
                    // points at the same turn, it is still fine.
                    blocked.push_back(
                        linked_turn_op_info(cluster_turn_index, i, ni));
                }
            }
        }
        return true;
    }

    bool check_blocked(Sbs const& sbs)
    {
        if (blocked.empty())
        {
            return true;
        }

        for (it_type it = possibilities.begin(); it != possibilities.end(); ++it)
        {
            linked_turn_op_info& info = *it;
            info.rank_index = get_rank(sbs, info);
        }
        for (it_type it = blocked.begin(); it != blocked.end(); ++it)
        {
            linked_turn_op_info& info = *it;
            info.rank_index = get_rank(sbs, info);
        }

        for (const_it_type it = possibilities.begin(); it != possibilities.end(); ++it)
        {
            linked_turn_op_info const& lti = *it;
            for (const_it_type bit = blocked.begin(); bit != blocked.end(); ++bit)
            {
                linked_turn_op_info const& blti = *bit;
                if (blti.next_turn_index == lti.next_turn_index
                        && blti.rank_index == lti.rank_index)
                {
                    return false;
                }
            }
        }
        return true;
    }

public :
    cluster_exits(Turns const& turns,
                  std::set<signed_size_type> const& ids,
                  Sbs const& sbs)
        : m_ids(ids)
        , m_valid(collect(turns) && check_blocked(sbs))
    {
    }

    inline bool apply(signed_size_type& turn_index,
            int& op_index,
            bool first_run = true) const
    {
        if (! m_valid)
        {
            return false;
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
            if (m_ids.count(lti.next_turn_index) == 0)
            {
                if (target.turn_index >= 0
                    && target.next_turn_index != lti.next_turn_index)
                {
                    // Points to different target
                    return false;
                }
                if (first_run
                    && BOOST_GEOMETRY_CONDITION(OverlayType == overlay_buffer)
                    && target.turn_index >= 0)
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
};

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CLUSTER_EXITS_HPP

/* cluster_exits.hpp
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
*/
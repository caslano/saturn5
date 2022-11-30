// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_HANDLE_COLOCATIONS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_HANDLE_COLOCATIONS_HPP

#include <cstddef>
#include <algorithm>
#include <map>
#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/algorithms/detail/overlay/cluster_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/do_reverse.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_clusters.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_ring.hpp>
#include <boost/geometry/algorithms/detail/overlay/is_self_turn.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>
#include <boost/geometry/algorithms/detail/overlay/sort_by_side.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/segment_identifier.hpp>
#include <boost/geometry/util/condition.hpp>

#if defined(BOOST_GEOMETRY_DEBUG_HANDLE_COLOCATIONS)
#  include <iostream>
#  include <boost/geometry/algorithms/detail/overlay/debug_turn_info.hpp>
#  include <boost/geometry/io/wkt/wkt.hpp>
#  define BOOST_GEOMETRY_DEBUG_IDENTIFIER
#endif

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template <typename Turns, typename Clusters>
inline void remove_clusters(Turns& turns, Clusters& clusters)
{
    typename Clusters::iterator it = clusters.begin();
    while (it != clusters.end())
    {
        // Hold iterator and increase. We can erase cit, this keeps the
        // iterator valid (cf The standard associative-container erase idiom)
        typename Clusters::iterator current_it = it;
        ++it;

        std::set<signed_size_type> const& turn_indices
                = current_it->second.turn_indices;
        if (turn_indices.size() == 1)
        {
            signed_size_type const turn_index = *turn_indices.begin();
            turns[turn_index].cluster_id = -1;
            clusters.erase(current_it);
        }
    }
}

template <typename Turns, typename Clusters>
inline void cleanup_clusters(Turns& turns, Clusters& clusters)
{
    // Removes discarded turns from clusters
    for (typename Clusters::iterator mit = clusters.begin();
         mit != clusters.end(); ++mit)
    {
        cluster_info& cinfo = mit->second;
        std::set<signed_size_type>& ids = cinfo.turn_indices;
        for (std::set<signed_size_type>::iterator sit = ids.begin();
             sit != ids.end(); /* no increment */)
        {
            std::set<signed_size_type>::iterator current_it = sit;
            ++sit;

            signed_size_type const turn_index = *current_it;
            if (turns[turn_index].discarded)
            {
                ids.erase(current_it);
            }
        }
    }

    remove_clusters(turns, clusters);
}

template <typename Turn, typename IdSet>
inline void discard_colocated_turn(Turn& turn, IdSet& ids, signed_size_type id)
{
    turn.discarded = true;
    // Set cluster id to -1, but don't clear colocated flags
    turn.cluster_id = -1;
    // To remove it later from clusters
    ids.insert(id);
}

template <bool Reverse>
inline bool is_interior(segment_identifier const& seg_id)
{
    return Reverse ? seg_id.ring_index == -1 : seg_id.ring_index >= 0;
}

template <bool Reverse0, bool Reverse1>
inline bool is_ie_turn(segment_identifier const& ext_seg_0,
                       segment_identifier const& ext_seg_1,
                       segment_identifier const& int_seg_0,
                       segment_identifier const& other_seg_1)
{
    if (ext_seg_0.source_index == ext_seg_1.source_index)
    {
        // External turn is a self-turn, dont discard internal turn for this
        return false;
    }


    // Compares two segment identifiers from two turns (external / one internal)

    // From first turn [0], both are from same polygon (multi_index),
    // one is exterior (-1), the other is interior (>= 0),
    // and the second turn [1] handles the same ring

    // For difference, where the rings are processed in reversal, all interior
    // rings become exterior and vice versa. But also the multi property changes:
    // rings originally from the same multi should now be considered as from
    // different multi polygons.
    // But this is not always the case, and at this point hard to figure out
    // (not yet implemented, TODO)

    bool const same_multi0 = ! Reverse0
                             && ext_seg_0.multi_index == int_seg_0.multi_index;

    bool const same_multi1 = ! Reverse1
                             && ext_seg_1.multi_index == other_seg_1.multi_index;

    boost::ignore_unused(same_multi1);

    return same_multi0
            && same_multi1
            && ! is_interior<Reverse0>(ext_seg_0)
            && is_interior<Reverse0>(int_seg_0)
            && ext_seg_1.ring_index == other_seg_1.ring_index;

    // The other way round is tested in another call
}

template
<
    bool Reverse0, bool Reverse1, // Reverse interpretation interior/exterior
    typename Turns,
    typename Clusters
>
inline void discard_interior_exterior_turns(Turns& turns, Clusters& clusters)
{
    typedef std::set<signed_size_type>::const_iterator set_iterator;
    typedef typename boost::range_value<Turns>::type turn_type;

    std::set<signed_size_type> ids_to_remove;

    for (typename Clusters::iterator cit = clusters.begin();
         cit != clusters.end(); ++cit)
    {
        cluster_info& cinfo = cit->second;
        std::set<signed_size_type>& ids = cinfo.turn_indices;

        ids_to_remove.clear();

        for (set_iterator it = ids.begin(); it != ids.end(); ++it)
        {
            turn_type& turn = turns[*it];
            segment_identifier const& seg_0 = turn.operations[0].seg_id;
            segment_identifier const& seg_1 = turn.operations[1].seg_id;

            if (! (turn.both(operation_union)
                   || turn.combination(operation_union, operation_blocked)))
            {
                // Not a uu/ux, so cannot be colocated with a iu turn
                continue;
            }

            for (set_iterator int_it = ids.begin(); int_it != ids.end(); ++int_it)
            {
                if (*it == *int_it)
                {
                    continue;
                }

                // Turn with, possibly, an interior ring involved
                turn_type& int_turn = turns[*int_it];
                segment_identifier const& int_seg_0 = int_turn.operations[0].seg_id;
                segment_identifier const& int_seg_1 = int_turn.operations[1].seg_id;

                if (is_ie_turn<Reverse0, Reverse1>(seg_0, seg_1, int_seg_0, int_seg_1))
                {
                    discard_colocated_turn(int_turn, ids_to_remove, *int_it);
                }
                if (is_ie_turn<Reverse1, Reverse0>(seg_1, seg_0, int_seg_1, int_seg_0))
                {
                    discard_colocated_turn(int_turn, ids_to_remove, *int_it);
                }
            }
        }

        // Erase from the ids (which cannot be done above)
        for (set_iterator sit = ids_to_remove.begin();
             sit != ids_to_remove.end(); ++sit)
        {
            ids.erase(*sit);
        }
    }
}

template
<
    overlay_type OverlayType,
    typename Turns,
    typename Clusters
>
inline void set_colocation(Turns& turns, Clusters const& clusters)
{
    typedef std::set<signed_size_type>::const_iterator set_iterator;
    typedef typename boost::range_value<Turns>::type turn_type;

    for (typename Clusters::const_iterator cit = clusters.begin();
         cit != clusters.end(); ++cit)
    {
        cluster_info const& cinfo = cit->second;
        std::set<signed_size_type> const& ids = cinfo.turn_indices;

        bool both_target = false;
        for (set_iterator it = ids.begin(); it != ids.end(); ++it)
        {
            turn_type const& turn = turns[*it];
            if (turn.both(operation_from_overlay<OverlayType>::value))
            {
                both_target = true;
                break;
            }
        }

        if (both_target)
        {
            for (set_iterator it = ids.begin(); it != ids.end(); ++it)
            {
                turn_type& turn = turns[*it];
                turn.has_colocated_both = true;
            }
        }
    }
}

template
<
    typename Turns,
    typename Clusters
>
inline void check_colocation(bool& has_blocked,
        signed_size_type cluster_id, Turns const& turns, Clusters const& clusters)
{
    typedef typename boost::range_value<Turns>::type turn_type;

    has_blocked = false;

    typename Clusters::const_iterator mit = clusters.find(cluster_id);
    if (mit == clusters.end())
    {
        return;
    }

    cluster_info const& cinfo = mit->second;

    for (std::set<signed_size_type>::const_iterator it
         = cinfo.turn_indices.begin();
         it != cinfo.turn_indices.end(); ++it)
    {
        turn_type const& turn = turns[*it];
        if (turn.any_blocked())
        {
            has_blocked = true;
        }
    }
}

template
<
    typename Turns,
    typename Clusters
>
inline void assign_cluster_ids(Turns& turns, Clusters const& clusters)
{
    for (auto& turn : turns)
    {
        turn.cluster_id = -1;
    }
    for (auto const& kv : clusters)
    {
        for (const auto& index : kv.second.turn_indices)
        {
            turns[index].cluster_id = kv.first;
        }
    }
}

// Checks colocated turns and flags combinations of uu/other, possibly a
// combination of a ring touching another geometry's interior ring which is
// tangential to the exterior ring

// This function can be extended to replace handle_tangencies: at each
// colocation incoming and outgoing vectors should be inspected

template
<
    bool Reverse1, bool Reverse2,
    overlay_type OverlayType,
    typename Geometry0,
    typename Geometry1,
    typename Turns,
    typename Clusters,
    typename RobustPolicy
>
inline bool handle_colocations(Turns& turns, Clusters& clusters,
                               RobustPolicy const& robust_policy)
{
    static const detail::overlay::operation_type target_operation
            = detail::overlay::operation_from_overlay<OverlayType>::value;

    get_clusters(turns, clusters, robust_policy);

    if (clusters.empty())
    {
        return false;
    }

    assign_cluster_ids(turns, clusters);

    // Get colocated information here, and not later, to keep information
    // on turns which are discarded afterwards
    set_colocation<OverlayType>(turns, clusters);

    if (BOOST_GEOMETRY_CONDITION(target_operation == operation_intersection))
    {
        discard_interior_exterior_turns
            <
                do_reverse<geometry::point_order<Geometry0>::value>::value != Reverse1,
                do_reverse<geometry::point_order<Geometry1>::value>::value != Reverse2
            >(turns, clusters);
    }

    // There might be clusters having only one turn, if the rest is discarded
    // This is cleaned up later, after gathering the properties.

#if defined(BOOST_GEOMETRY_DEBUG_HANDLE_COLOCATIONS)
    std::cout << "*** Colocations " << map.size() << std::endl;
    for (auto const& kv : map)
    {
        std::cout << kv.first << std::endl;
        for (auto const& toi : kv.second)
        {
            detail::debug::debug_print_turn(turns[toi.turn_index]);
            std::cout << std::endl;
        }
    }
#endif

    return true;
}


struct is_turn_index
{
    is_turn_index(signed_size_type index)
        : m_index(index)
    {}

    template <typename Indexed>
    inline bool operator()(Indexed const& indexed) const
    {
        // Indexed is a indexed_turn_operation<Operation>
        return indexed.turn_index == m_index;
    }

    signed_size_type m_index;
};

template
<
    typename Sbs,
    typename Point,
    typename Turns,
    typename Geometry1,
    typename Geometry2
>
inline bool fill_sbs(Sbs& sbs, Point& turn_point,
                     cluster_info const& cinfo,
                     Turns const& turns,
                     Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    typedef typename boost::range_value<Turns>::type turn_type;

    std::set<signed_size_type> const& ids = cinfo.turn_indices;

    if (ids.empty())
    {
        return false;
    }

    bool first = true;
    for (std::set<signed_size_type>::const_iterator sit = ids.begin();
         sit != ids.end(); ++sit)
    {
        signed_size_type turn_index = *sit;
        turn_type const& turn = turns[turn_index];
        if (first)
        {
            turn_point = turn.point;
        }
        for (int i = 0; i < 2; i++)
        {
            sbs.add(turn, turn.operations[i], turn_index, i, geometry1, geometry2, first);
            first = false;
        }
    }
    return true;
}

template
<
    bool Reverse1, bool Reverse2,
    overlay_type OverlayType,
    typename Turns,
    typename Clusters,
    typename Geometry1,
    typename Geometry2,
    typename SideStrategy
>
inline void gather_cluster_properties(Clusters& clusters, Turns& turns,
        operation_type for_operation,
        Geometry1 const& geometry1, Geometry2 const& geometry2,
        SideStrategy const& strategy)
{
    typedef typename boost::range_value<Turns>::type turn_type;
    typedef typename turn_type::point_type point_type;
    typedef typename turn_type::turn_operation_type turn_operation_type;

    // Define sorter, sorting counter-clockwise such that polygons are on the
    // right side
    typedef sort_by_side::side_sorter
        <
            Reverse1, Reverse2, OverlayType, point_type, SideStrategy, std::less<int>
        > sbs_type;

    for (typename Clusters::iterator mit = clusters.begin();
         mit != clusters.end(); ++mit)
    {
        cluster_info& cinfo = mit->second;

        sbs_type sbs(strategy);
        point_type turn_point; // should be all the same for all turns in cluster
        if (! fill_sbs(sbs, turn_point, cinfo, turns, geometry1, geometry2))
        {
            continue;
        }

        sbs.apply(turn_point);

        sbs.find_open();
        sbs.assign_zones(for_operation);

        cinfo.open_count = sbs.open_count(for_operation);

        bool const set_startable = OverlayType != overlay_dissolve;

        // Unset the startable flag for all 'closed' zones. This does not
        // apply for self-turns, because those counts are not from both
        // polygons
        for (std::size_t i = 0; i < sbs.m_ranked_points.size(); i++)
        {
            typename sbs_type::rp const& ranked = sbs.m_ranked_points[i];
            turn_type& turn = turns[ranked.turn_index];
            turn_operation_type& op = turn.operations[ranked.operation_index];

            if (set_startable
                    && for_operation == operation_union && cinfo.open_count == 0)
            {
                op.enriched.startable = false;
            }

            if (ranked.direction != sort_by_side::dir_to)
            {
                continue;
            }

            op.enriched.count_left = ranked.count_left;
            op.enriched.count_right = ranked.count_right;
            op.enriched.rank = ranked.rank;
            op.enriched.zone = ranked.zone;

            if (! set_startable)
            {
                continue;
            }

            if (BOOST_GEOMETRY_CONDITION(OverlayType != overlay_difference)
                    && is_self_turn<OverlayType>(turn))
            {
                // Difference needs the self-turns, TODO: investigate
                continue;
            }

            if ((for_operation == operation_union
                    && ranked.count_left != 0)
             || (for_operation == operation_intersection
                    && ranked.count_right != 2))
            {
                op.enriched.startable = false;
            }
        }

    }
}


}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_HANDLE_COLOCATIONS_HPP

/* handle_colocations.hpp
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
*/
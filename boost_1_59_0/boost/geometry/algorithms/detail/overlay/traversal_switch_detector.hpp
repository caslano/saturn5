// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2016 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018-2020.
// Modifications copyright (c) 2018-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_SWITCH_DETECTOR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_SWITCH_DETECTOR_HPP

#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/detail/ring_identifier.hpp>
#include <boost/geometry/algorithms/detail/overlay/copy_segments.hpp>
#include <boost/geometry/algorithms/detail/overlay/cluster_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/is_self_turn.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/util/condition.hpp>

#include <cstddef>
#include <map>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

// The switch detector, the first phase in traversal, inspects UU and II turns.
// Suppose you have these two polygons in a union. There is one UU turn.
// +-------+
// |       |
// |   A   |
// |       |
// +-------U---------+       U = UU turn
//         |         |
//         |    B    |
//         |         |
//         +---------+
// It first assigns region ids, A gets id 1 and B gets id 2.
// Because of that, it should NOT switch sources in traversal at U.
// So coming from upper left, it follows A, and also at U it keeps following A.
// The result is two rings. (See for example testcase "case_31" or others.)
//
// But suppose you have two larger input polygons, partially overlapping:
// +-----------------+
// |                 |
// |   A   +-----T---C       I = interior in output
// |       |  I  | O |       O = overlap A & B (included in output)
// +-------U-----T---C       U = UU turn
//         |         |       T = normal turn (u/i)
//         |    B    |       C = collinear turn (c/c)
//         |         |
//         +---------+
// Rings A and B will be connected (by inspecting turn information)
// and there will be one region 1.
// Because of that, it will switch sources in traversal at U.
// So coming from lower right, it follows B but at U it will switch to A.
// Also for the generated interior ring, coming from the top via A it will at U
// switch to B and go to the right, generating I. (See for example "case_91")
// Switching using region_id is only relevant for UU or II turns.
// In all T turns it will follow "u" for union or "i" for intersection,
// and in C turns it will follow either direction (they are the same).
// There is also "isolated", making it more complex, and documented below.
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
    typename Visitor
>
struct traversal_switch_detector
{
    static const operation_type target_operation
            = operation_from_overlay<OverlayType>::value;

    enum isolation_type
    {
        isolation_no = 0,
        isolation_yes = 1,
        isolation_multiple = 2
    };

    using turn_type = typename boost::range_value<Turns>::type;
    using set_type= std::set<signed_size_type>;

    // Per ring, first turns are collected (in turn_indices), and later
    // a region_id is assigned
    struct merged_ring_properties
    {
        signed_size_type region_id = -1;
        set_type turn_indices;
    };

    struct connection_properties
    {
        std::size_t count = 0;
        // Set with turn-index OR (if clustered) the negative cluster_id
        set_type unique_turn_ids;
    };

    // Maps region_id -> properties
    using connection_map = std::map<signed_size_type, connection_properties>;

    // Per region, a set of properties is maintained, including its connections
    // to other regions
    struct region_properties
    {
        signed_size_type region_id = -1;
        isolation_type isolated = isolation_no;
        set_type unique_turn_ids;
        connection_map connected_region_counts;
    };

    // Maps ring -> properties
    using merge_map = std::map<ring_identifier, merged_ring_properties>;

    // Maps region_id -> properties
    using region_connection_map = std::map<signed_size_type, region_properties>;

    inline traversal_switch_detector(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            Turns& turns, Clusters const& clusters,
            RobustPolicy const& robust_policy, Visitor& visitor)
        : m_geometry1(geometry1)
        , m_geometry2(geometry2)
        , m_turns(turns)
        , m_clusters(clusters)
        , m_robust_policy(robust_policy)
        , m_visitor(visitor)
    {
    }

    bool one_connection_to_another_region(region_properties const& region) const
    {
        // For example:
        // +----------------------+
        // |                   __ |
        // |                  /  \|
        // |                 |    x
        // |                  \__/|
        // |                      |
        // +----------------------+

        if (region.connected_region_counts.size() == 1)
        {
            auto const& cprop = region.connected_region_counts.begin()->second;
            return cprop.count <= 1;
        }
        return region.connected_region_counts.empty();
    }

    // TODO: might be combined with previous
    bool multiple_connections_to_one_region(region_properties const& region) const
    {
        // For example:
        // +----------------------+
        // |                   __ |
        // |                  /  \|
        // |                 |    x
        // |                  \  /|
        // |                  /  \|
        // |                 |    x
        // |                  \__/|
        // |                      |
        // +----------------------+

        if (region.connected_region_counts.size() == 1)
        {
            auto const& cprop = region.connected_region_counts.begin()->second;
            return cprop.count > 1;
        }
        return false;
    }

    bool one_connection_to_multiple_regions(region_properties const& region) const
    {
        // For example:
        // +----------------------+
        // |                   __ | __
        // |                  /  \|/  |
        // |                 |    x   |
        // |                  \__/|\__|
        // |                      |
        // +----------------------+

        bool first = true;
        signed_size_type first_turn_id = 0;
        for (auto const& key_val : region.connected_region_counts)
        {
            auto const& cprop = key_val.second;

            if (cprop.count != 1)
            {
                return false;
            }
            auto const unique_turn_id = *cprop.unique_turn_ids.begin();
            if (first)
            {
                first_turn_id = unique_turn_id;
                first = false;
            }
            else if (first_turn_id != unique_turn_id)
            {
                return false;
            }
        }
        return true;
    }

    bool ii_turn_connects_two_regions(region_properties const& region,
            region_properties const& connected_region,
            signed_size_type turn_index) const
    {
        turn_type const& turn = m_turns[turn_index];
        if (! turn.both(operation_intersection))
        {
            return false;
        }

        signed_size_type const id0 = turn.operations[0].enriched.region_id;
        signed_size_type const id1 = turn.operations[1].enriched.region_id;

        return (id0 == region.region_id && id1 == connected_region.region_id)
            || (id1 == region.region_id && id0 == connected_region.region_id);
    }


    bool isolated_multiple_connection(region_properties const& region,
            region_properties const& connected_region) const
    {
        if (connected_region.isolated != isolation_multiple)
        {
            return false;
        }

        // First step: compare turns of regions with turns of connected region
        set_type turn_ids = region.unique_turn_ids;
        for (auto turn_id : connected_region.unique_turn_ids)
        {
            turn_ids.erase(turn_id);
        }

        // There should be one connection (turn or cluster) left
        if (turn_ids.size() != 1)
        {
            return false;
        }

        for (auto id_or_index : connected_region.unique_turn_ids)
        {
            if (id_or_index >= 0)
            {
                if (! ii_turn_connects_two_regions(region, connected_region, id_or_index))
                {
                    return false;
                }
            }
            else
            {
                signed_size_type const cluster_id = -id_or_index;
                auto it = m_clusters.find(cluster_id);
                if (it != m_clusters.end())
                {
                    cluster_info const& cinfo = it->second;
                    for (auto turn_index : cinfo.turn_indices)
                    {
                        if (! ii_turn_connects_two_regions(region, connected_region, turn_index))
                        {
                            return false;
                        }
                    }
                }
            }
        }

        return true;
    }

    bool has_only_isolated_children(region_properties const& region) const
    {
        bool first_with_turn = true;
        signed_size_type first_turn_id = 0;

        for (auto const& key_val : region.connected_region_counts)
        {
            signed_size_type const region_id = key_val.first;
            connection_properties const& cprop = key_val.second;

            auto mit = m_connected_regions.find(region_id);
            if (mit == m_connected_regions.end())
            {
                // Should not occur
                return false;
            }

            region_properties const& connected_region = mit->second;

            if (cprop.count != 1)
            {
                // If there are more connections, check their isolation
                if (! isolated_multiple_connection(region, connected_region))
                {
                    return false;
                }
            }

            if (connected_region.isolated != isolation_yes
                && connected_region.isolated != isolation_multiple)
            {
                signed_size_type const unique_turn_id = *cprop.unique_turn_ids.begin();
                if (first_with_turn)
                {
                    first_turn_id = unique_turn_id;
                    first_with_turn = false;
                }
                else if (first_turn_id != unique_turn_id)
                {
                    return false;
                }
            }
        }

        // If there is only one connection (with a 'parent'), and all other
        // connections are itself isolated, it is isolated
        return true;
    }

    void get_isolated_regions()
    {
        // First time: check regions isolated (one connection only),
        // semi-isolated (multiple connections between same region),
        // and complex isolated (connection with multiple rings but all
        // at same point)
        for (auto& key_val : m_connected_regions)
        {
            region_properties& properties = key_val.second;
            if (one_connection_to_another_region(properties))
            {
                properties.isolated = isolation_yes;
            }
            else if (multiple_connections_to_one_region(properties))
            {
                properties.isolated = isolation_multiple;
            }
            else if (one_connection_to_multiple_regions(properties))
            {
                properties.isolated = isolation_yes;
            }
        }

        // Propagate isolation to next level
        // TODO: should be optimized
        std::size_t defensive_check = 0;
        bool changed = true;
        while (changed && defensive_check++ < m_connected_regions.size())
        {
            changed = false;
            for (auto& key_val : m_connected_regions)
            {
                region_properties& properties = key_val.second;

                if (properties.isolated == isolation_no
                        && has_only_isolated_children(properties))
                {
                    properties.isolated = isolation_yes;
                    changed = true;
                }
            }
        }
    }

    void assign_isolation_to_enriched()
    {
        for (turn_type& turn : m_turns)
        {
            // For difference, for the input walked through in reverse,
            // the meaning is reversed: what is isolated is actually not,
            // and vice versa.
            bool const reverseMeaningInTurn
                    = (Reverse1 || Reverse2)
                      && ! turn.is_self()
                      && ! turn.is_clustered()
                      && uu_or_ii(turn)
                      && turn.operations[0].enriched.region_id
                         != turn.operations[1].enriched.region_id;

            for (auto& op : turn.operations)
            {
                auto mit = m_connected_regions.find(op.enriched.region_id);
                if (mit != m_connected_regions.end())
                {
                    bool const reverseMeaningInOp
                        = reverseMeaningInTurn
                          && ((op.seg_id.source_index == 0 && Reverse1)
                               || (op.seg_id.source_index == 1 && Reverse2));

                    // It is assigned to isolated if it's property is "Yes",
                    // (one connected interior, or chained).
                    // "Multiple" doesn't count for isolation,
                    // neither for intersection, neither for difference.
                    region_properties const& prop = mit->second;
                    op.enriched.isolated
                            = reverseMeaningInOp
                            ? false
                            : prop.isolated == isolation_yes;
                }
            }
        }
    }

    void assign_region_ids_to_enriched()
    {
        for (auto const& key_val : m_turns_per_ring)
        {
            ring_identifier const& ring_id = key_val.first;
            merged_ring_properties const& properties = key_val.second;

            for (auto turn_index : properties.turn_indices)
            {
                turn_type& turn = m_turns[turn_index];

                if (! acceptable(turn))
                {
                    // No assignment necessary
                    continue;
                }

                for (auto& op : turn.operations)
                {
                    if (ring_id_by_seg_id(op.seg_id) == ring_id)
                    {
                        op.enriched.region_id = properties.region_id;
                    }
                }
            }
        }
    }

    void assign_connected_regions()
    {
        for (std::size_t turn_index = 0; turn_index < m_turns.size(); ++turn_index)
        {
            turn_type const& turn = m_turns[turn_index];

            signed_size_type const unique_turn_id
                    = turn.is_clustered() ? -turn.cluster_id : turn_index;

            signed_size_type const& id0 = turn.operations[0].enriched.region_id;
            signed_size_type const& id1 = turn.operations[1].enriched.region_id;

            // Add region (by assigning) and add involved turns
            if (id0 != -1)
            {
                m_connected_regions[id0].region_id = id0;
                m_connected_regions[id0].unique_turn_ids.insert(unique_turn_id);
            }
            if (id1 != -1 && id0 != id1)
            {
                m_connected_regions[id1].region_id = id1;
                m_connected_regions[id1].unique_turn_ids.insert(unique_turn_id);
            }

            if (id0 != id1 && id0 != -1 && id1 != -1)
            {
                // Assign connections
                connection_properties& prop0 = m_connected_regions[id0].connected_region_counts[id1];
                connection_properties& prop1 = m_connected_regions[id1].connected_region_counts[id0];

                // Reference this turn or cluster to later check uniqueness on ring
                if (prop0.unique_turn_ids.count(unique_turn_id) == 0)
                {
                    prop0.count++;
                    prop0.unique_turn_ids.insert(unique_turn_id);
                }
                if (prop1.unique_turn_ids.count(unique_turn_id) == 0)
                {
                    prop1.count++;
                    prop1.unique_turn_ids.insert(unique_turn_id);
                }
            }
        }
    }

    inline bool acceptable(turn_type const& turn) const
    {
        // Discarded turns don't connect rings to the same region
        // Also xx are not relevant
        // (otherwise discarded colocated uu turn could make a connection)
        return ! turn.discarded && ! turn.both(operation_blocked);
    }

    inline bool uu_or_ii(turn_type const& turn) const
    {
        return turn.both(operation_union) || turn.both(operation_intersection);
    }

    inline bool connects_same_region(turn_type const& turn) const
    {
        if (! acceptable(turn))
        {
            return false;
        }

        if (! turn.is_clustered())
        {
            // If it is a uu/ii-turn (non clustered), it is never same region
            return ! uu_or_ii(turn);
        }

        if (BOOST_GEOMETRY_CONDITION(target_operation == operation_union))
        {
            // It is a cluster, check zones
            // (assigned by sort_by_side/handle colocations) of both operations
            return turn.operations[0].enriched.zone
                    == turn.operations[1].enriched.zone;
        }

        // For an intersection, two regions connect if they are not ii
        // (ii-regions are isolated) or, in some cases, not iu (for example
        // when a multi-polygon is inside an interior ring and connecting it)
        return ! (turn.both(operation_intersection)
                  || turn.combination(operation_intersection, operation_union));
    }

    void create_region(signed_size_type& new_region_id, ring_identifier const& ring_id,
                merged_ring_properties& properties, signed_size_type region_id = -1)
    {
        if (properties.region_id > 0)
        {
            // Already handled
            return;
        }

        // Assign new id if this is a new region
        if (region_id == -1)
        {
            region_id = new_region_id++;
        }

        // Assign this ring to specified region
        properties.region_id = region_id;

#if defined(BOOST_GEOMETRY_DEBUG_TRAVERSAL_SWITCH_DETECTOR)
        std::cout << " ADD " << ring_id << " TO REGION " << region_id << std::endl;
#endif

        // Find connecting rings, recursively
        for (auto turn_index : properties.turn_indices)
        {
            turn_type const& turn = m_turns[turn_index];
            if (! connects_same_region(turn))
            {
                // This is a non clustered uu/ii-turn, or a cluster connecting different 'zones'
                continue;
            }

            // Union: This turn connects two rings (interior connected), create the region
            // Intersection: This turn connects two rings, set same regions for these two rings
            for (auto const& op : turn.operations)
            {
                ring_identifier connected_ring_id = ring_id_by_seg_id(op.seg_id);
                if (connected_ring_id != ring_id)
                {
                    propagate_region(new_region_id, connected_ring_id, region_id);
                }
            }
        }
    }

    void propagate_region(signed_size_type& new_region_id,
            ring_identifier const& ring_id, signed_size_type region_id)
    {
        auto it = m_turns_per_ring.find(ring_id);
        if (it != m_turns_per_ring.end())
        {
            create_region(new_region_id, ring_id, it->second, region_id);
        }
    }

#if defined(BOOST_GEOMETRY_DEBUG_TRAVERSAL_SWITCH_DETECTOR)
    void debug_show_results()
    {
        auto isolation_to_string = [](isolation_type const& iso) -> std::string
        {
            switch(iso)
            {
                case isolation_no : return "no";
                case isolation_yes : return "yes";
                case isolation_multiple : return "multiple";
            }
            return "error";
        };
        auto set_to_string = [](auto const& s) -> std::string
        {
            std::ostringstream result;
            for (auto item : s) { result << " " << item; }
            return result.str();
        };

        for (auto const& kv : m_connected_regions)
        {
            auto const& prop = kv.second;

            std::ostringstream sub;
            sub << "[turns" << set_to_string(prop.unique_turn_ids)
                << "] regions";
            for (auto const& kvs : prop.connected_region_counts)
            {
                sub << " { " << kvs.first
                    << " : via [" << set_to_string(kvs.second.unique_turn_ids)
                    << " ] }";
            }

            std::cout << "REGION " << prop.region_id
                      << " " << isolation_to_string(prop.isolated)
                      << " " << sub.str()
                      << std::endl;
        }

        for (std::size_t turn_index = 0; turn_index < m_turns.size(); ++turn_index)
        {
            turn_type const& turn = m_turns[turn_index];

            if (uu_or_ii(turn) && ! turn.is_clustered())
            {
                std::cout << (turn.both(operation_union) ? "UU" : "II")
                          << " " << turn_index
                          << " (" << geometry::get<0>(turn.point)
                          << ", " << geometry::get<1>(turn.point) << ")"
                          << " -> " << std::boolalpha
                          << " [" << turn.operations[0].seg_id.source_index
                          << "/" << turn.operations[1].seg_id.source_index << "] "
                          << "(" << turn.operations[0].enriched.region_id
                          << " " << turn.operations[0].enriched.isolated
                          << ") / (" << turn.operations[1].enriched.region_id
                          << " " << turn.operations[1].enriched.isolated << ")"
                          << std::endl;
            }
        }

        for (auto const& key_val : m_clusters)
        {
            cluster_info const& cinfo = key_val.second;
            std::cout << "CL RESULT " << key_val.first
                         << " -> " << cinfo.open_count << std::endl;
        }
    }
#endif

    void iterate()
    {
#if defined(BOOST_GEOMETRY_DEBUG_TRAVERSAL_SWITCH_DETECTOR)
        std::cout << "BEGIN SWITCH DETECTOR (region_ids and isolation)"
                  << (Reverse1 ? " REVERSE_1" : "")
                  << (Reverse2 ? " REVERSE_2" : "")
                  << std::endl;
#endif

        // Collect turns per ring
        m_turns_per_ring.clear();
        m_connected_regions.clear();

        for (std::size_t turn_index = 0; turn_index < m_turns.size(); ++turn_index)
        {
            turn_type const& turn = m_turns[turn_index];

            if (turn.discarded
                && BOOST_GEOMETRY_CONDITION(target_operation == operation_intersection))
            {
                // Discarded turn (union currently still needs it to determine regions)
                continue;
            }

            for (auto const& op : turn.operations)
            {
                m_turns_per_ring[ring_id_by_seg_id(op.seg_id)].turn_indices.insert(turn_index);
            }
        }

        // All rings having turns are in turns/ring map. Process them.
        {
            signed_size_type new_region_id = 1;
            for (auto& key_val : m_turns_per_ring)
            {
                create_region(new_region_id, key_val.first, key_val.second);
            }

            assign_region_ids_to_enriched();
            assign_connected_regions();
            get_isolated_regions();
            assign_isolation_to_enriched();
        }

#if defined(BOOST_GEOMETRY_DEBUG_TRAVERSAL_SWITCH_DETECTOR)
        std::cout << "END SWITCH DETECTOR" << std::endl;
        debug_show_results();
#endif

    }

private:

    Geometry1 const& m_geometry1;
    Geometry2 const& m_geometry2;
    Turns& m_turns;
    Clusters const& m_clusters;
    merge_map m_turns_per_ring;
    region_connection_map m_connected_regions;
    RobustPolicy const& m_robust_policy;
    Visitor& m_visitor;
};

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_SWITCH_DETECTOR_HPP

/* traversal_switch_detector.hpp
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
*/
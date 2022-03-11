// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2016 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_SWITCH_DETECTOR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_SWITCH_DETECTOR_HPP

#include <cstddef>
#include <map>

#include <boost/range.hpp>

#include <boost/geometry/algorithms/detail/ring_identifier.hpp>
#include <boost/geometry/algorithms/detail/overlay/copy_segments.hpp>
#include <boost/geometry/algorithms/detail/overlay/cluster_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/is_self_turn.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/util/condition.hpp>

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
    typename Clusters,
    typename RobustPolicy,
    typename Visitor
>
struct traversal_switch_detector
{
    static const operation_type target_operation
            = operation_from_overlay<OverlayType>::value;
    static const operation_type opposite_operation
            = target_operation == operation_union
            ? operation_intersection
            : operation_union;

    enum isolation_type
    {
        isolation_unknown = -1,
        isolation_no = 0,
        isolation_yes = 1,
        isolation_multiple = 2
    };

    typedef typename boost::range_value<Turns>::type turn_type;
    typedef typename turn_type::turn_operation_type turn_operation_type;
    typedef std::set<signed_size_type> set_type;

    // Per ring, first turns are collected (in turn_indices), and later
    // a region_id is assigned
    struct merged_ring_properties
    {
        signed_size_type region_id;
        set_type turn_indices;

        merged_ring_properties()
            : region_id(-1)
        {}
    };

    struct connection_properties
    {
        std::size_t count;
        // Contains turn-index OR, if clustered, minus-cluster_id
        set_type unique_turn_ids;
        connection_properties()
            : count(0)
        {}
    };

    typedef std::map<signed_size_type, connection_properties> connection_map;

    // Per region, a set of properties is maintained, including its connections
    // to other regions
    struct region_properties
    {
        signed_size_type region_id;
        isolation_type isolated;
        set_type unique_turn_ids;

        // Maps from connected region_id to their properties
        connection_map connected_region_counts;

        region_properties()
            : region_id(-1)
            , isolated(isolation_unknown)
        {}
    };

    // Keeps turn indices per ring
    typedef std::map<ring_identifier, merged_ring_properties > merge_map;
    typedef std::map<signed_size_type, region_properties> region_connection_map;

    typedef set_type::const_iterator set_iterator;

    inline traversal_switch_detector(Geometry1 const& geometry1, Geometry2 const& geometry2,
            Turns& turns, Clusters& clusters,
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
            connection_properties const& cprop = region.connected_region_counts.begin()->second;
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
            connection_properties const& cprop = region.connected_region_counts.begin()->second;
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
        for (typename connection_map::const_iterator it = region.connected_region_counts.begin();
             it != region.connected_region_counts.end(); ++it)
        {
            connection_properties const& cprop = it->second;

            if (cprop.count != 1)
            {
                return false;
            }
            signed_size_type const unique_turn_id = *cprop.unique_turn_ids.begin();
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
        for (set_iterator sit = connected_region.unique_turn_ids.begin();
             sit != connected_region.unique_turn_ids.end(); ++sit)
        {
            turn_ids.erase(*sit);
        }

        // There should be one connection (turn or cluster) left
        if (turn_ids.size() != 1)
        {
            return false;
        }

        for (set_iterator sit = connected_region.unique_turn_ids.begin();
             sit != connected_region.unique_turn_ids.end(); ++sit)
        {
            signed_size_type const id_or_index = *sit;
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
                typename Clusters::const_iterator it = m_clusters.find(cluster_id);
                if (it != m_clusters.end())
                {
                    cluster_info const& cinfo = it->second;
                    for (set_iterator cit = cinfo.turn_indices.begin();
                         cit != cinfo.turn_indices.end(); ++cit)
                    {
                        if (! ii_turn_connects_two_regions(region, connected_region, *cit))
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

        for (typename connection_map::const_iterator it = region.connected_region_counts.begin();
             it != region.connected_region_counts.end(); ++it)
        {
            signed_size_type const region_id = it->first;
            connection_properties const& cprop = it->second;

            typename region_connection_map::const_iterator mit = m_connected_regions.find(region_id);
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
        typedef typename region_connection_map::iterator it_type;

        // First time: check regions isolated (one connection only),
        // semi-isolated (multiple connections between same region),
        // and complex isolated (connection with multiple rings but all
        // at same point)
        for (it_type it = m_connected_regions.begin();
             it != m_connected_regions.end(); ++it)
        {
            region_properties& properties = it->second;
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
            for (it_type it = m_connected_regions.begin();
                 it != m_connected_regions.end(); ++it)
            {
                region_properties& properties = it->second;

                if (properties.isolated == isolation_unknown
                        && has_only_isolated_children(properties))
                {
                    properties.isolated = isolation_yes;
                    changed = true;
                }
            }
        }
    }

    void assign_isolation()
    {
        for (std::size_t turn_index = 0; turn_index < m_turns.size(); ++turn_index)
        {
            turn_type& turn = m_turns[turn_index];

            for (int op_index = 0; op_index < 2; op_index++)
            {
                turn_operation_type& op = turn.operations[op_index];
                typename region_connection_map::const_iterator mit = m_connected_regions.find(op.enriched.region_id);
                if (mit != m_connected_regions.end())
                {
                    region_properties const& prop = mit->second;
                    op.enriched.isolated = prop.isolated == isolation_yes;
                }
            }
        }
    }

    void assign_region_ids()
    {
        for (typename merge_map::const_iterator it
             = m_turns_per_ring.begin(); it != m_turns_per_ring.end(); ++it)
        {
            ring_identifier const& ring_id = it->first;
            merged_ring_properties const& properties = it->second;

            for (set_iterator sit = properties.turn_indices.begin();
                 sit != properties.turn_indices.end(); ++sit)
            {
                turn_type& turn = m_turns[*sit];

                if (! acceptable(turn))
                {
                    // No assignment necessary
                    continue;
                }

                for (int i = 0; i < 2; i++)
                {
                    turn_operation_type& op = turn.operations[i];
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

            turn_operation_type op0 = turn.operations[0];
            turn_operation_type op1 = turn.operations[1];

            signed_size_type const& id0 = op0.enriched.region_id;
            signed_size_type const& id1 = op1.enriched.region_id;

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
        return ! turn.discarded
            && ! turn.both(operation_blocked);
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
            return ! (turn.both(operation_union) || turn.both(operation_intersection));
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


    inline signed_size_type get_region_id(turn_operation_type const& op) const
    {
        return op.enriched.region_id;
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
        std::cout << " ADD " << ring_id << "  TO REGION " << region_id << std::endl;
#endif

        // Find connecting rings, recursively
        for (set_iterator sit = properties.turn_indices.begin();
             sit != properties.turn_indices.end(); ++sit)
        {
            signed_size_type const turn_index = *sit;
            turn_type const& turn = m_turns[turn_index];
            if (! connects_same_region(turn))
            {
                // This is a non clustered uu/ii-turn, or a cluster connecting different 'zones'
                continue;
            }

            // Union: This turn connects two rings (interior connected), create the region
            // Intersection: This turn connects two rings, set same regions for these two rings
            for (int op_index = 0; op_index < 2; op_index++)
            {
                turn_operation_type const& op = turn.operations[op_index];
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
        typename merge_map::iterator it = m_turns_per_ring.find(ring_id);
        if (it != m_turns_per_ring.end())
        {
            create_region(new_region_id, ring_id, it->second, region_id);
        }
    }


    void iterate()
    {
#if defined(BOOST_GEOMETRY_DEBUG_TRAVERSAL_SWITCH_DETECTOR)
        std::cout << "BEGIN ITERATION GETTING REGION_IDS" << std::endl;
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

            for (int op_index = 0; op_index < 2; op_index++)
            {
                turn_operation_type const& op = turn.operations[op_index];
                m_turns_per_ring[ring_id_by_seg_id(op.seg_id)].turn_indices.insert(turn_index);
            }
        }

        // All rings having turns are in turns/ring map. Process them.
        {
            signed_size_type new_region_id = 1;
            for (typename merge_map::iterator it
                 = m_turns_per_ring.begin(); it != m_turns_per_ring.end(); ++it)
            {
                create_region(new_region_id, it->first, it->second);
            }

            assign_region_ids();
            assign_connected_regions();
            get_isolated_regions();
            assign_isolation();
        }

#if defined(BOOST_GEOMETRY_DEBUG_TRAVERSAL_SWITCH_DETECTOR)
        std::cout << "END ITERATION GETTIN REGION_IDS" << std::endl;

        for (std::size_t turn_index = 0; turn_index < m_turns.size(); ++turn_index)
        {
            turn_type const& turn = m_turns[turn_index];

            if ((turn.both(operation_union) || turn.both(operation_intersection))
                 && ! turn.is_clustered())
            {
                std::cout << "UU/II RESULT "
                             << turn_index << " -> "
                          << turn.operations[0].enriched.region_id
                          << " " << turn.operations[1].enriched.region_id
                          << std::endl;
            }
        }

        for (typename Clusters::const_iterator it = m_clusters.begin(); it != m_clusters.end(); ++it)
        {
            cluster_info const& cinfo = it->second;
            std::cout << "CL RESULT " << it->first
                         << " -> " << cinfo.open_count << std::endl;
        }
#endif

    }

private:

    Geometry1 const& m_geometry1;
    Geometry2 const& m_geometry2;
    Turns& m_turns;
    Clusters& m_clusters;
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
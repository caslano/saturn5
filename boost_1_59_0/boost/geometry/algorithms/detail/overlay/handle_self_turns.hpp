// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2019-2020.
// Modifications copyright (c) 2019-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_HANDLE_SELF_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_HANDLE_SELF_TURNS_HPP

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/detail/overlay/cluster_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/is_self_turn.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>
#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/within.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template <overlay_type OverlayType>
struct check_within
{
    template
    <
        typename Turn, typename Geometry0, typename Geometry1,
        typename UmbrellaStrategy
    >
    static inline
    bool apply(Turn const& turn, Geometry0 const& geometry0,
               Geometry1 const& geometry1, UmbrellaStrategy const& strategy)
    {
        // Operations 0 and 1 have the same source index in self-turns
        return turn.operations[0].seg_id.source_index == 0
            ? geometry::within(turn.point, geometry1, strategy)
            : geometry::within(turn.point, geometry0, strategy);
    }

};

template <>
struct check_within<overlay_difference>
{
    template
    <
        typename Turn, typename Geometry0, typename Geometry1,
        typename UmbrellaStrategy
    >
    static inline
    bool apply(Turn const& turn, Geometry0 const& geometry0,
               Geometry1 const& geometry1, UmbrellaStrategy const& strategy)
    {
        // difference = intersection(a, reverse(b))
        // therefore we should reverse the meaning of within for geometry1
        return turn.operations[0].seg_id.source_index == 0
            ? ! geometry::covered_by(turn.point, geometry1, strategy)
            : geometry::within(turn.point, geometry0, strategy);
    }
};

struct discard_turns
{
    template
    <
        typename Turns, typename Clusters,
        typename Geometry0, typename Geometry1,
        typename Strategy
    >
    static inline
    void apply(Turns& , Clusters const& ,
               Geometry0 const& , Geometry1 const& ,
               Strategy const& )
    {}
};

template <overlay_type OverlayType, operation_type OperationType>
struct discard_closed_turns : discard_turns {};

// It is only implemented for operation_union, not in buffer
template <>
struct discard_closed_turns<overlay_union, operation_union>
{
    // Point in Geometry Strategy
    template
    <
        typename Turns, typename Clusters,
        typename Geometry0, typename Geometry1,
        typename Strategy
    >
    static inline
    void apply(Turns& turns, Clusters const& /*clusters*/,
               Geometry0 const& geometry0, Geometry1 const& geometry1,
               Strategy const& strategy)
    {
        typedef typename boost::range_value<Turns>::type turn_type;

        for (typename boost::range_iterator<Turns>::type
                it = boost::begin(turns);
             it != boost::end(turns);
             ++it)
        {
            turn_type& turn = *it;

            if (! turn.discarded
                && is_self_turn<overlay_union>(turn)
                && check_within<overlay_union>::apply(turn, geometry0,
                                                      geometry1, strategy))
            {
                // Turn is in the interior of other geometry
                turn.discarded = true;
            }
        }
    }
};

template <overlay_type OverlayType>
struct discard_self_intersection_turns
{
private :

    template <typename Turns, typename Clusters>
    static inline
    bool is_self_cluster(signed_size_type cluster_id,
            const Turns& turns, Clusters const& clusters)
    {
        typename Clusters::const_iterator cit = clusters.find(cluster_id);
        if (cit == clusters.end())
        {
            return false;
        }

        cluster_info const& cinfo = cit->second;
        for (std::set<signed_size_type>::const_iterator it
             = cinfo.turn_indices.begin();
             it != cinfo.turn_indices.end(); ++it)
        {
            if (! is_self_turn<OverlayType>(turns[*it]))
            {
                return false;
            }
        }

        return true;
    }

    template <typename Turns, typename Clusters,
              typename Geometry0, typename Geometry1, typename Strategy>
    static inline
    void discard_clusters(Turns& turns, Clusters const& clusters,
            Geometry0 const& geometry0, Geometry1 const& geometry1,
            Strategy const& strategy)
    {
        for (typename Clusters::const_iterator cit = clusters.begin();
             cit != clusters.end(); ++cit)
        {
            signed_size_type const cluster_id = cit->first;

            // If there are only self-turns in the cluster, the cluster should
            // be located within the other geometry, for intersection
            if (! cit->second.turn_indices.empty()
                && is_self_cluster(cluster_id, turns, clusters))
            {
                cluster_info const& cinfo = cit->second;
                signed_size_type const index = *cinfo.turn_indices.begin();
                if (! check_within<OverlayType>::apply(turns[index],
                                                       geometry0, geometry1,
                                                       strategy))
                {
                    // Discard all turns in cluster
                    for (std::set<signed_size_type>::const_iterator sit
                         = cinfo.turn_indices.begin();
                         sit != cinfo.turn_indices.end(); ++sit)
                    {
                        turns[*sit].discarded = true;
                    }
                }
            }
        }
    }

public :

    template <typename Turns, typename Clusters,
              typename Geometry0, typename Geometry1, typename Strategy>
    static inline
    void apply(Turns& turns, Clusters const& clusters,
            Geometry0 const& geometry0, Geometry1 const& geometry1,
            Strategy const& strategy)
    {
        discard_clusters(turns, clusters, geometry0, geometry1, strategy);

        typedef typename boost::range_value<Turns>::type turn_type;

        for (typename boost::range_iterator<Turns>::type
                it = boost::begin(turns);
             it != boost::end(turns);
             ++it)
        {
            turn_type& turn = *it;

            // It is a ii self-turn
            // Check if it is within the other geometry
            if (! turn.discarded
                && is_self_turn<overlay_intersection>(turn)
                && ! check_within<OverlayType>::apply(turn, geometry0,
                                                      geometry1, strategy))
            {
                // It is not within another geometry, set it as non startable.
                // It still might be traveled (#case_recursive_boxes_70)
                turn.operations[0].enriched.startable = false;
                turn.operations[1].enriched.startable = false;
            }
        }
    }
};


template <overlay_type OverlayType, operation_type OperationType>
struct discard_open_turns : discard_turns {};

// Handler for intersection
template <>
struct discard_open_turns<overlay_intersection, operation_intersection>
        : discard_self_intersection_turns<overlay_intersection> {};

// Handler for difference, with different meaning of 'within'
template <>
struct discard_open_turns<overlay_difference, operation_intersection>
        : discard_self_intersection_turns<overlay_difference> {};

}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_HANDLE_SELF_TURNS_HPP

/* handle_self_turns.hpp
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
*/
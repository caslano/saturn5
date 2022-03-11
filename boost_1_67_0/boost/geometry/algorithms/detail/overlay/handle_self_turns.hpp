// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_HANDLE_SELF_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_HANDLE_SELF_TURNS_HPP

#include <boost/range.hpp>

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


template
<
    typename Point, typename Geometry,
    typename Tag2 = typename geometry::tag<Geometry>::type
>
struct check_within_strategy
{
    template <typename Strategy>
    static inline typename Strategy::template point_in_geometry_strategy<Point, Geometry>::type
        within(Strategy const& strategy)
    {
        return strategy.template get_point_in_geometry_strategy<Point, Geometry>();
    }

    template <typename Strategy>
    static inline typename Strategy::template point_in_geometry_strategy<Point, Geometry>::type
        covered_by(Strategy const& strategy)
    {
        return strategy.template get_point_in_geometry_strategy<Point, Geometry>();
    }
};

template <typename Point, typename Geometry>
struct check_within_strategy<Point, Geometry, box_tag>
{
    template <typename Strategy>
    static inline typename Strategy::within_point_box_strategy_type
        within(Strategy const& )
    {
        return typename Strategy::within_point_box_strategy_type();
    }

    template <typename Strategy>
    static inline typename Strategy::covered_by_point_box_strategy_type
        covered_by(Strategy const&)
    {
        return typename Strategy::covered_by_point_box_strategy_type();
    }
};


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
        typedef typename Turn::point_type point_type;

        // Operations 0 and 1 have the same source index in self-turns
        return turn.operations[0].seg_id.source_index == 0
            ? geometry::within(turn.point, geometry1,
                check_within_strategy<point_type, Geometry1>::within(strategy))
            : geometry::within(turn.point, geometry0,
                check_within_strategy<point_type, Geometry0>::within(strategy));
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
        typedef typename Turn::point_type point_type;

        // difference = intersection(a, reverse(b))
        // therefore we should reverse the meaning of within for geometry1
        return turn.operations[0].seg_id.source_index == 0
            ? ! geometry::covered_by(turn.point, geometry1,
                  check_within_strategy<point_type, Geometry1>::covered_by(strategy))
            : geometry::within(turn.point, geometry0,
                check_within_strategy<point_type, Geometry0>::within(strategy));
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
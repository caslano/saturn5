// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017-2021.
// Modifications copyright (c) 2017-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SELF_TURN_POINTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SELF_TURN_POINTS_HPP


#include <cstddef>


#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/partition.hpp>
#include <boost/geometry/algorithms/detail/overlay/do_reverse.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turns.hpp>
#include <boost/geometry/algorithms/detail/sections/section_box_policies.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/relate/services.hpp>

#include <boost/geometry/util/condition.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace self_get_turn_points
{

struct no_interrupt_policy
{
    static bool const enabled = false;
    static bool const has_intersections = false;


    template <typename Range>
    static inline bool apply(Range const&)
    {
        return false;
    }
};


template
<
    bool Reverse,
    typename Geometry,
    typename Turns,
    typename TurnPolicy,
    typename Strategy,
    typename RobustPolicy,
    typename InterruptPolicy
>
struct self_section_visitor
{
    Geometry const& m_geometry;
    Strategy const& m_strategy;
    RobustPolicy const& m_rescale_policy;
    Turns& m_turns;
    InterruptPolicy& m_interrupt_policy;
    int m_source_index;
    bool m_skip_adjacent;

    inline self_section_visitor(Geometry const& g,
                                Strategy const& s,
                                RobustPolicy const& rp,
                                Turns& turns,
                                InterruptPolicy& ip,
                                int source_index,
                                bool skip_adjacent)
        : m_geometry(g)
        , m_strategy(s)
        , m_rescale_policy(rp)
        , m_turns(turns)
        , m_interrupt_policy(ip)
        , m_source_index(source_index)
        , m_skip_adjacent(skip_adjacent)
    {}

    template <typename Section>
    inline bool apply(Section const& sec1, Section const& sec2)
    {
        if (! detail::disjoint::disjoint_box_box(sec1.bounding_box,
                                                 sec2.bounding_box,
                                                 m_strategy)
                && ! sec1.duplicate
                && ! sec2.duplicate)
        {
            // false if interrupted
            return detail::get_turns::get_turns_in_sections
                    <
                        Geometry, Geometry,
                        Reverse, Reverse,
                        Section, Section,
                        TurnPolicy
                    >::apply(m_source_index, m_geometry, sec1,
                             m_source_index, m_geometry, sec2,
                             false, m_skip_adjacent,
                             m_strategy,
                             m_rescale_policy,
                             m_turns, m_interrupt_policy);
        }

        return true;
    }

};



template <bool Reverse, typename TurnPolicy>
struct get_turns
{
    template <typename Geometry, typename Strategy, typename RobustPolicy, typename Turns, typename InterruptPolicy>
    static inline bool apply(
            Geometry const& geometry,
            Strategy const& strategy,
            RobustPolicy const& robust_policy,
            Turns& turns,
            InterruptPolicy& interrupt_policy,
            int source_index, bool skip_adjacent)
    {
        typedef model::box
            <
                typename geometry::robust_point_type
                <
                    typename geometry::point_type<Geometry>::type,
                    RobustPolicy
                >::type
            > box_type;

        // sectionalize in two dimensions to detect
        // all potential spikes correctly
        typedef geometry::sections<box_type, 2> sections_type;

        typedef std::integer_sequence<std::size_t, 0, 1> dimensions;

        sections_type sec;
        geometry::sectionalize<Reverse, dimensions>(geometry, robust_policy,
                                                    sec, strategy);

        self_section_visitor
            <
                Reverse, Geometry,
                Turns, TurnPolicy, Strategy, RobustPolicy, InterruptPolicy
            > visitor(geometry, strategy, robust_policy, turns, interrupt_policy,
                      source_index, skip_adjacent);

        // false if interrupted
        geometry::partition
            <
                box_type
            >::apply(sec, visitor,
                     detail::section::get_section_box<Strategy>(strategy),
                     detail::section::overlaps_section_box<Strategy>(strategy));

        return ! interrupt_policy.has_intersections;
    }
};


}} // namespace detail::self_get_turn_points
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    bool Reverse,
    typename GeometryTag,
    typename Geometry,
    typename TurnPolicy
>
struct self_get_turn_points
{
};


template
<
    bool Reverse,
    typename Ring,
    typename TurnPolicy
>
struct self_get_turn_points
    <
        Reverse, ring_tag, Ring,
        TurnPolicy
    >
    : detail::self_get_turn_points::get_turns<Reverse, TurnPolicy>
{};


template
<
    bool Reverse,
    typename Box,
    typename TurnPolicy
>
struct self_get_turn_points
    <
        Reverse, box_tag, Box,
        TurnPolicy
    >
{
    template <typename Strategy, typename RobustPolicy, typename Turns, typename InterruptPolicy>
    static inline bool apply(
            Box const& ,
            Strategy const& ,
            RobustPolicy const& ,
            Turns& ,
            InterruptPolicy& ,
            int /*source_index*/,
            bool /*skip_adjacent*/)
    {
        return true;
    }
};


template
<
    bool Reverse,
    typename Polygon,
    typename TurnPolicy
>
struct self_get_turn_points
    <
        Reverse, polygon_tag, Polygon,
        TurnPolicy
    >
    : detail::self_get_turn_points::get_turns<Reverse, TurnPolicy>
{};


template
<
    bool Reverse,
    typename MultiPolygon,
    typename TurnPolicy
>
struct self_get_turn_points
    <
        Reverse, multi_polygon_tag, MultiPolygon,
        TurnPolicy
    >
    : detail::self_get_turn_points::get_turns<Reverse, TurnPolicy>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy
{

template
<
    bool Reverse,
    typename AssignPolicy,
    typename Strategies,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategies>::value
>
struct self_get_turn_points
{
    template
    <
        typename Geometry,
        typename RobustPolicy,
        typename Turns,
        typename InterruptPolicy
    >
    static inline void apply(Geometry const& geometry,
                             Strategies const& strategies,
                             RobustPolicy const& robust_policy,
                             Turns& turns,
                             InterruptPolicy& interrupt_policy,
                             int source_index,
                             bool skip_adjacent)
    {
        using turn_policy = detail::overlay::get_turn_info<AssignPolicy>;

        dispatch::self_get_turn_points
                <
                    Reverse,
                    typename tag<Geometry>::type,
                    Geometry,
                    turn_policy
                >::apply(geometry, strategies, robust_policy, turns, interrupt_policy,
                         source_index, skip_adjacent);
    }
};

template <bool Reverse, typename AssignPolicy, typename Strategy>
struct self_get_turn_points<Reverse, AssignPolicy, Strategy, false>
{
    template
    <
        typename Geometry,
        typename RobustPolicy,
        typename Turns,
        typename InterruptPolicy
    >
    static inline void apply(Geometry const& geometry,
                             Strategy const& strategy,
                             RobustPolicy const& robust_policy,
                             Turns& turns,
                             InterruptPolicy& interrupt_policy,
                             int source_index,
                             bool skip_adjacent)
    {
        using strategies::relate::services::strategy_converter;

        self_get_turn_points
            <
                Reverse,
                AssignPolicy,
                decltype(strategy_converter<Strategy>::get(strategy))
            >::apply(geometry,
                     strategy_converter<Strategy>::get(strategy),
                     robust_policy,
                     turns,
                     interrupt_policy,
                     source_index,
                     skip_adjacent);
    }
};


} // namespace resolve_strategy


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace self_get_turn_points
{

// Version where Reverse can be specified manually. TODO: 
// can most probably be merged with self_get_turn_points::get_turn
template
<
    bool Reverse,
    typename AssignPolicy,
    typename Geometry,
    typename Strategy,
    typename RobustPolicy,
    typename Turns,
    typename InterruptPolicy
>
inline void self_turns(Geometry const& geometry,
                       Strategy const& strategy,
                       RobustPolicy const& robust_policy,
                       Turns& turns,
                       InterruptPolicy& interrupt_policy,
                       int source_index = 0,
                       bool skip_adjacent = false)
{
    concepts::check<Geometry const>();

    resolve_strategy::self_get_turn_points
            <
                Reverse, AssignPolicy, Strategy
            >::apply(geometry, strategy, robust_policy, turns, interrupt_policy,
                     source_index, skip_adjacent);
}

}} // namespace detail::self_get_turn_points
#endif // DOXYGEN_NO_DETAIL

/*!
    \brief Calculate self intersections of a geometry
    \ingroup overlay
    \tparam Geometry geometry type
    \tparam Turns type of intersection container
                (e.g. vector of "intersection/turn point"'s)
    \param geometry geometry
    \param strategy strategy to be used
    \param robust_policy policy to handle robustness issues
    \param turns container which will contain intersection points
    \param interrupt_policy policy determining if process is stopped
        when intersection is found
    \param source_index source index for generated turns
    \param skip_adjacent indicates if adjacent turns should be skipped
 */
template
<
    typename AssignPolicy,
    typename Geometry,
    typename Strategy,
    typename RobustPolicy,
    typename Turns,
    typename InterruptPolicy
>
inline void self_turns(Geometry const& geometry,
                       Strategy const& strategy,
                       RobustPolicy const& robust_policy,
                       Turns& turns,
                       InterruptPolicy& interrupt_policy,
                       int source_index = 0,
                       bool skip_adjacent = false)
{
    concepts::check<Geometry const>();

    static bool const reverse =  detail::overlay::do_reverse
        <
            geometry::point_order<Geometry>::value
        >::value;

    resolve_strategy::self_get_turn_points
            <
                reverse, AssignPolicy, Strategy
            >::apply(geometry, strategy, robust_policy, turns, interrupt_policy,
                     source_index, skip_adjacent);
}



}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SELF_TURN_POINTS_HPP

/* self_turn_points.hpp
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
*/
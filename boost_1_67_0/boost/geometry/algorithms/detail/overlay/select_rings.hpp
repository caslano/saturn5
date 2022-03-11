// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SELECT_RINGS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SELECT_RINGS_HPP


#include <map>

#include <boost/range.hpp>

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/detail/ring_identifier.hpp>
#include <boost/geometry/algorithms/detail/overlay/range_in_geometry.hpp>
#include <boost/geometry/algorithms/detail/overlay/ring_properties.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

struct ring_turn_info
{
    bool has_traversed_turn;
    bool has_blocked_turn;
    bool within_other;

    ring_turn_info()
        : has_traversed_turn(false)
        , has_blocked_turn(false)
        , within_other(false)
    {}
};

namespace dispatch
{

    template <typename Tag, typename Geometry>
    struct select_rings
    {};

    template <typename Box>
    struct select_rings<box_tag, Box>
    {
        template <typename Geometry, typename RingPropertyMap, typename AreaStrategy>
        static inline void apply(Box const& box, Geometry const& ,
                ring_identifier const& id, RingPropertyMap& ring_properties,
                AreaStrategy const& strategy)
        {
            ring_properties[id] = typename RingPropertyMap::mapped_type(box, strategy);
        }

        template <typename RingPropertyMap, typename AreaStrategy>
        static inline void apply(Box const& box,
                ring_identifier const& id, RingPropertyMap& ring_properties,
                AreaStrategy const& strategy)
        {
            ring_properties[id] = typename RingPropertyMap::mapped_type(box, strategy);
        }
    };

    template <typename Ring>
    struct select_rings<ring_tag, Ring>
    {
        template <typename Geometry, typename RingPropertyMap, typename AreaStrategy>
        static inline void apply(Ring const& ring, Geometry const& ,
                    ring_identifier const& id, RingPropertyMap& ring_properties,
                    AreaStrategy const& strategy)
        {
            if (boost::size(ring) > 0)
            {
                ring_properties[id] = typename RingPropertyMap::mapped_type(ring, strategy);
            }
        }

        template <typename RingPropertyMap, typename AreaStrategy>
        static inline void apply(Ring const& ring,
                    ring_identifier const& id, RingPropertyMap& ring_properties,
                    AreaStrategy const& strategy)
        {
            if (boost::size(ring) > 0)
            {
                ring_properties[id] = typename RingPropertyMap::mapped_type(ring, strategy);
            }
        }
    };


    template <typename Polygon>
    struct select_rings<polygon_tag, Polygon>
    {
        template <typename Geometry, typename RingPropertyMap, typename AreaStrategy>
        static inline void apply(Polygon const& polygon, Geometry const& geometry,
                    ring_identifier id, RingPropertyMap& ring_properties,
                    AreaStrategy const& strategy)
        {
            typedef typename geometry::ring_type<Polygon>::type ring_type;
            typedef select_rings<ring_tag, ring_type> per_ring;

            per_ring::apply(exterior_ring(polygon), geometry, id, ring_properties, strategy);

            typename interior_return_type<Polygon const>::type
                rings = interior_rings(polygon);
            for (typename detail::interior_iterator<Polygon const>::type
                    it = boost::begin(rings); it != boost::end(rings); ++it)
            {
                id.ring_index++;
                per_ring::apply(*it, geometry, id, ring_properties, strategy);
            }
        }

        template <typename RingPropertyMap, typename AreaStrategy>
        static inline void apply(Polygon const& polygon,
                ring_identifier id, RingPropertyMap& ring_properties,
                AreaStrategy const& strategy)
        {
            typedef typename geometry::ring_type<Polygon>::type ring_type;
            typedef select_rings<ring_tag, ring_type> per_ring;

            per_ring::apply(exterior_ring(polygon), id, ring_properties, strategy);

            typename interior_return_type<Polygon const>::type
                rings = interior_rings(polygon);
            for (typename detail::interior_iterator<Polygon const>::type
                    it = boost::begin(rings); it != boost::end(rings); ++it)
            {
                id.ring_index++;
                per_ring::apply(*it, id, ring_properties, strategy);
            }
        }
    };

    template <typename Multi>
    struct select_rings<multi_polygon_tag, Multi>
    {
        template <typename Geometry, typename RingPropertyMap, typename AreaStrategy>
        static inline void apply(Multi const& multi, Geometry const& geometry,
                    ring_identifier id, RingPropertyMap& ring_properties,
                    AreaStrategy const& strategy)
        {
            typedef typename boost::range_iterator
                <
                    Multi const
                >::type iterator_type;

            typedef select_rings<polygon_tag, typename boost::range_value<Multi>::type> per_polygon;

            id.multi_index = 0;
            for (iterator_type it = boost::begin(multi); it != boost::end(multi); ++it)
            {
                id.ring_index = -1;
                per_polygon::apply(*it, geometry, id, ring_properties, strategy);
                id.multi_index++;
            }
        }
    };

} // namespace dispatch


template<overlay_type OverlayType>
struct decide
{
    // Default implementation (union, inflate, deflate, dissolve)
    static bool include(ring_identifier const& , ring_turn_info const& info)
    {
        return ! info.within_other;
    }

    static bool reversed(ring_identifier const& , ring_turn_info const& )
    {
        return false;
    }

};

template<>
struct decide<overlay_difference>
{
    static bool include(ring_identifier const& id, ring_turn_info const& info)
    {
        // Difference: A - B

        // If this is A (source_index=0), then the ring is inside B
        // If this is B (source_index=1), then the ring is NOT inside A

        // If this is A and the ring is within the other geometry,
        // then we should NOT include it.
        // If this is B then we SHOULD include it.

        return id.source_index == 0
            ? ! info.within_other
            : info.within_other;
    }

    static bool reversed(ring_identifier const& id, ring_turn_info const& info)
    {
        // Difference: A - B
        // If this is B, and the ring is included, it should be reversed afterwards

        return id.source_index == 1 && include(id, info);
    }
};

template<>
struct decide<overlay_intersection>
{
    static bool include(ring_identifier const& , ring_turn_info const& info)
    {
        return info.within_other;
    }

    static bool reversed(ring_identifier const& , ring_turn_info const& )
    {
        return false;
    }
};

template
<
    overlay_type OverlayType,
    typename Geometry1,
    typename Geometry2,
    typename TurnInfoMap,
    typename RingPropertyMap,
    typename Strategy
>
inline void update_ring_selection(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            TurnInfoMap const& turn_info_map,
            RingPropertyMap const& all_ring_properties,
            RingPropertyMap& selected_ring_properties,
            Strategy const& strategy)
{
    selected_ring_properties.clear();

    for (typename RingPropertyMap::const_iterator it = boost::begin(all_ring_properties);
        it != boost::end(all_ring_properties);
        ++it)
    {
        ring_identifier const& id = it->first;

        ring_turn_info info;

        typename TurnInfoMap::const_iterator tcit = turn_info_map.find(id);
        if (tcit != turn_info_map.end())
        {
            info = tcit->second; // Copy by value
        }

        if (info.has_traversed_turn || info.has_blocked_turn)
        {
            // This turn is traversed or blocked,
            // don't include the original ring
            continue;
        }

        // Check if the ring is within the other geometry, by taking
        // a point lying on the ring
        switch(id.source_index)
        {
            // within
            case 0 :
                info.within_other = range_in_geometry(it->second.point,
                                                      geometry1, geometry2,
                                                      strategy) > 0;
                break;
            case 1 :
                info.within_other = range_in_geometry(it->second.point,
                                                      geometry2, geometry1,
                                                      strategy) > 0;
                break;
        }

        if (decide<OverlayType>::include(id, info))
        {
            typename RingPropertyMap::mapped_type properties = it->second; // Copy by value
            properties.reversed = decide<OverlayType>::reversed(id, info);
            selected_ring_properties[id] = properties;
        }
    }
}


/*!
\brief The function select_rings select rings based on the overlay-type (union,intersection)
*/
template
<
    overlay_type OverlayType,
    typename Geometry1,
    typename Geometry2,
    typename RingTurnInfoMap,
    typename RingPropertyMap,
    typename Strategy
>
inline void select_rings(Geometry1 const& geometry1, Geometry2 const& geometry2,
            RingTurnInfoMap const& turn_info_per_ring,
            RingPropertyMap& selected_ring_properties,
            Strategy const& strategy)
{
    typedef typename geometry::tag<Geometry1>::type tag1;
    typedef typename geometry::tag<Geometry2>::type tag2;
    typedef typename geometry::point_type<Geometry1>::type point1_type;
    typedef typename geometry::point_type<Geometry2>::type point2_type;

    RingPropertyMap all_ring_properties;
    dispatch::select_rings<tag1, Geometry1>::apply(geometry1, geometry2,
                ring_identifier(0, -1, -1), all_ring_properties,
                strategy.template get_area_strategy<point1_type>());
    dispatch::select_rings<tag2, Geometry2>::apply(geometry2, geometry1,
                ring_identifier(1, -1, -1), all_ring_properties,
                strategy.template get_area_strategy<point2_type>());

    update_ring_selection<OverlayType>(geometry1, geometry2, turn_info_per_ring,
                all_ring_properties, selected_ring_properties,
                strategy);
}

template
<
    overlay_type OverlayType,
    typename Geometry,
    typename RingTurnInfoMap,
    typename RingPropertyMap,
    typename Strategy
>
inline void select_rings(Geometry const& geometry,
            RingTurnInfoMap const& turn_info_per_ring,
            RingPropertyMap& selected_ring_properties,
            Strategy const& strategy)
{
    typedef typename geometry::tag<Geometry>::type tag;
    typedef typename geometry::point_type<Geometry>::type point_type;

    RingPropertyMap all_ring_properties;
    dispatch::select_rings<tag, Geometry>::apply(geometry,
                ring_identifier(0, -1, -1), all_ring_properties,
                strategy.template get_area_strategy<point_type>());

    update_ring_selection<OverlayType>(geometry, geometry, turn_info_per_ring,
                all_ring_properties, selected_ring_properties,
                strategy);
}


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SELECT_RINGS_HPP

/* select_rings.hpp
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
*/
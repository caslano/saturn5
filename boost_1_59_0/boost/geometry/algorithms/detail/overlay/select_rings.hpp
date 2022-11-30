// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017-2021.
// Modifications copyright (c) 2017-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SELECT_RINGS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SELECT_RINGS_HPP


#include <map>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>

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
        template <typename Geometry, typename RingPropertyMap, typename Strategy>
        static inline void apply(Box const& box, Geometry const& ,
                ring_identifier const& id, RingPropertyMap& ring_properties,
                Strategy const& strategy)
        {
            ring_properties[id] = typename RingPropertyMap::mapped_type(box, strategy);
        }

        template <typename RingPropertyMap, typename Strategy>
        static inline void apply(Box const& box,
                ring_identifier const& id, RingPropertyMap& ring_properties,
                Strategy const& strategy)
        {
            ring_properties[id] = typename RingPropertyMap::mapped_type(box, strategy);
        }
    };

    template <typename Ring>
    struct select_rings<ring_tag, Ring>
    {
        template <typename Geometry, typename RingPropertyMap, typename Strategy>
        static inline void apply(Ring const& ring, Geometry const& ,
                    ring_identifier const& id, RingPropertyMap& ring_properties,
                    Strategy const& strategy)
        {
            if (boost::size(ring) > 0)
            {
                ring_properties[id] = typename RingPropertyMap::mapped_type(ring, strategy);
            }
        }

        template <typename RingPropertyMap, typename Strategy>
        static inline void apply(Ring const& ring,
                    ring_identifier const& id, RingPropertyMap& ring_properties,
                    Strategy const& strategy)
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
        template <typename Geometry, typename RingPropertyMap, typename Strategy>
        static inline void apply(Polygon const& polygon, Geometry const& geometry,
                    ring_identifier id, RingPropertyMap& ring_properties,
                    Strategy const& strategy)
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

        template <typename RingPropertyMap, typename Strategy>
        static inline void apply(Polygon const& polygon,
                ring_identifier id, RingPropertyMap& ring_properties,
                Strategy const& strategy)
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
        template <typename Geometry, typename RingPropertyMap, typename Strategy>
        static inline void apply(Multi const& multi, Geometry const& geometry,
                    ring_identifier id, RingPropertyMap& ring_properties,
                    Strategy const& strategy)
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
    
    RingPropertyMap all_ring_properties;
    dispatch::select_rings<tag1, Geometry1>::apply(geometry1, geometry2,
                ring_identifier(0, -1, -1), all_ring_properties,
                strategy);
    dispatch::select_rings<tag2, Geometry2>::apply(geometry2, geometry1,
                ring_identifier(1, -1, -1), all_ring_properties,
                strategy);

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

    RingPropertyMap all_ring_properties;
    dispatch::select_rings<tag, Geometry>::apply(geometry,
                ring_identifier(0, -1, -1), all_ring_properties,
                strategy);

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
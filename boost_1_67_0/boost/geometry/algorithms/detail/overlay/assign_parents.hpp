// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017, 2018, 2019.
// Modifications copyright (c) 2017-2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_ASSIGN_PARENTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_ASSIGN_PARENTS_HPP

#include <boost/range.hpp>

#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/algorithms/detail/partition.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_ring.hpp>
#include <boost/geometry/algorithms/detail/overlay/range_in_geometry.hpp>
#include <boost/geometry/algorithms/covered_by.hpp>

#include <boost/geometry/geometries/box.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{



template
<
    typename Item,
    typename InnerGeometry,
    typename Geometry1, typename Geometry2,
    typename RingCollection,
    typename Strategy
>
static inline bool within_selected_input(Item const& item2,
        InnerGeometry const& inner_geometry,
        ring_identifier const& outer_id,
        Geometry1 const& geometry1, Geometry2 const& geometry2,
        RingCollection const& collection,
        Strategy const& strategy)
{
    typedef typename geometry::tag<Geometry1>::type tag1;
    typedef typename geometry::tag<Geometry2>::type tag2;

    // NOTE: range_in_geometry first checks the item2.point and then
    // if this point is on boundary it checks points of inner_geometry
    // ring until a point inside/outside other geometry ring is found
    switch (outer_id.source_index)
    {
        // covered_by
        case 0 :
            return range_in_geometry(item2.point, inner_geometry,
                get_ring<tag1>::apply(outer_id, geometry1), strategy) >= 0;
        case 1 :
            return range_in_geometry(item2.point, inner_geometry,
                get_ring<tag2>::apply(outer_id, geometry2), strategy) >= 0;
        case 2 :
            return range_in_geometry(item2.point, inner_geometry,
                get_ring<void>::apply(outer_id, collection), strategy) >= 0;
    }
    return false;
}

template
<
    typename Item,
    typename Geometry1, typename Geometry2,
    typename RingCollection,
    typename Strategy
>
static inline bool within_selected_input(Item const& item2,
        ring_identifier const& inner_id, ring_identifier const& outer_id,
        Geometry1 const& geometry1, Geometry2 const& geometry2,
        RingCollection const& collection,
        Strategy const& strategy)
{
    typedef typename geometry::tag<Geometry1>::type tag1;
    typedef typename geometry::tag<Geometry2>::type tag2;

    switch (inner_id.source_index)
    {
        case 0 :
            return within_selected_input(item2,
               get_ring<tag1>::apply(inner_id, geometry1),
               outer_id, geometry1, geometry2, collection, strategy);
        case 1 :
            return within_selected_input(item2,
               get_ring<tag2>::apply(inner_id, geometry2),
               outer_id, geometry1, geometry2, collection, strategy);
        case 2 :
            return within_selected_input(item2,
                get_ring<void>::apply(inner_id, collection),
                outer_id, geometry1, geometry2, collection, strategy);
    }
    return false;
}


template <typename Point, typename AreaType>
struct ring_info_helper
{
    ring_identifier id;
    AreaType real_area;
    AreaType abs_area;
    model::box<Point> envelope;

    inline ring_info_helper()
        : real_area(0), abs_area(0)
    {}

    inline ring_info_helper(ring_identifier i, AreaType const& a)
        : id(i), real_area(a), abs_area(geometry::math::abs(a))
    {}
};


template <typename BoxExpandStrategy>
struct ring_info_helper_get_box
{
    template <typename Box, typename InputItem>
    static inline void apply(Box& total, InputItem const& item)
    {
        geometry::expand(total, item.envelope, BoxExpandStrategy());
    }
};

template <typename DisjointBoxBoxStrategy>
struct ring_info_helper_ovelaps_box
{
    template <typename Box, typename InputItem>
    static inline bool apply(Box const& box, InputItem const& item)
    {
        return ! geometry::detail::disjoint::disjoint_box_box(
                    box, item.envelope, DisjointBoxBoxStrategy());
    }
};

// Segments intersection Strategy
template
<
    typename Geometry1,
    typename Geometry2,
    typename Collection,
    typename RingMap,
    typename Strategy
>
struct assign_visitor
{
    typedef typename RingMap::mapped_type ring_info_type;

    Geometry1 const& m_geometry1;
    Geometry2 const& m_geometry2;
    Collection const& m_collection;
    RingMap& m_ring_map;
    Strategy const& m_strategy;
    bool m_check_for_orientation;

    inline assign_visitor(Geometry1 const& g1, Geometry2 const& g2, Collection const& c,
                          RingMap& map, Strategy const& strategy, bool check)
        : m_geometry1(g1)
        , m_geometry2(g2)
        , m_collection(c)
        , m_ring_map(map)
        , m_strategy(strategy)
        , m_check_for_orientation(check)
    {}

    template <typename Item>
    inline bool apply(Item const& outer, Item const& inner, bool first = true)
    {
        if (first && outer.abs_area < inner.abs_area)
        {
            // Apply with reversed arguments
            apply(inner, outer, false);
            return true;
        }

        if (m_check_for_orientation
         || (math::larger(outer.real_area, 0)
          && math::smaller(inner.real_area, 0)))
        {
            ring_info_type& inner_in_map = m_ring_map[inner.id];

            if (geometry::covered_by(inner_in_map.point, outer.envelope,
                                     typename Strategy::disjoint_point_box_strategy_type())
               && within_selected_input(inner_in_map, inner.id, outer.id,
                                        m_geometry1, m_geometry2, m_collection,
                                        m_strategy)
               )
            {
                // Assign a parent if there was no earlier parent, or the newly
                // found parent is smaller than the previous one
                if (inner_in_map.parent.source_index == -1
                    || outer.abs_area < inner_in_map.parent_area)
                {
                    inner_in_map.parent = outer.id;
                    inner_in_map.parent_area = outer.abs_area;
                }
            }
        }

        return true;
    }
};


template
<
    overlay_type OverlayType,
    typename Geometry1, typename Geometry2,
    typename RingCollection,
    typename RingMap,
    typename Strategy
>
inline void assign_parents(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            RingCollection const& collection,
            RingMap& ring_map,
            Strategy const& strategy)
{
    static bool const is_difference = OverlayType == overlay_difference;
    static bool const is_buffer = OverlayType == overlay_buffer;
    static bool const is_dissolve = OverlayType == overlay_dissolve;
    static bool const check_for_orientation = is_buffer || is_dissolve;

    typedef typename geometry::tag<Geometry1>::type tag1;
    typedef typename geometry::tag<Geometry2>::type tag2;

    typedef typename RingMap::mapped_type ring_info_type;
    typedef typename ring_info_type::point_type point_type;
    typedef model::box<point_type> box_type;
    typedef typename Strategy::template area_strategy
        <
            point_type
        >::type::template result_type<point_type>::type area_result_type;

    typedef typename RingMap::iterator map_iterator_type;

    {
        typedef ring_info_helper<point_type, area_result_type> helper;
        typedef std::vector<helper> vector_type;
        typedef typename boost::range_iterator<vector_type const>::type vector_iterator_type;

        std::size_t count_total = ring_map.size();
        std::size_t count_positive = 0;
        std::size_t index_positive = 0; // only used if count_positive>0
        std::size_t index = 0;

        // Copy to vector (with new approach this might be obsolete as well, using the map directly)
        vector_type vector(count_total);

        for (map_iterator_type it = boost::begin(ring_map);
            it != boost::end(ring_map); ++it, ++index)
        {
            vector[index] = helper(it->first, it->second.get_area());
            helper& item = vector[index];
            switch(it->first.source_index)
            {
                case 0 :
                    geometry::envelope(get_ring<tag1>::apply(it->first, geometry1),
                                       item.envelope, strategy.get_envelope_strategy());
                    break;
                case 1 :
                    geometry::envelope(get_ring<tag2>::apply(it->first, geometry2),
                                       item.envelope, strategy.get_envelope_strategy());
                    break;
                case 2 :
                    geometry::envelope(get_ring<void>::apply(it->first, collection),
                                       item.envelope, strategy.get_envelope_strategy());
                    break;
            }

            // Expand envelope slightly
            expand_by_epsilon(item.envelope);

            if (item.real_area > 0)
            {
                count_positive++;
                index_positive = index;
            }
        }

        if (! check_for_orientation)
        {
            if (count_positive == count_total)
            {
                // Optimization for only positive rings
                // -> no assignment of parents or reversal necessary, ready here.
                return;
            }

            if (count_positive == 1 && ! is_difference && ! is_dissolve)
            {
                // Optimization for one outer ring
                // -> assign this as parent to all others (all interior rings)
                // In unions, this is probably the most occuring case and gives
                //    a dramatic improvement (factor 5 for star_comb testcase)
                // In difference or other cases where interior rings might be
                // located outside the outer ring, this cannot be done
                ring_identifier id_of_positive = vector[index_positive].id;
                ring_info_type& outer = ring_map[id_of_positive];
                index = 0;
                for (vector_iterator_type it = boost::begin(vector);
                    it != boost::end(vector); ++it, ++index)
                {
                    if (index != index_positive)
                    {
                        ring_info_type& inner = ring_map[it->id];
                        inner.parent = id_of_positive;
                        outer.children.push_back(it->id);
                    }
                }
                return;
            }
        }

        assign_visitor
            <
                Geometry1, Geometry2,
                RingCollection, RingMap,
                Strategy
            > visitor(geometry1, geometry2, collection, ring_map, strategy, check_for_orientation);

        typedef ring_info_helper_get_box
            <
                typename Strategy::expand_box_strategy_type
            > expand_box_type;
        typedef ring_info_helper_ovelaps_box
            <
                typename Strategy::disjoint_box_box_strategy_type
            > overlaps_box_type;

        geometry::partition
            <
                box_type
            >::apply(vector, visitor, expand_box_type(), overlaps_box_type());
    }

    if (check_for_orientation)
    {
        for (map_iterator_type it = boost::begin(ring_map);
            it != boost::end(ring_map); ++it)
        {
            ring_info_type& info = it->second;
            if (geometry::math::equals(info.get_area(), 0))
            {
                info.discarded = true;
            }
            else if (info.parent.source_index >= 0)
            {
                const ring_info_type& parent = ring_map[info.parent];
                bool const pos = math::larger(info.get_area(), 0);
                bool const parent_pos = math::larger(parent.area, 0);

                bool const double_neg = is_dissolve && ! pos && ! parent_pos;

                if ((pos && parent_pos) || double_neg)
                {
                    // Discard positive inner ring with positive parent
                    // Also, for some cases (dissolve), negative inner ring
                    // with negative parent should be discarded
                    info.discarded = true;
                }

                if (pos || info.discarded)
                {
                    // Remove parent ID from any positive or discarded inner rings
                    info.parent.source_index = -1;
                }
            }
            else if (info.parent.source_index < 0
                    && math::smaller(info.get_area(), 0))
            {
                // Reverse negative ring without parent
                info.reversed = true;
            }
        }
    }

    // Assign childlist
    for (map_iterator_type it = boost::begin(ring_map);
        it != boost::end(ring_map); ++it)
    {
        if (it->second.parent.source_index >= 0)
        {
            ring_map[it->second.parent].children.push_back(it->first);
        }
    }
}


// Version for one geometry (called by buffer/dissolve)
template
<
    overlay_type OverlayType,
    typename Geometry,
    typename RingCollection,
    typename RingMap,
    typename Strategy
>
inline void assign_parents(Geometry const& geometry,
            RingCollection const& collection,
            RingMap& ring_map,
            Strategy const& strategy)
{
    // Call it with an empty geometry as second geometry (source_id == 1)
    // (ring_map should be empty for source_id==1)
    Geometry empty;
    assign_parents<OverlayType>(geometry, empty,
            collection, ring_map, strategy);
}


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_ASSIGN_PARENTS_HPP

/* assign_parents.hpp
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
*/
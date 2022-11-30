// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_ASSIGN_PARENTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_ASSIGN_PARENTS_HPP

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
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


template <typename Strategy>
struct ring_info_helper_get_box
{
    ring_info_helper_get_box(Strategy const& strategy)
        : m_strategy(strategy)
    {}

    template <typename Box, typename InputItem>
    inline void apply(Box& total, InputItem const& item) const
    {
        assert_coordinate_type_equal(total, item.envelope);
        geometry::expand(total, item.envelope, m_strategy);
    }

    Strategy const& m_strategy;
};

template <typename Strategy>
struct ring_info_helper_overlaps_box
{
    ring_info_helper_overlaps_box(Strategy const& strategy)
        : m_strategy(strategy)
    {}

    template <typename Box, typename InputItem>
    inline bool apply(Box const& box, InputItem const& item) const
    {
        assert_coordinate_type_equal(box, item.envelope);
        return ! geometry::detail::disjoint::disjoint_box_box(
                    box, item.envelope, m_strategy);
    }

    Strategy const& m_strategy;
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

            if (geometry::covered_by(inner_in_map.point, outer.envelope, m_strategy)
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
    typedef typename geometry::area_result
        <
            point_type, Strategy // TODO: point_type is technically incorrect
        >::type area_result_type;

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
                                       item.envelope, strategy);
                    break;
                case 1 :
                    geometry::envelope(get_ring<tag2>::apply(it->first, geometry2),
                                       item.envelope, strategy);
                    break;
                case 2 :
                    geometry::envelope(get_ring<void>::apply(it->first, collection),
                                       item.envelope, strategy);
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

        geometry::partition
            <
                box_type
            >::apply(vector, visitor,
                     ring_info_helper_get_box<Strategy>(strategy),
                     ring_info_helper_overlaps_box<Strategy>(strategy));
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
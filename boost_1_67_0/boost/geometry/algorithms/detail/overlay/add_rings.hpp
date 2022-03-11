// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_ADD_RINGS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_ADD_RINGS_HPP

#include <boost/range.hpp>
#include <boost/throw_exception.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exception.hpp>
#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/detail/overlay/convert_ring.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_ring.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template
<
    typename GeometryOut,
    typename Geometry1,
    typename Geometry2,
    typename RingCollection
>
inline void convert_and_add(GeometryOut& result,
            Geometry1 const& geometry1, Geometry2 const& geometry2,
            RingCollection const& collection,
            ring_identifier id,
            bool reversed, bool append)
{
    typedef typename geometry::tag<Geometry1>::type tag1;
    typedef typename geometry::tag<Geometry2>::type tag2;
    typedef typename geometry::tag<GeometryOut>::type tag_out;

    if (id.source_index == 0)
    {
        convert_ring<tag_out>::apply(result,
                    get_ring<tag1>::apply(id, geometry1),
                    append, reversed);
    }
    else if (id.source_index == 1)
    {
        convert_ring<tag_out>::apply(result,
                    get_ring<tag2>::apply(id, geometry2),
                    append, reversed);
    }
    else if (id.source_index == 2)
    {
        convert_ring<tag_out>::apply(result,
                    get_ring<void>::apply(id, collection),
                    append, reversed);
    }
}

enum add_rings_error_handling
{
    add_rings_ignore_unordered,
    add_rings_add_unordered,
    add_rings_throw_if_reversed
};

template
<
    typename GeometryOut,
    typename SelectionMap,
    typename Geometry1,
    typename Geometry2,
    typename RingCollection,
    typename OutputIterator,
    typename AreaStrategy
>
inline OutputIterator add_rings(SelectionMap const& map,
            Geometry1 const& geometry1, Geometry2 const& geometry2,
            RingCollection const& collection,
            OutputIterator out,
            AreaStrategy const& area_strategy,
            add_rings_error_handling error_handling = add_rings_ignore_unordered)
{
    typedef typename SelectionMap::const_iterator iterator;
    typedef typename AreaStrategy::template result_type
        <
            GeometryOut
        >::type area_type;

    area_type const zero = 0;
    std::size_t const min_num_points = core_detail::closure::minimum_ring_size
        <
            geometry::closure
                <
                    typename boost::range_value
                        <
                            RingCollection const
                        >::type
                >::value
        >::value;


    for (iterator it = boost::begin(map);
        it != boost::end(map);
        ++it)
    {
        if (! it->second.discarded
            && it->second.parent.source_index == -1)
        {
            GeometryOut result;
            convert_and_add(result, geometry1, geometry2, collection,
                    it->first, it->second.reversed, false);

            // Add children
            for (typename std::vector<ring_identifier>::const_iterator child_it
                        = it->second.children.begin();
                child_it != it->second.children.end();
                ++child_it)
            {
                iterator mit = map.find(*child_it);
                if (mit != map.end()
                    && ! mit->second.discarded)
                {
                    convert_and_add(result, geometry1, geometry2, collection,
                            *child_it, mit->second.reversed, true);
                }
            }

            // Only add rings if they satisfy minimal requirements.
            // This cannot be done earlier (during traversal), not
            // everything is figured out yet (sum of positive/negative rings)
            if (geometry::num_points(result) >= min_num_points)
            {
                area_type const area = geometry::area(result, area_strategy);
                // Ignore if area is 0
                if (! math::equals(area, zero))
                {
                    if (error_handling == add_rings_add_unordered
                        || area > zero)
                    {
                        *out++ = result;
                    }
                    else if (error_handling == add_rings_throw_if_reversed)
                    {
                        BOOST_THROW_EXCEPTION(invalid_output_exception());
                    }
                }
            }
        }
    }
    return out;
}


template
<
    typename GeometryOut,
    typename SelectionMap,
    typename Geometry,
    typename RingCollection,
    typename OutputIterator,
    typename AreaStrategy
>
inline OutputIterator add_rings(SelectionMap const& map,
            Geometry const& geometry,
            RingCollection const& collection,
            OutputIterator out,
            AreaStrategy const& area_strategy)
{
    Geometry empty;
    return add_rings<GeometryOut>(map, geometry, empty, collection, out, area_strategy);
}


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_ADD_RINGS_HPP

/* add_rings.hpp
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
*/
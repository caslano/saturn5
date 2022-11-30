// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_ADD_RINGS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_ADD_RINGS_HPP

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>
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
    typename Strategy
>
inline OutputIterator add_rings(SelectionMap const& map,
            Geometry1 const& geometry1, Geometry2 const& geometry2,
            RingCollection const& collection,
            OutputIterator out,
            Strategy const& strategy,
            add_rings_error_handling error_handling = add_rings_ignore_unordered)
{
    typedef typename SelectionMap::const_iterator iterator;

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
                typedef typename geometry::area_result<GeometryOut, Strategy>::type area_type;
                area_type const area = geometry::area(result, strategy);
                area_type const zero = 0;
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
    typename Strategy
>
inline OutputIterator add_rings(SelectionMap const& map,
            Geometry const& geometry,
            RingCollection const& collection,
            OutputIterator out,
            Strategy const& strategy)
{
    Geometry empty;
    return add_rings<GeometryOut>(map, geometry, empty, collection, out, strategy);
}


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_ADD_RINGS_HPP

/* add_rings.hpp
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
*/
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
VJoNOv9BeJbKLgrBqq/cs3TQR6WHNwfhiXutDf23dV7Hi9a1Jn4s575HPJ9Q1xp/ijfA3V74yGdy7o6O60ry0Wv24rDqOvZpfu3gYTf3n7MJRr2b3EsvbrTFJ9jSADrYDhen/YArjZGPpcXF9JGH0vuzPcUHedI1urv+FEyYbWzp4Zv1/mCUXJcttOxlvg19r796/Gm+xX8KspsdYkF99buqMLIxG37gspjTRk1SDB75mDoqHnBUbfEn2FyqG26ND/RT78gvdx8Mbz6ooh+m5ni3ay29knx2Xg/9MdfFLydl5js15eGT6YMur/DfSfypa2Pze9Z68IFbrWHV7eoHU9j/RnEXNo+sQu/d1SthWo7msAc2VzuP9+xho2PUzzfRS2E+eCO8Hi7+wdnP78JFS6lZyME/otveYnU7uU8f468LL9NUsw4+z9xfT87PRvDrsJ8Z28E9P8tfLz4tg9HGPQbuLHiIf90v/y+jH6Rv2r0dHd7p2ZRcfMlcXvfsevJ9Ummvws7d9Owa1a1VCh0XyUAvBXFLn72CKyfH80Facd1PqRL/Z9t+/3LDX7ytD3s0NvkYW4Xxjw+EAeth66fm5PMNuPFxP7NOxIn93JgbN0ra0LtsMedftZczfp4RrxcMY1eD+ObN6luf44H6Bhn9nqxt3exn7RLi5S3mvcZ9z+IDGdT031efLo0LnOTzcKZglUgf2BrWk1erF/20lt/QY3o5dJ2c1kDcXQZje2yCy3K85Ps8PpGjPyd+9W2AP1+kT/WXBmxl8VD7Zg7IQ4oln7HWUya3kPykEOnNly5bv6byxkUnxJc6/CPVeDvJQeXPX7jvFrlhicZ4urn9fZtYu8ScPDfdViunsRw/WfuslHwnE7/prT5Zq49aQ2/YpLeWpZt8xjjG1IHD/GG+nzWcs/1P/Q9jf2BQAmXUA78X9vGFqcY0gywki8gKspI8TZLPxRXIr1dOX82WwLfFMLat59FmwbJj4gH+fBGON0xyfL3kUu51x3e4Atx8OYuxwcoi+ew/+0Xvex6cU9sqJ7aX2QoTF8gV4NMm+J9VjKg3XDwbpbd8iR3Td/Pm4recYk9yLT9gOynyL3npS/Lq1e3kbjjhAP5YzZ6SEhPtgb2mzrtPLysdnBfD66Xqn43AacTwdeXUVNjS+XV4V1955Rn4KD706mWu1vulzmx/rv0G7D+XZ2hCR+OQAzUZTNfDjDkt+1AHzZsv8a93BHzzO5tcz4/OOy8bXdSQG2+R+4orG1qqJbKNTPoHLYbhFFXwMntDeqVJPndi/455tDSWFhXlbSvhN1xLvpus7DC8gZ6u/ABfU/7q1Q3ewR97q9k0dG+4OiGHveY/wrU1YhLdFHbdxqQpaU7aklTShdxLepA+pB9pQlpk/mtvZhvy3kviSWVx7Un94Zvtby6MyyzzbOPBZH5s3Py4dmE+uEOstrbV87CNBfZDjxHX5b3d/sbWs9p/UJwuGrD/H9XcxuLNppFBzWbkDGs1l58OkWewkwuN1JatRUN404/9XvsNX6DPsj5vXMx6eadWhU/krvCsPT+ftdjauG/Od3HZ6urI2ej2BvnCUeNYIX8Szx4Vj4fXsjbJd+XJx99S78jj2Y+ep9kinhmbwzr2M3WvfuPDMH0LntBcXjES/7X3KbkP4Yk+nheg81XWf9AYeYLYeEqOMJZ+bnpH7LyDvSd7ynjFq6/Q2Ry4oMZzeTA7wKs2XcC5xIZHzalrVzqfx4+q4brvw7C28hL4/+kk+e91bGSDesl65nVOfslXX03igRwsJYt1u0THuFX5FMd8gdM19YwKfdxYUU1OHvpVDnmC775Mr/fiOuebWIcJMKGm+DhODohT1j8=
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017, 2018, 2019.
// Modifications copyright (c) 2015-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_SPHERICAL_EXPAND_BOX_HPP
#define BOOST_GEOMETRY_STRATEGY_SPHERICAL_EXPAND_BOX_HPP

#include <algorithm>
#include <cstddef>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/normalize.hpp>
#include <boost/geometry/algorithms/detail/envelope/transform_units.hpp>
#include <boost/geometry/algorithms/detail/envelope/range_of_boxes.hpp>
#include <boost/geometry/algorithms/dispatch/envelope.hpp>

#include <boost/geometry/geometries/helper_geometry.hpp>

#include <boost/geometry/strategy/expand.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{

template
<
    std::size_t Index,
    std::size_t DimensionCount
>
struct envelope_indexed_box_on_spheroid
{
    template <typename BoxIn, typename BoxOut>
    static inline void apply(BoxIn const& box_in, BoxOut& mbr)
    {
        // transform() does not work with boxes of dimension higher
        // than 2; to account for such boxes we transform the min/max
        // points of the boxes using the indexed_point_view
        detail::indexed_point_view<BoxIn const, Index> box_in_corner(box_in);
        detail::indexed_point_view<BoxOut, Index> mbr_corner(mbr);

        // first transform the units
        transform_units(box_in_corner, mbr_corner);

        // now transform the remaining coordinates
        detail::conversion::point_to_point
            <
                detail::indexed_point_view<BoxIn const, Index>,
                detail::indexed_point_view<BoxOut, Index>,
                2,
                DimensionCount
            >::apply(box_in_corner, mbr_corner);
    }
};

struct envelope_box_on_spheroid
{
    template <typename BoxIn, typename BoxOut>
    static inline void apply(BoxIn const& box_in, BoxOut& mbr)
    {
        // BoxIn can be non-mutable
        typename helper_geometry<BoxIn>::type box_in_normalized;
        geometry::convert(box_in, box_in_normalized);
        
        if (! is_inverse_spheroidal_coordinates(box_in))
        {
            strategy::normalize::spherical_box::apply(box_in, box_in_normalized);
        }

        geometry::detail::envelope::envelope_indexed_box_on_spheroid
            <
                min_corner, dimension<BoxIn>::value
            >::apply(box_in_normalized, mbr);

        geometry::detail::envelope::envelope_indexed_box_on_spheroid
            <
                max_corner, dimension<BoxIn>::value
            >::apply(box_in_normalized, mbr);
    }
};

}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL


namespace strategy { namespace expand
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct box_on_spheroid
{
    template <typename BoxOut, typename BoxIn>
    static inline void apply(BoxOut& box_out, BoxIn const& box_in)
    {
        // normalize both boxes and convert box-in to be of type of box-out
        BoxOut mbrs[2];
        geometry::detail::envelope::envelope_box_on_spheroid::apply(box_in, mbrs[0]);
        geometry::detail::envelope::envelope_box_on_spheroid::apply(box_out, mbrs[1]);

        // compute the envelope of the two boxes
        geometry::detail::envelope::envelope_range_of_boxes::apply(mbrs, box_out);
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


struct spherical_box
    : detail::box_on_spheroid
{};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<box_tag, spherical_equatorial_tag, CalculationType>
{
    typedef spherical_box type;
};

template <typename CalculationType>
struct default_strategy<box_tag, spherical_polar_tag, CalculationType>
{
    typedef spherical_box type;
};

template <typename CalculationType>
struct default_strategy<box_tag, geographic_tag, CalculationType>
{
    typedef spherical_box type;
};

} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::expand

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGY_SPHERICAL_EXPAND_BOX_HPP

/* expand_box.hpp
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
*/
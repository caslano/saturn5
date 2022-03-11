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

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_EXPAND_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_EXPAND_BOX_HPP

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

#include <boost/geometry/strategies/expand.hpp>

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

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_EXPAND_BOX_HPP

/* expand_box.hpp
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
*/
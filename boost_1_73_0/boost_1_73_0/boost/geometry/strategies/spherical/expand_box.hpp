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
+cy1/LCuD+Ifu0vkCrjeFwBKOkPwjBOgBp+jjU8w9C3vKVinxqe9fhcpGNqodF+eKOniA/rTrJTiPQsKJ+6k6XGrn42dn0CC6oWBiCVcxf0EsO0dUEQOy98LLuH3Xw7CnVrdr3rI1QMGnXoDl0RkvEXEsit0GzWIAKVcZ8BeSwS/UjbfrpfNAz5OwAWmrT89f/4LLtNswmDJIkvYxdowD7PRNHU+aW7QrXe++ceXb7KdFkuBrRIA1TRC0Fgg3xFTr7opH8aGeMG6fOYcz+zHdgryOjjOUiEmurV5FJJZSblj//LUrkD8CxvEVwdIPLW3PaFmJOhPA6aupIjJIkQJmYMibQGq6kiIPCg2OrUVa8gpXq/ACaIwN92TVaHUeeB4KoMq+46ZYZutiJXPP0Yfvu+1SiunnulXvV+eQoM/dvD7DghEFUbDIr6WLm3pCfEulx5sGokx8OmuGoDt2r/ea8G3e6m01RqXAqzkOr85tKdbS1ddsc+zZxu+SyI5+wH2zdM8AewisaqmgN4ZkMT6mlGVjVcN6l9WWD5/46KJb/RjTp2P81TBLkJb/VWsp0jFH5n80N1Zzax06TIWG5F0r5PM2L3cnVrbnLOMCkOaxQxGaKNRFHEj4MC6Tbf80YYa5zpv+15HUq5/u1nx
*/
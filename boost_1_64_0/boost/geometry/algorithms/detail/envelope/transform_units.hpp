// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_TRANSFORM_UNITS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_TRANSFORM_UNITS_HPP

#include <cstddef>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/strategy_transform.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>
#include <boost/geometry/views/detail/two_dimensional_view.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/algorithms/transform.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{


template
<
    typename GeometryIn,
    typename GeometryOut,
    typename TagIn = typename tag<GeometryIn>::type,
    typename TagOut = typename tag<GeometryOut>::type
>
struct transform_units_impl
    : not_implemented<TagIn, TagOut>
{};

template <typename PointIn, typename PointOut>
struct transform_units_impl<PointIn, PointOut, point_tag, point_tag>
{
    static inline void apply(PointIn const& point_in, PointOut& point_out)
    {
        detail::two_dimensional_view<PointIn const> view_in(point_in);
        detail::two_dimensional_view<PointOut> view_out(point_out);

        geometry::transform(view_in, view_out);
    }
};

template <typename BoxIn, typename BoxOut>
struct transform_units_impl<BoxIn, BoxOut, box_tag, box_tag>
{
    template <std::size_t Index>
    static inline void apply(BoxIn const& box_in, BoxOut& box_out)
    {
        typedef detail::indexed_point_view<BoxIn const, Index> view_in_type;
        typedef detail::indexed_point_view<BoxOut, Index> view_out_type;

        view_in_type view_in(box_in);
        view_out_type view_out(box_out);

        transform_units_impl
            <
                view_in_type, view_out_type
            >::apply(view_in, view_out);
    }

    static inline void apply(BoxIn const& box_in, BoxOut& box_out)
    {
        apply<min_corner>(box_in, box_out);
        apply<max_corner>(box_in, box_out);
    }
};


// Short utility to transform the units of the first two coordinates of
// geometry_in to the units of geometry_out
template <typename GeometryIn, typename GeometryOut>
inline void transform_units(GeometryIn const& geometry_in,
                            GeometryOut& geometry_out)
{
    transform_units_impl
        <
            GeometryIn, GeometryOut
        >::apply(geometry_in, geometry_out);
}


}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost:geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_TRANSFORM_UNITS_HPP

/* transform_units.hpp
C4bd9YrNDPp4PyMnR4PVXYaA+1YJKCw+O6QzXbCCf/7FexLzqU83g1SCMiWirM4yHHlzneX11VOnrFJrwa2+HyF405xyplMY7k3AWRRc7PhhQ02k+VatBcsU+RHDNSDv8r3De4KyLURDWwqjKv48IiF6IjSXzlWqnv27xUbAzjMCuBIsipPAZsE7qMLis+Z7hCc58HyBRr54jR6pNMzPBcAeGiuQ63tU06vVIUV01Z3JHsq5/r62hTcSmqAfD55ypZ5Q34734gMy+nt2Ad8xIX/kRHrp5OZRHATAs8OaerVUoyYjzWoCr0TDI9siawnfl1dQQiz/fauzyL54Uqh/AiMOR2vm1dzIfkCFXNwJuFtyGPxuzZN6p31mm4iwjg1U9vKtVOeH0Sn0vp1jUYIysTA8j+S6vNxQHfqDBhwgR6C6RDJWI48zdKn0SHBxTb/+mhNAI0SbfQTf4hcKwCsLkG8YlAHKE49Edr+P5SoUwasgMUly1vSsaQiUjZDFd2qRyYsPLR9sNwOfAuy0xXLQEUkOwSfcr5X+cBHOwbBOx6Iglf+lrXZAZPT4JA==
*/
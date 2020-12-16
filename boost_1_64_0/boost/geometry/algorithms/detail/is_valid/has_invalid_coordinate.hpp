// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_INVALID_COORDINATE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_INVALID_COORDINATE_HPP

#include <cstddef>

#include <boost/type_traits/is_floating_point.hpp>

#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>

#include <boost/geometry/util/has_non_finite_coordinate.hpp>

namespace boost { namespace geometry
{
    
#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{

struct always_valid
{
    template <typename Geometry, typename VisitPolicy>
    static inline bool apply(Geometry const&, VisitPolicy& visitor)
    {
        return ! visitor.template apply<no_failure>();
    }
};

struct point_has_invalid_coordinate
{
    template <typename Point, typename VisitPolicy>
    static inline bool apply(Point const& point, VisitPolicy& visitor)
    {
        boost::ignore_unused(visitor);

        return
            geometry::has_non_finite_coordinate(point)
            ?
            (! visitor.template apply<failure_invalid_coordinate>())
            :
            (! visitor.template apply<no_failure>());
    }

    template <typename Point>
    static inline bool apply(Point const& point)
    {
        return geometry::has_non_finite_coordinate(point);
    }
};

struct indexed_has_invalid_coordinate
{
    template <typename Geometry, typename VisitPolicy>
    static inline bool apply(Geometry const& geometry, VisitPolicy& visitor)
    {
        geometry::detail::indexed_point_view<Geometry const, 0> p0(geometry);
        geometry::detail::indexed_point_view<Geometry const, 1> p1(geometry);

        return point_has_invalid_coordinate::apply(p0, visitor)
            || point_has_invalid_coordinate::apply(p1, visitor);
    }
};


struct range_has_invalid_coordinate
{
    struct point_has_valid_coordinates
    {
        template <typename Point>
        static inline bool apply(Point const& point)
        {
            return ! point_has_invalid_coordinate::apply(point);
        }
    };

    template <typename Geometry, typename VisitPolicy>
    static inline bool apply(Geometry const& geometry, VisitPolicy& visitor)
    {
        boost::ignore_unused(visitor);

        bool const has_valid_coordinates = detail::check_iterator_range
            <
                point_has_valid_coordinates,
                true // do not consider an empty range as problematic
            >::apply(geometry::points_begin(geometry),
                     geometry::points_end(geometry));

        return has_valid_coordinates
            ?
            (! visitor.template apply<no_failure>())
            :
            (! visitor.template apply<failure_invalid_coordinate>());
    }
};


template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type,
    bool HasFloatingPointCoordinates = boost::is_floating_point
        <
            typename coordinate_type<Geometry>::type
        >::value
>
struct has_invalid_coordinate
    : range_has_invalid_coordinate
{};

template <typename Geometry, typename Tag>
struct has_invalid_coordinate<Geometry, Tag, false>
    : always_valid
{};

template <typename Point>
struct has_invalid_coordinate<Point, point_tag, true>
    : point_has_invalid_coordinate
{};

template <typename Segment>
struct has_invalid_coordinate<Segment, segment_tag, true>
    : indexed_has_invalid_coordinate
{};

template <typename Box>
struct has_invalid_coordinate<Box, box_tag, true>
    : indexed_has_invalid_coordinate
{};


}} // namespace detail::is_valid
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_INVALID_COORDINATE_HPP

/* has_invalid_coordinate.hpp
hFe3BY5bt0dbJI7ra+63FeuXzyPOcrTleTnviGx2Vua4ZSdwGl3HAzsPpLK8RZyzWKH02Qfrh8MjB6kR4PP7Ls7vKHlgPCw/W6DXAJ31EWGOnON0/wCtD7q4+ybzg7a6eHzP6pkxPH4/y/dOc/H43e6rKTxdEYDLUgP8bYizJB698yJ+K9fj2bHw8T1a58Tx0OYj4PlY5/H8fKwHzuDI7sSwVRi7145jwriMMHdc1s7Dxcpoo65D3E54GXQhXnedbYuAp1iez9O4TZ+lvR3rZt20dyBeN+0+wsW0dyJOaTdw9yvW1UJmo7c2e/x6qZ4muc9N9mzUU4cWfzDgIejBxRv1HXCQtCT5jhN4nmifPPy3p7c3kUql+xKp3uHk0Ii9d4V8scRxffGerSIHDIn6/nuBQ+vgUUccg9D7ypSexEObtbxUi8yLz1sPafvy80dppjRHjI/FtS8qw4wUl+XsR5uaN72DhiOnZ3kPi3iz9Xi0Nxv7G36Stm9CaV8A3Nl639q4/Qf+3oRl66U16jTadzRnB8Eaugsf0yoKd+bdX0wrv9V9y0pNOhpsAjB3zpnK7rKlcQxPc5JPkcJDxti9ykudOOj9YZP+pBsezI6wgotN5tlY7UIPU7PRFLZIOOQJVNxO7y4/eSnH1LOvQS5TybEXGSiegOKBNDB/S8xYCeKBMM5+646TrSy9I5XoGe7dne7dO5TeOUBx3ozhIkXF2+gy2i59mr1Qz30jplKHh20t1YVqPR5UhUWnHXv7Za4OD5tmsp/DxKMroGJzEpeIHGjoG+53B3XWCjtEX/8N1n9J7dsxMpwQ5gsEDp8veORWH+dzEpcCrppRvmRn3oxcvSAn3TvA8vsogefvn/c5fP/85UIcaC+UzmOAA2sNMCT1H+RcGRuzxuPiY7fHQTxBNp0L2Fj3Ci3D91a5jN4Kc7n43pfhPhFl3j1/D2LydAiLGPCkXiyeWoX5lSfbsXKUAvgAKo+noD36xYoDX6uDZ4g8d0/ss0QOVgCT3nNEDq2xx8ZTss5hnf35W3Gd/X7HgK/X51av1LIHKlkDd/VgfSpn/bcSBqkusXJ92Va0BwjRZPf3RzouZfNhqOT4QSzMqwGH+VuFNTi2hxAZqU83sl56B+YqSGdoePDAQTxUrxr3+JV6wKX6U59bcM7JvnbeeN0xw+stF6depTEpx/lY6upY2Lh/f5Puq9XNC8vHWy2X4uNxvR37YYuK6xrLpbgaX9cr1/HZjxB99jshTUzJ94LUP5c4bv/8XXI8oFl/jsPneXMcIkfVv3fr+jcN3OHG6990zat/U6Je3qu+h+Z8huD1i8E+b9+LxHH3vdwgxuOOHz6gbcjjMc6H0Dbm5XwEfYbPabjdL8OJZ8mGysK4k+yDDi+76wynN8dxeQ2UcHcN9KNbPRzn1yW7ojzY9uBj2B64sDDv+nGJh02Lty/LJS3+Dk6t30rg2eHFom4/6fTJcRWW96c+J+D8bvIvuDg0GSpx+uYvEU5ddYzGxvEV4NSC6aB0KFCkCG28LwnvXIrn8C8Xx1ffjI2vYCBi8/NtnWe4s2x4aDAVPWuFdY7GRxw3IySut5ticeAtNxTHdyQcp/gX4ITOfNu9T/U56hrsAusfLVsqc8LYmtWTJR7esEDvbwl5UomtrIvb50LpPNymGCfMO3N53zdxYJ86M037oeAuGQfLZpgtf+2BhNGj94RfZ9J1H5+nN8F0uqhns/N9Oq+0yedtfsR4aNW5fC7i1cIM7DeVeGT9+HAr2orAo2jobiiOq22+cGAO7VHCK6W5w5bl340UWo7KB60bmThCLw5648xyauVydPkzfRWt8+M9S6Z4eD7vCr7NUT2+Ml8=
*/
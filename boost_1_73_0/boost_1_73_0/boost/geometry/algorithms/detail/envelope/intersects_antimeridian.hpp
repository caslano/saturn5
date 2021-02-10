// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INTERSECTS_ANTIMERIDIAN_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INTERSECTS_ANTIMERIDIAN_HPP

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_system.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/algorithms/detail/normalize.hpp>


namespace boost { namespace geometry                  
{

namespace detail { namespace envelope
{


struct intersects_antimeridian
{
    template <typename Units, typename CoordinateType>
    static inline bool apply(CoordinateType const& lon1,
                             CoordinateType const& lat1,
                             CoordinateType const& lon2,
                             CoordinateType const& lat2)
    {
        typedef math::detail::constants_on_spheroid
            <
                CoordinateType, Units
            > constants;
    
        return
            math::equals(math::abs(lat1), constants::max_latitude())
            ||
            math::equals(math::abs(lat2), constants::max_latitude())
            ||
            math::larger(math::abs(lon1 - lon2), constants::half_period());
    }

    template <typename Segment>
    static inline bool apply(Segment const& segment)
    {
        return apply(detail::indexed_point_view<Segment, 0>(segment),
                     detail::indexed_point_view<Segment, 1>(segment));
    }

    template <typename Point>
    static inline bool apply(Point const& p1, Point const& p2)
    {
        Point p1_normalized = detail::return_normalized<Point>(p1);
        Point p2_normalized = detail::return_normalized<Point>(p2);

        return apply
            <
                typename coordinate_system<Point>::type::units
            >(geometry::get<0>(p1_normalized),
              geometry::get<1>(p1_normalized),
              geometry::get<0>(p2_normalized),
              geometry::get<1>(p2_normalized));
    }
};


}} // namespace detail::envelope

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INTERSECTS_ANTIMERIDIAN_HPP

/* intersects_antimeridian.hpp
k8eZzYFsuYrBgkSDvKMNtrlOSHajaGxao5WmGrvQsKyhaSx1TBU27z1kBAkj5GN4vaf5FANyIdZILypXjEYUwBGOxChtAW+dQj0bafLJJlNL4PzIgBTRGbJMLTPiRdFE5JTIZYtm4zPABAmKFHbTgAKcBVraavbLiObPGsZKSP4On9MS5ejP/pLqxRPgo38NeFJE35vib160cCw7h5V0+KjGolqidznoX00+jAaTvvN6ePqxJUy0ZnHYPGY5WNqIygSLLJIg2/Qc23YLgJxOfedddzyeXIzeO/3RaDgyY77u0B/+AXEIVMPsMBOsYTR3jlps4T5rdyVqfQ78L+xi0KtW/ky2NQs9eRCJy0vNSyvnbffXq/dvncv+VXk0OYoH49SKg8Jv5am/E23jBY5L47nhxx/LTWZP7fbxplgWVB79Nf9EZb2iSdWWk+HQuRxeneeVj84vBPrYE84hIQWeTpfLKE4yalGWn73XVjEYBYKwTOLjss0OxclJRelmSbMDC+D0PyrPtc2MFumQH4L+MGxSAYDRjKIAHFFeFaokqY/i4PpUVw3PK2tfN8Lg8rJ/3r1kG+TnAjaGAQYCdXaIwf3Qnmy9ssz7HXxYlWuvGChVqdwU5HmqUDlN5aWvfMGQBuV1atln7yroiJ7d
*/
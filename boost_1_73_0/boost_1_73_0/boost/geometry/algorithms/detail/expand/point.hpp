// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015-2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_POINT_HPP


#include <boost/geometry/algorithms/dispatch/expand.hpp>

#include <boost/geometry/core/tags.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/expand_point.hpp>
#include <boost/geometry/strategies/spherical/expand_point.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// Box + point -> new box containing also point
template
<
    typename BoxOut, typename Point
>
struct expand
    <
        BoxOut, Point,
        box_tag, point_tag
    >
{
    template <typename Strategy>
    static inline void apply(BoxOut& box,
                             Point const& point,
                             Strategy const& )
    {
        Strategy::apply(box, point);
    }
};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_POINT_HPP

/* point.hpp
Q6yv2yC8CLC336Pi0fzsrNqvgaHBWsu10ePhmNrRwTs/CsnH9/0z28oipr3BmVNr8LnEqduIuCCyyuwa7fE4YAn7b4p0KtDWbDq3ysRRMOSm4TJZE7dXLUdqE3hJw0vTFvuVeTS8/6hnNS4rb7Oq6P5eSWbelgj9BAmd+GlzRu2DXNyAsKq7WPy0irU1FXE8y7pGGIHRjQWkVkgOwRAAEjEKEEMbjvs75a5yTEZf4X2VHusXIL0rnf7m3lJvKIyJTM+xqUqEk2NNp+NpYUuxeVit6UsX+xG8sARMfifUdnmY4p0mLEGjL/N4DHcFedHvBesYYaMfLcwFg+FdESOJY1VbMKxtTDHAwb+ct987Lw5evvnh4Oqt9/bF6zdvXr8qSm899Yp00PiUSu34Yzbx1XxmmVIm9dKy4g5nonhrPfISpmhlWz0yJ9eBZ5pm8Av1U0fZ0VYN18xWWk1X35KbjW9FH61GCf/TRF3RZn0rLhNsrjo5RzYm9OWgQQ11Y3vt0H61jvJUyu9opYgV7pItE6Z3lXN1LJOuklY+3vh5QD0qhXvJmbTS0z3R4k5jD9hRH0rlxpYNxroElJOrHDzzmTN+73yyPo2nFxWdeWXKCcYazUgCGy+6437of7YcnOtPhht0RUtTkbGT7QzG
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ASSIGN_BOX_CORNERS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ASSIGN_BOX_CORNERS_HPP


#include <cstddef>

#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/algorithms/detail/assign_values.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{
// Note: this is moved to namespace detail because the names and parameter orders
// are not yet 100% clear.

/*!
\brief Assign the four points of a 2D box
\ingroup assign
\note The order is crucial. Most logical is LOWER, UPPER and sub-order LEFT, RIGHT
    so this is how it is implemented.
\tparam Box \tparam_box
\tparam Point \tparam_point
\param box \param_box
\param lower_left point being assigned to lower left coordinates of the box
\param lower_right point being assigned to lower right coordinates of the box
\param upper_left point being assigned to upper left coordinates of the box
\param upper_right point being assigned to upper right coordinates of the box

\qbk{
[heading Example]
[assign_box_corners] [assign_box_corners_output]
}
*/
template <typename Box, typename Point>
inline void assign_box_corners(Box const& box,
        Point& lower_left, Point& lower_right,
        Point& upper_left, Point& upper_right)
{
    concepts::check<Box const>();
    concepts::check<Point>();

    detail::assign::assign_box_2d_corner
            <min_corner, min_corner>(box, lower_left);
    detail::assign::assign_box_2d_corner
            <max_corner, min_corner>(box, lower_right);
    detail::assign::assign_box_2d_corner
            <min_corner, max_corner>(box, upper_left);
    detail::assign::assign_box_2d_corner
            <max_corner, max_corner>(box, upper_right);
}

// Silence warning C4127: conditional expression is constant
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4127)
#endif


template <bool Reverse, typename Box, typename Range>
inline void assign_box_corners_oriented(Box const& box, Range& corners)
{
    if (Reverse)
    {
        // make counterclockwise ll,lr,ur,ul
        assign_box_corners(box,
                           range::at(corners, 0), range::at(corners, 1),
                           range::at(corners, 3), range::at(corners, 2));
    }
    else
    {
        // make clockwise ll,ul,ur,lr
        assign_box_corners(box,
                           range::at(corners, 0), range::at(corners, 3),
                           range::at(corners, 1), range::at(corners, 2));
    }
}
#if defined(_MSC_VER)
#pragma warning(pop)
#endif


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ASSIGN_BOX_CORNERS_HPP

/* assign_box_corners.hpp
H6ZAc7KguVKMszJKviyFs0q+HHhsFDwWKlk3geZJpLsZNFsU3vtVnk4F3mmC961Cvg8r+baW06fkOwM8zlRpPa3K6qPAO6t87HmtYvvXht/HgnTpt1g7U/KcC7nPgY88D/KcL/JeqmguAM3T0OsnQbNN4Z2j9Hoh8D4NvGVFjEPrumi/7JKVXe70Yp445Pli8L3lvxoToYfbM8R7NT5DNDQPk8sO2okNxq0FLoZQcm8H+l0uXvKZ6+VGmBNk2m7XC9z6QxPWCj4rfdu7Wm9zZXCLXt9DGXxO1lfhGy5Xtn1FOX3Ktq8Ej88LG7tB9Ge+oOzgi6C/EfbyJdB/GXigYRmuUTJcW06fkuE68PiK4LFNr2GBxoNtfx0031DyecpOrwfedsH7eJHX3UV9+o6D837ob1P4BvpSZq6Ovhx9cj/0jRQHXFpXd7jj8+DeVI41ePDdGLEG/z2Csx/S8aSnWynenAObhTPa6zyPzyAZO62we1X0npMJ3u0EmBFZP7PD1vKyw9ym3gkdQHbeDyj3AyxSbeVdLDfkkOlT/I9UPMkfov8xyiyH9PYpDfB/UD46vfuhh12hh1mkB6lbkpHKIDy/+4DSP++BEDgPElyGz5DpYo9E9PjCvenjV2QOkVYNfXmEHismjs7XL5SeDJ2Mf4zlg15h24/qcQbR/ga49NfiPk5/ZbxO+0kRPzNCtt8p2WYq2X5vZSkhWYL69IyS69lyRytt4w8EszYMnUxAmWYlf7Lh50X5zRR4snxeFDJS+XP8TMj4J+YB/UesA/xZppMH5y+ME9i7xiGDDJ3hnMw2Cv1F0LzOfLkMGYd+W5w3GCfQZ1btMXuTdYo9bkpfM6HTtwXeTODxvjKh+38yniwf9JkFv38HslG60XkkZUnZwI9+q3OT4yoC3zrA+/3cN0OdS5lAuDh/E4VLMuk8TfImEo28q4XSfwW2QzTwDcK+dyZ8O89YIdobLQvB30PxiFN5p3oAHruDB9IjfxjgpuDry4BbDlzoIpS3KRWQU+iikmDLCu/nMAuIakdeZBz3P6tVnqdSWLaxMchaA7xF+dcF6ZSgGJMKkBzXTVf6MX2qPQgmy+O9SHPPQLbS60W/pVbxMPR7Kx4zwGOmwt07Ancf4O5bMeZ5EjqYucnPIQNk/maDB+oBtVcuPZPW++ivrHtzkO7+oFmWd0yxsNsM8e34XvYqVZSeT39/RaCzAyP0fpDSw1zIc7DDdeciFN38CP0dAroPhGxJ4RH8UOAtBJ71J5BlfYQvXgT8wyPKUI/pjwTuURH51PIuBm6drH8oqxa0n1xeov7Vg65B5XO76rs3AW+psgXCQx8OdVvYQgtolhW0QaxYCCMUEK7TrY4HnxVcXhH0OWk8RO1KIHMWZwVXIP22grSgV7THgrYDtKePk+vrKWua/Z44R+hg5vUUigj2lE92cLcA/5pca0/ZTblpL4DFPGPtjnavCuPjydeY1/3EXUSzCD7bwuMjEr4fwedaeN9wCjwPINhCguERVs/A5hFssZ1vA2PgLiB4s4ODMfPAfjHHhMeZBF/j8mZ31fuwddBDIpth2CDw4n05mpRFJPgcQfEpNzfrC2ThRxN8E+AQiNPdCvgwDaX9sw5LCH4O4HS/ymapl22AG834ebrEwZAph9tI8KvMWobQVzPBrkMZpuMun8cQbLuD9WXTQ56fj5u95FB/t9It8nIn4rR+2ynuXi+RjQ/jZTbAOwn+kIXbEbb1o3tQRe8iuP/vV++6jSyhNjLwo6sqgvHvauVr1phyVr5mLerGccBlHsJ/nAAa0/aalD4ImhOBNxC688RWD3GnzsgwakxQj+waFKChe7noST+Ag3McVK8A8+8=
*/
// Boost.Geometry

// Copyright (c) 2018-2019 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ARITHMETIC_LINE_FUNCTIONS_HPP
#define BOOST_GEOMETRY_ARITHMETIC_LINE_FUNCTIONS_HPP

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/config.hpp>
#include <boost/geometry/geometries/infinite_line.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

namespace boost { namespace geometry
{

namespace arithmetic
{

// Calculates intersection point of two infinite lines.
// Returns true if the lines intersect.
// Returns false if lines are parallel (or collinear, possibly opposite)
template <typename Point, typename Type>
inline bool intersection_point(model::infinite_line<Type> const& p,
    model::infinite_line<Type> const& q, Point& ip)
{
    Type const denominator = p.b * q.a - p.a * q.b;

    static Type const zero = 0;
    if (math::equals(denominator, zero))
    {
        // Lines are parallel
        return false;
    }

    // Calculate the intersection coordinates
    geometry::set<0>(ip, (p.c * q.b - p.b * q.c) / denominator);
    geometry::set<1>(ip, (p.a * q.c - p.c * q.a) / denominator);

    return true;
}

//! Return a distance-side-measure for a point to a line
//! Point is located left of the line if value is positive,
//! right of the line is value is negative, and on the line if the value
//! is exactly zero
template <typename Type, typename CoordinateType>
inline
typename select_most_precise<Type, CoordinateType>::type
side_value(model::infinite_line<Type> const& line,
    CoordinateType const& x, CoordinateType const& y)
{
    // https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line#Line_defined_by_an_equation
    // Distance from point to line in general form is given as:
    // (a * x + b * y + c) / sqrt(a * a + b * b);
    // In most use cases comparisons are enough, saving the sqrt
    // and often even the division.
    // Also, this gives positive values for points left to the line,
    // and negative values for points right to the line.
    return line.a * x + line.b * y + line.c;
}

template <typename Type, typename Point>
inline
typename select_most_precise
<
    Type,
    typename geometry::coordinate_type<Point>::type
>::type
side_value(model::infinite_line<Type> const& line, Point const& p)
{
    return side_value(line, geometry::get<0>(p), geometry::get<1>(p));
}

// Returns true for two lines which are supposed to be (close to) collinear
// (which is not checked) and have a similar direction
// (in practice up to 45 degrees, TO BE VERIFIED)
// true: -----------------> p -----------------> q
// false: -----------------> p <----------------- q
template <typename Type>
inline
bool similar_direction(const model::infinite_line<Type>& p,
                       const model::infinite_line<Type>& q)
{
    return p.a * q.a >= 0 && p.b * q.b >= 0;
}

template <typename Type>
inline bool is_degenerate(const model::infinite_line<Type>& line)
{
    static Type const zero = 0;
    return math::equals(line.a, zero) && math::equals(line.b, zero);
}


} // namespace arithmetic


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ARITHMETIC_LINE_FUNCTIONS_HPP

/* infinite_line_functions.hpp
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
*/
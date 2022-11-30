// Boost.Geometry

// Copyright (c) 2018-2019 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ARITHMETIC_LINE_FUNCTIONS_HPP
#define BOOST_GEOMETRY_ARITHMETIC_LINE_FUNCTIONS_HPP

#include <boost/geometry/arithmetic/determinant.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/config.hpp>
#include <boost/geometry/geometries/infinite_line.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

namespace boost { namespace geometry
{

namespace arithmetic
{

template <typename Line, typename Line::type Line::* member1, typename Line::type Line::* member2>
inline auto determinant(Line const& p, Line const& q)
{
    return geometry::detail::determinant<typename Line::type>(p.*member1, p.*member2,
                                                              q.*member1, q.*member2);
}

template <typename Point, typename Line, typename Type>
inline Point assign_intersection_point(Line const& p, Line const& q, Type const& denominator)
{
    BOOST_ASSERT(denominator != Type(0));

    // x = | pb pc | / d  and y = | pc pa | / d
    //     | qb qc |              | qc qa |

    Point result;
    geometry::set<0>(result, determinant<Line, &Line::b, &Line::c>(p, q) / denominator);
    geometry::set<1>(result, determinant<Line, &Line::c, &Line::a>(p, q) / denominator);
    return result;
}

// Calculates intersection point of two infinite lines.
// Returns true if the lines intersect.
// Returns false if lines are parallel (or collinear, possibly opposite)
template <typename Line, typename Point>
inline bool intersection_point(Line const& p, Line const& q, Point& ip)
{
    auto const denominator = determinant<Line, &Line::a, &Line::b>(p, q);
    constexpr decltype(denominator) const zero = 0;

    if (math::equals(denominator, zero))
    {
        // Lines are parallel
        return false;
    }

    ip = assign_intersection_point<Point>(p, q, denominator);

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
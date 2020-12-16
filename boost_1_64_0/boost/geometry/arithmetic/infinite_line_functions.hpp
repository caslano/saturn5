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
LNPKshw4GptIPxa+A/Kpg6vpcjTEO6BvPgVZiH/8qZ/rbZ3o75RFoMsr+sGlGdyaqNVIYelfpeYnWRV2FkrPla6RSTZfIi4wZBW4R1aBiSHucBFT3kaEbPGNmzhooURfE/EuQ3oWW/VxR/U5CfJcPToRVgF+p5snRBVdkUrr1mRZblyhVU0dLh9/jL6lP0tf0vdEODX8/UiGP2nxfXABpIa+09TQ58TSVg17ibSwZcGQ579cRjIRURRH3lHQsIjdF421nV7/5mclyvXkeGuW2+pLUmptOZy9B/CNdgWuz8LZrSu4UZJxrhBxjmwhzemHj6Z5s6JH023Zat5H5eidI6rm5FjrT4nR57/3RsvXCO2lx1Yc4KSUgLOXYd2a21cc4HzUV15TUVewM5TkJ1PEJ2ZujtYmicLResl03HkQfsfVNHl8epUElUsIS5HTCDkaTz5cSaocUFzkkkNsXPGKFP+cegonaRHkx6ETADSTW0InAKHvnWPxPSRjAU8CtpR9fDLKK49xfzf+Hl3Dr5klPzlIsmMjueKANOga7gTzt1V1boWupyYN3yLKKfCFdXHfwBc9r01zz6gTNcI40J0yXbqTo1KKFGe4v6xqa+R+dhTVbJkv4SSrPyIYGzl/5WUnWXydlPbXJPfoqaiNsmZEhTR5a/0xynP9z0LlwSwCWpiqVYpKfeoMK9S/nstzNnW1OPf2g8Hjj0eDVXoeUQG3HeU4E21Rs3bLmOCpSg47VHJ0KNWN9WjaMzL16JAOenuODlUWLJNCA8RwVFsFamGtWh+tDa2P4haIo1of0YLTlXBC7L11Vt+wwzv1NVdFd+qD57BTN/A0Tw+D25u0ttc2p6R3o9TlqgyYsqpseF3IwvEO7DfTZIy1HV4zIulVxi27p+q4V2Oh7/vTn+oVLdpLz6vL0YNf4g1OHfWvYXbwt+My4Xapqjg8+gZjfmgD1d7Zy+vlpgt3LzJY7scFWHOiy7i9Xm7FZKKxQ7mjxGekKYjksWbWhs/fJfpiid5BRcd9GEYa7PSNJfVyTybzkr0AZUTk7gWyQYZDkpwopo6WLeGN8aj9UyE47rD6MO4K9183qgZNKF79hPRk4aMpSj0hgXW5k7TWfY6754RSrVDH2E1eY63SUrNK8YisTrSLYuk23BwnyeCpuDBlfsXqA4vUKqw/PMbTJdSq/6T0kAUzMPfKZNLQnstb3OoEzSW7ROyriT3zYHdgVLPFny7kM4tWCZWfoxn8og/LTB/4h9XfTphH5cVdZQf1GZJJ9uQw4bI/eA0yqSB17Holo1z+cCGESUPO0sBaz1q4Ptnib2NWjpBkxibjPdECqoWF6j3RnMcHO9xTJdx05Z6K9zSLv+vagVLqseeqQ5ZpsOGZBs8B4vmKePbTnnnKcwA8M8TzVfFsoz37Kk8tMjFceaeiXZyoOUL+YN4q/cldiaINdsZ+NKko7V025xJ9hZBLUstOrUmBrNL3FR9/hyxB7cPSYsx3MizCDtSe3tvgLWvXZ4ZFX1TUhHl/hGdD3iy+u9zgVCRHVEMooPFKKM2GiRbLKZA8eZzx/8esFlBBy+hqoZwfkH5LfzsfNabdrSF36fBDI+62aPeuEXd7tPuhH4fdHdHu70Xc46LdX4i4x0e7PwH3rzyWt0qfODlCld/nTtbD+Oqz2lDR29sky3pe+L+myse+mafEn0Ca6EdnhzZ4os+D+YNqHCGcvtRbnZI/xUr6grFGl5szN2fW5mV3SfZ1xsKmxTy/udkWrONn3bELS/wrltb7L2u301XpsRp1WOtSLYPVww38prLHPYYT+Vh0eVgwiX+oTD3n6QnurPRW6dM13T1IQl1kDkAS37pcNcxzEB8=
*/
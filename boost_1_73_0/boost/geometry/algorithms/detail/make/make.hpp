// Boost.Geometry

// Copyright (c) 2019 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_MAKE_MAKE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_MAKE_MAKE_HPP

#include <boost/geometry/geometries/infinite_line.hpp>
#include <boost/geometry/core/access.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace make
{

template <typename Type, typename Coordinate>
inline
model::infinite_line<Type> make_infinite_line(Coordinate const& x1,
    Coordinate const& y1, Coordinate const& x2, Coordinate const& y2)
{
    model::infinite_line<Type> result;
    result.a = y1 - y2;
    result.b = x2 - x1;
    result.c = -result.a * x1 - result.b * y1;
    return result;
}

template <typename Type, typename Point>
inline
model::infinite_line<Type> make_infinite_line(Point const& a, Point const& b)
{
    return make_infinite_line<Type>(geometry::get<0>(a), geometry::get<1>(a),
        geometry::get<0>(b), geometry::get<1>(b));
}

template <typename Type, typename Segment>
inline
model::infinite_line<Type> make_infinite_line(Segment const& segment)
{
    return make_infinite_line<Type>(geometry::get<0, 0>(segment),
        geometry::get<0, 1>(segment),
        geometry::get<1, 0>(segment),
        geometry::get<1, 1>(segment));
}



}} // namespace detail::make
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_MAKE_MAKE_HPP

/* make.hpp
IgziKg4Gzh/vKNgF39MXHif3dNPkUaCTVO3y+z/chtwCIG59SBe8I/gUKi9NnRd1rZJVa62BytfOsMTezDtlvvL5/zjIX2Ymz5pY23m7icPHiv92Y8IzyvbGuohvs//xMr82lc4Dk9H64Vx+ggHaqj2B3gRlmaIYBI+XZ9g6K1I0l0rsMcbPRpqiNkq2D3kl415wXhH6m2xMVSU53v9BKW5vZIOSAZvvHxR8KpXGVZGmlVHN
*/
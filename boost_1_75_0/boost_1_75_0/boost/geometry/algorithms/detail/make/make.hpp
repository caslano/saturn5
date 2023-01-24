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
J/bftD3PcMda6eeGNr4OAjfxtG74PLqNHzDLp/A0DBSulxiPZX2WPKTPNmrpJaelox0QeOxzNub3xpQteYRtIsZXEJv07eTokdzILnjEiE4J0M2x9jMufM5pfoLHfgOB0V+wsiZ8oZc1+5IDnU2wvIq3CS8AmQXJ5gMqy/ksXPef81kK4TPfNPib/wXBrf+TLLs/IX8/JX93k78d8Cd2oQL8qDw83bn2C8M6eC8EHvyCzb379HJRuvOkWboB44MRunOY9F4zpjdTyUDvwgNpBsaH2Jfx8HLlS8Na44TAD75k7Z72ZfRa84Bkv0jvAegH96JIGK4UJZ8bf19o/NIwZ26GwP/5ktVt2ZfR68oEUVqG8WdmWOX9w+wxvV/G3Nn01JeUl1g7zP4y+KWhHc5DwHyZ5f35l9H7ywQsDfL9JV4/ey/zfp4IHon15u7vaP/ay4Z8myDwU57vosvR/fkK7c8nIv2ZMwJ5AuORB/CtMYMpIRtfQ/Zc5vezPQKe98B9c1nDQ9JwvgEfGTBcIKgLPFOzemcxxhb1U70AR/BBGJsnFdsHOBsohkbLC1gtsxQLyhOAAgej7Fv7/sb5M5PAk/83jZ/Tjd8hfH4zSjRVIY1nXg2vVxPe7Y3gaaRxy/6uwKxvJnYYRgCNXY10iXx+/vU3zu+9Bzy7/qbrYZAvOY4l7sanBGr/WiJ6eUN0l57/G5/bZ8BzCZz8FaX7
*/
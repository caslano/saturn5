// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_AS_RANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_AS_RANGE_HPP


#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/add_const_if_c.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename GeometryTag, typename Geometry, typename Range, bool IsConst>
struct as_range
{
    static inline typename add_const_if_c<IsConst, Range>::type& get(
            typename add_const_if_c<IsConst, Geometry>::type& input)
    {
        return input;
    }
};


template <typename Geometry, typename Range, bool IsConst>
struct as_range<polygon_tag, Geometry, Range, IsConst>
{
    static inline typename add_const_if_c<IsConst, Range>::type& get(
            typename add_const_if_c<IsConst, Geometry>::type& input)
    {
        return exterior_ring(input);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

// Will probably be replaced by the more generic "view_as", therefore in detail
namespace detail
{

/*!
\brief Function getting either the range (ring, linestring) itself
or the outer ring (polygon)
\details Utility to handle polygon's outer ring as a range
\ingroup utility
*/
template <typename Range, typename Geometry>
inline Range& as_range(Geometry& input)
{
    return dispatch::as_range
        <
            typename tag<Geometry>::type,
            Geometry,
            Range,
            false
        >::get(input);
}


/*!
\brief Function getting either the range (ring, linestring) itself
or the outer ring (polygon), const version
\details Utility to handle polygon's outer ring as a range
\ingroup utility
*/
template <typename Range, typename Geometry>
inline Range const& as_range(Geometry const& input)
{
    return dispatch::as_range
        <
            typename tag<Geometry>::type,
            Geometry,
            Range,
            true
        >::get(input);
}

}

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_AS_RANGE_HPP

/* as_range.hpp
/jtXLunqaOQi0GB5h5nys48pv/8r+NlfF6zLdBkGvcdJb27mgmuVFQz7Fh8XPv4JMaZ4Uo0pfltpPnUmCLI8VWhsA3+G5UErSQgCm3la5fsZle9nkdYfCrYvnWtWNHZ1t3CrIMJI53mVzgsqnReRzh8DPJIt0NFLQkd/Vjp6uZI+paO/gN9fgTsj1OfZkhwRvmqy7e/QOhZs8VVpi2PkbV6eeSjbX/NJEJT29nqkXAm+d+ZvVoa0IeO3Nd/4L33W3y19jn3WmzKfJHNLf1tayc2ggvceFOnvTJm+Lcr0H6JM/6nK9F+V9Kky/TfK9J3KMe/sSOXSqWSGM6JgkKWkKpBlHP2WY5zxFP5+xLmHCVVOhp2Af2ZI10hC7oFQd9hNDvo/VKqkd9xh51MGe+hxhx3CtZgjDNYkc5k01iAXoT8zqUrMGxaph2j7Nd059xqGJQuCbL87ExXqKf0O9DilStZz+l3l9LcL/TVYu0J/u1UVmMfdAf9veJUKWUqFLOVKlgrIUgZZKiFLFfAOlHXR6r8u446FS1+R8js7XI+mCr2XFtmfi7TdIuugkblG5LlG5Hm6yvMeyPM05Pm9yPOegv6Xok7WKvq9Qf8YxhszQD9T4RH/kD/fB3j7inSeF+nMrgrq/vvot6z7c6rcJ+v+/uB3QNWY7a9ufhkk9Xegkv8gJf9cpHcw8MYYX6pCU3Dhc+aLsjpE6OADSgcLquhTOjgUMi0EblPh/qN0wFaqyBjItUjIdbiQ6wgl15FV9Cm5joJcR1dFtWnDCflGymT37gG3tXWy7ozRbkbnt66+vrGzs7uhsbO+o6XdPvMN8sgY+Ix6YZf1Iu+Nyi6akNcG1J+lyGsz8Og39eXwG305SX8M6JeBvhX0ywX9S6rta6M48vGhc6ntoDtW0M1WsnYirRdQV7tAszKgoXIu6m42M6x3LXfjiq6OtTCf6EiuU2uUH11t8zyQGxoK2rK1FpaO06oZ7fJ0cL9/c1xVcf2bBXn6N8db+iCtS9xdJCmsVfI9UycIm4t5DS2dXTSealnRFeq+KDDbYBHr/kTTuLQRt5FGxcAGT4xsd5Lp9T0jeHfc5aPb5svNx40kM3zv17pQ3XGzfR2NTX4OGKDXVndRvq4XdtJXVWA8IfQUoSKuV3FlkwMqrfVIa1D3tybyPL2we3r7Hfgbqoq6C1Z1XCLgkHNY+TVKn9MeqXJ1Lom0UxG4KfWmfxq4mQhc4hfCzQF3I3B7Uf5DNt31cf3W08mm/B087p78R//S9h/NcT4QAH4KwWOAg4DfUdgkbKb2Xczr5W931f5UAZLt7hYux0JvPutyBDyiHE91/NgnfMjmz6Qb7NebbMOus2xgp1m9ub7zHPiE06VPcPmRGWH7ni986SHK1s9AOW+Frz8T5fwRQXM9j6Phw6ydJ0Zobor3wZ9l6XtcDyLu9yEyPA48u0g/mW8c+DFLn/P8e/DOkX4k6NPUDyYTfdwWK3DBu8jHmEs1ejhX1n+0eefRhzrId/OcDx1+QrTXB4r2+pOqDLahDA5CGXwK9BcWMd4oZp3BpH+RSP9i0Vf6jKr7n62iT/WVLoE8lxbytUXMvRkel6m8X6587RVI60qhu7iQ/SpF/wXQD0B3XwT9l4T9Nor8Xq3ye00VfSq/14LHdZxfOXct/BlgaL85XIr31eahnn5V1tMxxqkjIfuPb0p1U8WQY3ML6xvqyWSC8bmDJUfIo+b6svF+eUbBxqV6AMN+H4LhLIN/RvfrQsZKj9LstmlT/bNSSkD+tYUi6Mxa4zeJcqaxe9pXcXYov4nh0fklmM4v9jQFeTST9j1qz1dwvv9607a4PCfINJn3dSUEwz5mf31le6A=
*/
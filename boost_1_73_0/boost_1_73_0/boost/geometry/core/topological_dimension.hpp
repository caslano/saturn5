// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_TOPOLOGICAL_DIMENSION_HPP
#define BOOST_GEOMETRY_CORE_TOPOLOGICAL_DIMENSION_HPP


#include <boost/mpl/int.hpp>


#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{


template <typename GeometryTag>
struct top_dim {};


template <>
struct top_dim<point_tag>      : boost::mpl::int_<0> {};


template <>
struct top_dim<linestring_tag> : boost::mpl::int_<1> {};


template <>
struct top_dim<segment_tag>    : boost::mpl::int_<1> {};


// ring: topological dimension of two, but some people say: 1 !!
// NOTE: This is not OGC LinearRing!
template <>
struct top_dim<ring_tag>       : boost::mpl::int_<2> {};


// TODO: This is wrong! Boxes may have various topological dimensions
template <>
struct top_dim<box_tag>        : boost::mpl::int_<2> {};


template <>
struct top_dim<polygon_tag>    : boost::mpl::int_<2> {};


template <>
struct top_dim<multi_point_tag> : boost::mpl::int_<0> {};


template <>
struct top_dim<multi_linestring_tag> : boost::mpl::int_<1> {};


template <>
struct top_dim<multi_polygon_tag> : boost::mpl::int_<2> {};


} // namespace core_dispatch
#endif





/*!
    \brief Meta-function returning the topological dimension of a geometry
    \details The topological dimension defines a point as 0-dimensional,
        a linestring as 1-dimensional,
        and a ring or polygon as 2-dimensional.
    \see http://www.math.okstate.edu/mathdept/dynamics/lecnotes/node36.html
    \ingroup core
*/
template <typename Geometry>
struct topological_dimension
    : core_dispatch::top_dim<typename tag<Geometry>::type> {};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_TOPOLOGICAL_DIMENSION_HPP

/* topological_dimension.hpp
a5qcbkN2P17ieBxuAaPYMAqJjWsc9vR8jCFcHOdXCNDDbhP8CquJDBgA/ZA3HPiXGwhPh09/Upn95IYytYRplH3nva3BdSdL8mT8fdGnFTAZJ/DGOYc7EU/rXTbjJ0E6Da6Cm0ytLbNbBKcc92j6vtt3mLCyLKHFCa5M5UatQxfWjoqOeHgDpb97gRvZd8niaI7YMcvC8Nti8SoJMQkYJLsSri5gSoT3HYw5u9RoOC7I+qTd/rWz81FHT+tgs6fbFWOibR5rztra7cPd6trOD+bVvNX01sVfqlWMt9LfXhXqeiNLPktsc+/j4U5nr7XPUThlXIEeDunKyke/ynGx0X80MBRIUojbI08lRnpS5mKZ2liS0XZOr8NgqE9APcSct8xD8eQIdaJcpFDxQOG9OHjDUIfC/i3MOeGu7Y+Kp3EMTfsjc8SHJYwbGwx/P+Ngd08E9kfW83RbeSkLnS57yAtZHkZe3U2cFIaB6O5Vkm5oRyL/fBJ3VffRkq9RKS/4TN5fKTCglwwDFQCa5yftU7p+SU8x/FjJP6WJpqxmiSTb5IutuhFGygcDJMkNunLfHO0JzpxK4RpZYChNtDLoNdXiIInPG5ZCmjqvi5zlA91pHZ7il80ZZQcNUpXwmHUAKPK3MDO1gqlPnwku
*/
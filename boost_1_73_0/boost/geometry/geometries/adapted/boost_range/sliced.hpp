// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_SLICED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_SLICED_HPP


#include <boost/range/adaptor/sliced.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Geometry>
struct tag<boost::adaptors::sliced_range<Geometry> >
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_SLICED_HPP


/* sliced.hpp
TObEqvT+3/hsAXMVZj1m/Z+MC8xSmIVFZnnuTcUqZnfYyXNaMct1W9mfGYUa1pCStifOMp4weS+LN7a9wD0Nk/tocqremybAZC793P6pP/MaFiVzonO7guyFYfI+0yy9cljnFdsdsLIXn9VgpsLqf3q/kvGEFRWWNOznKs69kGHdvXDt3FqeATA597LGR6/wnQBM7oeJ064eZlxgMid2np/BeFaBOQibdDPJgjkIk/GsUaoI
*/
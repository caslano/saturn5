// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_UNIQUED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_UNIQUED_HPP


#include <boost/range/adaptor/uniqued.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Geometry>
#if BOOST_VERSION > 104500
struct tag<boost::uniqued_range<Geometry> >
#else
struct tag<boost::range_detail::unique_range<Geometry> >
#endif
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_UNIQUED_HPP


/* uniqued.hpp
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
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_FILTERED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_FILTERED_HPP


#include <boost/range/adaptor/filtered.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Filter, typename Geometry>
#if BOOST_VERSION > 104500
struct tag<boost::filtered_range<Filter, Geometry> >
#else
struct tag<boost::range_detail::filter_range<Filter, Geometry> >
#endif
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_FILTERED_HPP


/* filtered.hpp
qgMPEhKHHjG6QQpujbhhyupRfb2A4nKNK3m+0mElvwCScKU229thFe+CtXM1soLzxP8kP2yaGs8wGJ9i7xh/Lix+KCw+MKpjvCgsnh7TMT7YjONhPPhNk8MhAw6fOxQo9EUqsc/kv4ONFXfXpSBxQ3wOZJ2Qn2YeAdkI8ltBrzz34hHr7yCTFXq1tDcN5BsgB4F8E69X5KeeeCf1MkjcKtaDxHPEKyBx090Aco5Crui9tQr97ZoXnb4eAIkmwXo=
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_REVERSED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_REVERSED_HPP


#include <boost/range/adaptor/reversed.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Geometry>
#if BOOST_VERSION > 104500
struct tag<boost::reversed_range<Geometry> >
#else
struct tag<boost::range_detail::reverse_range<Geometry> >
#endif
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_REVERSED_HPP


/* reversed.hpp
VYdTpsM43Uo3TVi19BbFzNvnubJhMhN5GJQjOC9NcZlU+1LBt4V/vZ57ZN3e5aCs2Q0cerR3xZCo3OMFSy04UislY5G2yY9Q4cXSQyWOORV054ow0ScuIK07JVf4Tz4Uu1G51XH5PGKepofJmOKcnXZGIu1K5CPytWM8qsiHosfzQMSydFh3YM8WXTdd+nci9CvVOE13NMI8y5jmzJeKTOWlN54p3zb/cOc63iWb0uTyNQ5/7tPInSPXGyCTFbCflObjESUwEotAm+/4059gDcRvsBlGFmIUBneYU8azlsbyuhzmtInkMzRc4v1QduelOg+QoPEM1F9auM9DpHj2QhrFXmnDfKaQ3H3bbfloou3MowtPYTQjB4KyWAM3vtS9BJ/48GJeklGxeDuQWEWT1A8I8v4Gp9GOAp+Rddzi3SiTZ76r2jCcE45qoyxFO7dR4598YrZ6tBRQQPHrlIgHUoUzFb5sipzfbaYfeaVywSJh36kIObetseyILHoS8+1C2vwz7NNQEiyVt0637XC5qksQ4rlycKXkaIZgzTxlkQTheUoyN1bERZ1bo7HdNicjdQiBq9GtN5wNHroCD4axy/N26B/y4K/iGyeAmla/NNtftN9jqBmzTUs1MQRCMcWSim8RCra5uVnK9Jxg
*/
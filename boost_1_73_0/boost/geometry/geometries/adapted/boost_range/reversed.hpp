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
cU8HG+73Uw6Z+voFG9Yz4/g143hW4f8oKqzLieY/2M8r1sTY6CTrvHLN100qRuabaUFDc/9j317OAVZSmO3nyu5cI5iPsJdHp5bnHGBBwlbWejGcawSLEFa32bNNXAdYiLDkv6z1n1fBiglrHnKVee0ZYrgfrPoZTWEPHQIX1jDdrimfZWAyJ3w7haawv4Z5CDOd9G8z7j9YEWGfQy2Gsg7CLITdizlUiHUQ5iasRux0xnoH
*/
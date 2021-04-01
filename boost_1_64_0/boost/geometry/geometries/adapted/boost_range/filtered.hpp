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
o0CA7Sc5FKg/6mowQDBUEYuYRdqD41yMIHEGG86Io0zq6CHUkSVOLeJXfhFwNbijirIGeH6NZSL9ZeeJt/y35zdQcVE1iCE1d/PbiqyWLhqL+Z3yFM8YG3AF+0v2hpEHj+XVMWiAS/lT/6hn+hWvN6YcOzKfna0J5vqhxYC2Xum/K7kqQm4R8f8+2f96G470Fwtvqdvf86Q7WCB4jsh1JZInD4ux+Jqq4wAOtwdAY28Kb+ADh3zWeHy70ZrKBEVIdG8kuZuITuRGScXvQ4FV1msphU2lmeW8cX4u55/6WB+gKUIV03ddxurM9T6GoONUrudukurB941zzqbwa89Vd3VzEwQOnRjjz4KU2dwd+ZBu58IsxqmbHU+qsk02EFM6YR7uirHDRYQyUxqmqp2Bh6CggTya6YEUMRmJNaBgsa1+kgcTQmKQyxtRkdW6b0tkxx8IPz0m0e4FGh6KmoEA90cW9Z+gbhv6IXeki3PJv+wqyhgg7ka4WbbMNkeBv9ImmBChfXE4wn6gMH21r9YiXDpjJg65ZuHwwaqusflv7l3n9vXH5yjpDLKUkw==
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_STRIDED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_STRIDED_HPP


#include <boost/range/adaptor/strided.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Geometry>
struct tag<boost::strided_range<Geometry> >
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_STRIDED_HPP


/* strided.hpp
BhJvVWGMei8A2QhyEMidIIeB3A1yLMi3QOIZ7mPsJ8h/YrkgPwF5GOQ+kBfDPD0A8jcgPwCJd+ww1r2zQf4D5DyQH4JcCPKQIr9lUCqsbxlgKF4UMitmVsGsipmXWTWzZcxWMNvA7FVm25ntZPYus/eZ/cAswCxBsZimWOxCZinM0pldySyb2XXMxjErZFbOrIKZl1k1syXMljGrY/Y0sy3MtjJ7i9k7zA4x+4TZl8xOMgswU20W02wW68oshVk=
*/
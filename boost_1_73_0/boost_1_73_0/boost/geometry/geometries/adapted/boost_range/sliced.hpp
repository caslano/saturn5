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
uSDRXeI9IJtB/hZkK8h7sV473lCBXUHCgPdeCiPrPpBXg7wf+wNyAUg8yj+I+UEuBfkjyGUg8S4B40kgHwbZ3Yz3MuO43S8HiceER0AWgVwBEv9y8lGQeFxYCfKPIP8E8k9mfLUZfy4aT6XCW2/Gt5nxRjO+04zvNuN7zPjbZvxdkM+CPGDGPwD5Ekj8jHU9yKMgN4CMjpH96QLyNZD4Ie6bIK8EuRnkEJD1IAtB+kGuN+N+M453RzBmvXFwJts=
*/
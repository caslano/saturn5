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
cBsv89ysZcKzxOO0LppKRhF/NHvzEizRNPArYzBAB31YN4tKiLGUKsTXgQcPUYhupUJ0H0Mh7iBFRnch4hRK9XjRYM+wc4O19avAvIqO/1X4TesI0i9Yl9cfSgEuq32AkvhvlcR0tYYp/G4Ey3LvMMPfOe+MsvJ7InmFw9+md6dT4HJiXM/QN0gaCu2WgS7QB395cRyRHC6L8FJIzdGCrq0F5aJF/XUXqt+CVa0lVZwlmdWKrtlGhSTA0VmxGkyKiiLBOPY8rscuHEtg2jmdwt9o5vQQa9SV+uSRSWWzw6QX0u+ZKFBTwBsSYgoNtvvz0aB7cgq+8J7zf4HMGLiXlDbXOm4oRHvruohqAG6lCVBUA+lG2bS+uuoU2DWPW0q759X5ino7vrNIhSdaecuhHqaok07ughz5Y1z/z1XD4q6S8jCEgfvHdC4zIZFmhKK6KHL4E5R5vQkbKq4rpQJ9IrSkYXxLbe+DeFFtWos2eRlLWxB/5RFoui9tbDXNWp2H+FFzPZZlJPaf4Y/MJVOSjiKUQuL1tzgjep5jMVEu2PRPA+K9sX+rH5aftsLqEed9s/yqWMaePIZo/1Pk+OahhlJu4R8qevaoDxCrh2CxWBLuV/4HUEsDBAoAAAAIAC1nSlJQxK3gMRIAAC5E
*/
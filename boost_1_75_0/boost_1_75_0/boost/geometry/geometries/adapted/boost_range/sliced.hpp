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
W3sv2/MRP4DLbs1NP7Gsw29fMJbn8RNAbFSP2cMAT0WVEs+1a1I7LY5P6TDL9hONB/qThezHTGiWrOd/Ey31Uzg9v9a6MttRV+6QnkZ/UtVJD2dqS3d/vk6VAvw+MQqKRkOZfZEYnUAV3dBbgxFXg/WJY206lbeDwvg3phHRwmGH/04jhXUoN85/PAI5E0HkUuipsKD9loe1i7P+Pjx6Bg5rqLR65tg0wIvalPq3CH41xrYne5pqNfBvz6gwMZHMsXBt6YUD3THHNYHvZich1+qaNC1xrW/j5179gz1cTv7u1kzR48/jgxEMc5/SpsLgT9L7IX7ijfD1ZimU2g5A/ZoJ2mauR+ywFvpd3hVzlfseoj7IvpQ+Gcxz1f+qY3/WoDOrWXCT86TxGtFBObLhX/zBfSLs0g0iW5V1/9oBYfkVu5kpnUyb0yxpb8KzhhgbPpH65bz2KJ35YF7vYkRR95PdWDfohbzr27EUnxcPh7hRhtIL0Xj2McIvOEhttHv5hfyM3NxIkYe/izaVfyWR7Nv8joAac71ou7W8dJFhDYLv9eRBP1eUlAPa7KQ0wAWSJzHWHcLX2qJcYbVYVTom7LmlObP8k5mgAslj7+tu48OhenFeeXt+RZudy3w4MwxoU3DHr1RB2JNEa275pwnowK/0pbAn3RDsGQw7AfDZ49XSrgageqGU1/BWnje8d1oFsQINM9OllcLfN1Qf
*/
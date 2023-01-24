// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_ORDER_AS_DIRECTION_HPP
#define BOOST_GEOMETRY_UTIL_ORDER_AS_DIRECTION_HPP

#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/views/reversible_view.hpp>

namespace boost { namespace geometry
{


template<order_selector Order>
struct order_as_direction
{};


template<>
struct order_as_direction<clockwise>
{
    static const iterate_direction value = iterate_forward;
};


template<>
struct order_as_direction<counterclockwise>
{
    static const iterate_direction value = iterate_reverse;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_ORDER_AS_DIRECTION_HPP

/* order_as_direction.hpp
NBXsrXbtHVmQVq5pBqwvsM/Z8Sb6HrzkTW4Ym9B/L/3iyaAdvnYyftElI/772sT4PJdOZCT297NjfG6BatgzXOHl8dczZrKu1riW+T5PXOXUVHuZUWLl5IL5Sf1NPSbLmb1ASrOhWIo5k2m6YDV3TtfnzPfxnzox99UjZs/iJJHaOsm8VsP4s+3y4S5IZ6F5kOKCjqC7gibUBEEZ9zJH99l1F0qvVaXsNLAkVdqiYrci/QyWH44ko0QezR+/P7F5hcbIw/rf+jrse2R4vQjJz/J0uNxURChY+fcBQmc2H2nGhyN6C+YmkZuS1nvsaHMO6xlOve4IWQ5zta6nWR6jFYxCGs1wsnAPSvEm0DF91r/XfmNLLT5swKzdeWixoU3rb+mIwW/XIVkNN0DP7sFi+EugOfaDOWdvdfwx20LnUvYJmopRoqoYCeuxUIz8TnQAB8vrqeHLKKK3gN9qC/bJNTmltiYsFFerqM0BP4kn0OrTa10BfHmiPWVxfMQtQ8+jKeqTZgsDE642YqsDTSjkukyrQ/w7l8u9wjqEu9zbCVf6LH7XrSdx9uaZy+ykAmRgM8z7++SrWEuVUb2KlgBbE/aKZNRl5RFrJGwPBYplbjeyBtHej6as1CaneUvjMUu1quHZY8XkYzFRjqRkIlzEr9lGOV5hK9ZReYTUCZhnsyGiEwfIBLmuNO6L64MXNwVdyrY1Dq2tboYkXkrC
*/
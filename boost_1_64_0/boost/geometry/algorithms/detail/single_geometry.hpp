// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014.
// Modifications copyright (c) 2013-2014, Oracle and/or its affiliates.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_SINGLE_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_SINGLE_GEOMETRY_HPP

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/util/range.hpp>

namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DISPATCH
namespace detail_dispatch {

// Returns single geometry by Id
// for single geometries returns the geometry itself
template <typename Geometry,
          bool IsMulti = boost::is_base_of
                            <
                                multi_tag,
                                typename geometry::tag<Geometry>::type
                            >::value
>
struct single_geometry
{
    typedef Geometry & return_type;

    template <typename Id>
    static inline return_type apply(Geometry & g, Id const& ) { return g; }
};

// for multi geometries returns one of the stored single geometries
template <typename Geometry>
struct single_geometry<Geometry, true>
{
    typedef typename boost::range_reference<Geometry>::type return_type;

    template <typename Id>
    static inline return_type apply(Geometry & g, Id const& id)
    {
        BOOST_GEOMETRY_ASSERT(id.multi_index >= 0);
        typedef typename boost::range_size<Geometry>::type size_type;
        return range::at(g, static_cast<size_type>(id.multi_index));
    }
};

} // namespace detail_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace detail {

template <typename Geometry>
struct single_geometry_return_type
{
    typedef typename detail_dispatch::single_geometry<Geometry>::return_type type;
};

template <typename Geometry, typename Id>
inline
typename single_geometry_return_type<Geometry>::type
single_geometry(Geometry & geometry, Id const& id)
{
    return detail_dispatch::single_geometry<Geometry>::apply(geometry, id);
}

template <typename Geometry, typename Id>
inline
typename single_geometry_return_type<Geometry const>::type
single_geometry(Geometry const& geometry, Id const& id)
{
    return detail_dispatch::single_geometry<Geometry const>::apply(geometry, id);
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_SINGLE_GEOMETRY_HPP

/* single_geometry.hpp
/muG++t7HV39uBWPn/kLR/EeJtIjx1t975/v4eBrz424b25L5lNYzlccwXWbxfG+3krsSakT+FPITo3A07fFN6BdWwg5oLV0h/n1M2gXgfZIRWvwoOV5qyWgXepoeWw3wGum/vukYg++OiOyDDyWg4fBnYZ3jd/Z3wuUW4r+usS/UIE36oQtV+AbbQrV51FzXcXeKqQnhfmkJyrQDoJex0sh3jFsb1cPj2a80+tYthPfi8L0lYYeNqgA/QlEr+/b0O3oieA5AeGbJwieoJfnR1qZZzYPNM92n0bgM4omifxZK2x83iFB3+gk3Hex34T+WvldzNvgsM9M8V6P9m7X6Gx71yPzT+zr7q1xP9kf6UPYisTbKaxfsXjnrkboRrzTot/WqXADSO8G6IE+lJHNaRgNneQYalD0oUYLvTOqH3Mq0c3P/ZbzivqliSa6VxSLPAqKeeXToF99zv2aNkZi0eqmhhbLLQQOfptF/i7gc2LhZyC31Pjn+MT98DjnNw317xk1cm3UKL9wBe0PtVpwKHLvWmtHR7IjYU7boTaVANz5iXvvYbtE3cKFjQutlToGeno22c7CUDD2YmKfjNXRkddjP+rZQu+RnCdZNsgUDc5xdpxaJrenlPdvBCCw/zmqDdiqxhPn1sC3s3QmDpebC2rEuWFVd19UQz9Vd38O/LaBdg76gZfGXLrZ36Q5NRS6z+czibnOzLr5pouN71ibpD1/Hf0SgukzoOm+/kwS5xgFIPuO35Ssv04bo9+KRHujxuTbkebLXZq5r3GplW/zlPf+Xmb1bO9JiT3CV9g+Mu8RZv2vlL6eR37Pkb5bgK19v71a+O18+O010m8LrEsuUL63A75CPmh97zrY7XrQzZO+UmDZgw/K/DBnaPW+ZlvH6PXhmwkm+z2l4swT5aHJM5tHUsYtFA49KxtZJ+FdN4qnz/LeVqPedaMwzv1y2bsT8ULrgjx9+y4l+3TTZmA/6k01Tvbdog27SdUV90Cve0P43KfS8A3Q3gFaa0/QfrNGphnrcizX0gTvnBK0MjxehlkX6C3S9CDzRnpF3Ieg5/dD8gW0XLf9ELQPK9ofUPgRyDwdMn+kdNJr/Y+C/tM1wX3rm0Xd+1NVfh5XdvmZkGH4nK/y4AmF36rq6id9PHgTHOXT4Z/CvMxo9ANT9H6jDL/2Ie/10H5Cge2bnUdDWuW+6p6xNA9E4dJSFx625eEbTd9gfER7UEJ0I83Zei97L8FvZRuQR/sv7VtW6vL7M0K3FzAHRF16rM/Ju+zsj/d9GJi9I4nna8JpYXfQl3h/En3cOE2GNQiagRLclwQatEv8k3XUS8jv4hinh/vyMmzshv2c6Gvy2Irv5JH941drOB7qS+u7ZCdxf5IqI2/W0E/5399FuXxTlem3BO4FVf7fRjn8l5LxHIXfUWXg34LPc4rPfygs4rKcF+D/70HOP0Uf9h9KZtFUopzq4j2HeMMpLPm+qfjupfC6bhgh8GNKXf5Lu+1NeLlXcwvvazf55X6SfhTR5+7Pm9vMEjQplepOcn9ewdF+fWhqrrseFBsZG3vJYhS/CHevlk51+r9d5M4hUZjn1MqAmwtcDHKZTtSL+8P++011+TqG/hq6ctDND9QXaVqiTATueSt2fTR191uKNhc7WK1/fsbwx79Ru0+r1c3oJH1uHHQ7SKTHpFX61Eemup/MwwrEOwS0KPvE36Wf6IQNaG4Q9Psr+omON9NPBH3V1OC4PhNyZ2mcaYAPGddXC9/dH7rJdNQI/Ifpez+FnzYV5RV4abvpAjceOKKxuFrF92A/LvjOcnGN/3IdNUfZ/WPajhRvbmTZoV2ktC+Utn/aUwkD3CsPgaPszIM=
*/
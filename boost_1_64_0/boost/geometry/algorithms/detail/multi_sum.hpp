// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_SUM_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_SUM_HPP

#include <boost/range.hpp>


namespace boost { namespace geometry
{
#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct multi_sum
{
    template <typename ReturnType, typename Policy, typename MultiGeometry, typename Strategy>
    static inline ReturnType apply(MultiGeometry const& geometry, Strategy const& strategy)
    {
        ReturnType sum = ReturnType();
        for (typename boost::range_iterator
                <
                    MultiGeometry const
                >::type it = boost::begin(geometry);
            it != boost::end(geometry);
            ++it)
        {
            sum += Policy::apply(*it, strategy);
        }
        return sum;
    }
};


} // namespace detail
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_SUM_HPP

/* multi_sum.hpp
qNjC9WtwJ7tGdk3b4p2LfpwjzGbue7xjqmk3ZZ8mf7Dk+WGEcvdwIqcHcMKl4R81JjsshXPnpPuV8pKp1DMM69TkK5Vk6Gxl9iTGmqIzeL9RU6/vVHFSoCWrkCFDP+x+RS2cTrmrIUWcK3UmkKvLpC/zaAyBDu+Wy/eRH7KiERQuiqWXd+VCe8wYMXYj85fOjj/+QdKIEMDBUVv5C6fL423MPyMyv+6OS1VjAgTM85GFpJ+S++C/V0coaMISto9CagBiMu9gpQk/iS7hXUU0lf4oBXTxVg7NyA/p4k+AC0AYK6INLEI0hT/WyFgM3RR21+P8YdtidWxZIBDveOt1dtg37wtvDXR9RWl8o5d4TiUQmbrR3hJT/a79e2WoI/S3RggJCH/s587MKHa6DZKXhuwjxv9fQGJ0jsG+e66dQ+SMyhDcE8GXA+pJnu1jmKqvSuHTPOx0CcTgjyrf51jjYOZuUiDg1SLsT0pdaCmNR+FXbJchrrL9Vx5cClAZRu98qTkQPN27Y/ywk8xuj13P2+gzfknJ4CgjX5CpzrIXTcBbKuw5a4ZURGzN/g==
*/
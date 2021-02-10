// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_CARTESIAN_IO_HPP
#define BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_CARTESIAN_IO_HPP


#include <boost/geometry/strategies/io.hpp>

#include <boost/geometry/strategies/cartesian/point_order.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_winding.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace io
{

template <typename CalculationType = void>
struct cartesian
{
    typedef strategy::point_order::cartesian<CalculationType> point_order_strategy_type;
    
    static inline point_order_strategy_type get_point_order_strategy()
    {
        return point_order_strategy_type();
    }

    template <typename Geometry1, typename Geometry2>
    struct point_in_geometry_strategy
    {
        typedef strategy::within::cartesian_winding
            <
                typename point_type<Geometry1>::type,
                typename point_type<Geometry2>::type,
                CalculationType
            > type;
    };

    template <typename Geometry1, typename Geometry2>
    static inline typename point_in_geometry_strategy<Geometry1, Geometry2>::type
        get_point_in_geometry_strategy()
    {
        typedef typename point_in_geometry_strategy
            <
                Geometry1, Geometry2
            >::type strategy_type;
        return strategy_type();
    }
};

namespace services
{

template <>
struct default_strategy<cartesian_tag>
{
    typedef cartesian<> type;
};

} // namespace services

}} // namespace strategy::io

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_CARTESIAN_IO_HPP

/* io.hpp
M5fLxEnvGEm2NVEkVaLjei43HIiETNQUwRKUFbXxd79dAHzoZV86VVtLBLDv3y522eOjv+9TgyN48uPp/zz84LemGKfyN+5n+0973jcw/yDVF/x+SsgxlCTfvCY8TfINGprEs1Le0W/Pe0rQF9KN/hwT5RePfuIKkhFlRybrVNyGGTQ6TTg9+ek1/IhfpyctmGb8nsOljBa8Be8UPXkhPf07lNmCiajty8XPbcvIDYUCJefZiqUc8HckfB4rHgBTEHDlp2KGDyKGLOQwFxGHzmh80x9etGAVCj8kJmu5BBXKZRRAyFB4yn0u7g2PhKUZyDmSI/NAqAwZLjMh4zbK5pDxdKGIB4lnkZLA7lFHNkNBLIMwyxL19vjYX6ZRW/HjQPrq2M+Nb4fZIsotuUElFmwNMskgk7BUaD6dbMFCBmJO3zy9xcVkOYuEClulNigqDo5lCopHEfFCOsGVUZvD1LqnRccgQY1FRl9KxopErUK52DiIfiQu82UaoyD0Ax4KJLq5Bcs44Kk+rC3PRVifagcfDE2pbwAyRmWg7kyhP63DjCmhWnDddy9HVy5cO5OJM3RvYHQOzvCGmH3sD7st4AKFpcC/JilXKDwFsUgiwQMr8+/7HNdqz0XsR8uAQ52i5ymeLZN2WKeNOUJr
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015-2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_POINT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_POINT_HPP

#include <cstddef>
#include <functional>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>

#include <boost/geometry/strategies/expand.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace expand
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <std::size_t Dimension, std::size_t DimensionCount>
struct point_loop
{
    template <typename Box, typename Point>
    static inline void apply(Box& box, Point const& source)
    {
        typedef typename select_coordinate_type
            <
                Point, Box
            >::type coordinate_type;

        std::less<coordinate_type> less;
        std::greater<coordinate_type> greater;

        coordinate_type const coord = get<Dimension>(source);

        if (less(coord, get<min_corner, Dimension>(box)))
        {
            set<min_corner, Dimension>(box, coord);
        }

        if (greater(coord, get<max_corner, Dimension>(box)))
        {
            set<max_corner, Dimension>(box, coord);
        }

        point_loop<Dimension + 1, DimensionCount>::apply(box, source);
    }
};


template <std::size_t DimensionCount>
struct point_loop<DimensionCount, DimensionCount>
{
    template <typename Box, typename Point>
    static inline void apply(Box&, Point const&) {}
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


struct cartesian_point
{
    template <typename Box, typename Point>
    static void apply(Box & box, Point const& point)
    {
        expand::detail::point_loop
            <
                0, dimension<Point>::value
            >::apply(box, point);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<point_tag, cartesian_tag, CalculationType>
{
    typedef cartesian_point type;
};


} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::expand

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_POINT_HPP

/* expand_point.hpp
2M10fiVHGaV4KqO4yoHMS73Qle9Sen4P1lSfRSekxWdnG4/FWp2qDYtWVMfV1yVZn29KBgNN740VjXR9s3cQtpHtXuaw3O52bhCTwfHps9Jsat1Sz7l8lH4uzzp7u9Ur3hb1irfn9o7Cds59nMW7vvvIOskwQ1+VobhdG5czZbI+xTFfPW+YOlfqW3/zs52Cq9VEr+LY7Nxv0Fn2cy3zICtb3lmtqqfslxnK/t8Wmcv+cbeyX2NR9s9alP1oY9mXdY5w5QUfd03JkPagbtcsiewN8+0Ora2o8d0Jub4J0dubchai3DxiN89MdNXRX3d2LpfVZ9+Qfe5uP/U+NI/vPXY8uf/M9pBrCtco/E3uyRjTJsvrYrp+Ynmx8nc53yymzOazzeYpx9yF5KvUAYP1+Slt2+KzMnNIlTpLj/ou/Bp1Y3WW40J7dG7zxZbbnDvbDTkm/LJjgFV9HWZRX4/TznPDpK6mnAbg33zUc8qwpR5pl8rHcIemAfeJlXPLi+5Uy6vzXooM++4O0/mmdV+kVu82WjwTi7A4Vwj37DdZzlNzpby67m90NNXHyvqpb4TVdV6ZbBpXrXOlXGvz1OvLXNdzEVZCLXMRlJfTJOAL/pawzHWeZ3c7r2U7mc7/Q8eqGXuY+XXG11HZVoUF1ttKLu/U+2jeP7+NLl3nvj1o/7fO7ZzE2608elu+7yn5RVIcc5lU3Qe5T0M+eDwrk3tNxm0l59eG+/s1bs+4wtW/S1+lrnPwGLc+TLvR9qwP002rUPLS+f6l8ocs9W62mt5y2T6G9vKW210rjz3kPFw7Rvjq66V/Cl9/Jlarz1u7gc50huNwoeGaOFumqdKnMSaVv5muq3jxZe5gHg4kZNKwS70WoDzFjOFYQXr+XmC+D5EjbQQ9v2UtdbPUadp8TjCfMOqwx5YzH1n2JplG336G42SY62/Jzs6eZ6uvF3TT73mb88D47kFfyT/DtKa0tA9X3y2NLXKt01m9PucS3C3tkYzfgrSfKHKlPVcvP8qL6vIY2G26knC1bXbQ/eZ74g69nKkbr7XpO+qpzt8TXe0wzWlnf/VhZh0ecJ1Lp+nTZjrXxaFPq9aOct9OhmXo9wTX68PmOn9PNi5T7m1kFKrLeUbu089ao/4+xPxuipqhzn4q1Tp/MSr1SGCJuR6xvq3RkDa2zfz7bTTWHdZtV811u/U+N9Tc/s5UH56W9XhNniXv91LXI+oRj/XIYO9UfnE07B4673Vsatx1bDfTeaRrccayHiH7tn5u5XGeaUimoZ/kTr/1k/xbP8n/on6SQzoqw3fPzf3y8ZUxY3ueyRn/3YopHf71/Sc7WC7jf/rOsekvpd9auH5pccz6P73+y/pPjvKS/pNwrOzIFxDhhPRRkNcGJ2AgTsQgjMIQnIzX4BQMx6l4DtU6Tq1DJ8u8mhPqZa7aL2dXnIhDcRKG4mS8FqdiJEaj9l1eu8xPXi82fZf3GpbbDMOwFY4yfG+6UKabLeMavzedIP01JuJAtMl6JeEsdRpZH+kzCMdarM8m0hmAj2Jf3IwDsBSvxCcwDLegNj+7zO9ai/md9lLndwYvxa9xEJ7Fq/AcjsY/G9JX7V13fodIfg+W/B4i+X255Pcwye9QSV+cl/TDg9o1yu+IaPn384zXGXfgQNyJM7ACb8EXMQsrcTHuxRX4Et6L+13LYUPWvZwvZDlfynK+kuWckeWcleV8I8s5J8s5L8v51pDflU3rzu8HJb/XSX6vl/z+g+R3ieT3BkN+B/rUPb8XZH7lMr8dMr9dMr/dMr89hvnl+dS9/W6TcroYh2Ie/4XiUrwW8zESl8n8+Lv0+cKyZR6tCIf8O0fKQy5egfNxNC4=
*/
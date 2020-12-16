// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_FOR_EACH_COORDINATE_HPP
#define BOOST_GEOMETRY_UTIL_FOR_EACH_COORDINATE_HPP

#include <boost/concept/requires.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/util/add_const_if_c.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Point, int Dimension, int DimensionCount, bool IsConst>
struct coordinates_scanner
{
    template <typename Op>
    static inline Op apply(typename add_const_if_c
        <
            IsConst,
            Point
        >::type& point, Op operation)
    {
        operation.template apply<Point, Dimension>(point);
        return coordinates_scanner
            <
                Point,
                Dimension+1,
                DimensionCount,
                IsConst
            >::apply(point, operation);
    }
};

template <typename Point, int DimensionCount, bool IsConst>
struct coordinates_scanner<Point, DimensionCount, DimensionCount, IsConst>
{
    template <typename Op>
    static inline Op apply(typename add_const_if_c
        <
            IsConst,
            Point
        >::type& , Op operation)
    {
        return operation;
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

template <typename Point, typename Op>
inline void for_each_coordinate(Point& point, Op operation)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    typedef typename detail::coordinates_scanner
        <
            Point, 0, dimension<Point>::type::value, false
        > scanner;

    scanner::apply(point, operation);
}

template <typename Point, typename Op>
inline Op for_each_coordinate(Point const& point, Op operation)
{
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point>) );

    typedef typename detail::coordinates_scanner
        <
            Point, 0, dimension<Point>::type::value, true
        > scanner;

    return scanner::apply(point, operation);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_FOR_EACH_COORDINATE_HPP

/* for_each_coordinate.hpp
RbItSd0checcaFG/T4C9rUlmrnFLjB0HPAsdhoVJihPtxWSMICw6FFHej4C/xNymoUSJhXjOxpX2P8/Bl8EiO/Xh+lC4mTnu3hywW83sQDBYw7RfJbg7Pg8bezuXSWcl47+Be4qdq1d27u3VRR0PnY/1Qje4gQmHVZaSyWiInD6PTtRztC/Rt64Ee5KVDSewFI0mlAOG/W8h+5AXMN+08g8NlNey2ceXiPoGu8KdbRRCUyjeqJKleCT3Oi6/8P18EXOjP8gH9XiWPEj/T+ThAGceWP0Ethd94CWcJdwp+ZXkKJIh89Kon8HuTHA7wJ3j5JLIfDqCdRfgXF8nN+KP5l5eef4TuJkeE1dvYYn6o9Uwy9xBtLE1X0bsaovMVaW1ZbXkjFBTXjm2/2xuL3np/5ZWpesP+h314U3R78y9zqXP/Qv/jpe85CUveclLXvKSl7zkJS95yUte6l//H4X1dsNedWS6GkpF1XRdeZwONWtRI1GKKl/XGs4kErF0XUu6NZzKDI+HMnTiXDKVOFopKdyjuHiPwhGFdaTKi9SFWiIlxXXhZJaO9U4nh9M9Xc9OujvfZG3NvhGt1i+if4lP67q9KkkRjKJTKeZpQSk5SJG5VIrsptfM/3FL8o+tJe+dQEXF6EDpQUpZ5SHlNVWV9KdJa1eRv+FmGiPP0O2vDL+jVXy+TeizhT73G0b2Sb9o+j+fQsb1ISXUGorGQvUx49Q+YmyYV+1ePAE6jp3yulf+AfRZtdJKvg19+fkF9O/OLbSfS6snlgd9w+heHt3L6M/Qtk2rSpZt2WQykcqoEdq3pO8L6bv9h2nfj1FDmWxKLY9r0RVDiK2p/41V5d9IxkIZ7Wvt2Ar9ad8W9D3l30ds+j6QzTTRNkk0HBgf9Onf+eR3Y9V4Nhqnv59RY2Sv61slfz7d35jKJUqfKd8aVA7G7wyhzwP0PLWFU4Xa3k9G6Nv1q9dH5U4Pt65L9hsrPb3o1jvPP0cJHvPONWPfWjHsI7L92kK7/8Zxb77w2/fn9045Z+vN7p1+BKlRz9Xv73bhPo++d9C8bzf7da0bf+w8ayef77L1tPvNFyw+NbR8+K/nf69eU/HpSIoN9aT+fGrSc4UrXzP/sVP2b/2q4YdiinXxo35/p1nv377tstV+fL762EXHblVHZ6HtsKV2P7924TVHbF+9eXzrp6sCxR+QF90k/f6YyvAW70/q3XWt5NBlJ47sI5ubdv3+HicEepd8+NN+szef+9Wr216zps93r37/xksbauau+sXSR6/f/rfLO9rJD3/x2tr9k8rfuPuTjTa79uU1dt/s6c2v2JZs7PTnRx297W2RystmFjz/1O6vHHkfVdiGQ7X7F54+oe+hzafPKLxfuXad5n3fIDuIDbT72bVGbHDoo5HuK2bNOmzO0/UTSA9PZbrjuyv7xtHVRFc7XbPpWkbXUGpoa763sm9HuoJ0JQNUzvTpo/vT6PPjUor3QnV+EpXbCrryxtBeDl0z6TppLOnMxpGtWjk9S1fngVSBpAl7hq5ZFRSnZTzZddF1O119dF1Jf+9z6kWP0Odk6gBJuoYeTDZgdGXomk3XPLpWraH2Q9d2dHXSs1/TZ3Ut+QrTlaGrl+7NnUj7OYcQ91Bi0DWLrrz3V/blHUa2xfRZTZ9XHk72EkeQ/xRd8+gqrqO80nde8pKXvOQlL3nJS17ykpcGJ3Gs/7VFdZrseszr/5X+4fp/Q1r/Bzak9cbEQ8lcRymlP/enOgHt+1toTebytXLICENnsHRTssmDzuCklYyyGE/X2nSNpuuSjchfY4WmMzhJqaktVcpJpmgoRmf/aM/slz9qmF5iZH8QyC+n379Wf7ZE1yU=
*/
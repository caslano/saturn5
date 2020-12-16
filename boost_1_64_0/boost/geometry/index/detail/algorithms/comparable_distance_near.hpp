// Boost.Geometry Index
//
// squared distance between point and nearest point of the box or point
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_COMPARABLE_DISTANCE_NEAR_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_COMPARABLE_DISTANCE_NEAR_HPP

#include <boost/geometry/index/detail/algorithms/sum_for_indexable.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

struct comparable_distance_near_tag {};

template <
    typename Point,
    typename PointIndexable,
    size_t N>
struct sum_for_indexable<Point, PointIndexable, point_tag, comparable_distance_near_tag, N>
{
    typedef typename geometry::default_comparable_distance_result<Point, PointIndexable>::type result_type;

    inline static result_type apply(Point const& pt, PointIndexable const& i)
    {
        return geometry::comparable_distance(pt, i);
    }
};

template <
    typename Point,
    typename BoxIndexable,
    size_t DimensionIndex>
struct sum_for_indexable_dimension<Point, BoxIndexable, box_tag, comparable_distance_near_tag, DimensionIndex>
{
    typedef typename geometry::default_comparable_distance_result<Point, BoxIndexable>::type result_type;

    inline static result_type apply(Point const& pt, BoxIndexable const& i)
    {
        typedef typename coordinate_type<Point>::type point_coord_t;
        typedef typename coordinate_type<BoxIndexable>::type indexable_coord_t;

        point_coord_t pt_c = geometry::get<DimensionIndex>(pt);
        indexable_coord_t ind_c_min = geometry::get<geometry::min_corner, DimensionIndex>(i);
        indexable_coord_t ind_c_max = geometry::get<geometry::max_corner, DimensionIndex>(i);

        result_type diff = 0;

        if ( pt_c < ind_c_min )
            diff = ind_c_min - pt_c;
        else if ( ind_c_max < pt_c )
            diff = pt_c - ind_c_max;

        return diff * diff;
    }
};

template <typename Point, typename Indexable>
typename geometry::default_comparable_distance_result<Point, Indexable>::type
comparable_distance_near(Point const& pt, Indexable const& i)
{
    return detail::sum_for_indexable<
        Point,
        Indexable,
        typename tag<Indexable>::type,
        detail::comparable_distance_near_tag,
        dimension<Indexable>::value
    >::apply(pt, i);
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_COMPARABLE_DISTANCE_NEAR_HPP

/* comparable_distance_near.hpp
O+7X6W4EDUo72kyT5kU3mtWg6ZVONBe50WwDTW+TZpzQqPo6RA9jH9A9CDwZaJgnbXsEidxe/4F1eADJ5MMdKOayFNO/b3rzdDZymWe7umbZ4ltZs1T1HM80AzqVAxwAc2sO6stRKXOkY892+b2s1HWvh/kQWh9+B727X+Y73H4JDfnPp/YttN9eGPKPeN64TDNvxHeV+UgW3PAtuNG3lD7LU+o883sb0iCgpgFNKF3mkaCN7Pwur9Hq9t2QCibhzTyvXQGzGT5BjRxFJfOhpco4MqmVh3l6y/vO95K9hNL8blPnsbGvyHli0feQ9443k72C6Dea9LWBOaE39O8m/3mSZ+CXO88Pka4ySi1pn9aTf5mH6hbS2w+/O42xT4tTHGfqmlrerbU5xAt2ipeszW0kN5JdWT/YOdsMcA+33Q/D/Bl5XvCdmtayiKDPd6Y/VdJ5Admv4b5bXU8YL/T9yD4V9lqy3wp5mT60viB5ESCaNZzWVhj5/A1Zb5C8qeQwub9n+t7O+shj013kn6H0/+CRfrfQ6tfjZD1CeN8lujTbmEDlRd/rWiYuIbrVVCYCcO882yoTp//HygTSR1nXKCA357rGGHJX1zUKne0IxQfpoKxrjLbKVDnJgzaA16a4LS08ppap0IUf/JxdXVdRgjZVv/fDvO1c21L2d21L2T/idonb0ma1o4UVznZ0HeIfVOLPum3d1x1BH1lbqlk3VOp4+iUm8a9gkvm89u2QZ3W4PGU4MlU7s65WreOy5rGJ6Id5BssdWCuMbJ5rmOsxp8Gcnh5Jfx2b8tEx1/mVEoctlzjXOe9AHPzfO+OAEzZu/RPo1TMiQ5txpsc+5ymY47yvsD4H7iKXi25efTkHX2T3EKScavrPPXOc5e8uyFSsymQeMK0wrtiVY0VdKw94IiuDIo8mjYqrTMLjMFm8P7/BGFco8vQtqp0fwOwQbYCo5NXmIfh4LZr7muvI/jbeL46Ts+0JYet19URzKbT0JMJtBNYT+O1kch/gySE3L7ntILd12FWPxdgj0bGmZsTh70RzNU4DoL+Q8/QiN6/lYfxEdE96fCi1W416w2t8F/zA96v5PS/whtYIuQykct/4PdlLMHdsy25ejs/F4D+Lzn7uQ2ynoTEZhojFRUe3TewOTfptfdRnWP4rK/n8fvTFvthYX3Qh/urWdjKZfivojxr0LQM+LBQ61mVSmW4f6BLpTHxwvUWTGEZzrBL8Bk1C8CbZKwqjaVMFGYjGqUfeknM44jcioralgfODVc76sTkH8f3BXh6LgMZZXx7jO9tn0DdaN8a5jM+V+tomoL4XlwdzL+TZqcqDI4BFJbWLq2YWzSp1PbMEHtnHuSfH8AOxrJmwP76UKuMYvNfG4XFfadFQGCNIQvUs8z7yz5DyMLoZbag1LoGMsEMA63yqjCtELqUf2Bhw7uttRRieH5W0sqnZ17ZroI9Mx35D7dqUGme+PZgDDJMFOzizy0obzzvwheUdNuxmlUrewd+Zd0RSy3knNLYwSsvmchjnuoVBJLXKuBd0yj6cW1no/6NaFsY2Y42Rx51cFihCsvcmZYGceR1LaCE40xYLrcRHKTfHKNWxtsB99XyYh40+UckrRa+Vrtww/VmynvQK2ZOkj0B68r6wRZsie27zyF6BvgA7LzDcVzn2ln5DdGeArgVo4Cbfidf2F4+TXwu2My3rxZqGMooBHbfjhc42nGnW1lp3u0Y65hyZTLOt1uxfojuhb8nwNWk+sky7Zl6ltMvBOq5PJlA5vNuo28c1eVSrzR+m7d5om9zQ+Mk/3yTsyAwdWI4CRQ4+gyniaOVhno7NamcseXotMAknctkdC/OoMX7SylM=
*/
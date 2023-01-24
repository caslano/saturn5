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
INgAnDDb2+GVCsUTqGZfnG9czbbv42keg6zq3MZz8r/Bejhkhzl0BgO1vcTlXGilaJBTI61h0KldnUxmLadWJQfvYJT/VkYE+ntu56s322tg/x6PvVCr/Yof6ViqfJTZ4wlIrr8p+CVRphy9en4LU1Et+h6NYUZnKRPk1Tk36lRKsz8yvkJFFaHEJ+uSTtft5/c7mb4KpDTSfs6f1PkbL0eytlyRFGliVDGHje8svTT+eImVSRSq9IlsEeRIT8jhpF+Z8CJdawiVRp4xo5QaknYxuvqX7VP0+WrSt+9ev3BaNPd4u6sw/n0vzeIkStIs9F7aM/8Zr7k/oodjmoacpUV3l7SMmnrX4Z1Jdbk2i3rD5qC+GYjbn22v9fh78I5nJ5Kqww9PiUVdXA/uElTk78t2p550/Xq2yB1TSfW+EgNxlfdqYWAd1zbO82cL2PZHYgeSjzLw/yEeBdglqPZ54AhUfgUU1sjbUevrz0PLz8HM4hPb4Ndfwb9NZe0tgzs2rMir+g7rCs59vHZn2ov6+0k7vOXI3eeOCQ5P7ctMSMrS6eCtHhIc2JYQDR6+mw7L0440fLnRXunxjmDo5xv+rAI5h9Pb63Oq9a0l1OyeeDNo1P1sCXXHzcwvYut1TxvvsWAv8+w9kbJ/mGupj2vNKv7VvB7ltrM84ZpkibKkdS0YfxnkM/Kk194+yWR2NBUBr+txkpbXiiw5rob1
*/
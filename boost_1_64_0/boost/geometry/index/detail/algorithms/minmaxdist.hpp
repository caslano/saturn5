// Boost.Geometry Index
//
// minmaxdist used in R-tree k nearest neighbors query
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_MINMAXDIST_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_MINMAXDIST_HPP

#include <boost/geometry/algorithms/distance.hpp>
#include <boost/geometry/algorithms/comparable_distance.hpp>

#include <boost/geometry/index/detail/algorithms/diff_abs.hpp>
#include <boost/geometry/index/detail/algorithms/sum_for_indexable.hpp>
#include <boost/geometry/index/detail/algorithms/smallest_for_indexable.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

struct minmaxdist_tag {};

template <
    typename Point,
    typename BoxIndexable,
    size_t DimensionIndex>
struct smallest_for_indexable_dimension<Point, BoxIndexable, box_tag, minmaxdist_tag, DimensionIndex>
{
    typedef typename geometry::default_comparable_distance_result<Point, BoxIndexable>::type result_type;

    inline static result_type apply(Point const& pt, BoxIndexable const& i, result_type const& maxd)
    {
        typedef typename coordinate_type<Point>::type point_coord_t;
        typedef typename coordinate_type<BoxIndexable>::type indexable_coord_t;

        point_coord_t pt_c = geometry::get<DimensionIndex>(pt);
        indexable_coord_t ind_c_min = geometry::get<geometry::min_corner, DimensionIndex>(i);
        indexable_coord_t ind_c_max = geometry::get<geometry::max_corner, DimensionIndex>(i);

        indexable_coord_t ind_c_avg = ind_c_min + (ind_c_max - ind_c_min) / 2;
        // TODO: awulkiew - is (ind_c_min + ind_c_max) / 2 safe?

        // TODO: awulkiew - optimize! don't calculate 2x pt_c <= ind_c_avg
        // take particular case pt_c == ind_c_avg into account

        result_type closer_comp = 0;
        if ( pt_c <= ind_c_avg )
            closer_comp = detail::diff_abs(pt_c, ind_c_min); // unsigned values protection
        else
            closer_comp = ind_c_max - pt_c;
        
        result_type further_comp = 0;
        if ( ind_c_avg <= pt_c )
            further_comp = pt_c - ind_c_min;
        else
            further_comp = detail::diff_abs(pt_c, ind_c_max); // unsigned values protection

        return (maxd + closer_comp * closer_comp) - further_comp * further_comp;
    }
};

template <typename Point, typename Indexable, typename IndexableTag>
struct minmaxdist_impl
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_INDEXABLE_TAG_TYPE,
        (minmaxdist_impl));
};

template <typename Point, typename Indexable>
struct minmaxdist_impl<Point, Indexable, point_tag>
{
    typedef typename geometry::default_comparable_distance_result<Point, Indexable>::type result_type;

    inline static result_type apply(Point const& pt, Indexable const& i)
    {
        return geometry::comparable_distance(pt, i);
    }
};

template <typename Point, typename Indexable>
struct minmaxdist_impl<Point, Indexable, box_tag>
{
    typedef typename geometry::default_comparable_distance_result<Point, Indexable>::type result_type;

    inline static result_type apply(Point const& pt, Indexable const& i)
    {
        result_type maxd = geometry::comparable_distance(pt, i);

        return smallest_for_indexable<
            Point,
            Indexable,
            box_tag,
            minmaxdist_tag,
            dimension<Indexable>::value
        >::apply(pt, i, maxd);
    }
};

/**
 * This is comparable distace.
 */
template <typename Point, typename Indexable>
typename geometry::default_comparable_distance_result<Point, Indexable>::type
minmaxdist(Point const& pt, Indexable const& i)
{
    return detail::minmaxdist_impl<
        Point,
        Indexable,
        typename tag<Indexable>::type
    >::apply(pt, i);
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_MINMAXDIST_HPP

/* minmaxdist.hpp
SEh1wyPvScs6+jtEM8o72BNN4UyTcHJtPKhN/J3p4t+awpgL+5tmHnl1czSjqu3ow/N4fn+mnuyJzvrK9ew68r8AukJi7bpbZd4/kfz9jrpszTdnkP9GZY3kwXTDNLpHL3lcrJZrWSdBusMN6W5bJ0EaKW9LLxI3xEppC+H+mfmhTyBYBuNi40zryVw++EnyIrwN6HGpFygLTN9d2sJNZH8iJh9/+0V7Oe/UN8qjPRZfF+KrAt8Gsu+I6QMZ+6IhTyU+51vl0+SbOBvB+X4H2Z+NORUxHBztKGNSXsAn9zcrYf8T2V+MGYTycnp0DJcDef9ayu/RfNLzEv2KN1vRd4LwRE/Jauv9ciC/Xy73P78iugUx/aMe9/SPaS1h5NvCyESWr7XsyI3BUUWei6JHe6X/5zU7q750OoXKftRCzzWggRtsfyS3gVRWD9BoDe9J8HrAiL6G33dRi70dtOsX1cTbE3LAjl/5ZG8ZdSbcbvZc4HX0RZz/V+QTXWi9nOzZzjkdx+8xkmNZlG3uLPXtMPmNRj/axwt6KtMPkNs1UUZ455r0eFwitP7YSuJaU2afK51B8rfhMzVWfM4G30BTp/KHyMNP0H7SXtnnOEiW2ILaafabAL8fjfY8ZUWuY67BNAHQfG/QxK5Icry7yzRrPuH35hOXr3WMmZhmO2i2pYMmefk3Fs3D6SrNAdA8Qrodl28NH1ddAns2ty+WmQw/oKIjbyjcHk3H92CA5B6Tav5+DOZxdkf/Az8g+zGttFljGmmzAmq/ZGuL1Hfyg+TmfCd/paYtW036cNR34teKzniqb+KGcgc3LneKzpyA9JvnmnaUJd7r53ZxJ7eLmTBJbOINHVEDqF2cW07qISaPmjx57MRzimbVlPE4cS31g3PLbXWDeUL9/M0N7svlKWMZhAf5KDxFvjUHnfL1Mfp1rXzQJ8F1pDtovDgnVCXyMQ/rvulF/jPZn/vxMPl/3wT58T3Ij+/Zzsv0Ijd8wzovyHEa9A9nnI6hQNdr44R2sAibKJW1ruleHyb3X9Ijl1vSPUzGhM+dMr6Sgz+n6mSsKcPktGyBe9kAH8sI/z0Z1GdwuotfSH9rE9LdJr+8OYfw4VaqxOegJj435iA0Mz7Yyp04YnJh0aRRkwvHjiwKVAdsZb2bOVeeY4sP82VSv/0srUMZ9LPmV83k8iQ09nFv5PHqRvFiff4cL3wHbvIdZXxT+IUzfsnGGp3Eb/KIKUb9QHmai4G/tN8RyKTMLTTfycR3ipXvoMzKOoMz7YrD0qVFBDJY6dJR0kWVK3jIKZc/F+6KXMhX62yPRq5gmFx/bkI57OIi14QvnXKlQq51qlzza8td5WLaTFnzwJ0Iux4B8Zd+uwnpKXLb2i18A274Rlhcsv7pjEsW4rJTiQvuq88vc8t7ps10f7cxLC5JTYiLrWy4vd0o+wPPaeLySjra0lBcJk0pLCqcNHHKqBFT0MYZP0ePnTDK1i4McMYP/Kr8sU2Qf4DIr/aBpV85ZW2djT8DWVZThdPYwjGjJhWVzkcR53FihkM+8KjyJaRFLh/C08oXc9gpX042uDXycfKxjguHfOBpfvohPJZP7cvqNPLlQr4CnXzSRDa9jbTSI/1fzu+9h7Qr1n4PTaV7foGn+W2lW34d1Mi3H7RBjXzcNLnmF3ikPl/vd7RN8G9+24TvOeozvsFtkxqnJ752xqkecVqniRM3UW5pDp4G2yj4N7+NOpDReBs1nOO07htnnNYYY1+J0zTsXRaNmjZl1Dk0DEP3Zq9fPTTtE3hl3PJwmnbcAprmj1t6aMYt+I7ruGXIEWccr8xB3qlxPGfY2aOMpo3iNT5L0+6eQLuG8LTtxhY=
*/
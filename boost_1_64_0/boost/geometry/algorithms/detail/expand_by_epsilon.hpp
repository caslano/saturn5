// Boost.Geometry

// Copyright (c) 2015-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_EXPAND_BY_EPSILON_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_EXPAND_BY_EPSILON_HPP

#include <cstddef>
#include <algorithm>

#include <boost/type_traits/is_integral.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace expand
{

template
<
    typename Point,
    template <typename> class PlusOrMinus,
    std::size_t I = 0,
    std::size_t D = dimension<Point>::value
>
struct corner_by_epsilon
{
    static inline void apply(Point & point)
    {
        typedef typename coordinate_type<Point>::type coord_type;
        coord_type const coord = get<I>(point);
        coord_type const seps = math::scaled_epsilon(coord);
        
        set<I>(point, PlusOrMinus<coord_type>()(coord, seps));

        corner_by_epsilon<Point, PlusOrMinus, I+1>::apply(point);
    }

    static inline void apply(Point & point,
                             typename coordinate_type<Point>::type const& eps)
    {
        typedef typename coordinate_type<Point>::type coord_type;
        coord_type const coord = get<I>(point);
        coord_type const seps = math::scaled_epsilon(coord, eps);

        set<I>(point, PlusOrMinus<coord_type>()(coord, seps));

        corner_by_epsilon<Point, PlusOrMinus, I + 1>::apply(point);
    }
};

template
<
    typename Point,
    template <typename> class PlusOrMinus,
    std::size_t D
>
struct corner_by_epsilon<Point, PlusOrMinus, D, D>
{
    static inline void apply(Point const&) {}
    static inline void apply(Point const&, typename coordinate_type<Point>::type const&) {}
};

template
<
    typename Box,
    bool Enable = ! boost::is_integral<typename coordinate_type<Box>::type>::value
>
struct expand_by_epsilon
{
    static inline void apply(Box & box)
    {
        typedef detail::indexed_point_view<Box, min_corner> min_type;
        min_type min_point(box);
        corner_by_epsilon<min_type, std::minus>::apply(min_point);

        typedef detail::indexed_point_view<Box, max_corner> max_type;
        max_type max_point(box);
        corner_by_epsilon<max_type, std::plus>::apply(max_point);
    }

    static inline void apply(Box & box,
                             typename coordinate_type<Box>::type const& eps)
    {
        typedef detail::indexed_point_view<Box, min_corner> min_type;
        min_type min_point(box);
        corner_by_epsilon<min_type, std::minus>::apply(min_point, eps);

        typedef detail::indexed_point_view<Box, max_corner> max_type;
        max_type max_point(box);
        corner_by_epsilon<max_type, std::plus>::apply(max_point, eps);
    }
};

template <typename Box>
struct expand_by_epsilon<Box, false>
{
    static inline void apply(Box &) {}
    static inline void apply(Box &, typename coordinate_type<Box>::type const&) {}
};

} // namespace expand

template <typename Box>
inline void expand_by_epsilon(Box & box)
{
    expand::expand_by_epsilon<Box>::apply(box);
}

template <typename Box>
inline void expand_by_epsilon(Box & box,
                              typename coordinate_type<Box>::type const& eps)
{
    expand::expand_by_epsilon<Box>::apply(box, eps);
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_EXPAND_BY_EPSILON_HPP

/* expand_by_epsilon.hpp
5VGjVqRvnh+yBnj+wBygROGTPpz/6kWTrQiD/5YuzK9pvy6xYMcU7hQhT/9RC0l2Y1ZAEQPDmpzt+GRjW5LrkYYbxJnPvyR4A4iDMRnbLX/d+E+qZOr4u4UburE3Cf2cYcVPyPyfCgW/xYFtES1uOnxMaXiqbE9Oy0GqUDlv9XEpL7BDHq+7ZDto4gPo476G9SvwxQKMx3lPkLBGJaH5OF9mEc6XhUQ4pviyVRVnkvh3Cr6khEDQ3L/XFhfX70iJdw29jjfkCsZO4dA2RtZKPltC1o5vnJG6P4O1v+lwglLQozTs1xuNqF9/6fQW3IuUIeAsYvJY94I9x2K22eISvuUXHjHNxVLOi/LPjrrLcVomUPFaBZsn4AVpWwlIZ4V/AXv5jeu8g6C8K1Bo5RueQ7shST5x4YtVH8JCB4YB8R7ZIx53KO0/CyjK0ncvMOjzf/FT6J2IZoZN5R0DsKqvDtuN7X2sr13/DFRdVKj6gaEVSe/EAbBIJLlsBzBZBUGRuIH7BVgdoUh3LUJQnE4n+99uwl5LNfywMHynODLwud3QfMG8ZVhhY+omgA==
*/
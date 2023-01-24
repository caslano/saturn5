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
kVtd2xlm3xXrSxregAaeOiD/MSw1yE9iJVe9F2vleppktLhbPZ95d/u2uvx3SahSxKos1PMoDoBH9xX69eS35ab8tsrzIXQb/bapQByH9Pp5hvdhfZuzB0ptcWtDpEsEu2QAeztIkXAZTzPxFT5Op1gfz5+3PvD2AbDoeAonYKlKLlL2Y/UsMN3zjcOed713Yt8G/6LAeX8m1mPaVfGRdIEJegLeAF/G0S3jfcf/INaNEUBMgTT/D0msHNM0tzkZh5fjYtT8wcnuPCxpmVhqlA+5RA3yhNz7mlNm0vwHcZbfC8RzkC78gfFs9F2mixBDCmE82+k/OA9dj6WrX0Iff4qpp5LsiF1h4wvJBZteKRMy37rA+YPsC1aTUpjyQ5icxfvE3FsLc29Vl7lXCY/8kMZJmwrELEj3XzB1GnVcpzHPKrR68jtetLWHdBbDQrbM5dQzaEk9w84Lgm/dD8QzkNqSZTbxMp+zlUklU5fSlWdhw8l2AU80RZTZm8WgMPUJn18Q/FX6RVijIOVcNMts4GV6LlplUkPOcQTK3EDOoVoSM/fj22E/zoP9OLfLfjzpopgHM4Egb4ZQP0hxjsvmxJcSyOwCeZxjmXfM4FOA0m3CWYXS7TMsdxcTEB3vEBu1mEJsP8+S+C0MHKNlvnV6M0uwl8yffzUDTj0F6pvJr07Da2EazY0t+BK/LL0gj1TmqKNc2jis32/sdC/2
*/
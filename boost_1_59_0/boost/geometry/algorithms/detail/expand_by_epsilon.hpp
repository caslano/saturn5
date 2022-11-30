// Boost.Geometry

// Copyright (c) 2015-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_EXPAND_BY_EPSILON_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_EXPAND_BY_EPSILON_HPP

#include <algorithm>
#include <cstddef>
#include <type_traits>

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
    bool Enable = ! std::is_integral<typename coordinate_type<Box>::type>::value
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
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
*/
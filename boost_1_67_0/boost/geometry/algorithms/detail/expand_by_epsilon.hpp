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
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
*/
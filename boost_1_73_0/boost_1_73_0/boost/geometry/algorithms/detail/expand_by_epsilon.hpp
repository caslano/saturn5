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
o4dOTh5cxr3I0djMsOcgkp6coYJuE6IG3JoUgQW/NuAXk24NXcIGVEzbiFDAeeGfgyE6142aT2mJ73afOXGcnV3JaeY7qLBFe0T4BWuhIDlU4I3iYYI5CSVltJGQRKNYUiPZCT01krO9inRsl6CND7QhICc2S7UGXJKKT+DNnPJMO0H5LvxogA7Bh6wOXtio1LRz2zt/EeS5ZFNSVPXoq5MQzt8dwpKjUH76d7DZ9x1NYkJN9ha3WfxllMPekvzD++13lGT/vQls6NOLhuBVXMCXa2qMRvQuYB6a3jzdgFcrvuaHT3f8v9HH6G183aMPkXkB9iW71o8LJzqy+RR1KZGHdXdi+HA28ibLQUqUFzZXnKYwKrw+sEqs0S5vsnE5gRFmpiDBPM2jIsltLRv95Ii/BAVXGgLxna2Z+CZjXhcTqMMoRTJWlFZTjZJbwAdkPgSSGvfYzropQYrrJ73jk1cnffqArJ30zfqB2tjc0AQHPsESSnpOdmktZnMEW5HhxUVfxEjmtI6U3tilclGlewgtvAsIaCsJkUvlw1wHZC9vOCk3pY/z8kkmMV1yxWS712n1MAN+UooXqqRq9L28KgV++ePalQl5RCET35oH4/UpepNltRrLhUlWqflXkqbdC9+Li44U4arc9scU
*/
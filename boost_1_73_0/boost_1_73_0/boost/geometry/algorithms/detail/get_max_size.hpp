// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2014 Bruno Lalande, Paris, France.
// Copyright (c) 2014 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_GET_MAX_SIZE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_GET_MAX_SIZE_HPP

#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Box, std::size_t Dimension>
struct get_max_size_box
{
    static inline typename coordinate_type<Box>::type apply(Box const& box)
    {
        typename coordinate_type<Box>::type s
            = geometry::math::abs(geometry::get<1, Dimension>(box) - geometry::get<0, Dimension>(box));

        return (std::max)(s, get_max_size_box<Box, Dimension - 1>::apply(box));
    }
};

template <typename Box>
struct get_max_size_box<Box, 0>
{
    static inline typename coordinate_type<Box>::type apply(Box const& box)
    {
        return geometry::math::abs(geometry::get<1, 0>(box) - geometry::get<0, 0>(box));
    }
};

// This might be implemented later on for other geometries too.
// Not dispatched yet.
template <typename Box>
inline typename coordinate_type<Box>::type get_max_size(Box const& box)
{
    return get_max_size_box<Box, dimension<Box>::value - 1>::apply(box);
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_GET_MAX_SIZE_HPP

/* get_max_size.hpp
TG0Q1+o2HzWvbftWrwcNDt15CLEku/U2zFiIUO2uBks2Wzb+ZxD2frQTFSO6EPNYn+awK4bhO84E1THIFss8A8ZcI3OM3kh9iNxBO7I8sHuTtiJZfEVoQagCt3cUhWagjy5EDxK/oT7OF+MYU0XPElMT9tL3ShKl+6FPR9hyiRjXz9Ca12c1ledWlyvQx3UHnuQWCoUE4FDR9nzsMwwrAsN7MPdyX7E8/CEciMy4UVNx0K7QF9twX7BQv1HYoxw=
*/
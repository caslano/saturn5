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
9zQsPyuieqWy4ar7sxn/GohVkHb8OSlzqGQsHPepW2cVywzxrmBlkIvGBoAlMpfWMSTzs/wBp51kGzw3mbbbRSA879J2s8x+zCDU9ja02s1sSVsb5j4LbXZePa/l6WeNPPd8aLOAEgF+KIJmuXXkgfYs18tZmw3phW6rvw3dVhNGt8Up7+tDFhqNwL+B6pymdbsXiJFXQqjEMa6ZrM9UsdhD7aQzpLdWR8SfrjcvwfP55B6IuYSRA8SFcJltQm/n947g947Ah3rwk2SZTbx1uWtsIXO6deagTT6dXtNce15GN2DNHCPF5WpllrpYdsNiOVYL6CPdcc80b61vscftjhnVjlzEXxaMh+ty1uXuCEYCidzCsDsYDTxuBLQAyYvkxBbk7co/UrAzfqRwd2J00e7iQMnLxZGEO+7Od8fc0UgkQgpRdUmREvaOyQsXhAtzi3KRzgVnHJaJXfNyR+YYYT2ox4L5wXgwoZeYsucDXfcU93smrwTELEgL3kvaOHXFLm0qLAxloxg74RX+GMhlrN3ruhgFNQxhuqJ571FBNh3Y/wE35+6RxitFap5eplwlFcYOd9gT87Z48gw3KcNeBFy84aELZWYnu7mDUErkGFxOvmfuoc34Loz5OBwM4zAG4/DbMA5zuozD6/CIQfHsbgIx4y8US8E2nJYkdwC7MJSfoHbeLkH/78qH63N80O4ZAvQoMUC5q7I1r7gz
*/
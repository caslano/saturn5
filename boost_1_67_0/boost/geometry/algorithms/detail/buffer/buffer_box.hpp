// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2018-2019 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFER_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFER_BOX_HPP

#include <cstddef>

#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/access.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{

template <typename BoxIn, typename BoxOut, typename T, std::size_t C, std::size_t D, std::size_t N>
struct box_loop
{
    typedef typename coordinate_type<BoxOut>::type coordinate_type;

    static inline void apply(BoxIn const& box_in, T const& distance, BoxOut& box_out)
    {
        coordinate_type d = distance;
        set<C, D>(box_out, get<C, D>(box_in) + d);
        box_loop<BoxIn, BoxOut, T, C, D + 1, N>::apply(box_in, distance, box_out);
    }
};

template <typename BoxIn, typename BoxOut, typename T, std::size_t C, std::size_t N>
struct box_loop<BoxIn, BoxOut, T, C, N, N>
{
    static inline void apply(BoxIn const&, T const&, BoxOut&) {}
};

// Extends a box with the same amount in all directions
template<typename BoxIn, typename BoxOut, typename T>
inline void buffer_box(BoxIn const& box_in, T const& distance, BoxOut& box_out)
{
    assert_dimension_equal<BoxIn, BoxOut>();

    static const std::size_t N = dimension<BoxIn>::value;

    box_loop<BoxIn, BoxOut, T, min_corner, 0, N>::apply(box_in, -distance, box_out);
    box_loop<BoxIn, BoxOut, T, max_corner, 0, N>::apply(box_in, distance, box_out);
}

}} // namespace detail::buffer
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFER_BOX_HPP

/* buffer_box.hpp
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
*/
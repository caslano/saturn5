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
HbIM0+ztcmuRU6SZN9P1k/gqiUgboKxAY0kC9ep/mTtK2AWGQWUilB+MMv3te/X9t1k+65mvff0oZwRAekbwBD7GIgAK1WotpsxjEQBVhEHhatSg1lcM6IFRwi/7OFSuq4DJqTB9e03f/xZcbHn9X0lhe1gixQ7OXlncmPDfpuPewanlDjySxS4NrLD8Bf88kpqaE6/hiViZoJZpIGw/i7VBLqPSvcIz1Vvom+apcY81Etp4ZQ+N+aSgZHDWRzQGU+cDkTHFs/SO/beuQvgJboXK9G+E0VIopY5YzJEp+dvi3kUsWRrphmIiTgQ2Jab9ba8lzlwx08raRUb+IutNMMGPBLC/zaAmNPotLj5PruE8y4SrzGahEzE19XyUXY38qNmhYlxcMvsbNuZpeFkOGlm26VN8O5ZPYfWQtk4PG5Pcpz2V3hyXZ5l7rL8icLsrOCOclZ5bmXcPzh0fftG3K1IRrYrNdeUfjT2GC+bFEtEVkUnxqqJrOHHcVXwo0YFLFiUSRScjMV/MnTDq9ISWUAfhwn3GeOpKL9PX4mMSfAzk91hQDwfyAoyPDeTrsViBHteLYolAsZ6IleiFusH5J3ZWw1Kjvoe9nNWVlcIPcRxU1kHhmJvtdpXVVTtGR7vd6tvCU+sII1teFx5Ldmmb1MMufbwxTz+p5atFcMJFpEmonK4pwuweahbNfdCgOPwzz8CtIy/BJXN0GLkZ
*/
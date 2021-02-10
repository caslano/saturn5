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
kFkqfZwrLjPxdRlkMRIx/IffXcVfQO8RXWbcJ11PuTR0S6tDCCriEExsGacBNvSH+hetny4WcGjc5yl+BbuDU4wzelGBc2seUEs41MaB4gbTWT7scqu8Szj1Su0cqK2tmq/1bIq21ai2+rVu3C21+5ss4MvanAGkTfULpDvXZ2f49RcL8ZMkF7zP1Wa06V4CmtaSyG11WqgxUbAblLOI80PkHmQsNbG8Zbr3ot6Q5DGVTgpC2Y1xlKQb2GdbnUzSZyjezXrDMr1epzPVh2qePD7Yvlnv41/hR1BG/UN8DvI2XbtT/aotTxwbiKnN0jAHyCWmZTbRNIZVHhjGT2nmMEkHk0GDWbsNIQnAXx9fnJ+3j6/wqc3gYNPJ/d/SjSbfvfJ97scjuci4NIJmHg1iQi/4PEkZ85eesw/na2eTm46n2O5e/OTcdRSA4MkEmYGkfaJcs5yJVwRkNn1Q0wk+D414+3ZbvSepGklu3iSNQxYDbsYtHIrJNaJZlOczIMrFkEYwjzs9aSR5A8zV32c54nAPHwGV0OdIrlFVoUX2U3jv4CPglwelFi2VzVIGE55dNErukEoB7Z3G8UdcOaIzz0isBhJkkPeBdM+SfAjzFvcxMCm90SRnhoS2vO0SspW46XqGmckcMvx30QgP
*/
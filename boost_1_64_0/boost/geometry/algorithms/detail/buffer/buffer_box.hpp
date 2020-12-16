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
4+0Nfg5uY0k+YmQsIBlHkYyjjYyjjIxTofOxRsY3SMbCSEbAjkyQcT/we4NkfN3IeADJOJ5kPDCSETDw0H5xkJHxYZJxYiQjYOUJMh4Cfg+TjA8ZGYtJxsNIxsMjGcGn6oC4PXWkgR+GOtj5o6RC055exQEqt+5HuN+WVeh41XuXS3kOhy9lw2gzdwMua3JPXybVbv0ohX7eb+0USzdweVX+rZK2HvcNtQTrcWWFWY91TjKTkZlXp4xUvbm/VZ9TK+J7yhpJlwt8HOpY7XnIN2yjN5fHfvujCZ43Mg7/SNQ3wENpC++PahsSLmjZfjRD+5Hy2f79HUsP9EHP69HynqOyoM+p3OBH9RpH9vlxJE8m4LrL2e04DZVB/g/9vwZek6Dbj1XkPE82r76puaVuQXPjEt/sJo31pwntOyF6A9vXc7Z8yD4lQFr64wyX1rc9Fpl+NXIHPBqT5Wpsntcys7G+uX5mrRhGdTOb6xcuaJlVN2NRaDsNAIfcJ0Du2YOnn5syaC4BzRehi4M8LbzDjbR8TehLuedWZ8gAau5rbUvVq1211OlK4B2ZjrbWzqZUWyZ7xsLpeWTQ0NcjZxfS89ypdv/ovJ5XLQrqujN9a2f29HeH76Ej/+Bgpjsl3u1IhUD7FtHs8NwDZDsyWTZ3mFdxSoIm+QyeOmFh4yzfNiPcO0WmPUv/x7Y5G7pb7GnOSi3rX1EfxRgr8N4yV/mwJsgTnTem2vr9iZRY/Yf6/cjC1d1ypKJ5pVStPdD8Qk+nKdXV2ruypy8V6JlcqV8HyLi+kefeZrfz4AfqG+HcMCEvPm+0VIQ2+l54ZyEWr3OijlHg2nOOmCcMfruZg5bSnLYcfFZUmL0q8PicbQdwTyZcZwx+voj85LCVCnwKvm+Us7Ly97jeCvM9WmAZ/M/3CfsqQrv0I/j+PH2IW5v4bIssYitMDDqfl5LPEmkfiy+6w9Ifm3Oamxy8paNLDqJ160vVnCurW45zInVNTS0d6XR/qs+9otyBew6Uq/ccVkMnh0P2o1T2sD+u8eM+VlLnyrVWbs/XxXCUh8DBUdM5ZZVapf0T9C0uWJ/WlXMh6+mQdVouWpl0hghplrUHPgU6x6DO63w9DEuNrefqnuk5JRWeszrDz3MRRbkfgDNInzZ6KBQ5/HNpKgOS4B/p+QSpQQC9Yk5AH4GSTf/4jNXzTrTvDvwursjMusbmlvpZnkQSQHX2OehsxsA0GxbOq5+5xAbK53y05RdALxozn/d1RH9Jh33vTN/35IZOR9tatIvq5CzWiT8nKZOp73OeOWWG+k/shzsx5vydgB31w9Y2mfJbRWglZLNUp+eAzl0DxHvMy7c6CP1bZ/t+aEQL7FlL7T+aVxRkOqLzsudK2eIgkiYw3z29N1l0FWi5GnNf7Cap6XTp+63g5d5NnCvnGGX5dtJ6/8w0fO88z7RNwyDH5Q78W7VNC8paFjXPrjFOqFxA1e8FOs5VvzrOI/1c6PuYu6pmz7Eul+Oq/X2psNNpXNIv2XG+E3MX8U/J3Tjp4nbMd3V0dnZAJsggeW19PaFewf8rlv8g+9kZufoW+tFw7kfocyNtn9O+hf6APlMUjld5pzHQPlFMfaIEdspF1g4T2V0pFRspkdivsYsRA2ltcaBpPtO3BnbEGuxlLrV2BdKAa9nEsb8Tc4e/o0J78MvB53LIcYXKgbSB2z2WW0twb1ppnQvccwH7rtJC2sBZH2cDdjbKXmXLIg04yubyDeZuG1f/a6j+14LuteB7neWLNODgm2M/l3vdVN1fT7xvAO0bwPtG5Y20gbO+1gG2DmVv0bJIGziXdW1n2/BWLYu0gdvYqIspFumvKmJnQQWOb1Y=
*/
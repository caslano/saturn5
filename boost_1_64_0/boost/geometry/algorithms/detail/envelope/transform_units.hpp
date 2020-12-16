// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_TRANSFORM_UNITS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_TRANSFORM_UNITS_HPP

#include <cstddef>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/strategy_transform.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>
#include <boost/geometry/views/detail/two_dimensional_view.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/algorithms/transform.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{


template
<
    typename GeometryIn,
    typename GeometryOut,
    typename TagIn = typename tag<GeometryIn>::type,
    typename TagOut = typename tag<GeometryOut>::type
>
struct transform_units_impl
    : not_implemented<TagIn, TagOut>
{};

template <typename PointIn, typename PointOut>
struct transform_units_impl<PointIn, PointOut, point_tag, point_tag>
{
    static inline void apply(PointIn const& point_in, PointOut& point_out)
    {
        detail::two_dimensional_view<PointIn const> view_in(point_in);
        detail::two_dimensional_view<PointOut> view_out(point_out);

        geometry::transform(view_in, view_out);
    }
};

template <typename BoxIn, typename BoxOut>
struct transform_units_impl<BoxIn, BoxOut, box_tag, box_tag>
{
    template <std::size_t Index>
    static inline void apply(BoxIn const& box_in, BoxOut& box_out)
    {
        typedef detail::indexed_point_view<BoxIn const, Index> view_in_type;
        typedef detail::indexed_point_view<BoxOut, Index> view_out_type;

        view_in_type view_in(box_in);
        view_out_type view_out(box_out);

        transform_units_impl
            <
                view_in_type, view_out_type
            >::apply(view_in, view_out);
    }

    static inline void apply(BoxIn const& box_in, BoxOut& box_out)
    {
        apply<min_corner>(box_in, box_out);
        apply<max_corner>(box_in, box_out);
    }
};


// Short utility to transform the units of the first two coordinates of
// geometry_in to the units of geometry_out
template <typename GeometryIn, typename GeometryOut>
inline void transform_units(GeometryIn const& geometry_in,
                            GeometryOut& geometry_out)
{
    transform_units_impl
        <
            GeometryIn, GeometryOut
        >::apply(geometry_in, geometry_out);
}


}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost:geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_TRANSFORM_UNITS_HPP

/* transform_units.hpp
PLrE6j9J9WT85W0mfD14AzaHU+ifLKztXtHieJdNwes56hjP+9gUvLGtXDeuCHklHOtFOzZMHgM+EXBoFluCtW2a3pafjHgUkX+fM8JlETm9q/N5SI551+g8eu5T0f/4aFYb3P9dKji6BbiNXsZc3QqC+zHB1S3BdeAK5kbWkH3EtczTLSLfhVW4FCHH92nmqJaRaV89FRdJgxvZB1zNQg19z3HtbUD9LnXVXs1+53LxldT4rlHb7/UoB8IE8yl3V7h/o1bj4Cu6u4fH8W7QeGYpbO4XbrIMZfVd789yGUS6N5EtMvMzOH7aUs+P591C+Yvme2keRZ25NZfHZeEyS2620A36t3yZJ5Qy36yW+UtUZp5vCsPJenpbqzIue2fgdDxy00ndfEXjUSMlFweW/o77VY0Lk2yuVyhEpeS5X8/ngkZnEhz3Dp07BuoAZneG7Oe/d+VyKQvFYfedkPjfnppP/XEdWRK6+44aJgE9rH/f1XlOd37c+p7KwxX2Yl/TfZaDLndRoe6IJj3m/JA5bYIDHfEYeT9xqHBBgvx+1gPgFMtJ+kSnSWEY7qu4/nM95PrPNruNeJp9fW1shFsebYg7xtFOm4cxjpZt9eN8rikc7wsEz7bddB1PbkNuL79gnI4RpWsVRGU+1Vb4LRGF6yjeVr9knHRN4yLnR3CMPZnIdeJXhFNjBQkTR6pZYhz8LTg4koJqoS35ccxElO/3U3LNUQseR/5E3LhqI0rZZ/05h0f3pDDvLzk8Spbt/jfmqcsJJO/7iyem4ZqoG/eJU7+uv5v1872m3cuAXPBeBlrP/Nv6mVbOwJyqhWQt+5FstZBtZ2UbjKzZ/CaJkt8H1XFoR6SDbGbXoDQQLeJ6t5PKI4+ys9OzdY6pyqT3hON7js6Fd5k5u+zH/V9I5P7v+ZaDRCKOv6cIHOjFwWiXxpnG6+iZhNuFp6MxvrfFR5IhLAVpdiTXzrMUPM20qBdzwCm1Vwpxmbm8reBU2ktTcuaBg/qdWZaiBYi0DtQ4mbY8nzjYa9y1vmN1AVerdPWaO46MRZttH5WqNl99Yi9tX9bBSNfdf4sM+vXxAsipuaDmjfB3mTbI12HPDKSpYmR/u1hiGK0s7sO+lHC6bjYFOeyhEvOBuV0cHuGcO5nGEeD1rsGdDpxDjx3uMYpFlvfloj4gdi9/BdUBL2/luKTc5qS5+anxScR+6h32Zjux3+uo/abwHfE0zfO7puL72SKPO6vAV+ZpRW3c787j8hzQ90HHTMPF/NaPFaun4ZqxHrn2/DXT8OHbSdhnyvPcmO+iDnX43Vw+TzIR/3TzoWIT86Gimw+5OHuoLyPEXgJZxkfBEewYHMYcTn5bfKXlYmZnvxxy3e+1mJlzUgqsl+O5f9KrC7ozqccTp+HTvIL5r56Ob7rCBu/ocG1Hf8dyr721OcBGqifyG0i0t/s1CscMfn6/ZozbTf2owaKfeh2PkYuUGZy3a7/gqTMjuTdSck1TF9hQgJl779VwbXE4xrLhKhYzs+HsPc0nCaw78+7kZsJswyZFyXF5WOJlq8m+yZos66jkjIVYlTEqT8L1uyYxlCcR4U62WCVBXzaGPSJlPp+YuHEO4cI8cbnGmcMRCH29xrYt4TLwdt4CjH04HcNDVQw9m0boDVJUHdl/bNW5fvXHafI6kdRMsItnkuKxduA6WBigSihtcorkll1sRvHcV71ecuq+rvronJ5OtbxKMeERSdSPN/n+abJS8gy24VsJJ1sgElne0wRGEfB88HQeu2X79Pl6J4/VEvfjyBnA89dc6AXorQRvp3dPxafOz/s/zmSu1so5dtG/vmfqMJSCsOF7iX/CUlwC27l+NccpOGc=
*/
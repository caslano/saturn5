// Boost.Geometry

// Copyright (c) 2015 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_HAS_INFINITE_COORDINATE_HPP
#define BOOST_GEOMETRY_UTIL_HAS_INFINITE_COORDINATE_HPP

#include <boost/type_traits/is_floating_point.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/util/has_nan_coordinate.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

namespace boost { namespace geometry
{
    
#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct isinf
{
    template <typename T>
    static inline bool apply(T const& t)
    {
        return boost::math::isinf(t);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

template <typename Point>
bool has_infinite_coordinate(Point const& point)
{
    return detail::has_coordinate_with_property
        <
            Point,
            detail::isinf,
            boost::is_floating_point
                <
                    typename coordinate_type<Point>::type
                >::value
        >::apply(point);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_HAS_INFINITE_COORDINATE_HPP

/* has_infinite_coordinate.hpp
FLgX9QGkS6Dn98x/Sn+WdBX0N2idLfOx5sru+fjalI9aqhWqI1qou+djpV/+ej62/cWUD6z356808Do9rt9/puKEPb/ce6/KH+7dZtgT+WvPHkg/8PfX0fvq6+il+6+YPvq0y05srH+mvMgfvGfgdbS7nmEg/cDA6/RuPf9zf/o2PGWb1eIHBO/Y/dPXv1hB63Rd3hePX71x9WtnfnrYZXNOu3XOK5OoHPS/c2jBOZ2RE3sfPa6jfKPuYb/+NJC+YmD9w9X637nkiWEfL39iyxmTt7po5KhRn/UNrMdw11cMrIfRKnfX5YYOQdMfBOnfdXRl6JpOV7/OwapbuIG+g34BugW7XuGv6RTmLXfqFebTPTfdwsB6BatOoXO5U6fwMd2z6xX66N6QDzzdgpe85CUveclLXvKSl7zEvf6n/9PyvzFtXv+vYvXdcV3/jw/RTwWBdFptqae1v+Fv7Ns33xc+NqJlLhKROaFs0L91b8Vssq4+G41F6tpaIsghHUCViquxEX6f2qbiN43fE78fVFuLijVp69pG+JHtllhJ8XDtF9Kp8B/i6Pu6xrRd2FC6hfK7qW/d/AL6POk7bU29XZvmcp+e0uLbD2v8bugatqFLfNIan9ZhsE8Qh7PhdKlwItEcVbW/u1p+n/FMDUXASqTUmnAb/e4WdH+FuK8ZHIwh04Zsin6jf00/ma7X9bVmxy4bRaYoNx6z2y3JkZ9cfCedN77GVtr9kjlD17/+4lUe9S06YsiC3bLf+Hx76vcf3/HkrzcYm/pq3oWvTDp2STudV9us379rRd+2z8zcunnGvhN2mqpMP450F8Soo/VWxltzeclLXvKSl7zkJS95yUte8tK/Mq1K1+E5Xv+Hm5rTmebhdOe/ufZviabDVlGta/8m29p/ONb+c7H2P1gvd/rE2v+1d7D2N/4aldBq+Sst0++F00WF+s8bip/9hZZ1/dX6evyNynenDtsj+Pnk61c55ZSZ23fkdl0/j9b0r3nrei956Xf2rgQqqioMP8ZUKjVQQUxENCszKztmkS1qolJZTVpKaQ7jzAPGcBhnHgZlSrtlpZZ5NLWsLG2xOmVlpUaJ1Slyy06UdjI1XCI1NMXCTt+9959xBmbAEYas/u94/Xnr/e/y5r1/vQwGg8FgMBgMxr8aJ6GMaWD5PyvP6rbLDABWw5Zdfz3Auye+HiCwydX0ASkHA/UBV5E+YJnSB+AYUa+/f3cZo28JvKnFIVJwW5y5ruq2/Y1Sdo+KfWzue1c9dMaZqWOHtMuMmtOwOoCYMsSkl7EOgMFgMBgMBoPBYDD+rYiE/3+WBwvY2CG9C9G/EfL/jYk7Gss/j2TqPigJKL1R2ici/HkL2dgHD0tTzA0Q/vUyTr5bLXHySZS7b00HkSdvYL5NB5O5zqG6Lddtp+MpoE2ayeNQD4zJcXiydfcgt3WcLvPsydyBJfL6Abno1nyDrhbXpuFYXKI4lkpyvu6ms4SM74sbKCfRuxKlDcp+lA64bnrwdqH/xonEgrJ96XW0LyMk/+p4dmgeZftcIq5Bts/HRCpUHb6+cTWTbZeRDPK2V1k9una0bw7La2923uFw2kVaRI2OJYO21o5ee0Nmpkc3FE9izM7wO5ae6x5uzcnT5RrlNGb+x/11Jou1hssVGCoHwb2niv03fnJw1q4r7n7m2kkXm+55/wVT+DkREqNk7L4vTj+/TMXztx2q8u3Nw/bSMhVTXwJ6AEXExrfYYdKSUS5CSUOxo0zcoWL8H92h4vtfA/WP8S8S+wdDnwSak3Y01n8ftkW8f4udJq0Hijfu34y//WP/87E9BYVyAFSP/ad4f9QneMd5y1HMFOtfKu41AvMclHI=
*/
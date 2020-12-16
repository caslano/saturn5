// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_SELECT_COORDINATE_TYPE_HPP
#define BOOST_GEOMETRY_UTIL_SELECT_COORDINATE_TYPE_HPP


#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{


/*!
    \brief Meta-function selecting the most precise coordinate type
        of two geometries
    \ingroup utility
 */
template <typename T1, typename T2 = void, typename T3 = void>
struct select_coordinate_type
{
    typedef typename select_most_precise
        <
            typename coordinate_type<T1>::type,
            typename coordinate_type<T2>::type,
            typename coordinate_type<T3>::type
        >::type type;
};

template <typename T1, typename T2>
struct select_coordinate_type<T1, T2, void>
{
    typedef typename select_most_precise
        <
            typename coordinate_type<T1>::type,
            typename coordinate_type<T2>::type
        >::type type;
};

template <typename T1>
struct select_coordinate_type<T1, void, void>
{
    typedef typename select_most_precise
        <
            typename coordinate_type<T1>::type
        >::type type;
};

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_SELECT_COORDINATE_TYPE_HPP

/* select_coordinate_type.hpp
Y5wYQ3tH077Dad/Ds5S/9MG67C3tpzIf1i1P6T/uUSRNZrtn9qh06inGuaG8P9zG9Tmf/uW+9+P89UjifQX94wDtso52mRrM9XQU7XAvx/8uxp8h3L9lMF6UcZ/KODOO5zgH7ZTNdXrkOe47OH/iHZzvI3le3c77Gpb3vof7qCDGRa7nBVy3tq3jObM/4zPrmZii7Dg8mfum6YxbL/L+o512ma+exzYwHq/k+XWakh+iP8ynXx8eRbtwHbLzXuEU8015hutuCefZe7z/TuU+IZj+8Az34XJukpTzKdPG9ZjnkPl+jPvrWX814+RJnnfO0e+eZf9f4LmA+ng8wfnHe/P5gxnvrExr2G87z1Exal3I20Z7r2J9HYy7nK8nlvLeIoX+S3vsLqLevKdx8J6ggOv/lESeH3w4H1nfud9xfhRwvHszHrP9vA417n3cv4cUcF647xkild4DMH7eYne2e5Jx4QL9bTm/b6W/2zexfcRNL2kvivel7vUxlnGK9e3+Bf2H+5fYu1j+XdqbcTN2saRyf8/y7vV1Otf70dyfX2L8WsrxmE2/oj8nTOA+7H3ux+nHY6j/5Y1Mud5kruQ8vZP+NpLnuuc5j+l3p7ifm8rzxNAM3mPw+ckFtAPjyoBo2EPKP8R46r5XuIf9TWW8i/fg7138zri9/E3ajetocgH9dj79braab5dbGUc4L88s5HqeSj+jX+yMQ39FjvgVIfk5bjsSuX8t4O+Un7N8EuOV7Bsl5e9hfbieHqffJj/A8yjvzy/14bmE97DjvmKcvofrUCbPh2/znpDtbAnlOhOp9BwcTPs6eJ8zjP7A35cyub8saON9ajTHbRXjEc+ffqO4f6MfnkljvBjC/RLjUcFDvFcYQP8v4++HnEen6Kcr2b9Xz3K9kPVBUomrkt7NdYL1buW4x87m+PI8Zqc9jr9E++zhPqhZzauDAfTLt3hvz3O6x1Psl/tcxPRoF8/p9Odozm+PR7i+5bGdhTwvcLyOnmc/uK881MDzG/eb67jubg1he9yXOup5bqU/732B6zzLTXyQ84vlp9JPVztob/f6/RDnI9e7vHX8XWsH43cp98vPcj+9gOV5fxn9Oe9HmD+B43CC9+J5Nu6/4hhH+nL8Uin/Bu/b19K+jI/jXLwn3sTfd+mfBy9w3e1ku3/n+HKcDr5JPc/Qb5n6fUI78x4gk36fuZX3D/7cB/F8MZz77l3Ub7Uf4//LnHfct59L5jmc3w8Nob9P5zx7mOvHYPo353t2FOPtHK5DD9BvZ9BPT3O+7OD9czv7bWd/4+jHTyq7DWf821nC/jLOenA8N9Bv93EcR7IfVxkf7Fe4X1yo/MbBeHvCvS5wfAdw33jpfuXfxxifTqfy/Ei/SL6VdqO/HOQ+JmSOKjec/fX+p0rtL3G82N/B57l/XM/xrOZ68mf6/QtcdxkPptzPcbuf95fvcJ0aSD9x35/Tn7ayH1OiOV7cD+RxHTjKc1Qm1/kNs6hvIO0Rxfnbps5HDq4LscVc599gfP2A87Kc/bqD9z2zGP8dvE+gfPd7PD/QP5f/kP4az3Fx30vey3jAOLuS99FXt3J95zp5warsvZffL3/K8aa/HEri/RTnxVGud6deoP+9STs8wrjwGPczCbwv4zp0aD315vMBf6d+ixg/eV7K5jw+lc44z3NMHuPgogTqdUWN/7nLjBsc512trG8x7c3+n9hBf6C+Ix+hXnmcB+5zTDrvgTdz/eI82XrVU92Pjuf8SeH9zWy1Xh/kuSzbzvq4TnrbOK6bGX+e4DqeQ/s8x3FYw/5x/Q7h/dYp7uuHbuG4ufdvHK/oj7mfGs15z3yrMz1U+hD3obT7Vfbr6CY=
*/
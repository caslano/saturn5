// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Geometry Library by Barend Gehrels (Geodan, Amsterdam)

// Original copyright notice:

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef BOOST_GEOMETRY_PROJECTIONS_PHI2_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PHI2_HPP

#include <boost/geometry/srs/projections/exception.hpp>
#include <boost/geometry/srs/projections/impl/pj_strerrno.hpp>
#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry { namespace projections {
namespace detail {

template <typename T>
inline T pj_phi2(T const& ts, T const& e)
{
    static const T TOL = 1.0e-10;
    static const int N_ITER = 15;

    T eccnth, Phi, con, dphi;
    int i;

    eccnth = .5 * e;
    Phi = geometry::math::half_pi<T>() - 2. * atan (ts);
    i = N_ITER;
    do {
        con = e * sin (Phi);
        dphi = geometry::math::half_pi<T>() - 2. * atan (ts * math::pow((T(1) - con) /
           (T(1) + con), eccnth)) - Phi;
        Phi += dphi;
    } while ( geometry::math::abs(dphi) > TOL && --i);
    if (i <= 0)
        BOOST_THROW_EXCEPTION( projection_exception(error_non_con_inv_phi2) );
    return Phi;
}

} // namespace detail
}}} // namespace boost::geometry::projections

#endif

/* pj_phi2.hpp
y07G0z8eM1wUbavTh3CjHSINGnEpUkdtoxaQenNUYp17vF3nLpJ6vhvjkHb8usFLesxK7JjJtdit7J0ar2Ul96r0U/44S5l9or1TQcuNoO6bTLmyzOmEnX+OMp3fT+i2zn7+NxdYG2E/W4au297Nl95HuBFY1/XWWJ2q/SYTspO++TOT9kZVTWGkcMq06ppp7j4WP25mFTdBVFRX+08mWrvCplVUVc2orNFULpzm7rH302aUl5aX6i8LmQzOqC62d7jJ73ibLb9MZzBpPfy00rKy4sn5ZfhpxXtr+2fbFhpRalnLWCfB2OTe9wnCNtspcE+fXJtYJcLujhiPvPLtUdIOWo/dSDfziyL2lTdezLS3ZlTZJ8tmbDAXzf7OkzJEK8eu/bNuzcP4TZzXyum0TbW/xMWL+ZR9N9kIcn1lWVsyLVOmVaee9R+gCrk0TM8nrI+J1zuinfEO3SqurRbvOxbFfJ+E3qxhXlaFcWPtjS3xOun7yHb5alo6qJLMafONwJ+h7yzjrZDFvuvZplmfkVkdyI8npmKGaIn0CYl5Dk+z4NNIW35e4j3Y/Pp67aVbMp1nzIQdMSWRrp0thjBJGpepwuoi6S+08eXyfTfn6ymua+ow7gRX9yztr+vUd7H57xnrMoSPJ/Hgsum2TGtMphmrSKa1qsmdWgCXGBdW4g1OO6cVtFucyFfEjkAtmANZZZlLE3kTefwWufTlwXS/VY6GJ/vpKbZDBN78tcLM8J+S0kQwds5g+H2O0AWr0/GXcwQLz1PXWewb5tI/7DcluS6CaorqJ2mlz9fG2QsubLw8++72aM0V7e3zI8qD///7/7////v/v///+3H/Zb8WUlf8hLMaF3tqlz9zH/gK3lI4P6wWHeepm0/w1GvzPfV6saeW8/uGc3lP55mwuvsYT/Um/N4JIXXkGvYwX+GpTz4PsU+au5cvVOqz+pD6SwPpf+des7+yV3ZxWB0yOKRu+hXnrA+kjA7uizsDO/a7sHryGqVei4XVfi+zv/uukOr5Fmd1d+bd/fFh9cKysLplmKe2+YmnLjjEU9VZIXX21JB6ZQzncTYLqT33DamLqjkvcghvSU/zOLyk1HeL2ZdfyK3OvwipLX8dVufe4alXR3APWyd+oTx8W69yx8D+vGT6pqfeneupgovpP+044UxPfXot7SP902kh1WcXT53+NG8FzvRU7lch1eNxziJBm19hN3uE9z2PNwgf8tQJr3jqkgto/xdKvXUtdPq5py66yVOL7/bUoB3C6vvjw2rlYdo28NQDKzzVUsydyoVhNbPeU/0e89TO/cNq1Aecwzk0pAb0xjY6zFOjr/bUNC+szsL6vuB15k6ne+rvId7eKQ2pzU4LqcLBjMWXIbX1GZ7a/gVekN4Wv+Cm3PO8E/cN1qKEP/HU0X8LqUF/99SXL3Ef6M0h9Sb11HCL5SHvYedR7mf3sS/+VE99tz1zAvK9ivLu3M5TffA0vzExrJ7fA/s1y1NbXOmpBX9lXfhg6t8vrG7LCKu5/aH/zor33HgPeB/8EY+E1G3tYbXv9LD6y54htYbw2iMYx289tQKMHTTPU4v+zCzpQPpWxTtlfDP0L9yx+FpYnbMqpP76SkiNPymszvxWqd/+Dt9rjL3gf4DGn4XUONreeLZSp66EjnNDanNovEeIth8YUts87qnJl4XU52+H1amlnrr9/ZAaeISn2v4YUr8Dp9N2wLf2uqe+epSxmqfUrVdyF/A7IXU3/dl6U6VunAx+HwyrW/fjdVja8elenrr8mLAaWBRSNcNDas4B2HOMSQF92rIBrByI3XM65WaDidywunKkUu9+Ay9MZF4EPXfcPKSOOSCs1j4bUjc=
*/
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

/* meridional distance for ellipsoid and inverse
**	8th degree - accurate to < 1e-5 meters when used in conjunction
**		with typical major axis values.
**	Inverse determines phi to EPS (1e-11) radians, about 1e-6 seconds.
*/

#ifndef BOOST_GEOMETRY_PROJECTIONS_PJ_MLFN_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PJ_MLFN_HPP


#include <cstdlib>

#include <boost/geometry/srs/projections/exception.hpp>
#include <boost/geometry/srs/projections/impl/pj_strerrno.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry { namespace projections {

namespace detail {

template <typename T>
struct en
{
    static const std::size_t size = 5;

    T const& operator[](size_t i) const { return data[i]; }
    T & operator[](size_t i) { return data[i]; }

private:
    T data[5];
};

template <typename T>
inline en<T> pj_enfn(T const& es)
{
    static const T C00 = 1.;
    static const T C02 = .25;
    static const T C04 = .046875;
    static const T C06 = .01953125;
    static const T C08 = .01068115234375;
    static const T C22 = .75;
    static const T C44 = .46875;
    static const T C46 = .01302083333333333333;
    static const T C48 = .00712076822916666666;
    static const T C66 = .36458333333333333333;
    static const T C68 = .00569661458333333333;
    static const T C88 = .3076171875;

    T t;
    detail::en<T> en;

    {
        en[0] = C00 - es * (C02 + es * (C04 + es * (C06 + es * C08)));
        en[1] = es * (C22 - es * (C04 + es * (C06 + es * C08)));
        en[2] = (t = es * es) * (C44 - es * (C46 + es * C48));
        en[3] = (t *= es) * (C66 - es * C68);
        en[4] = t * es * C88;
    }
    
    return en;
}

template <typename T>
inline T pj_mlfn(T const& phi, T sphi, T cphi, detail::en<T> const& en)
{
    cphi *= sphi;
    sphi *= sphi;
    return(en[0] * phi - cphi * (en[1] + sphi*(en[2]
        + sphi*(en[3] + sphi*en[4]))));
}

template <typename T>
inline T pj_inv_mlfn(T const& arg, T const& es, detail::en<T> const& en)
{
    static const T EPS = 1e-11;
    static const int MAX_ITER = 10;

    T s, t, phi, k = 1./(1.-es);
    int i;

    phi = arg;
    for (i = MAX_ITER; i ; --i) { /* rarely goes over 2 iterations */
        s = sin(phi);
        t = 1. - es * s * s;
        phi -= t = (pj_mlfn(phi, s, cos(phi), en) - arg) * (t * sqrt(t)) * k;
        if (geometry::math::abs(t) < EPS)
            return phi;
    }
    BOOST_THROW_EXCEPTION( projection_exception(error_non_conv_inv_meri_dist) );
    return phi;
}

} // namespace detail
}}} // namespace boost::geometry::projections

#endif

/* pj_mlfn.hpp
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
*/
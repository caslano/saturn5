// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.
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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PROJ_MDIST_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PROJ_MDIST_HPP


#include <boost/geometry/srs/projections/exception.hpp>
#include <boost/geometry/srs/projections/impl/pj_strerrno.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry { namespace projections
{
namespace detail
{
    template <typename T>
    struct mdist
    {
        static const int static_size = 20;

        T es;
        T E;
        T b[static_size];
        int nb;
    };

    template <typename T>
    inline bool proj_mdist_ini(T const& es, mdist<T>& b)
    {
        T numf, numfi, twon1, denf, denfi, ens, t, twon;
        T den, El, Es;
        T E[mdist<T>::static_size];
        int i, j;

        /* generate E(e^2) and its terms E[] */
        ens = es;
        numf = twon1 = denfi = 1.;
        denf = 1.;
        twon = 4.;
        Es = El = E[0] = 1.;
        for (i = 1; i < mdist<T>::static_size ; ++i)
        {
            numf *= (twon1 * twon1);
            den = twon * denf * denf * twon1;
            t = numf/den;
            E[i] = t * ens;
            Es -= E[i];
            ens *= es;
            twon *= 4.;
            denf *= ++denfi;
            twon1 += 2.;
            if (Es == El) /* jump out if no change */
                break;
            El = Es;
        }
        b.nb = i - 1;
        b.es = es;
        b.E = Es;
        /* generate b_n coefficients--note: collapse with prefix ratios */
        b.b[0] = Es = 1. - Es;
        numf = denf = 1.;
        numfi = 2.;
        denfi = 3.;
        for (j = 1; j < i; ++j)
        {
            Es -= E[j];
            numf *= numfi;
            denf *= denfi;
            b.b[j] = Es * numf / denf;
            numfi += 2.;
            denfi += 2.;
        }
        return true;
    }

    template <typename T>
    inline T proj_mdist(T const& phi, T const& sphi, T const& cphi, mdist<T> const& b)
    {
        T sc, sum, sphi2, D;
        int i;

        sc = sphi * cphi;
        sphi2 = sphi * sphi;
        D = phi * b.E - b.es * sc / sqrt(1. - b.es * sphi2);
        sum = b.b[i = b.nb];
        while (i) sum = b.b[--i] + sphi2 * sum;
        return(D + sc * sum);
    }

    template <typename T>
    inline T proj_inv_mdist(T const& dist, mdist<T> const& b)
    {
        static const T TOL = 1e-14;
        T s, t, phi, k;
        int i;

        k = 1./(1.- b.es);
        i = mdist<T>::static_size;
        phi = dist;
        while ( i-- ) {
            s = sin(phi);
            t = 1. - b.es * s * s;
            phi -= t = (proj_mdist(phi, s, cos(phi), b) - dist) *
                (t * sqrt(t)) * k;
            if (geometry::math::abs(t) < TOL) /* that is no change */
                return phi;
        }
            /* convergence failed */
        BOOST_THROW_EXCEPTION( projection_exception(error_non_conv_inv_meri_dist) );
    }
} // namespace detail

}}} // namespace boost::geometry::projections

#endif

/* proj_mdist.hpp
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
*/
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
kr8vvJVzUNdj0ykfPySDmJ28BLS9ZgH0G8R5rQriVuR2KP16X0DrvqznkcjDUmTsdXLFrzKWCeQ+4f1D4Pk5udAOHZ1/DHvrW5JvRe9l4z+od15eRQ8+ls38NuLDq7i2E5lhP8rDryw7HRvIXvfYQmiMPvKaiI0n4ctEkUl4asul2PrbMvCBs9hvyoLG5OCQp/wouV9yc/1Yz8lvQAP4a8bRWcSU2OWn0NFXwsM7Yz+zsYvI49WcLXl3BPFpMXr5ZPge33qXT/Cr2BcvzkXHs9YXF6o9anzO8ZwdQdd//Rgx7Ebyh+/j171FzvB+8rjojQevxcauQmbg0+9Y/9oPsPmjkU/4sByfI34BtFoPL98BTf6eib+PLvkPfij0/pI1PPckX59ejfxXtxIHUt51GbzFuj79LrZxDn2yPhPwm25hTv3uYO//BvplDL8izu2Anx7Dj736XGSigZzIn+Fn+PH132Nn1BlE5ON27Mm9IXgEHfcQ/sPx0GUNtuVacnELqHcz9mmLm9HP0PTrn+GRM9AP1Nu/D3ob3tsOftyD/GJjhNwtPHjY9vApMtfxGrH1L+jhYuaPjXyWse71RgY5T3z//fF3xxH/wx+lrMHTD2O7j4bn4dFTFrIOuyGDh5LX2VPlc8grs0ade0F/+PQW/I9a/ImFf8LuoT9+W47NuI32D8e3IqfzRIV/V2S348kTvKHOqBInYrPvP4gxx6ANumnFAPzIXYkPs+GDZZyX/C00ZC5P4I+NPoH+iWEq74KXkPt9V5AvwNcvfgB/vRn7daLHOVz8i0z8nQPwnbZABp+mXeZaU8jeGX7cxjxiLHJdbXP4W40zhj8cQ5c+maVzWCdiozIb8O/OQmfA1w+8w9ruyVlXxnByxNN+2bmV+JrkBUKLyDEha1Xkx/psRby3D/vEy+AL1qKL9f64nH1p6j0L3d/+Brrx/8ePRPd8kanPKxSNwsf5E75SFvEuvuySQ7A35Ekn7Qxf3wOt3sKPp631G6AhMlgVx/5+QJuVtLeCmKGcWOQR5gvf3zgbX/0u5GUraDgTXvoPckXMcDyxzgNziT+/wU/LIW+3K/o0gzMqg9GZQxgDsr4cX+xu/h0Jj/1uX/bezlN72eiuc+EfeDQ/An81Epcfid6Dd5+twufB7pxXQT4HPXMh8uOtJg6h3RB2eCL76p07sf+O73/FRvzvy9Fr5HZ33B3/5UnOp52Pbn6E3Ae2ZOA55Blm4R9j02ddmIkdJld4LD4cBudX6KCbjsMHws+L4t98j24Ln0Je8UbsBOO+vhjdegQ2+Fj0HHcpPtgb3/sj8o+VyAc6eAm+xF7YgiE/YKtK8TEmcUYghp7sS/xxNznvsZSH4S/k7+8dxIH9kY2B6InvmOe98Eoxtmkaev8B9jkyyZOHM8kF4N9si81HLrLg0Wx468B9WO8pxBBHkVcbi9ycBa+gs96CB37N2p1GTBJ7OAubSRlye81o9oeyOJuFDv8UvnznNg9fHDo1Iwcbse1jsbnKVl+AjenL+lV7XuQl9uKrsZOPqn1FciD4M7sNxXdhfCt3YY/pwQx9tvB69Nzqx9Bns8kz3YcOJX64D5q/AD33z8VP3kB+K5N490dydvR3TAd+I/F26XByg/2I3dH/CxjXYcjiWuj0wdnI0qnkEbaFBur8wSVZWl6mFrOWN6NjiM0/UPdD0KvbwQ9F8OLBEc7fvAEfsI4j1rOHdRq65ih4rpXY+ET2IdATK0bg+/ZDT5MTHjWcnCY824oeOPVM6qJvdm0iX3Ez7a1BJujzWMZ3ybP4yvDJp9D+D+j7hcTz04E34setgOZH9CP2uA7e557VmA+wo/jDc8lhNc1iH9RDpxM=
*/
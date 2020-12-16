// Boost.Geometry - gis-projections (based on PROJ4)

// Copyright (c) 2008-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018, 2019.
// Modifications copyright (c) 2017-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Boost.Geometry by Barend Gehrels

// Last updated version of proj: 5.0.0

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_LABRD_HPP
#define BOOST_GEOMETRY_PROJECTIONS_LABRD_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace labrd
    {
            static const double epsilon = 1.e-10;

            template <typename T>
            struct par_labrd
            {
                T    Az, kRg, p0s, A, C, Ca, Cb, Cc, Cd;
            };

            template <typename T, typename Parameters>
            struct base_labrd_ellipsoid
            {
                par_labrd<T> m_proj_parm;

                // FORWARD(e_forward)
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();

                    T V1, V2, ps, sinps, cosps, sinps2, cosps2;
                    T I1, I2, I3, I4, I5, I6, x2, y2, t;

                    V1 = this->m_proj_parm.A * log( tan(fourth_pi + .5 * lp_lat) );
                    t = par.e * sin(lp_lat);
                    V2 = .5 * par.e * this->m_proj_parm.A * log ((1. + t)/(1. - t));
                    ps = 2. * (atan(exp(V1 - V2 + this->m_proj_parm.C)) - fourth_pi);
                    I1 = ps - this->m_proj_parm.p0s;
                    cosps = cos(ps);    cosps2 = cosps * cosps;
                    sinps = sin(ps);    sinps2 = sinps * sinps;
                    I4 = this->m_proj_parm.A * cosps;
                    I2 = .5 * this->m_proj_parm.A * I4 * sinps;
                    I3 = I2 * this->m_proj_parm.A * this->m_proj_parm.A * (5. * cosps2 - sinps2) / 12.;
                    I6 = I4 * this->m_proj_parm.A * this->m_proj_parm.A;
                    I5 = I6 * (cosps2 - sinps2) / 6.;
                    I6 *= this->m_proj_parm.A * this->m_proj_parm.A *
                        (5. * cosps2 * cosps2 + sinps2 * (sinps2 - 18. * cosps2)) / 120.;
                    t = lp_lon * lp_lon;
                    xy_x = this->m_proj_parm.kRg * lp_lon * (I4 + t * (I5 + t * I6));
                    xy_y = this->m_proj_parm.kRg * (I1 + t * (I2 + t * I3));
                    x2 = xy_x * xy_x;
                    y2 = xy_y * xy_y;
                    V1 = 3. * xy_x * y2 - xy_x * x2;
                    V2 = xy_y * y2 - 3. * x2 * xy_y;
                    xy_x += this->m_proj_parm.Ca * V1 + this->m_proj_parm.Cb * V2;
                    xy_y += this->m_proj_parm.Ca * V2 - this->m_proj_parm.Cb * V1;
                }

                // INVERSE(e_inverse)  ellipsoid & spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();

                    /* t = 0.0 optimization is to avoid a false positive cppcheck warning */
                    /* (cppcheck git beaf29c15867984aa3c2a15cf15bd7576ccde2b3). Might no */
                    /* longer be necessary with later versions. */
                    T x2, y2, V1, V2, V3, V4, t = 0.0, t2, ps, pe, tpe, s;
                    T I7, I8, I9, I10, I11, d, Re;
                    int i;

                    x2 = xy_x * xy_x;
                    y2 = xy_y * xy_y;
                    V1 = 3. * xy_x * y2 - xy_x * x2;
                    V2 = xy_y * y2 - 3. * x2 * xy_y;
                    V3 = xy_x * (5. * y2 * y2 + x2 * (-10. * y2 + x2 ));
                    V4 = xy_y * (5. * x2 * x2 + y2 * (-10. * x2 + y2 ));
                    xy_x += - this->m_proj_parm.Ca * V1 - this->m_proj_parm.Cb * V2 + this->m_proj_parm.Cc * V3 + this->m_proj_parm.Cd * V4;
                    xy_y +=   this->m_proj_parm.Cb * V1 - this->m_proj_parm.Ca * V2 - this->m_proj_parm.Cd * V3 + this->m_proj_parm.Cc * V4;
                    ps = this->m_proj_parm.p0s + xy_y / this->m_proj_parm.kRg;
                    pe = ps + par.phi0 - this->m_proj_parm.p0s;

                    for ( i = 20; i; --i) {
                        V1 = this->m_proj_parm.A * log(tan(fourth_pi + .5 * pe));
                        tpe = par.e * sin(pe);
                        V2 = .5 * par.e * this->m_proj_parm.A * log((1. + tpe)/(1. - tpe));
                        t = ps - 2. * (atan(exp(V1 - V2 + this->m_proj_parm.C)) - fourth_pi);
                        pe += t;
                        if (fabs(t) < epsilon)
                            break;
                    }

                    t = par.e * sin(pe);
                    t = 1. - t * t;
                    Re = par.one_es / ( t * sqrt(t) );
                    t = tan(ps);
                    t2 = t * t;
                    s = this->m_proj_parm.kRg * this->m_proj_parm.kRg;
                    d = Re * par.k0 * this->m_proj_parm.kRg;
                    I7 = t / (2. * d);
                    I8 = t * (5. + 3. * t2) / (24. * d * s);
                    d = cos(ps) * this->m_proj_parm.kRg * this->m_proj_parm.A;
                    I9 = 1. / d;
                    d *= s;
                    I10 = (1. + 2. * t2) / (6. * d);
                    I11 = (5. + t2 * (28. + 24. * t2)) / (120. * d * s);
                    x2 = xy_x * xy_x;
                    lp_lat = pe + x2 * (-I7 + I8 * x2);
                    lp_lon = xy_x * (I9 + x2 * (-I10 + x2 * I11));
                }

                static inline std::string get_name()
                {
                    return "labrd_ellipsoid";
                }

            };

            // Laborde
            template <typename Params, typename Parameters, typename T>
            inline void setup_labrd(Params const& params, Parameters const& par, par_labrd<T>& proj_parm)
            {
                static const T fourth_pi = detail::fourth_pi<T>();

                T Az, sinp, R, N, t;

                Az = pj_get_param_r<T, srs::spar::azi>(params, "azi", srs::dpar::azi);
                sinp = sin(par.phi0);
                t = 1. - par.es * sinp * sinp;
                N = 1. / sqrt(t);
                R = par.one_es * N / t;
                proj_parm.kRg = par.k0 * sqrt( N * R );
                proj_parm.p0s = atan( sqrt(R / N) * tan(par.phi0) );
                proj_parm.A = sinp / sin(proj_parm.p0s);
                t = par.e * sinp;
                proj_parm.C = .5 * par.e * proj_parm.A * log((1. + t)/(1. - t)) +
                    - proj_parm.A * log( tan(fourth_pi + .5 * par.phi0))
                    + log( tan(fourth_pi + .5 * proj_parm.p0s));
                t = Az + Az;
                proj_parm.Ca = (1. - cos(t)) * ( proj_parm.Cb = 1. / (12. * proj_parm.kRg * proj_parm.kRg) );
                proj_parm.Cb *= sin(t);
                proj_parm.Cc = 3. * (proj_parm.Ca * proj_parm.Ca - proj_parm.Cb * proj_parm.Cb);
                proj_parm.Cd = 6. * proj_parm.Ca * proj_parm.Cb;
            }

    }} // namespace detail::labrd
    #endif // doxygen

    /*!
        \brief Laborde projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
         - Special for Madagascar
        \par Projection parameters
         - no_rot: No rotation (boolean)
         - azi: Azimuth (or Gamma) (degrees)
        \par Example
        \image html ex_labrd.gif
    */
    template <typename T, typename Parameters>
    struct labrd_ellipsoid : public detail::labrd::base_labrd_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline labrd_ellipsoid(Params const& params, Parameters const& par)
        {
            detail::labrd::setup_labrd(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_labrd, labrd_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(labrd_entry, labrd_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(labrd_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(labrd, labrd_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_LABRD_HPP


/* labrd.hpp
ffUyVq977Xk4Qgd1rjnrUsOyPDz6lozslay1auuJ8CJXwoDH8WQuZg1VHlWNgii5MwR+q51LWsvC0+pNQfsqFm9jtqAWXql8y1RZtfE5Ez6afEiu7DKqwIQgKVDrSc1vP+j3wtME7E8BOzhgPyscSCmVWRMwBwGdvs7szRV/U2bh5f28mgc36ZeU4dDa47qxQapyvMGuld2mKldVYuR9Riv7bk8WcaREfTbzZ0NbCIUjzJ6aW674PhaMl/ullpP+skeueItS71BM/UQR9RiFKplOteUNLJcpYYn0dsPZsHtYc3mINIIRDXodsAjJSn4ENKyIVeluMIE6r+CVxxd0XEYhF19GIRd4LwveaPeon4avFfUtV+iovV6rMGov76ogas9JHMwEaiotNnJ1bcLhASe+LL5V+4qmBRSPMwvv53drO0TExzDNR2qRAIIAdNMB1J5EW59mH6YCK3D884bmoqnUNVVwA7I2YSq4MaDV2T3N9ssjiEnXiRalrRdq4Rlc+/+Itt7/3s9piu/J+zv/IfuKyxF+T+wrnnZ/5z9kX3Foz/EZ3OR9nf+wfcXv3df5Wbev2AT8JuA3GXXSHfcy09jypDvAWEsXpiNAM4KeL/48iEbA6nXpXulwlrvN79b5EU3zvXp+17HSzO/q/aJbHfXwu6ZQzfeqPAKYEpIhodgbW/ZIQQewaY9lAc2kWm0zqTtFxn/XSJ5J5Y/qA/sUi4IehaXvQ4V4FMFlPCtZzFOzimXozm71wSL/VO0KN86ibhpfgZqj6BUNNy4DCfLfwP478ZV8xiug7zJovvq6jb+uJYS7ePYk419i8GIeEWhBfXkOwYNHh82kij53gS9t2XdGnsqOIpV6T3Ktndj1iwyxg4RY7SAHsW/aiQ1hVQN7+HOs8H/pzwGeHOIIX24PP5LCD7eHn2iF/5GEX+4Mn2sPH6Hwr3hs4XdebsJ/VcKfN9QR/g0gmPBFSv++XlWJPKJ3lZ3enRa90UJvqJPeKju9qAu91BGlLW9JJbpvX65EU4ejEtV9MygSxX4z7yansneO6O7pRzUFNFjM9wlblfyzUJsn1F7CKzEJ1BSWl+uT8MBB221B/6Ls20vQP1HQd77BQdslKKJEMi7LXE+8I+HeHcHh7sMr8ZCEW2dJFscG4B1+tLEggYRgZN4Hadrul90dWAnKaQaKzVsfpPsojhz10ccDfHbqmX2MJ3p+vbek1lvwmAE4Oanr4h38DQRXLwhhIEov3oV4p/mSm0LgrLFJC2iNRx1Ju4kkTucSk9vE3FAc/xQ6/phai1kgS15+Cs1ISKrExHS3MzO0rLZXp5Y+OHZx0nEXhS8RHhdGaFEDptaoFKr1ZmH4HjjwUUY8tG33wxm1ogkv36aESDnlgXbypmBiVoJkoH00eEEEWBVO7EhTUW63FfjJIkruyecC70cF/hRu9VZY8NThlYTxq3Aa8ptuC7qbbwAjbLthJMFwAX2A0Bt2HE6yKVhQ0Feqg2bNcJk2mCYNuUfRVSEXF1JWNyQC8VaToE18Aw5ipFS3JfKp6BuSgfhWEISfAucJ2J8BDgnYZwdPIfkjGq2iWCERLDWfoM4IX/huRoRB9wj7uEfY1wbGN8C2GJXma/jK78FpK9tGsjyh8jB2GW+gBgUAojFVSS6m0mjxO7MvDjhVCONHytr6ZkPg1VOpfQh5YI1IxOKtcF0M71x463JupYGuA5hUSoA7oqEy92aUOTeWMmoT6XYu+0N0LS4gipBJN62Oo5tMQtp2oqn7k+vNikonwDB9rDBdCLOxIAfoygxeCz4Vr8zpAW6cwnL+zkwOf2qMrQPaStXjxxvE3hdRzWgBdbQ5zi2d2sBVk8AXacM=
*/
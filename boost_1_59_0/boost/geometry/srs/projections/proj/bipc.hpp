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

#ifndef BOOST_GEOMETRY_PROJECTIONS_BIPC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_BIPC_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/math/special_functions/hypot.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace bipc
    {

            static const double epsilon = 1e-10;
            static const double epsilon10 = 1e-10;
            static const double one_plus_eps = 1.000000001;
            static const int n_iter = 10;
            static const double lamB = -.34894976726250681539;
            static const double n = .63055844881274687180;
            static const double F = 1.89724742567461030582;
            static const double Azab = .81650043674686363166;
            static const double Azba = 1.82261843856185925133;
            static const double const_T = 1.27246578267089012270;
            static const double rhoc = 1.20709121521568721927;
            static const double cAzc = .69691523038678375519;
            static const double sAzc = .71715351331143607555;
            static const double C45 = .70710678118654752469;
            static const double S45 = .70710678118654752410;
            static const double C20 = .93969262078590838411;
            static const double S20 = -.34202014332566873287;
            static const double R110 = 1.91986217719376253360;
            static const double R104 = 1.81514242207410275904;

            struct par_bipc
            {
                bool   noskew;
            };

            template <typename T, typename Parameters>
            struct base_bipc_spheroid
            {
                par_bipc m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T pi = detail::pi<T>();

                    T cphi, sphi, tphi, t, al, Az, z, Av, cdlam, sdlam, r;
                    int tag;

                    cphi = cos(lp_lat);
                    sphi = sin(lp_lat);
                    cdlam = cos(sdlam = lamB - lp_lon);
                    sdlam = sin(sdlam);
                    if (fabs(fabs(lp_lat) - half_pi) < epsilon10) {
                        Az = lp_lat < 0. ? pi : 0.;
                        tphi = HUGE_VAL;
                    } else {
                        tphi = sphi / cphi;
                        Az = atan2(sdlam , C45 * (tphi - cdlam));
                    }
                    if( (tag = (Az > Azba)) ) {
                        cdlam = cos(sdlam = lp_lon + R110);
                        sdlam = sin(sdlam);
                        z = S20 * sphi + C20 * cphi * cdlam;
                        if (fabs(z) > 1.) {
                            if (fabs(z) > one_plus_eps)
                                BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                            else
                                z = z < 0. ? -1. : 1.;
                        } else
                            z = acos(z);
                        if (tphi != HUGE_VAL)
                            Az = atan2(sdlam, (C20 * tphi - S20 * cdlam));
                        Av = Azab;
                        xy_y = rhoc;
                    } else {
                        z = S45 * (sphi + cphi * cdlam);
                        if (fabs(z) > 1.) {
                            if (fabs(z) > one_plus_eps)
                                BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                            else
                                z = z < 0. ? -1. : 1.;
                        } else
                            z = acos(z);
                        Av = Azba;
                        xy_y = -rhoc;
                    }
                    if (z < 0.) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                    r = F * (t = math::pow(tan(T(0.5) * z), n));
                    if ((al = .5 * (R104 - z)) < 0.) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                    al = (t + math::pow(al, n)) / const_T;
                    if (fabs(al) > 1.) {
                        if (fabs(al) > one_plus_eps)
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        else
                            al = al < 0. ? -1. : 1.;
                    } else
                        al = acos(al);
                    if (fabs(t = n * (Av - Az)) < al)
                        r /= cos(al + (tag ? t : -t));
                    xy_x = r * sin(t);
                    xy_y += (tag ? -r : r) * cos(t);
                    if (this->m_proj_parm.noskew) {
                        t = xy_x;
                        xy_x = -xy_x * cAzc - xy_y * sAzc;
                        xy_y = -xy_y * cAzc + t * sAzc;
                    }
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    T t, r, rp, rl, al, z, fAz, Az, s, c, Av;
                    int neg, i;

                    if (this->m_proj_parm.noskew) {
                        t = xy_x;
                        xy_x = -xy_x * cAzc + xy_y * sAzc;
                        xy_y = -xy_y * cAzc - t * sAzc;
                    }
                    if( (neg = (xy_x < 0.)) ) {
                        xy_y = rhoc - xy_y;
                        s = S20;
                        c = C20;
                        Av = Azab;
                    } else {
                        xy_y += rhoc;
                        s = S45;
                        c = C45;
                        Av = Azba;
                    }
                    rl = rp = r = boost::math::hypot(xy_x, xy_y);
                    fAz = fabs(Az = atan2(xy_x, xy_y));
                    for (i = n_iter; i ; --i) {
                        z = 2. * atan(math::pow(r / F,T(1) / n));
                        al = acos((math::pow(tan(T(0.5) * z), n) +
                           math::pow(tan(T(0.5) * (R104 - z)), n)) / const_T);
                        if (fAz < al)
                            r = rp * cos(al + (neg ? Az : -Az));
                        if (fabs(rl - r) < epsilon)
                            break;
                        rl = r;
                    }
                    if (! i)
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    Az = Av - Az / n;
                    lp_lat = asin(s * cos(z) + c * sin(z) * cos(Az));
                    lp_lon = atan2(sin(Az), c / tan(z) - s * cos(Az));
                    if (neg)
                        lp_lon -= R110;
                    else
                        lp_lon = lamB - lp_lon;
                }

                static inline std::string get_name()
                {
                    return "bipc_spheroid";
                }

            };

            // Bipolar conic of western hemisphere
            template <typename Params, typename Parameters>
            inline void setup_bipc(Params const& params, Parameters& par, par_bipc& proj_parm)
            {
                proj_parm.noskew = pj_get_param_b<srs::spar::ns>(params, "ns", srs::dpar::ns);
                par.es = 0.;
            }

    }} // namespace detail::bipc
    #endif // doxygen

    /*!
        \brief Bipolar conic of western hemisphere projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
        \par Projection parameters
         - ns (boolean)
        \par Example
        \image html ex_bipc.gif
    */
    template <typename T, typename Parameters>
    struct bipc_spheroid : public detail::bipc::base_bipc_spheroid<T, Parameters>
    {
        template <typename Params>
        inline bipc_spheroid(Params const& params, Parameters & par)
        {
            detail::bipc::setup_bipc(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_bipc, bipc_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(bipc_entry, bipc_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(bipc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(bipc, bipc_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_BIPC_HPP


/* bipc.hpp
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
*/
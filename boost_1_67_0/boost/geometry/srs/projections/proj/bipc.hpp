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
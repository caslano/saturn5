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

// Copyright (c) 2008   Gerald I. Evenden

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

/* The code in this file is largly based upon procedures:
 *
 * Written by: Knud Poder and Karsten Engsager
 *
 * Based on math from: R.Koenig and K.H. Weise, "Mathematische
 * Grundlagen der hoeheren Geodaesie und Kartographie,
 * Springer-Verlag, Berlin/Goettingen" Heidelberg, 1951.
 *
 * Modified and used here by permission of Reference Networks
 * Division, Kort og Matrikelstyrelsen (KMS), Copenhagen, Denmark
*/

#ifndef BOOST_GEOMETRY_PROJECTIONS_ETMERC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ETMERC_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/function_overloads.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

#include <boost/math/special_functions/hypot.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace etmerc
    {

            static const int PROJ_ETMERC_ORDER = 6;

            template <typename T>
            struct par_etmerc
            {
                T    Qn;    /* Merid. quad., scaled to the projection */
                T    Zb;    /* Radius vector in polar coord. systems  */
                T    cgb[6]; /* Constants for Gauss -> Geo lat */
                T    cbg[6]; /* Constants for Geo lat -> Gauss */
                T    utg[6]; /* Constants for transv. merc. -> geo */
                T    gtu[6]; /* Constants for geo -> transv. merc. */
            };

            template <typename T>
            inline T log1py(T const& x) {              /* Compute log(1+x) accurately */
                volatile T
                  y = 1 + x,
                  z = y - 1;
                /* Here's the explanation for this magic: y = 1 + z, exactly, and z
                 * approx x, thus log(y)/z (which is nearly constant near z = 0) returns
                 * a good approximation to the true log(1 + x)/x.  The multiplication x *
                 * (log(y)/z) introduces little additional error. */
                return z == 0 ? x : x * log(y) / z;
            }

            template <typename T>
            inline T asinhy(T const& x) {              /* Compute asinh(x) accurately */
                T y = fabs(x);         /* Enforce odd parity */
                y = log1py(y * (1 + y/(boost::math::hypot(1.0, y) + 1)));
                return x < 0 ? -y : y;
            }

            template <typename T>
            inline T gatg(const T *p1, int len_p1, T const& B) {
                const T *p;
                T h = 0, h1, h2 = 0, cos_2B;

                cos_2B = 2*cos(2*B);
                for (p = p1 + len_p1, h1 = *--p; p - p1; h2 = h1, h1 = h)
                    h = -h2 + cos_2B*h1 + *--p;
                return (B + h*sin(2*B));
            }

            /* Complex Clenshaw summation */
            template <typename T>
            inline T clenS(const T *a, int size, T const& arg_r, T const& arg_i, T *R, T *I) {
                T      r, i, hr, hr1, hr2, hi, hi1, hi2;
                T      sin_arg_r, cos_arg_r, sinh_arg_i, cosh_arg_i;

                /* arguments */
                const T* p = a + size;
                sin_arg_r  = sin(arg_r);
                cos_arg_r  = cos(arg_r);
                sinh_arg_i = sinh(arg_i);
                cosh_arg_i = cosh(arg_i);
                r          =  2*cos_arg_r*cosh_arg_i;
                i          = -2*sin_arg_r*sinh_arg_i;
                /* summation loop */
                for (hi1 = hr1 = hi = 0, hr = *--p; a - p;) {
                    hr2 = hr1;
                    hi2 = hi1;
                    hr1 = hr;
                    hi1 = hi;
                    hr  = -hr2 + r*hr1 - i*hi1 + *--p;
                    hi  = -hi2 + i*hr1 + r*hi1;
                }
                r   = sin_arg_r*cosh_arg_i;
                i   = cos_arg_r*sinh_arg_i;
                *R  = r*hr - i*hi;
                *I  = r*hi + i*hr;
                return(*R);
            }

            /* Real Clenshaw summation */
            template <typename T>
            inline T clens(const T *a, int size, T const& arg_r) {
                T      r, hr, hr1, hr2, cos_arg_r;

                const T* p = a + size;
                cos_arg_r  = cos(arg_r);
                r          =  2*cos_arg_r;

                /* summation loop */
                for (hr1 = 0, hr = *--p; a - p;) {
                    hr2 = hr1;
                    hr1 = hr;
                    hr  = -hr2 + r*hr1 + *--p;
                }
                return(sin(arg_r)*hr);
            }

            template <typename T, typename Parameters>
            struct base_etmerc_ellipsoid
            {
                par_etmerc<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T sin_Cn, cos_Cn, cos_Ce, sin_Ce, dCn, dCe;
                    T Cn = lp_lat, Ce = lp_lon;

                    /* ell. LAT, LNG -> Gaussian LAT, LNG */
                    Cn  = gatg(this->m_proj_parm.cbg, PROJ_ETMERC_ORDER, Cn);
                    /* Gaussian LAT, LNG -> compl. sph. LAT */
                    sin_Cn = sin(Cn);
                    cos_Cn = cos(Cn);
                    sin_Ce = sin(Ce);
                    cos_Ce = cos(Ce);

                    Cn     = atan2(sin_Cn, cos_Ce*cos_Cn);
                    Ce     = atan2(sin_Ce*cos_Cn, boost::math::hypot(sin_Cn, cos_Cn*cos_Ce));

                    /* compl. sph. N, E -> ell. norm. N, E */
                    Ce  = asinhy(tan(Ce));     /* Replaces: Ce  = log(tan(fourth_pi + Ce*0.5)); */
                    Cn += clenS(this->m_proj_parm.gtu, PROJ_ETMERC_ORDER, 2*Cn, 2*Ce, &dCn, &dCe);
                    Ce += dCe;
                    if (fabs(Ce) <= 2.623395162778) {
                        xy_y  = this->m_proj_parm.Qn * Cn + this->m_proj_parm.Zb;  /* Northing */
                        xy_x  = this->m_proj_parm.Qn * Ce;  /* Easting  */
                    } else
                        xy_x = xy_y = HUGE_VAL;
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T sin_Cn, cos_Cn, cos_Ce, sin_Ce, dCn, dCe;
                    T Cn = xy_y, Ce = xy_x;

                    /* normalize N, E */
                    Cn = (Cn - this->m_proj_parm.Zb)/this->m_proj_parm.Qn;
                    Ce = Ce/this->m_proj_parm.Qn;

                    if (fabs(Ce) <= 2.623395162778) { /* 150 degrees */
                        /* norm. N, E -> compl. sph. LAT, LNG */
                        Cn += clenS(this->m_proj_parm.utg, PROJ_ETMERC_ORDER, 2*Cn, 2*Ce, &dCn, &dCe);
                        Ce += dCe;
                        Ce = atan(sinh(Ce)); /* Replaces: Ce = 2*(atan(exp(Ce)) - fourth_pi); */
                        /* compl. sph. LAT -> Gaussian LAT, LNG */
                        sin_Cn = sin(Cn);
                        cos_Cn = cos(Cn);
                        sin_Ce = sin(Ce);
                        cos_Ce = cos(Ce);
                        Ce     = atan2(sin_Ce, cos_Ce*cos_Cn);
                        Cn     = atan2(sin_Cn*cos_Ce, boost::math::hypot(sin_Ce, cos_Ce*cos_Cn));
                        /* Gaussian LAT, LNG -> ell. LAT, LNG */
                        lp_lat = gatg(this->m_proj_parm.cgb,  PROJ_ETMERC_ORDER, Cn);
                        lp_lon = Ce;
                    }
                    else
                        lp_lat = lp_lon = HUGE_VAL;
                }

                static inline std::string get_name()
                {
                    return "etmerc_ellipsoid";
                }

            };

            template <typename Parameters, typename T>
            inline void setup(Parameters& par, par_etmerc<T>& proj_parm)
            {
                T f, n, np, Z;

                if (par.es <= 0) {
                    BOOST_THROW_EXCEPTION( projection_exception(error_ellipsoid_use_required) );
                }

                f = par.es / (1 + sqrt(1 -  par.es)); /* Replaces: f = 1 - sqrt(1-par.es); */

                /* third flattening */
                np = n = f/(2 - f);

                /* COEF. OF TRIG SERIES GEO <-> GAUSS */
                /* cgb := Gaussian -> Geodetic, KW p190 - 191 (61) - (62) */
                /* cbg := Geodetic -> Gaussian, KW p186 - 187 (51) - (52) */
                /* PROJ_ETMERC_ORDER = 6th degree : Engsager and Poder: ICC2007 */

                proj_parm.cgb[0] = n*( 2 + n*(-2/3.0  + n*(-2      + n*(116/45.0 + n*(26/45.0 +
                            n*(-2854/675.0 ))))));
                proj_parm.cbg[0] = n*(-2 + n*( 2/3.0  + n*( 4/3.0  + n*(-82/45.0 + n*(32/45.0 +
                            n*( 4642/4725.0))))));
                np     *= n;
                proj_parm.cgb[1] = np*(7/3.0 + n*( -8/5.0  + n*(-227/45.0 + n*(2704/315.0 +
                            n*( 2323/945.0)))));
                proj_parm.cbg[1] = np*(5/3.0 + n*(-16/15.0 + n*( -13/9.0  + n*( 904/315.0 +
                            n*(-1522/945.0)))));
                np     *= n;
                /* n^5 coeff corrected from 1262/105 -> -1262/105 */
                proj_parm.cgb[2] = np*( 56/15.0  + n*(-136/35.0 + n*(-1262/105.0 +
                            n*( 73814/2835.0))));
                proj_parm.cbg[2] = np*(-26/15.0  + n*(  34/21.0 + n*(    8/5.0   +
                            n*(-12686/2835.0))));
                np     *= n;
                /* n^5 coeff corrected from 322/35 -> 332/35 */
                proj_parm.cgb[3] = np*(4279/630.0 + n*(-332/35.0 + n*(-399572/14175.0)));
                proj_parm.cbg[3] = np*(1237/630.0 + n*( -12/5.0  + n*( -24832/14175.0)));
                np     *= n;
                proj_parm.cgb[4] = np*(4174/315.0 + n*(-144838/6237.0 ));
                proj_parm.cbg[4] = np*(-734/315.0 + n*( 109598/31185.0));
                np     *= n;
                proj_parm.cgb[5] = np*(601676/22275.0 );
                proj_parm.cbg[5] = np*(444337/155925.0);

                /* Constants of the projections */
                /* Transverse Mercator (UTM, ITM, etc) */
                np = n*n;
                /* Norm. mer. quad, K&W p.50 (96), p.19 (38b), p.5 (2) */
                proj_parm.Qn = par.k0/(1 + n) * (1 + np*(1/4.0 + np*(1/64.0 + np/256.0)));
                /* coef of trig series */
                /* utg := ell. N, E -> sph. N, E,  KW p194 (65) */
                /* gtu := sph. N, E -> ell. N, E,  KW p196 (69) */
                proj_parm.utg[0] = n*(-0.5  + n*( 2/3.0 + n*(-37/96.0 + n*( 1/360.0 +
                            n*(  81/512.0 + n*(-96199/604800.0))))));
                proj_parm.gtu[0] = n*( 0.5  + n*(-2/3.0 + n*(  5/16.0 + n*(41/180.0 +
                            n*(-127/288.0 + n*(  7891/37800.0 ))))));
                proj_parm.utg[1] = np*(-1/48.0 + n*(-1/15.0 + n*(437/1440.0 + n*(-46/105.0 +
                            n*( 1118711/3870720.0)))));
                proj_parm.gtu[1] = np*(13/48.0 + n*(-3/5.0  + n*(557/1440.0 + n*(281/630.0 +
                            n*(-1983433/1935360.0)))));
                np      *= n;
                proj_parm.utg[2] = np*(-17/480.0 + n*(  37/840.0 + n*(  209/4480.0  +
                            n*( -5569/90720.0 ))));
                proj_parm.gtu[2] = np*( 61/240.0 + n*(-103/140.0 + n*(15061/26880.0 +
                            n*(167603/181440.0))));
                np      *= n;
                proj_parm.utg[3] = np*(-4397/161280.0 + n*(  11/504.0 + n*( 830251/7257600.0)));
                proj_parm.gtu[3] = np*(49561/161280.0 + n*(-179/168.0 + n*(6601661/7257600.0)));
                np     *= n;
                proj_parm.utg[4] = np*(-4583/161280.0 + n*(  108847/3991680.0));
                proj_parm.gtu[4] = np*(34729/80640.0  + n*(-3418889/1995840.0));
                np     *= n;
                proj_parm.utg[5] = np*(-20648693/638668800.0);
                proj_parm.gtu[5] = np*(212378941/319334400.0);

                /* Gaussian latitude value of the origin latitude */
                Z = gatg(proj_parm.cbg, PROJ_ETMERC_ORDER, par.phi0);

                /* Origin northing minus true northing at the origin latitude */
                /* i.e. true northing = N - proj_parm.Zb                         */
                proj_parm.Zb  = - proj_parm.Qn*(Z + clens(proj_parm.gtu, PROJ_ETMERC_ORDER, 2*Z));
            }

            // Extended Transverse Mercator
            template <typename Parameters, typename T>
            inline void setup_etmerc(Parameters& par, par_etmerc<T>& proj_parm)
            {
                setup(par, proj_parm);
            }

            // Universal Transverse Mercator (UTM)
            template <typename Params, typename Parameters, typename T>
            inline void setup_utm(Params const& params, Parameters& par, par_etmerc<T>& proj_parm)
            {
                static const T pi = detail::pi<T>();

                int zone;

                if (par.es == 0.0) {
                    BOOST_THROW_EXCEPTION( projection_exception(error_ellipsoid_use_required) );
                }

                par.y0 = pj_get_param_b<srs::spar::south>(params, "south", srs::dpar::south) ? 10000000. : 0.;
                par.x0 = 500000.;
                if (pj_param_i<srs::spar::zone>(params, "zone", srs::dpar::zone, zone)) /* zone input ? */
                {
                    if (zone > 0 && zone <= 60)
                        --zone;
                    else {
                        BOOST_THROW_EXCEPTION( projection_exception(error_invalid_utm_zone) );
                    }
                }
                else /* nearest central meridian input */
                {
                    zone = int_floor((adjlon(par.lam0) + pi) * 30. / pi);
                    if (zone < 0)
                        zone = 0;
                    else if (zone >= 60)
                        zone = 59;
                }
                par.lam0 = (zone + .5) * pi / 30. - pi;
                par.k0 = 0.9996;
                par.phi0 = 0.;

                setup(par, proj_parm);
            }

    }} // namespace detail::etmerc
    #endif // doxygen

    /*!
        \brief Extended Transverse Mercator projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Projection parameters
         - lat_ts: Latitude of true scale
         - lat_0: Latitude of origin
        \par Example
        \image html ex_etmerc.gif
    */
    template <typename T, typename Parameters>
    struct etmerc_ellipsoid : public detail::etmerc::base_etmerc_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline etmerc_ellipsoid(Params const& , Parameters & par)
        {
            detail::etmerc::setup_etmerc(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Universal Transverse Mercator (UTM) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Projection parameters
         - zone: UTM Zone (integer)
         - south: Denotes southern hemisphere UTM zone (boolean)
        \par Example
        \image html ex_utm.gif
    */
    template <typename T, typename Parameters>
    struct utm_ellipsoid : public detail::etmerc::base_etmerc_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline utm_ellipsoid(Params const& params, Parameters & par)
        {
            detail::etmerc::setup_utm(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_etmerc, etmerc_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_utm, utm_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(etmerc_entry, etmerc_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(utm_entry, utm_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(etmerc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(etmerc, etmerc_entry);
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(utm, utm_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_ETMERC_HPP


/* etmerc.hpp
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
*/
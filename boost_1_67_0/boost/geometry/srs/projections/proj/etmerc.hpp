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
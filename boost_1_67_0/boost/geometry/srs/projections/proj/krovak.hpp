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

// Purpose:  Implementation of the krovak (Krovak) projection.
//           Definition: http://www.ihsenergy.com/epsg/guid7.html#1.4.3
// Author:   Thomas Flemming, tf@ttqv.com
// Copyright (c) 2001, Thomas Flemming, tf@ttqv.com

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_KROVAK_HPP
#define BOOST_GEOMETRY_PROJECTIONS_KROVAK_HPP

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
    namespace detail { namespace krovak
    {
            static double epsilon = 1e-15;
            static double S45 = 0.785398163397448;  /* 45 deg */
            static double S90 = 1.570796326794896;  /* 90 deg */
            static double UQ  = 1.04216856380474;   /* DU(2, 59, 42, 42.69689) */
            static double S0  = 1.37008346281555;   /* Latitude of pseudo standard parallel 78deg 30'00" N */
            /* Not sure at all of the appropriate number for max_iter... */
            static int max_iter = 100;

            template <typename T>
            struct par_krovak
            {
                T alpha;
                T k;
                T n;
                T rho0;
                T ad;
                int czech;
            };

            /**
               NOTES: According to EPSG the full Krovak projection method should have
                      the following parameters.  Within PROJ.4 the azimuth, and pseudo
                      standard parallel are hardcoded in the algorithm and can't be
                      altered from outside.  The others all have defaults to match the
                      common usage with Krovak projection.

              lat_0 = latitude of centre of the projection

              lon_0 = longitude of centre of the projection

              ** = azimuth (true) of the centre line passing through the centre of the projection

              ** = latitude of pseudo standard parallel

              k  = scale factor on the pseudo standard parallel

              x_0 = False Easting of the centre of the projection at the apex of the cone

              y_0 = False Northing of the centre of the projection at the apex of the cone

             **/

            template <typename T, typename Parameters>
            struct base_krovak_ellipsoid
            {
                par_krovak<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T gfi, u, deltav, s, d, eps, rho;

                    gfi = math::pow( (T(1) + par.e * sin(lp_lat)) / (T(1) - par.e * sin(lp_lat)), this->m_proj_parm.alpha * par.e / T(2));

                    u = 2. * (atan(this->m_proj_parm.k * math::pow( tan(lp_lat / T(2) + S45), this->m_proj_parm.alpha) / gfi)-S45);
                    deltav = -lp_lon * this->m_proj_parm.alpha;

                    s = asin(cos(this->m_proj_parm.ad) * sin(u) + sin(this->m_proj_parm.ad) * cos(u) * cos(deltav));
                    d = asin(cos(u) * sin(deltav) / cos(s));

                    eps = this->m_proj_parm.n * d;
                    rho = this->m_proj_parm.rho0 * math::pow(tan(S0 / T(2) + S45) , this->m_proj_parm.n) / math::pow(tan(s / T(2) + S45) , this->m_proj_parm.n);

                    xy_y = rho * cos(eps);
                    xy_x = rho * sin(eps);

                    xy_y *= this->m_proj_parm.czech;
                    xy_x *= this->m_proj_parm.czech;
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    T u, deltav, s, d, eps, rho, fi1, xy0;
                    int i;

                    // TODO: replace with std::swap()
                    xy0 = xy_x;
                    xy_x = xy_y;
                    xy_y = xy0;

                    xy_x *= this->m_proj_parm.czech;
                    xy_y *= this->m_proj_parm.czech;

                    rho = sqrt(xy_x * xy_x + xy_y * xy_y);
                    eps = atan2(xy_y, xy_x);

                    d = eps / sin(S0);
                    s = T(2) * (atan(math::pow(this->m_proj_parm.rho0 / rho, T(1) / this->m_proj_parm.n) * tan(S0 / T(2) + S45)) - S45);

                    u = asin(cos(this->m_proj_parm.ad) * sin(s) - sin(this->m_proj_parm.ad) * cos(s) * cos(d));
                    deltav = asin(cos(s) * sin(d) / cos(u));

                    lp_lon = par.lam0 - deltav / this->m_proj_parm.alpha;

                    /* ITERATION FOR lp_lat */
                    fi1 = u;

                    for (i = max_iter; i ; --i) {
                        lp_lat = T(2) * ( atan( math::pow( this->m_proj_parm.k, T(-1) / this->m_proj_parm.alpha)  *
                                              math::pow( tan(u / T(2) + S45) , T(1) / this->m_proj_parm.alpha)  *
                                              math::pow( (T(1) + par.e * sin(fi1)) / (T(1) - par.e * sin(fi1)) , par.e / T(2))
                                            )  - S45);

                        if (fabs(fi1 - lp_lat) < epsilon)
                            break;
                        fi1 = lp_lat;
                    }
                    if( i == 0 )
                        BOOST_THROW_EXCEPTION( projection_exception(error_non_convergent) );

                   lp_lon -= par.lam0;
                }

                static inline std::string get_name()
                {
                    return "krovak_ellipsoid";
                }

            };

            // Krovak
            template <typename Params, typename Parameters, typename T>
            inline void setup_krovak(Params const& params, Parameters& par, par_krovak<T>& proj_parm)
            {
                T u0, n0, g;

                /* we want Bessel as fixed ellipsoid */
                par.a = 6377397.155;
                par.es = 0.006674372230614;
                par.e = sqrt(par.es);

                /* if latitude of projection center is not set, use 49d30'N */
                if (!pj_param_exists<srs::spar::lat_0>(params, "lat_0", srs::dpar::lat_0))
                    par.phi0 = 0.863937979737193;

                /* if center long is not set use 42d30'E of Ferro - 17d40' for Ferro */
                /* that will correspond to using longitudes relative to greenwich    */
                /* as input and output, instead of lat/long relative to Ferro */
                if (!pj_param_exists<srs::spar::lon_0>(params, "lon_0", srs::dpar::lon_0))
                    par.lam0 = 0.7417649320975901 - 0.308341501185665;

                /* if scale not set default to 0.9999 */
                if (!pj_param_exists<srs::spar::k>(params, "k", srs::dpar::k))
                    par.k0 = 0.9999;

                proj_parm.czech = 1;
                if( !pj_param_exists<srs::spar::czech>(params, "czech", srs::dpar::czech) )
                    proj_parm.czech = -1;

                /* Set up shared parameters between forward and inverse */
                proj_parm.alpha = sqrt(T(1) + (par.es * math::pow(cos(par.phi0), 4)) / (T(1) - par.es));
                u0 = asin(sin(par.phi0) / proj_parm.alpha);
                g = math::pow( (T(1) + par.e * sin(par.phi0)) / (T(1) - par.e * sin(par.phi0)) , proj_parm.alpha * par.e / T(2) );
                proj_parm.k = tan( u0 / 2. + S45) / math::pow(tan(par.phi0 / T(2) + S45) , proj_parm.alpha) * g;
                n0 = sqrt(T(1) - par.es) / (T(1) - par.es * math::pow(sin(par.phi0), 2));
                proj_parm.n = sin(S0);
                proj_parm.rho0 = par.k0 * n0 / tan(S0);
                proj_parm.ad = S90 - UQ;
            }

    }} // namespace detail::krovak
    #endif // doxygen

    /*!
        \brief Krovak projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Ellipsoid
        \par Projection parameters
         - lat_ts: Latitude of true scale (degrees)
         - lat_0: Latitude of origin
         - lon_0: Central meridian
         - k: Scale factor on the pseudo standard parallel
        \par Example
        \image html ex_krovak.gif
    */
    template <typename T, typename Parameters>
    struct krovak_ellipsoid : public detail::krovak::base_krovak_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline krovak_ellipsoid(Params const& params, Parameters & par)
        {
            detail::krovak::setup_krovak(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_krovak, krovak_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(krovak_entry, krovak_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(krovak_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(krovak, krovak_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_KROVAK_HPP


/* krovak.hpp
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
*/
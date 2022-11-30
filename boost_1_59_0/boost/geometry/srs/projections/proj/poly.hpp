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

#ifndef BOOST_GEOMETRY_PROJECTIONS_POLY_HPP
#define BOOST_GEOMETRY_PROJECTIONS_POLY_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_mlfn.hpp>
#include <boost/geometry/srs/projections/impl/pj_msfn.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace poly
    {

            static const double tolerance = 1e-10;
            static const double conv_tolerance = 1e-10;
            static const int n_iter = 10;
            static const int i_iter = 20;
            static const double i_tolerance = 1.e-12;

            template <typename T>
            struct par_poly
            {
                T ml0;
                detail::en<T> en;
            };

            template <typename T, typename Parameters>
            struct base_poly_ellipsoid
            {
                par_poly<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T  ms, sp, cp;

                    if (fabs(lp_lat) <= tolerance) {
                        xy_x = lp_lon;
                        xy_y = -this->m_proj_parm.ml0;
                    } else {
                        sp = sin(lp_lat);
                        ms = fabs(cp = cos(lp_lat)) > tolerance ? pj_msfn(sp, cp, par.es) / sp : 0.;
                        xy_x = ms * sin(lp_lon *= sp);
                        xy_y = (pj_mlfn(lp_lat, sp, cp, this->m_proj_parm.en) - this->m_proj_parm.ml0) + ms * (1. - cos(lp_lon));
                    }
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    xy_y += this->m_proj_parm.ml0;
                    if (fabs(xy_y) <= tolerance) {
                        lp_lon = xy_x;
                        lp_lat = 0.;
                    } else {
                        T r, c, sp, cp, s2ph, ml, mlb, mlp, dPhi;
                        int i;

                        r = xy_y * xy_y + xy_x * xy_x;
                        for (lp_lat = xy_y, i = i_iter; i ; --i) {
                            sp = sin(lp_lat);
                            s2ph = sp * ( cp = cos(lp_lat));
                            if (fabs(cp) < i_tolerance) {
                                BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                            }
                            c = sp * (mlp = sqrt(1. - par.es * sp * sp)) / cp;
                            ml = pj_mlfn(lp_lat, sp, cp, this->m_proj_parm.en);
                            mlb = ml * ml + r;
                            mlp = par.one_es / (mlp * mlp * mlp);
                            lp_lat += ( dPhi =
                                ( ml + ml + c * mlb - 2. * xy_y * (c * ml + 1.) ) / (
                                par.es * s2ph * (mlb - 2. * xy_y * ml) / c +
                                2.* (xy_y - ml) * (c * mlp - 1. / s2ph) - mlp - mlp ));
                            if (fabs(dPhi) <= i_tolerance)
                                break;
                        }
                        if (!i) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        c = sin(lp_lat);
                        lp_lon = asin(xy_x * tan(lp_lat) * sqrt(1. - par.es * c * c)) / sin(lp_lat);
                    }
                }

                static inline std::string get_name()
                {
                    return "poly_ellipsoid";
                }

            };

            template <typename T, typename Parameters>
            struct base_poly_spheroid
            {
                par_poly<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T  cot, E;

                    if (fabs(lp_lat) <= tolerance) {
                        xy_x = lp_lon;
                        xy_y = this->m_proj_parm.ml0;
                    } else {
                        cot = 1. / tan(lp_lat);
                        xy_x = sin(E = lp_lon * sin(lp_lat)) * cot;
                        xy_y = lp_lat - par.phi0 + cot * (1. - cos(E));
                    }
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    T B, dphi, tp;
                    int i;

                    if (fabs(xy_y = par.phi0 + xy_y) <= tolerance) {
                        lp_lon = xy_x;
                        lp_lat = 0.;
                    } else {
                        lp_lat = xy_y;
                        B = xy_x * xy_x + xy_y * xy_y;
                        i = n_iter;
                        do {
                            tp = tan(lp_lat);
                            lp_lat -= (dphi = (xy_y * (lp_lat * tp + 1.) - lp_lat -
                                .5 * ( lp_lat * lp_lat + B) * tp) /
                                ((lp_lat - xy_y) / tp - 1.));
                        } while (fabs(dphi) > conv_tolerance && --i);
                        if (! i) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        lp_lon = asin(xy_x * tan(lp_lat)) / sin(lp_lat);
                    }
                }

                static inline std::string get_name()
                {
                    return "poly_spheroid";
                }

            };

            // Polyconic (American)
            template <typename Parameters, typename T>
            inline void setup_poly(Parameters const& par, par_poly<T>& proj_parm)
            {
                if (par.es != 0.0) {
                    proj_parm.en = pj_enfn<T>(par.es);
                    proj_parm.ml0 = pj_mlfn(par.phi0, sin(par.phi0), cos(par.phi0), proj_parm.en);
                } else {
                    proj_parm.ml0 = -par.phi0;
                }
            }

    }} // namespace detail::poly
    #endif // doxygen

    /*!
        \brief Polyconic (American) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - Ellipsoid
        \par Example
        \image html ex_poly.gif
    */
    template <typename T, typename Parameters>
    struct poly_ellipsoid : public detail::poly::base_poly_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline poly_ellipsoid(Params const& , Parameters const& par)
        {
            detail::poly::setup_poly(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Polyconic (American) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - Ellipsoid
        \par Example
        \image html ex_poly.gif
    */
    template <typename T, typename Parameters>
    struct poly_spheroid : public detail::poly::base_poly_spheroid<T, Parameters>
    {
        template <typename Params>
        inline poly_spheroid(Params const& , Parameters const& par)
        {
            detail::poly::setup_poly(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI2(srs::spar::proj_poly, poly_spheroid, poly_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI2(poly_entry, poly_spheroid, poly_ellipsoid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(poly_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(poly, poly_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_POLY_HPP


/* poly.hpp
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
*/
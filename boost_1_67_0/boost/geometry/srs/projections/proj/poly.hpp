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
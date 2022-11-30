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

 // Author: Gerald Evenden (1995)
 //         Thomas Knudsen (2016) - revise/add regression tests

// Last updated version of proj: 5.0.0

// Original copyright notice:

// Purpose:  Implementation of the aea (Albers Equal Area) projection.
// Author:   Gerald Evenden
// Copyright (c) 1995, Gerald Evenden

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_AEA_HPP
#define BOOST_GEOMETRY_PROJECTIONS_AEA_HPP

#include <boost/core/ignore_unused.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/math/special_functions/hypot.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_mlfn.hpp>
#include <boost/geometry/srs/projections/impl/pj_msfn.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/pj_qsfn.hpp>


namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace aea
    {

            static const double epsilon10 = 1.e-10;
            static const double tolerance7 = 1.e-7;
            static const double epsilon = 1.0e-7;
            static const double tolerance = 1.0e-10;
            static const int n_iter = 15;

            template <typename T>
            struct par_aea
            {
                T    ec;
                T    n;
                T    c;
                T    dd;
                T    n2;
                T    rho0;
                T    phi1;
                T    phi2;
                detail::en<T> en;
                bool ellips;
            };

            /* determine latitude angle phi-1 */
            template <typename T>
            inline T phi1_(T const& qs, T const& Te, T const& Tone_es)
            {
                int i;
                T Phi, sinpi, cospi, con, com, dphi;

                Phi = asin (.5 * qs);
                if (Te < epsilon)
                    return( Phi );
                i = n_iter;
                do {
                    sinpi = sin (Phi);
                    cospi = cos (Phi);
                    con = Te * sinpi;
                    com = 1. - con * con;
                    dphi = .5 * com * com / cospi * (qs / Tone_es -
                       sinpi / com + .5 / Te * log ((1. - con) /
                       (1. + con)));
                    Phi += dphi;
                } while (fabs(dphi) > tolerance && --i);
                return( i ? Phi : HUGE_VAL );
            }

            template <typename T, typename Parameters>
            struct base_aea_ellipsoid
            {
                par_aea<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid & spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T rho = this->m_proj_parm.c - (this->m_proj_parm.ellips
                                                                    ? this->m_proj_parm.n * pj_qsfn(sin(lp_lat), par.e, par.one_es)
                                                                    : this->m_proj_parm.n2 * sin(lp_lat));
                    if (rho < 0.)
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    rho = this->m_proj_parm.dd * sqrt(rho);
                    xy_x = rho * sin( lp_lon *= this->m_proj_parm.n );
                    xy_y = this->m_proj_parm.rho0 - rho * cos(lp_lon);
                }

                // INVERSE(e_inverse)  ellipsoid & spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T rho = 0.0;
                    if( (rho = boost::math::hypot(xy_x, xy_y = this->m_proj_parm.rho0 - xy_y)) != 0.0 ) {
                        if (this->m_proj_parm.n < 0.) {
                            rho = -rho;
                            xy_x = -xy_x;
                            xy_y = -xy_y;
                        }
                        lp_lat =  rho / this->m_proj_parm.dd;
                        if (this->m_proj_parm.ellips) {
                            lp_lat = (this->m_proj_parm.c - lp_lat * lp_lat) / this->m_proj_parm.n;
                            if (fabs(this->m_proj_parm.ec - fabs(lp_lat)) > tolerance7) {
                                if ((lp_lat = phi1_(lp_lat, par.e, par.one_es)) == HUGE_VAL)
                                    BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                            } else
                                lp_lat = lp_lat < 0. ? -half_pi : half_pi;
                        } else if (fabs(lp_lat = (this->m_proj_parm.c - lp_lat * lp_lat) / this->m_proj_parm.n2) <= 1.)
                            lp_lat = asin(lp_lat);
                        else
                            lp_lat = lp_lat < 0. ? -half_pi : half_pi;
                        lp_lon = atan2(xy_x, xy_y) / this->m_proj_parm.n;
                    } else {
                        lp_lon = 0.;
                        lp_lat = this->m_proj_parm.n > 0. ? half_pi : - half_pi;
                    }
                }

                static inline std::string get_name()
                {
                    return "aea_ellipsoid";
                }

            };

            template <typename Parameters, typename T>
            inline void setup(Parameters const& par, par_aea<T>& proj_parm) 
            {
                T cosphi, sinphi;
                int secant;

                if (fabs(proj_parm.phi1 + proj_parm.phi2) < epsilon10)
                    BOOST_THROW_EXCEPTION( projection_exception(error_conic_lat_equal) );
                proj_parm.n = sinphi = sin(proj_parm.phi1);
                cosphi = cos(proj_parm.phi1);
                secant = fabs(proj_parm.phi1 - proj_parm.phi2) >= epsilon10;
                if( (proj_parm.ellips = (par.es > 0.))) {
                    T ml1, m1;

                    proj_parm.en = pj_enfn<T>(par.es);
                    m1 = pj_msfn(sinphi, cosphi, par.es);
                    ml1 = pj_qsfn(sinphi, par.e, par.one_es);
                    if (secant) { /* secant cone */
                        T ml2, m2;

                        sinphi = sin(proj_parm.phi2);
                        cosphi = cos(proj_parm.phi2);
                        m2 = pj_msfn(sinphi, cosphi, par.es);
                        ml2 = pj_qsfn(sinphi, par.e, par.one_es);
                        if (ml2 == ml1)
                            BOOST_THROW_EXCEPTION( projection_exception(0) );

                        proj_parm.n = (m1 * m1 - m2 * m2) / (ml2 - ml1);
                    }
                    proj_parm.ec = 1. - .5 * par.one_es * log((1. - par.e) /
                        (1. + par.e)) / par.e;
                    proj_parm.c = m1 * m1 + proj_parm.n * ml1;
                    proj_parm.dd = 1. / proj_parm.n;
                    proj_parm.rho0 = proj_parm.dd * sqrt(proj_parm.c - proj_parm.n * pj_qsfn(sin(par.phi0),
                        par.e, par.one_es));
                } else {
                    if (secant) proj_parm.n = .5 * (proj_parm.n + sin(proj_parm.phi2));
                    proj_parm.n2 = proj_parm.n + proj_parm.n;
                    proj_parm.c = cosphi * cosphi + proj_parm.n2 * sinphi;
                    proj_parm.dd = 1. / proj_parm.n;
                    proj_parm.rho0 = proj_parm.dd * sqrt(proj_parm.c - proj_parm.n2 * sin(par.phi0));
                }
            }


            // Albers Equal Area
            template <typename Params, typename Parameters, typename T>
            inline void setup_aea(Params const& params, Parameters const& par, par_aea<T>& proj_parm)
            {
                proj_parm.phi1 = 0.0;
                proj_parm.phi2 = 0.0;
                bool is_phi1_set = pj_param_r<srs::spar::lat_1>(params, "lat_1", srs::dpar::lat_1, proj_parm.phi1);
                bool is_phi2_set = pj_param_r<srs::spar::lat_2>(params, "lat_2", srs::dpar::lat_2, proj_parm.phi2);

                // Boost.Geometry specific, set default parameters manually
                if (! is_phi1_set || ! is_phi2_set) {
                    bool const use_defaults = ! pj_get_param_b<srs::spar::no_defs>(params, "no_defs", srs::dpar::no_defs);
                    if (use_defaults) {
                        if (!is_phi1_set)
                            proj_parm.phi1 = 29.5;
                        if (!is_phi2_set)
                            proj_parm.phi2 = 45.5;
                    }
                }

                setup(par, proj_parm);
            }

            // Lambert Equal Area Conic
            template <typename Params, typename Parameters, typename T>
            inline void setup_leac(Params const& params, Parameters const& par, par_aea<T>& proj_parm)
            {
                static const T half_pi = detail::half_pi<T>();

                proj_parm.phi2 = pj_get_param_r<T, srs::spar::lat_1>(params, "lat_1", srs::dpar::lat_1);
                proj_parm.phi1 = pj_get_param_b<srs::spar::south>(params, "south", srs::dpar::south) ? -half_pi : half_pi;
                setup(par, proj_parm);
            }

    }} // namespace detail::aea
    #endif // doxygen

    /*!
        \brief Albers Equal Area projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel (degrees)
         - lat_2: Latitude of second standard parallel (degrees)
        \par Example
        \image html ex_aea.gif
    */
    template <typename T, typename Parameters>
    struct aea_ellipsoid : public detail::aea::base_aea_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline aea_ellipsoid(Params const& params, Parameters const& par)
        {
            detail::aea::setup_aea(params, par, this->m_proj_parm);
        }
    };

    /*!
        \brief Lambert Equal Area Conic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel (degrees)
         - south: Denotes southern hemisphere UTM zone (boolean)
        \par Example
        \image html ex_leac.gif
    */
    template <typename T, typename Parameters>
    struct leac_ellipsoid : public detail::aea::base_aea_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline leac_ellipsoid(Params const& params, Parameters const& par)
        {
            detail::aea::setup_leac(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_aea, aea_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_leac, leac_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(aea_entry, aea_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(leac_entry, leac_ellipsoid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(aea_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(aea, aea_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(leac, leac_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_AEA_HPP


/* aea.hpp
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
*/
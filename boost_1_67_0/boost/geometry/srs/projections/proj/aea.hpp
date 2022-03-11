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
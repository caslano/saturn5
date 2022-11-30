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

#ifndef BOOST_GEOMETRY_PROJECTIONS_LCC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_LCC_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_msfn.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/pj_phi2.hpp>
#include <boost/geometry/srs/projections/impl/pj_tsfn.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/math/special_functions/hypot.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace lcc
    {
            static const double epsilon10 = 1.e-10;

            template <typename T>
            struct par_lcc
            {
                T    phi1;
                T    phi2;
                T    n;
                T    rho0;
                T    c;
                bool ellips;
            };

            template <typename T, typename Parameters>
            struct base_lcc_ellipsoid
            {
                par_lcc<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid & spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();
                    static const T half_pi = detail::half_pi<T>();

                    T rho;

                    if (fabs(fabs(lp_lat) - half_pi) < epsilon10) {
                        if ((lp_lat * this->m_proj_parm.n) <= 0.) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        rho = 0.;
                    } else {
                        rho = this->m_proj_parm.c * (this->m_proj_parm.ellips
                            ? math::pow(pj_tsfn(lp_lat, sin(lp_lat), par.e), this->m_proj_parm.n)
                            : math::pow(tan(fourth_pi + T(0.5) * lp_lat), -this->m_proj_parm.n));
                    }
                    lp_lon *= this->m_proj_parm.n;
                    xy_x = par.k0 * (rho * sin( lp_lon) );
                    xy_y = par.k0 * (this->m_proj_parm.rho0 - rho * cos(lp_lon) );
                }

                // INVERSE(e_inverse)  ellipsoid & spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T rho;

                    xy_x /= par.k0;
                    xy_y /= par.k0;

                    xy_y = this->m_proj_parm.rho0 - xy_y;
                    rho = boost::math::hypot(xy_x, xy_y);
                    if(rho != 0.0) {
                        if (this->m_proj_parm.n < 0.) {
                            rho = -rho;
                            xy_x = -xy_x;
                            xy_y = -xy_y;
                        }
                        if (this->m_proj_parm.ellips) {
                            lp_lat = pj_phi2(math::pow(rho / this->m_proj_parm.c, T(1)/this->m_proj_parm.n), par.e);
                            if (lp_lat == HUGE_VAL) {
                                BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                            }
                        } else
                            lp_lat = 2. * atan(math::pow(this->m_proj_parm.c / rho, T(1)/this->m_proj_parm.n)) - half_pi;
                        lp_lon = atan2(xy_x, xy_y) / this->m_proj_parm.n;
                    } else {
                        lp_lon = 0.;
                        lp_lat = this->m_proj_parm.n > 0. ? half_pi : -half_pi;
                    }
                }

                static inline std::string get_name()
                {
                    return "lcc_ellipsoid";
                }

            };

            // Lambert Conformal Conic
            template <typename Params, typename Parameters, typename T>
            inline void setup_lcc(Params const& params, Parameters& par, par_lcc<T>& proj_parm)
            {
                static const T fourth_pi = detail::fourth_pi<T>();
                static const T half_pi = detail::half_pi<T>();

                T cosphi, sinphi;
                int secant;

                proj_parm.phi1 = 0.0;
                proj_parm.phi2 = 0.0;
                bool is_phi1_set = pj_param_r<srs::spar::lat_1>(params, "lat_1", srs::dpar::lat_1, proj_parm.phi1);
                bool is_phi2_set = pj_param_r<srs::spar::lat_2>(params, "lat_2", srs::dpar::lat_2, proj_parm.phi2);

                // Boost.Geometry specific, set default parameters manually
                if (! is_phi1_set || ! is_phi2_set) {
                    bool const use_defaults = ! pj_get_param_b<srs::spar::no_defs>(params, "no_defs", srs::dpar::no_defs);
                    if (use_defaults) {
                        if (!is_phi1_set) {
                            proj_parm.phi1 = 33;
                            is_phi1_set = true;
                        }
                        if (!is_phi2_set) {
                            proj_parm.phi2 = 45;
                            is_phi2_set = true;
                        }
                    }
                }

                if (! is_phi2_set) {
                    proj_parm.phi2 = proj_parm.phi1;
                    if (! pj_param_exists<srs::spar::lat_0>(params, "lat_0", srs::dpar::lat_0))
                        par.phi0 = proj_parm.phi1;
                }
                if (fabs(proj_parm.phi1 + proj_parm.phi2) < epsilon10)
                    BOOST_THROW_EXCEPTION( projection_exception(error_conic_lat_equal) );

                proj_parm.n = sinphi = sin(proj_parm.phi1);
                cosphi = cos(proj_parm.phi1);
                secant = fabs(proj_parm.phi1 - proj_parm.phi2) >= epsilon10;
                if( (proj_parm.ellips = (par.es != 0.)) ) {
                    double ml1, m1;

                    par.e = sqrt(par.es); // TODO: Isn't it already set?
                    m1 = pj_msfn(sinphi, cosphi, par.es);
                    ml1 = pj_tsfn(proj_parm.phi1, sinphi, par.e);
                    if (secant) { /* secant cone */
                        sinphi = sin(proj_parm.phi2);
                        proj_parm.n = log(m1 / pj_msfn(sinphi, cos(proj_parm.phi2), par.es));
                        proj_parm.n /= log(ml1 / pj_tsfn(proj_parm.phi2, sinphi, par.e));
                    }
                    proj_parm.c = (proj_parm.rho0 = m1 * math::pow(ml1, -proj_parm.n) / proj_parm.n);
                    proj_parm.rho0 *= (fabs(fabs(par.phi0) - half_pi) < epsilon10) ? T(0) :
                        math::pow(pj_tsfn(par.phi0, sin(par.phi0), par.e), proj_parm.n);
                } else {
                    if (secant)
                        proj_parm.n = log(cosphi / cos(proj_parm.phi2)) /
                           log(tan(fourth_pi + .5 * proj_parm.phi2) /
                           tan(fourth_pi + .5 * proj_parm.phi1));
                    proj_parm.c = cosphi * math::pow(tan(fourth_pi + T(0.5) * proj_parm.phi1), proj_parm.n) / proj_parm.n;
                    proj_parm.rho0 = (fabs(fabs(par.phi0) - half_pi) < epsilon10) ? 0. :
                        proj_parm.c * math::pow(tan(fourth_pi + T(0.5) * par.phi0), -proj_parm.n);
                }
            }

    }} // namespace detail::lcc
    #endif // doxygen

    /*!
        \brief Lambert Conformal Conic projection
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
         - lat_0: Latitude of origin
        \par Example
        \image html ex_lcc.gif
    */
    template <typename T, typename Parameters>
    struct lcc_ellipsoid : public detail::lcc::base_lcc_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline lcc_ellipsoid(Params const& params, Parameters & par)
        {
            detail::lcc::setup_lcc(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_lcc, lcc_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(lcc_entry, lcc_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(lcc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(lcc, lcc_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_LCC_HPP


/* lcc.hpp
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
*/
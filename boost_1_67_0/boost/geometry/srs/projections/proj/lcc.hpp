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
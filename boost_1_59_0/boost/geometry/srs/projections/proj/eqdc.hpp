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

#ifndef BOOST_GEOMETRY_PROJECTIONS_EQDC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_EQDC_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_mlfn.hpp>
#include <boost/geometry/srs/projections/impl/pj_msfn.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/math/special_functions/hypot.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace eqdc
    {

            static const double epsilon10 = 1.e-10;

            template <typename T>
            struct par_eqdc
            {
                T    phi1;
                T    phi2;
                T    n;
                T    rho0;
                T    c;
                detail::en<T> en;
                bool ellips;
            };

            template <typename T, typename Parameters>
            struct base_eqdc_ellipsoid
            {
                par_eqdc<T> m_proj_parm;

                // FORWARD(e_forward)  sphere & ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T rho = 0.0;

                    rho = this->m_proj_parm.c - (this->m_proj_parm.ellips ? pj_mlfn(lp_lat, sin(lp_lat),
                        cos(lp_lat), this->m_proj_parm.en) : lp_lat);
                    xy_x = rho * sin( lp_lon *= this->m_proj_parm.n );
                    xy_y = this->m_proj_parm.rho0 - rho * cos(lp_lon);
                }

                // INVERSE(e_inverse)  sphere & ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    static T const half_pi = detail::half_pi<T>();

                    T rho = 0.0;

                    if ((rho = boost::math::hypot(xy_x, xy_y = this->m_proj_parm.rho0 - xy_y)) != 0.0 ) {
                        if (this->m_proj_parm.n < 0.) {
                            rho = -rho;
                            xy_x = -xy_x;
                            xy_y = -xy_y;
                        }
                        lp_lat = this->m_proj_parm.c - rho;
                        if (this->m_proj_parm.ellips)
                            lp_lat = pj_inv_mlfn(lp_lat, par.es, this->m_proj_parm.en);
                        lp_lon = atan2(xy_x, xy_y) / this->m_proj_parm.n;
                    } else {
                        lp_lon = 0.;
                        lp_lat = this->m_proj_parm.n > 0. ? half_pi : -half_pi;
                    }
                }

                static inline std::string get_name()
                {
                    return "eqdc_ellipsoid";
                }

            };

            // Equidistant Conic
            template <typename Params, typename Parameters, typename T>
            inline void setup_eqdc(Params const& params, Parameters& par, par_eqdc<T>& proj_parm)
            {
                T cosphi, sinphi;
                int secant;

                proj_parm.phi1 = pj_get_param_r<T, srs::spar::lat_1>(params, "lat_1", srs::dpar::lat_1);
                proj_parm.phi2 = pj_get_param_r<T, srs::spar::lat_2>(params, "lat_2", srs::dpar::lat_2);

                if (fabs(proj_parm.phi1 + proj_parm.phi2) < epsilon10)
                    BOOST_THROW_EXCEPTION( projection_exception(error_conic_lat_equal) );

                proj_parm.en = pj_enfn<T>(par.es);

                proj_parm.n = sinphi = sin(proj_parm.phi1);
                cosphi = cos(proj_parm.phi1);
                secant = fabs(proj_parm.phi1 - proj_parm.phi2) >= epsilon10;
                if( (proj_parm.ellips = (par.es > 0.)) ) {
                    double ml1, m1;

                    m1 = pj_msfn(sinphi, cosphi, par.es);
                    ml1 = pj_mlfn(proj_parm.phi1, sinphi, cosphi, proj_parm.en);
                    if (secant) { /* secant cone */
                        sinphi = sin(proj_parm.phi2);
                        cosphi = cos(proj_parm.phi2);
                        proj_parm.n = (m1 - pj_msfn(sinphi, cosphi, par.es)) /
                            (pj_mlfn(proj_parm.phi2, sinphi, cosphi, proj_parm.en) - ml1);
                    }
                    proj_parm.c = ml1 + m1 / proj_parm.n;
                    proj_parm.rho0 = proj_parm.c - pj_mlfn(par.phi0, sin(par.phi0),
                        cos(par.phi0), proj_parm.en);
                } else {
                    if (secant)
                        proj_parm.n = (cosphi - cos(proj_parm.phi2)) / (proj_parm.phi2 - proj_parm.phi1);
                    proj_parm.c = proj_parm.phi1 + cos(proj_parm.phi1) / proj_parm.n;
                    proj_parm.rho0 = proj_parm.c - par.phi0;
                }
            }

    }} // namespace detail::eqdc
    #endif // doxygen

    /*!
        \brief Equidistant Conic projection
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
        \image html ex_eqdc.gif
    */
    template <typename T, typename Parameters>
    struct eqdc_ellipsoid : public detail::eqdc::base_eqdc_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline eqdc_ellipsoid(Params const& params, Parameters const& par)
        {
            detail::eqdc::setup_eqdc(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_eqdc, eqdc_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(eqdc_entry, eqdc_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(eqdc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(eqdc, eqdc_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_EQDC_HPP


/* eqdc.hpp
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
*/
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
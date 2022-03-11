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

// Copyright (c) 2003, 2006   Gerald I. Evenden

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_ROUSS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ROUSS_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/proj_mdist.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace rouss
    {
            template <typename T>
            struct par_rouss
            {
                T s0;
                T A1, A2, A3, A4, A5, A6;
                T B1, B2, B3, B4, B5, B6, B7, B8;
                T C1, C2, C3, C4, C5, C6, C7, C8;
                T D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11;
                mdist<T> en;
            };

            template <typename T, typename Parameters>
            struct base_rouss_ellipsoid
            {
                par_rouss<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T s, al, cp, sp, al2, s2;

                    cp = cos(lp_lat);
                    sp = sin(lp_lat);
                    s = proj_mdist(lp_lat, sp, cp,  this->m_proj_parm.en) - this->m_proj_parm.s0;
                    s2 = s * s;
                    al = lp_lon * cp / sqrt(1. - par.es * sp * sp);
                    al2 = al * al;
                    xy_x = par.k0 * al*(1.+s2*(this->m_proj_parm.A1+s2*this->m_proj_parm.A4)-al2*(this->m_proj_parm.A2+s*this->m_proj_parm.A3+s2*this->m_proj_parm.A5
                                +al2*this->m_proj_parm.A6));
                    xy_y = par.k0 * (al2*(this->m_proj_parm.B1+al2*this->m_proj_parm.B4)+
                        s*(1.+al2*(this->m_proj_parm.B3-al2*this->m_proj_parm.B6)+s2*(this->m_proj_parm.B2+s2*this->m_proj_parm.B8)+
                        s*al2*(this->m_proj_parm.B5+s*this->m_proj_parm.B7)));
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T s, al, x = xy_x / par.k0, y = xy_y / par.k0, x2, y2;

                    x2 = x * x;
                    y2 = y * y;
                    al = x*(1.-this->m_proj_parm.C1*y2+x2*(this->m_proj_parm.C2+this->m_proj_parm.C3*y-this->m_proj_parm.C4*x2+this->m_proj_parm.C5*y2-this->m_proj_parm.C7*x2*y)
                        +y2*(this->m_proj_parm.C6*y2-this->m_proj_parm.C8*x2*y));
                    s = this->m_proj_parm.s0 + y*(1.+y2*(-this->m_proj_parm.D2+this->m_proj_parm.D8*y2))+
                        x2*(-this->m_proj_parm.D1+y*(-this->m_proj_parm.D3+y*(-this->m_proj_parm.D5+y*(-this->m_proj_parm.D7+y*this->m_proj_parm.D11)))+
                        x2*(this->m_proj_parm.D4+y*(this->m_proj_parm.D6+y*this->m_proj_parm.D10)-x2*this->m_proj_parm.D9));
                    lp_lat=proj_inv_mdist(s, this->m_proj_parm.en);
                    s = sin(lp_lat);
                    lp_lon=al * sqrt(1. - par.es * s * s)/cos(lp_lat);
                }

                static inline std::string get_name()
                {
                    return "rouss_ellipsoid";
                }

            };

            // Roussilhe Stereographic
            template <typename Parameters, typename T>
            inline void setup_rouss(Parameters const& par, par_rouss<T>& proj_parm)
            {
                T N0, es2, t, t2, R_R0_2, R_R0_4;

                if (!proj_mdist_ini(par.es, proj_parm.en))
                    BOOST_THROW_EXCEPTION( projection_exception(0) );

                es2 = sin(par.phi0);
                proj_parm.s0 = proj_mdist(par.phi0, es2, cos(par.phi0), proj_parm.en);
                t = 1. - (es2 = par.es * es2 * es2);
                N0 = 1./sqrt(t);
                R_R0_2 = t * t / par.one_es;
                R_R0_4 = R_R0_2 * R_R0_2;
                t = tan(par.phi0);
                t2 = t * t;
                proj_parm.C1 = proj_parm.A1 = R_R0_2 / 4.;
                proj_parm.C2 = proj_parm.A2 = R_R0_2 * (2 * t2 - 1. - 2. * es2) / 12.;
                proj_parm.A3 = R_R0_2 * t * (1. + 4. * t2)/ ( 12. * N0);
                proj_parm.A4 = R_R0_4 / 24.;
                proj_parm.A5 = R_R0_4 * ( -1. + t2 * (11. + 12. * t2))/24.;
                proj_parm.A6 = R_R0_4 * ( -2. + t2 * (11. - 2. * t2))/240.;
                proj_parm.B1 = t / (2. * N0);
                proj_parm.B2 = R_R0_2 / 12.;
                proj_parm.B3 = R_R0_2 * (1. + 2. * t2 - 2. * es2)/4.;
                proj_parm.B4 = R_R0_2 * t * (2. - t2)/(24. * N0);
                proj_parm.B5 = R_R0_2 * t * (5. + 4.* t2)/(8. * N0);
                proj_parm.B6 = R_R0_4 * (-2. + t2 * (-5. + 6. * t2))/48.;
                proj_parm.B7 = R_R0_4 * (5. + t2 * (19. + 12. * t2))/24.;
                proj_parm.B8 = R_R0_4 / 120.;
                proj_parm.C3 = R_R0_2 * t * (1. + t2)/(3. * N0);
                proj_parm.C4 = R_R0_4 * (-3. + t2 * (34. + 22. * t2))/240.;
                proj_parm.C5 = R_R0_4 * (4. + t2 * (13. + 12. * t2))/24.;
                proj_parm.C6 = R_R0_4 / 16.;
                proj_parm.C7 = R_R0_4 * t * (11. + t2 * (33. + t2 * 16.))/(48. * N0);
                proj_parm.C8 = R_R0_4 * t * (1. + t2 * 4.)/(36. * N0);
                proj_parm.D1 = t / (2. * N0);
                proj_parm.D2 = R_R0_2 / 12.;
                proj_parm.D3 = R_R0_2 * (2 * t2 + 1. - 2. * es2) / 4.;
                proj_parm.D4 = R_R0_2 * t * (1. + t2)/(8. * N0);
                proj_parm.D5 = R_R0_2 * t * (1. + t2 * 2.)/(4. * N0);
                proj_parm.D6 = R_R0_4 * (1. + t2 * (6. + t2 * 6.))/16.;
                proj_parm.D7 = R_R0_4 * t2 * (3. + t2 * 4.)/8.;
                proj_parm.D8 = R_R0_4 / 80.;
                proj_parm.D9 = R_R0_4 * t * (-21. + t2 * (178. - t2 * 26.))/720.;
                proj_parm.D10 = R_R0_4 * t * (29. + t2 * (86. + t2 * 48.))/(96. * N0);
                proj_parm.D11 = R_R0_4 * t * (37. + t2 * 44.)/(96. * N0);
            }

    }} // namespace detail::rouss
    #endif // doxygen

    /*!
        \brief Roussilhe Stereographic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Ellipsoid
        \par Example
        \image html ex_rouss.gif
    */
    template <typename T, typename Parameters>
    struct rouss_ellipsoid : public detail::rouss::base_rouss_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline rouss_ellipsoid(Params const& , Parameters const& par)
        {
            detail::rouss::setup_rouss(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_rouss, rouss_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(rouss_entry, rouss_ellipsoid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(rouss_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(rouss, rouss_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_ROUSS_HPP


/* rouss.hpp
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
*/
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

/*****************************************************************************

               Lambert Conformal Conic Alternative
               -----------------------------------

    This is Gerald Evenden's 2003 implementation of an alternative
    "almost" LCC, which has been in use historically, but which
    should NOT be used for new projects - i.e: use this implementation
    if you need interoperability with old data represented in this
    projection, but not in any other case.

    The code was originally discussed on the PROJ.4 mailing list in
    a thread archived over at

    http://lists.maptools.org/pipermail/proj/2003-March/000644.html

    It was discussed again in the thread starting at

    http://lists.maptools.org/pipermail/proj/2017-October/007828.html
        and continuing at
    http://lists.maptools.org/pipermail/proj/2017-November/007831.html

    which prompted Clifford J. Mugnier to add these clarifying notes:

    The French Army Truncated Cubic Lambert (partially conformal) Conic
    projection is the Legal system for the projection in France between
    the late 1800s and 1948 when the French Legislature changed the law
    to recognize the fully conformal version.

    It was (might still be in one or two North African prior French
    Colonies) used in North Africa in Algeria, Tunisia, & Morocco, as
    well as in Syria during the Levant.

    Last time I have seen it used was about 30+ years ago in
    Algeria when it was used to define Lease Block boundaries for
    Petroleum Exploration & Production.

    (signed)

    Clifford J. Mugnier, c.p., c.m.s.
    Chief of Geodesy
    LSU Center for GeoInformatics
    Dept. of Civil Engineering
    LOUISIANA STATE UNIVERSITY

*****************************************************************************/

#ifndef BOOST_GEOMETRY_PROJECTIONS_LCCA_HPP
#define BOOST_GEOMETRY_PROJECTIONS_LCCA_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_mlfn.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace lcca
    {

            static const int max_iter = 10;
            static const double del_tol = 1e-12;

            template <typename T>
            struct par_lcca
            {
                detail::en<T> en;
                T    r0, l, M0;
                T    C;
            };

            template <typename T> /* func to compute dr */
            inline T fS(T const& S, T const& C)
            {
                return(S * ( 1. + S * S * C));
            }

            template <typename T> /* deriv of fs */
            inline T fSp(T const& S, T const& C)
            {
                return(1. + 3.* S * S * C);
            }

            template <typename T, typename Parameters>
            struct base_lcca_ellipsoid
            {
                par_lcca<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T S, r, dr;

                    S = pj_mlfn(lp_lat, sin(lp_lat), cos(lp_lat), this->m_proj_parm.en) - this->m_proj_parm.M0;
                    dr = fS(S, this->m_proj_parm.C);
                    r = this->m_proj_parm.r0 - dr;
                    xy_x = par.k0 * (r * sin( lp_lon *= this->m_proj_parm.l ) );
                    xy_y = par.k0 * (this->m_proj_parm.r0 - r * cos(lp_lon) );
                }

                // INVERSE(e_inverse)  ellipsoid & spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    T theta, dr, S, dif;
                    int i;

                    xy_x /= par.k0;
                    xy_y /= par.k0;
                    theta = atan2(xy_x , this->m_proj_parm.r0 - xy_y);
                    dr = xy_y - xy_x * tan(0.5 * theta);
                    lp_lon = theta / this->m_proj_parm.l;
                    S = dr;
                    for (i = max_iter; i ; --i) {
                        S -= (dif = (fS(S, this->m_proj_parm.C) - dr) / fSp(S, this->m_proj_parm.C));
                        if (fabs(dif) < del_tol) break;
                    }
                    if (!i) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                    lp_lat = pj_inv_mlfn(S + this->m_proj_parm.M0, par.es, this->m_proj_parm.en);
                }

                static inline std::string get_name()
                {
                    return "lcca_ellipsoid";
                }

            };

            // Lambert Conformal Conic Alternative
            template <typename Parameters, typename T>
            inline void setup_lcca(Parameters const& par, par_lcca<T>& proj_parm)
            {
                T s2p0, N0, R0, tan0;

                proj_parm.en = pj_enfn<T>(par.es);
                
                if (par.phi0 == 0.) {
                    BOOST_THROW_EXCEPTION( projection_exception(error_lat_0_is_zero) );
                }
                proj_parm.l = sin(par.phi0);
                proj_parm.M0 = pj_mlfn(par.phi0, proj_parm.l, cos(par.phi0), proj_parm.en);
                s2p0 = proj_parm.l * proj_parm.l;
                R0 = 1. / (1. - par.es * s2p0);
                N0 = sqrt(R0);
                R0 *= par.one_es * N0;
                tan0 = tan(par.phi0);
                proj_parm.r0 = N0 / tan0;
                proj_parm.C = 1. / (6. * R0 * N0);
            }

    }} // namespace detail::lcca
    #endif // doxygen

    /*!
        \brief Lambert Conformal Conic Alternative projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lat_0: Latitude of origin
        \par Example
        \image html ex_lcca.gif
    */
    template <typename T, typename Parameters>
    struct lcca_ellipsoid : public detail::lcca::base_lcca_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline lcca_ellipsoid(Params const& , Parameters const& par)
        {
            detail::lcca::setup_lcca(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_lcca, lcca_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(lcca_entry, lcca_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(lcca_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(lcca, lcca_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_LCCA_HPP


/* lcca.hpp
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
*/
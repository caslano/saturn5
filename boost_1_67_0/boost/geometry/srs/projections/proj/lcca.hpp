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
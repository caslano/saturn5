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

#ifndef BOOST_GEOMETRY_PROJECTIONS_CASS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_CASS_HPP

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
    namespace detail { namespace cass
    {

            //static const double epsilon10 = 1e-10;
            //static const double C1 = .16666666666666666666;
            //static const double C2 = .00833333333333333333;
            //static const double C3 = .04166666666666666666;
            //static const double C4 = .33333333333333333333;
            //static const double C5 = .06666666666666666666;

            template <typename T>
            inline T C1() { return .16666666666666666666666666666666666666; }
            template <typename T>
            inline T C2() { return .00833333333333333333333333333333333333; }
            template <typename T>
            inline T C3() { return .04166666666666666666666666666666666666; }
            template <typename T>
            inline T C4() { return .33333333333333333333333333333333333333; }
            template <typename T>
            inline T C5() { return .06666666666666666666666666666666666666; }

            template <typename T>
            struct par_cass
            {
                T m0;
                detail::en<T> en;
            };

            template <typename T, typename Parameters>
            struct base_cass_ellipsoid
            {
                par_cass<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T C1 = cass::C1<T>();
                    static const T C2 = cass::C2<T>();
                    static const T C3 = cass::C3<T>();

                    T n = sin(lp_lat);
                    T c = cos(lp_lat);
                    xy_y = pj_mlfn(lp_lat, n, c, this->m_proj_parm.en);
                    n = 1./sqrt(1. - par.es * n * n);
                    T tn = tan(lp_lat);
                    T t = tn * tn;
                    T a1 = lp_lon * c;
                    c *= par.es * c / (1 - par.es);
                    T a2 = a1 * a1;
                    xy_x = n * a1 * (1. - a2 * t *
                        (C1 - (8. - t + 8. * c) * a2 * C2));
                    xy_y -= this->m_proj_parm.m0 - n * tn * a2 *
                        (.5 + (5. - t + 6. * c) * a2 * C3);
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T C3 = cass::C3<T>();
                    static const T C4 = cass::C4<T>();
                    static const T C5 = cass::C5<T>();

                    T ph1;

                    ph1 = pj_inv_mlfn(this->m_proj_parm.m0 + xy_y, par.es, this->m_proj_parm.en);
                    T tn = tan(ph1); T t = tn * tn;
                    T n = sin(ph1);
                    T r = 1. / (1. - par.es * n * n);
                    n = sqrt(r);
                    r *= (1. - par.es) * n;
                    T dd = xy_x / n;
                    T d2 = dd * dd;
                    lp_lat = ph1 - (n * tn / r) * d2 *
                        (.5 - (1. + 3. * t) * d2 * C3);
                    lp_lon = dd * (1. + t * d2 *
                        (-C4 + (1. + 3. * t) * d2 * C5)) / cos(ph1);
                }

                static inline std::string get_name()
                {
                    return "cass_ellipsoid";
                }

            };

            template <typename T, typename Parameters>
            struct base_cass_spheroid
            {
                par_cass<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = asin(cos(lp_lat) * sin(lp_lon));
                    xy_y = atan2(tan(lp_lat) , cos(lp_lon)) - par.phi0;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T dd = xy_y + par.phi0;
                    lp_lat = asin(sin(dd) * cos(xy_x));
                    lp_lon = atan2(tan(xy_x), cos(dd));
                }

                static inline std::string get_name()
                {
                    return "cass_spheroid";
                }

            };

            // Cassini
            template <typename Parameters, typename T>
            inline void setup_cass(Parameters& par, par_cass<T>& proj_parm)
            {
                if (par.es) {
                    proj_parm.en = pj_enfn<T>(par.es);
                    proj_parm.m0 = pj_mlfn(par.phi0, sin(par.phi0), cos(par.phi0), proj_parm.en);
                } else {
                }
            }

    }} // namespace detail::cass
    #endif // doxygen

    /*!
        \brief Cassini projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
         - Ellipsoid
        \par Example
        \image html ex_cass.gif
    */
    template <typename T, typename Parameters>
    struct cass_ellipsoid : public detail::cass::base_cass_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline cass_ellipsoid(Params const& , Parameters const& par)
        {
            detail::cass::setup_cass(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Cassini projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
         - Ellipsoid
        \par Example
        \image html ex_cass.gif
    */
    template <typename T, typename Parameters>
    struct cass_spheroid : public detail::cass::base_cass_spheroid<T, Parameters>
    {
        template <typename Params>
        inline cass_spheroid(Params const& , Parameters const& par)
        {
            detail::cass::setup_cass(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI2(srs::spar::proj_cass, cass_spheroid, cass_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI2(cass_entry, cass_spheroid, cass_ellipsoid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(cass_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(cass, cass_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_CASS_HPP


/* cass.hpp
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
*/
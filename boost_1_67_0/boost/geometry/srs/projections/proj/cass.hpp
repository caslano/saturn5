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
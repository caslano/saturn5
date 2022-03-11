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

#ifndef BOOST_GEOMETRY_PROJECTIONS_IGH_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IGH_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/proj/gn_sinu.hpp>
#include <boost/geometry/srs/projections/proj/moll.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/shared_ptr.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace igh
    {
            template <typename T>
            struct par_igh_zone
            {
                T x0;
                T y0;
                T lam0;
            };

            // NOTE: x0, y0, lam0 are not used in moll nor sinu projections
            // so it is a waste of memory to keep 12 copies of projections
            // with parameters as in the original Proj4.

            // TODO: It would be possible to further decrease the size of par_igh
            // because spherical sinu and moll has constant parameters.
            // TODO: Furthermore there is no need to store par_igh_zone parameters
            // since they are constant for zones. In both fwd() and inv() there are
            // parts of code dependent on specific zones (if statements) anyway
            // so these parameters could be hardcoded there instead of stored.

            template <typename T, typename Parameters>
            struct par_igh
            {
                moll_spheroid<T, Parameters> moll;
                sinu_spheroid<T, Parameters> sinu;
                par_igh_zone<T> zones[12];
                T dy0;

                // NOTE: The constructors of moll and sinu projections sets
                // par.es = 0

                template <typename Params>
                inline par_igh(Params const& params, Parameters & par)
                    : moll(params, par)
                    , sinu(params, par)
                {}

                inline void fwd(int zone, Parameters const& par, T const& lp_lon, T const& lp_lat, T & xy_x, T & xy_y) const
                {
                    if (zone <= 2 || zone >= 9) // 1, 2, 9, 10, 11, 12
                        moll.fwd(par, lp_lon, lp_lat, xy_x, xy_y);
                    else // 3, 4, 5, 6, 7, 8
                        sinu.fwd(par, lp_lon, lp_lat, xy_x, xy_y);
                }

                inline void inv(int zone, Parameters const& par, T const& xy_x, T const& xy_y, T & lp_lon, T & lp_lat) const
                {
                    if (zone <= 2 || zone >= 9) // 1, 2, 9, 10, 11, 12
                        moll.inv(par, xy_x, xy_y, lp_lon, lp_lat);
                    else // 3, 4, 5, 6, 7, 8
                        sinu.inv(par, xy_x, xy_y, lp_lon, lp_lat);
                }

                inline void set_zone(int zone, T const& x_0, T const& y_0, T const& lon_0)
                {
                    zones[zone - 1].x0 = x_0;
                    zones[zone - 1].y0 = y_0;
                    zones[zone - 1].lam0 = lon_0;
                }

                inline par_igh_zone<T> const& get_zone(int zone) const
                {
                    return zones[zone - 1];
                }
            };

            /* 40d 44' 11.8" [degrees] */
            template <typename T>
            inline T d4044118() { return (T(40) + T(44)/T(60.) + T(11.8)/T(3600.)) * geometry::math::d2r<T>(); }

            template <typename T>
            inline T d10() { return T(10) * geometry::math::d2r<T>(); }
            template <typename T>
            inline T d20() { return T(20) * geometry::math::d2r<T>(); }
            template <typename T>
            inline T d30() { return T(30) * geometry::math::d2r<T>(); }
            template <typename T>
            inline T d40() { return T(40) * geometry::math::d2r<T>(); }
            template <typename T>
            inline T d50() { return T(50) * geometry::math::d2r<T>(); }
            template <typename T>
            inline T d60() { return T(60) * geometry::math::d2r<T>(); }
            template <typename T>
            inline T d80() { return T(80) * geometry::math::d2r<T>(); }
            template <typename T>
            inline T d90() { return T(90) * geometry::math::d2r<T>(); }
            template <typename T>
            inline T d100() { return T(100) * geometry::math::d2r<T>(); }
            template <typename T>
            inline T d140() { return T(140) * geometry::math::d2r<T>(); }
            template <typename T>
            inline T d160() { return T(160) * geometry::math::d2r<T>(); }
            template <typename T>
            inline T d180() { return T(180) * geometry::math::d2r<T>(); }

            static const double epsilon = 1.e-10; // allow a little 'slack' on zone edge positions

            template <typename T, typename Parameters>
            struct base_igh_spheroid
            {
                par_igh<T, Parameters> m_proj_parm;

                template <typename Params>
                inline base_igh_spheroid(Params const& params, Parameters & par)
                    : m_proj_parm(params, par)
                {}

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T d4044118 = igh::d4044118<T>();
                    static const T d20  =  igh::d20<T>();
                    static const T d40  =  igh::d40<T>();
                    static const T d80  =  igh::d80<T>();
                    static const T d100 = igh::d100<T>();

                        int z;
                        if (lp_lat >=  d4044118) {          // 1|2
                          z = (lp_lon <= -d40 ? 1: 2);
                        }
                        else if (lp_lat >=  0) {            // 3|4
                          z = (lp_lon <= -d40 ? 3: 4);
                        }
                        else if (lp_lat >= -d4044118) {     // 5|6|7|8
                               if (lp_lon <= -d100) z =  5; // 5
                          else if (lp_lon <=  -d20) z =  6; // 6
                          else if (lp_lon <=   d80) z =  7; // 7
                          else z = 8;                       // 8
                        }
                        else {                              // 9|10|11|12
                               if (lp_lon <= -d100) z =  9; // 9
                          else if (lp_lon <=  -d20) z = 10; // 10
                          else if (lp_lon <=   d80) z = 11; // 11
                          else z = 12;                      // 12
                        }

                        lp_lon -= this->m_proj_parm.get_zone(z).lam0;
                        this->m_proj_parm.fwd(z, par, lp_lon, lp_lat, xy_x, xy_y);
                        xy_x += this->m_proj_parm.get_zone(z).x0;
                        xy_y += this->m_proj_parm.get_zone(z).y0;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T d4044118 = igh::d4044118<T>();
                    static const T d10  =  igh::d10<T>();
                    static const T d20  =  igh::d20<T>();
                    static const T d40  =  igh::d40<T>();
                    static const T d50  =  igh::d50<T>();
                    static const T d60  =  igh::d60<T>();
                    static const T d80  =  igh::d80<T>();
                    static const T d90  =  igh::d90<T>();
                    static const T d100 = igh::d100<T>();
                    static const T d160 = igh::d160<T>();
                    static const T d180 = igh::d180<T>();

                    static const T c2 = 2.0;
                    
                    const T y90 = this->m_proj_parm.dy0 + sqrt(c2); // lt=90 corresponds to y=y0+sqrt(2.0)

                        int z = 0;
                        if (xy_y > y90+epsilon || xy_y < -y90+epsilon) // 0
                          z = 0;
                        else if (xy_y >=  d4044118)       // 1|2
                          z = (xy_x <= -d40? 1: 2);
                        else if (xy_y >=  0)              // 3|4
                          z = (xy_x <= -d40? 3: 4);
                        else if (xy_y >= -d4044118) {     // 5|6|7|8
                               if (xy_x <= -d100) z =  5; // 5
                          else if (xy_x <=  -d20) z =  6; // 6
                          else if (xy_x <=   d80) z =  7; // 7
                          else z = 8;                     // 8
                        }
                        else {                            // 9|10|11|12
                               if (xy_x <= -d100) z =  9; // 9
                          else if (xy_x <=  -d20) z = 10; // 10
                          else if (xy_x <=   d80) z = 11; // 11
                          else z = 12;                    // 12
                        }

                        if (z)
                        {
                          int ok = 0;

                          xy_x -= this->m_proj_parm.get_zone(z).x0;
                          xy_y -= this->m_proj_parm.get_zone(z).y0;
                          this->m_proj_parm.inv(z, par, xy_x, xy_y, lp_lon, lp_lat);
                          lp_lon += this->m_proj_parm.get_zone(z).lam0;

                          switch (z) {
                            case  1: ok = (lp_lon >= -d180-epsilon && lp_lon <=  -d40+epsilon) ||
                                         ((lp_lon >=  -d40-epsilon && lp_lon <=  -d10+epsilon) &&
                                          (lp_lat >=   d60-epsilon && lp_lat <=   d90+epsilon)); break;
                            case  2: ok = (lp_lon >=  -d40-epsilon && lp_lon <=  d180+epsilon) ||
                                         ((lp_lon >= -d180-epsilon && lp_lon <= -d160+epsilon) &&
                                          (lp_lat >=   d50-epsilon && lp_lat <=   d90+epsilon)) ||
                                         ((lp_lon >=  -d50-epsilon && lp_lon <=  -d40+epsilon) &&
                                          (lp_lat >=   d60-epsilon && lp_lat <=   d90+epsilon)); break;
                            case  3: ok = (lp_lon >= -d180-epsilon && lp_lon <=  -d40+epsilon); break;
                            case  4: ok = (lp_lon >=  -d40-epsilon && lp_lon <=  d180+epsilon); break;
                            case  5: ok = (lp_lon >= -d180-epsilon && lp_lon <= -d100+epsilon); break;
                            case  6: ok = (lp_lon >= -d100-epsilon && lp_lon <=  -d20+epsilon); break;
                            case  7: ok = (lp_lon >=  -d20-epsilon && lp_lon <=   d80+epsilon); break;
                            case  8: ok = (lp_lon >=   d80-epsilon && lp_lon <=  d180+epsilon); break;
                            case  9: ok = (lp_lon >= -d180-epsilon && lp_lon <= -d100+epsilon); break;
                            case 10: ok = (lp_lon >= -d100-epsilon && lp_lon <=  -d20+epsilon); break;
                            case 11: ok = (lp_lon >=  -d20-epsilon && lp_lon <=   d80+epsilon); break;
                            case 12: ok = (lp_lon >=   d80-epsilon && lp_lon <=  d180+epsilon); break;
                          }

                          z = (!ok? 0: z); // projectable?
                        }
                     // if (!z) pj_errno = -15; // invalid x or y
                        if (!z) lp_lon = HUGE_VAL;
                        if (!z) lp_lat = HUGE_VAL;
                }

                static inline std::string get_name()
                {
                    return "igh_spheroid";
                }

            };

            // Interrupted Goode Homolosine
            template <typename Params, typename Parameters, typename T>
            inline void setup_igh(Params const& params, Parameters& par, par_igh<T, Parameters>& proj_parm)
            {
                static const T d0   =  0;
                static const T d4044118 = igh::d4044118<T>();
                static const T d20  =  igh::d20<T>();
                static const T d30  =  igh::d30<T>();
                static const T d60  =  igh::d60<T>();
                static const T d100 = igh::d100<T>();
                static const T d140 = igh::d140<T>();
                static const T d160 = igh::d160<T>();

            /*
              Zones:

                -180            -40                       180
                  +--------------+-------------------------+    Zones 1,2,9,10,11 & 12:
                  |1             |2                        |      Mollweide projection
                  |              |                         |
                  +--------------+-------------------------+    Zones 3,4,5,6,7 & 8:
                  |3             |4                        |      Sinusoidal projection
                  |              |                         |
                0 +-------+------+-+-----------+-----------+
                  |5      |6       |7          |8          |
                  |       |        |           |           |
                  +-------+--------+-----------+-----------+
                  |9      |10      |11         |12         |
                  |       |        |           |           |
                  +-------+--------+-----------+-----------+
                -180    -100      -20         80          180
            */
                
                    T lp_lam = 0, lp_phi = d4044118;
                    T xy1_x, xy1_y;
                    T xy3_x, xy3_y;

                    // sinusoidal zones
                    proj_parm.set_zone(3, -d100, d0, -d100);
                    proj_parm.set_zone(4,   d30, d0,   d30);
                    proj_parm.set_zone(5, -d160, d0, -d160);
                    proj_parm.set_zone(6,  -d60, d0,  -d60);
                    proj_parm.set_zone(7,   d20, d0,   d20);
                    proj_parm.set_zone(8,  d140, d0,  d140);

                    // mollweide zones
                    proj_parm.set_zone(1, -d100, d0, -d100);

                    // NOTE: x0, y0, lam0 are not used in moll nor sinu fwd
                    // so the order of initialization doesn't matter that much.
                    // But keep the original one from Proj4.

                    // y0 ?
                    proj_parm.fwd(1, par, lp_lam, lp_phi, xy1_x, xy1_y); // zone 1
                    proj_parm.fwd(3, par, lp_lam, lp_phi, xy3_x, xy3_y); // zone 3
                    // y0 + xy1_y = xy3_y for lt = 40d44'11.8"
                    proj_parm.dy0 = xy3_y - xy1_y;

                    proj_parm.zones[0].y0 = proj_parm.dy0; // zone 1

                    // mollweide zones (cont'd)
                    proj_parm.set_zone(2,   d30,  proj_parm.dy0,   d30);
                    proj_parm.set_zone(9, -d160, -proj_parm.dy0, -d160);
                    proj_parm.set_zone(10, -d60, -proj_parm.dy0,  -d60);
                    proj_parm.set_zone(11,  d20, -proj_parm.dy0,   d20);
                    proj_parm.set_zone(12, d140, -proj_parm.dy0,  d140);

                    // NOTE: Already done before in sinu and moll constructor
                    //par.es = 0.;
            }

    }} // namespace detail::igh
    #endif // doxygen

    /*!
        \brief Interrupted Goode Homolosine projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_igh.gif
    */
    template <typename T, typename Parameters>
    struct igh_spheroid : public detail::igh::base_igh_spheroid<T, Parameters>
    {
        template <typename Params>
        inline igh_spheroid(Params const& params, Parameters & par)
            : detail::igh::base_igh_spheroid<T, Parameters>(params, par)
        {
            detail::igh::setup_igh(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_igh, igh_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(igh_entry, igh_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(igh_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(igh, igh_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_IGH_HPP


/* igh.hpp
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
*/
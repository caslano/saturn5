// Boost.Geometry - gis-projections (based on PROJ4)

// Copyright (c) 2008-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2021.
// Modifications copyright (c) 2017-2021, Oracle and/or its affiliates.
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
            inline void setup_igh(Params const& , Parameters& par, par_igh<T, Parameters>& proj_parm)
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
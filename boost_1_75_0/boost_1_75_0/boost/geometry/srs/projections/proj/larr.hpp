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

#ifndef BOOST_GEOMETRY_PROJECTIONS_LARR_HPP
#define BOOST_GEOMETRY_PROJECTIONS_LARR_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace larr
    {

            template <typename T, typename Parameters>
            struct base_larr_spheroid
            {
                // FORWARD(s_forward)  sphere
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T sixth = detail::sixth<T>();

                    xy_x = 0.5 * lp_lon * (1. + sqrt(cos(lp_lat)));
                    xy_y = lp_lat / (cos(0.5 * lp_lat) * cos(sixth * lp_lon));
                }

                static inline std::string get_name()
                {
                    return "larr_spheroid";
                }

            };

            // Larrivee
            template <typename Parameters>
            inline void setup_larr(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::larr
    #endif // doxygen

    /*!
        \brief Larrivee projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_larr.gif
    */
    template <typename T, typename Parameters>
    struct larr_spheroid : public detail::larr::base_larr_spheroid<T, Parameters>
    {
        template <typename Params>
        inline larr_spheroid(Params const& , Parameters & par)
        {
            detail::larr::setup_larr(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_larr, larr_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(larr_entry, larr_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(larr_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(larr, larr_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_LARR_HPP


/* larr.hpp
tyyQkfgj7V2k/QzdEsZb4ltUt/AmAwTZ+WUrQ/jlgiZ/B7Hm4CFwN1xcYhAjVeLxjGSe75K6Wf/FVslxwIoI/WTmUkBiGNaXu5uzfDc8KZacEeKxK0lk7yMzTABCXuB/Hjupff0yiDHo5+uYczu/TUNijWWEFCfHYEosN8sc8vxgzMT4NORs1MFZPKRhuGZSxayGD4mWHdJyjF2M0srqovLFcByBbUI1hS0YXBLmiWa+ijT9Uh8tLNZ6WTZjOb8VzG29Zr4mpsxV4x82Y6xDq63N6B67YfliD8qdmsZ/vw/SR+rmHn4HcJYT1wfnnyb6y+fIEsQOqx12Xr+Hia6rA3PvQNnvPm/vjgGR7/6XDlt7WyyBREQRvSVnLWciBnYvBMx+LRx6YY17/gTlgLy09zAeu9se3rh3qMt3e49TpjTYd23JV3ehS/A7/1H7JxuIHSS9EiEFtPuuToicMvXeH+j9Kv8AgqtFyP2Tx4FBBF1v7r3CBrLZeA92G7BXH/T+8v7OZv5svMGE9QACX6lqld2CnmdtHlsTV8y5XtF/1+TNu8IzgP9p8PofavJ/dqJVMfVwYfmnOYyNzrBrTqOPcpIIgH68hUJfGodSk+nMSTKyhCLhOS+1RW9RKslUMj/1J2X7nVNqt7c61mmb5orSMS45TT1h6WUomgI8/LHoVhP8Uz9DdAH/U+2rMgW8Vi/DvL5s5tAXnSLFptep
*/
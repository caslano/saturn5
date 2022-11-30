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

#ifndef BOOST_GEOMETRY_PROJECTIONS_GINS8_HPP
#define BOOST_GEOMETRY_PROJECTIONS_GINS8_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace gins8
    {

            static const double Cl = 0.000952426;
            static const double Cp = 0.162388;
            //static const double C12 = 0.08333333333333333;

            template <typename T>
            inline T C12() { return 0.083333333333333333333333333333333333; }

            template <typename T, typename Parameters>
            struct base_gins8_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T C12 = gins8::C12<T>();

                    T t = lp_lat * lp_lat;

                    xy_y = lp_lat * (1. + t * C12);
                    xy_x = lp_lon * (1. - Cp * t);
                    t = lp_lon * lp_lon;
                    xy_x *= (0.87 - Cl * t * t);
                }

                static inline std::string get_name()
                {
                    return "gins8_spheroid";
                }

            };

            // Ginsburg VIII (TsNIIGAiK)
            template <typename Parameters>
            inline void setup_gins8(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::gins8
    #endif // doxygen

    /*!
        \brief Ginsburg VIII (TsNIIGAiK) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
         - no inverse
        \par Example
        \image html ex_gins8.gif
    */
    template <typename T, typename Parameters>
    struct gins8_spheroid : public detail::gins8::base_gins8_spheroid<T, Parameters>
    {
        template <typename Params>
        inline gins8_spheroid(Params const& , Parameters & par)
        {
            detail::gins8::setup_gins8(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_gins8, gins8_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(gins8_entry, gins8_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(gins8_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(gins8, gins8_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_GINS8_HPP


/* gins8.hpp
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
*/
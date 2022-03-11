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
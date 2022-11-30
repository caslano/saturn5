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

#ifndef BOOST_GEOMETRY_PROJECTIONS_TCC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_TCC_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace tcc
    {

            static const double epsilon10 = 1.e-10;

            template <typename T, typename Parameters>
            struct base_tcc_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T b, bt;

                    b = cos(lp_lat) * sin(lp_lon);
                    if ((bt = 1. - b * b) < epsilon10) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                    xy_x = b / sqrt(bt);
                    xy_y = atan2(tan(lp_lat) , cos(lp_lon));
                }

                static inline std::string get_name()
                {
                    return "tcc_spheroid";
                }

            };

            // Transverse Central Cylindrical
            template <typename Parameters>
            inline void setup_tcc(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::tcc
    #endif // doxygen

    /*!
        \brief Transverse Central Cylindrical projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
         - no inverse
        \par Example
        \image html ex_tcc.gif
    */
    template <typename T, typename Parameters>
    struct tcc_spheroid : public detail::tcc::base_tcc_spheroid<T, Parameters>
    {
        template <typename Params>
        inline tcc_spheroid(Params const& , Parameters & par)
        {
            detail::tcc::setup_tcc(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_tcc, tcc_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(tcc_entry, tcc_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(tcc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(tcc, tcc_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_TCC_HPP


/* tcc.hpp
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
*/
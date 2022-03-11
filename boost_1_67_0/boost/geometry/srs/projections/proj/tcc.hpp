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
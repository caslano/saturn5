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

#ifndef BOOST_GEOMETRY_PROJECTIONS_URMFPS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_URMFPS_HPP

#include <boost/geometry/srs/projections/impl/aasincos.hpp>
#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace urmfps
    {

            static const double C_x = 0.8773826753;
            static const double Cy = 1.139753528477;

            template <typename T>
            struct par_urmfps
            {
                T    n, C_y;
            };

            template <typename T, typename Parameters>
            struct base_urmfps_spheroid
            {
                par_urmfps<T> m_proj_parm;

                // FORWARD(s_forward)  sphere
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    lp_lat = aasin(this->m_proj_parm.n * sin(lp_lat));
                    xy_x = C_x * lp_lon * cos(lp_lat);
                    xy_y = this->m_proj_parm.C_y * lp_lat;
                }

                // INVERSE(s_inverse)  sphere
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    xy_y /= this->m_proj_parm.C_y;
                    lp_lat = aasin(sin(xy_y) / this->m_proj_parm.n);
                    lp_lon = xy_x / (C_x * cos(xy_y));
                }

                static inline std::string get_name()
                {
                    return "urmfps_spheroid";
                }

            };

            template <typename Parameters, typename T>
            inline void setup(Parameters& par, par_urmfps<T>& proj_parm) 
            {
                proj_parm.C_y = Cy / proj_parm.n;
                par.es = 0.;
            }


            // Urmaev Flat-Polar Sinusoidal
            template <typename Params, typename Parameters, typename T>
            inline void setup_urmfps(Params const& params, Parameters& par, par_urmfps<T>& proj_parm)
            {
                if (pj_param_f<srs::spar::n>(params, "n", srs::dpar::n, proj_parm.n)) {
                    if (proj_parm.n <= 0. || proj_parm.n > 1.)
                        BOOST_THROW_EXCEPTION( projection_exception(error_n_out_of_range) );
                } else
                    BOOST_THROW_EXCEPTION( projection_exception(error_n_out_of_range) );

                setup(par, proj_parm);
            }

            // Wagner I (Kavraisky VI)
            template <typename Parameters, typename T>
            inline void setup_wag1(Parameters& par, par_urmfps<T>& proj_parm)
            {
                proj_parm.n = 0.8660254037844386467637231707;
                setup(par, proj_parm);
            }

    }} // namespace detail::urmfps
    #endif // doxygen

    /*!
        \brief Urmaev Flat-Polar Sinusoidal projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Projection parameters
         - n (real)
        \par Example
        \image html ex_urmfps.gif
    */
    template <typename T, typename Parameters>
    struct urmfps_spheroid : public detail::urmfps::base_urmfps_spheroid<T, Parameters>
    {
        template <typename Params>
        inline urmfps_spheroid(Params const& params, Parameters & par)
        {
            detail::urmfps::setup_urmfps(params, par, this->m_proj_parm);
        }
    };

    /*!
        \brief Wagner I (Kavraisky VI) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_wag1.gif
    */
    template <typename T, typename Parameters>
    struct wag1_spheroid : public detail::urmfps::base_urmfps_spheroid<T, Parameters>
    {
        template <typename Params>
        inline wag1_spheroid(Params const& , Parameters & par)
        {
            detail::urmfps::setup_wag1(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_urmfps, urmfps_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_wag1, wag1_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(urmfps_entry, urmfps_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(wag1_entry, wag1_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(urmfps_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(urmfps, urmfps_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(wag1, wag1_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_URMFPS_HPP


/* urmfps.hpp
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
*/
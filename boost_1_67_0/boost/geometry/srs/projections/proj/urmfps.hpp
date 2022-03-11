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
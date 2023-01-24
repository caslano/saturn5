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

#ifndef BOOST_GEOMETRY_PROJECTIONS_LOXIM_HPP
#define BOOST_GEOMETRY_PROJECTIONS_LOXIM_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace loxim
    {
            static const double epsilon = 1e-8;

            template <typename T>
            struct par_loxim
            {
                T phi1;
                T cosphi1;
                T tanphi1;
            };

            template <typename T, typename Parameters>
            struct base_loxim_spheroid
            {
                par_loxim<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();
                    static const T half_pi = detail::half_pi<T>();

                    xy_y = lp_lat - this->m_proj_parm.phi1;
                    if (fabs(xy_y) < epsilon)
                        xy_x = lp_lon * this->m_proj_parm.cosphi1;
                    else {
                        xy_x = fourth_pi + 0.5 * lp_lat;
                        if (fabs(xy_x) < epsilon || fabs(fabs(xy_x) - half_pi) < epsilon)
                            xy_x = 0.;
                        else
                            xy_x = lp_lon * xy_y / log( tan(xy_x) / this->m_proj_parm.tanphi1 );
                    }
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const&, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();
                    static const T half_pi = detail::half_pi<T>();

                    lp_lat = xy_y + this->m_proj_parm.phi1;
                    if (fabs(xy_y) < epsilon) {
                        lp_lon = xy_x / this->m_proj_parm.cosphi1;
                    } else {
                        lp_lon = fourth_pi + 0.5 * lp_lat;
                        if (fabs(lp_lon) < epsilon || fabs(fabs(lp_lon) - half_pi) < epsilon)
                            lp_lon = 0.;
                        else
                            lp_lon = xy_x * log( tan(lp_lon) / this->m_proj_parm.tanphi1 ) / xy_y ;
                    }
                }

                static inline std::string get_name()
                {
                    return "loxim_spheroid";
                }

            };

            // Loximuthal
            template <typename Params, typename Parameters, typename T>
            inline void setup_loxim(Params const& params, Parameters& par, par_loxim<T>& proj_parm)
            {
                static const T fourth_pi = detail::fourth_pi<T>();

                proj_parm.phi1 = pj_get_param_r<T, srs::spar::lat_1>(params, "lat_1", srs::dpar::lat_1);
                proj_parm.cosphi1 = cos(proj_parm.phi1);
                if (proj_parm.cosphi1 < epsilon)
                    BOOST_THROW_EXCEPTION( projection_exception(error_lat_larger_than_90) );

                proj_parm.tanphi1 = tan(fourth_pi + 0.5 * proj_parm.phi1);

                par.es = 0.;
            }

    }} // namespace detail::loxim
    #endif // doxygen

    /*!
        \brief Loximuthal projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel (degrees)
        \par Example
        \image html ex_loxim.gif
    */
    template <typename T, typename Parameters>
    struct loxim_spheroid : public detail::loxim::base_loxim_spheroid<T, Parameters>
    {
        template <typename Params>
        inline loxim_spheroid(Params const& params, Parameters & par)
        {
            detail::loxim::setup_loxim(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_loxim, loxim_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(loxim_entry, loxim_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(loxim_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(loxim, loxim_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_LOXIM_HPP


/* loxim.hpp
wcUdEK1XJxRaZbzpRnz1l48enzMq9ND3wbXl8sdjf21/UL+038Gtwf/UI1h7LwLt+4rFB8Fw39b0wxgVr/GuiehMi/xJ4BRPA2oWYkyI+un7GCNBR9tzNB5hqT/FMbnX7UN6PhDCf70W+RMA5na2SM7dBsk9l/TmsvRGXK1mK2fP0WKPuu8DWrmdc7QbBm1hnWJo7L4ruU82/8kk8ugqE+NF7AqmerDJuD2E15Vd9GCaW0s8U9A2D03hswuKC9o8utQPUUyVDxUwp3BsASgja6jpoUnVvZ6IkR7da2WltnmIRx+zCwpdAoVYg+dZJG7JsAtTD007hG5VkGOpHAjhhvW8MK+vUjy0O8lLBloHXB2F10TsNzHOI3DAOm5R+FrSmRZ0AEHEEfFql+CgG9bsosYb3i4BqkEa0V2KrUQYPhqKeIpkJrqUQpE38nM44dm1XncO60PolYK4KbaB+e8veHnoHvFDh9+s1OfEvEScm6cNkRTgHr9csAXcjjnY4jybq03AxiFfLwADYxsWVMQJDg1XhJ9HpSfn5XRvsLLz5lxyGGf+HKOQYPMkXx+5OCfclHmnSP54JHlcZMctB5p1dolHsEgTo5ElYiRIlVOVerfI0x0Uj5DXz6UhHV6s+TiKu7WM+mCaURJ3iJiHf6I+iHGJVqC22oRu3Ze620y5sZPS6cbtjOqpJ2/BrytYPCpsajLtZnmufgi5wfeF
*/
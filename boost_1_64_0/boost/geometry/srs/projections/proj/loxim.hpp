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
kBpMSNWIdJxEujKJgwp610qVFNzuLJWtphJQ+PhZvhilAuZzKQM8YIZDoXhoreTjJNRrVIq+zxG+UKL7VF87hxvza+uwMXutXWL1bs1BJxgqWkpjFjXeYq7SFnODxTe3VIHcWituoudxrbji80wF0ohFx4dC+otgM0vp/J/7sSZFS74hWliCEAPytit6QsITjI/TV5qp9DWoeE1Rx3v4MCGonz1sf2JMy3/YAP1f/tmf/x/N5ic/AiteMO9KVgK4CppdZ0OviVQTtpNHmBReb2ihiQXpPreYDOVG8iWkrmmbMmjRTurrq2iXkpWcjjncrYyKyBhRMiiVQnGACq8FiogTiA9kmDKpC50F4VH4s9OxaCjFR9sh0AJ2Irhko0sc48ClRWFafAU2YJ8GLpUXgEN2iyTA+xj1uwbe6RAE/EhghyAQ1J/LUATUOwScsc0euqKwGfF3C/yQfq/Cp30EE/rEUoXucUpb4lUW9Hkm9AoD3S/Qq/USCze1TyjDDAasScAqjQJHma32x1WJr5XGKgnGKmIk0iHFYkqRLQLpI1Wixut74TFGLHpd0UQEEIhIuSBCw9ONLnNFUIu5dqDBIgCEJRYLqVrBTyWTYhOE33dZcBoETq3T9BJatRWnWLC0ln6FvYPZEkepvrEteFaRbyNUsp7PyutN/6tvqCWLmtVDWNTUf4KipsUkZXI/EFKm+/MeojRjiPm4sB8Nia2GzeX4VDlhghFlCWlBEADGa0iXndFyD6e9gTVSiRWIk93oOVAtCLv3pJGyDygjLMQ+uh/MztagTw7OxA3E8WxJ+zycimLyEaaiCA/j0XP0XjT4RR3dKs7Pw63JHKF+Yijfpld/LxQI1ZaXHWy38D6lQuLRL3hPc1jo8loky6gQ4GE+HOnsJHno3ncvRt5GcLql2h7T5Ok1H0HSxIJuRx9ghZhYzy8w70e+cJHYj+w6v38dbFp7u9vNFy2/2SsNhkz6WywBu0lvYefpPdw7rfSs9IZa6G1zmuj9MLtn9Co1rP/DBT334fsy5Ssp5RovS0PqmSUh56o1OXSdpGsOY9WpNMluJhT9fj7w5u6nrwUfOIpXlDpd0FUnOQCFH0ja6qLJ8bE/cKMSMU6OX1GT42vfgcnxX9Q0l1/QZPrQ1OZBlGYgJIbGRwFZ7SMt6bUMfjCwxh27j09I+HGcKmTu3f7CKi1u2MWGJeDLexTemYKmGb4ykffrWVm0z7yDeYvChVG80d0LGXPRHa23NbqPBgFw5irKJO9V8G7MwPATgBcksJMJnH4PZg7c5szdBTRoF3IsdQM22NuLi/atdzU6tQGGoSb4yZCWwfRkSKX27x5Wkk/pV+dT+1GtRW1r8FSPiqb4ZLlJP6SX2JPWR0MmsdH2+6ulHfFLXVEuOd/31TW9HarkvgERYo+jvMGzUdhlwOBvKYXE/X/ReDG4Vqls0ZYKh67EVGldFBGvSwHAet41nxczo1ICTqeOxvmYTsurmhzGfQ0r80hT8D5efYngTRicE7sa2pn+CrDHu88OxXIewJgbaBVspIzJ7Pbw6dqXub1u2rVqGshD+11ZjtQHEF/lZe2Vd6sqWqt2aZ94i3a+a0UrUBbMi0ixnTes9flZ/PDu4nMhwwLGdhhBMr5taRTh/qZD+u9lUdkeCe1qATQFBk7PkoVZDjAYXrLit9AodNCLTUPe0376BHJGHbwpFjmGvOrw8DD2qqM9MiVyClkDGRsfLXG30ZzYJ3HRG8+L92e/Or5pT+8KCB9t98mjqoIyGTmGDvV++nEm3B6ivhDOibrvBi8KUOPtQTzVVueamVF3/rOZaT0xaOr6awdw+7gUkqH3f96UtaZO/GT1K6kAHDY=
*/
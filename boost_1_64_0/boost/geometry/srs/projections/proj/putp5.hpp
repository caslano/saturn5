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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PUTP5_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PUTP5_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace putp5
    {

            static const double C = 1.01346;
            static const double D = 1.2158542;

            template <typename T>
            struct par_putp5
            {
                T    A, B;
            };

            template <typename T, typename Parameters>
            struct base_putp5_spheroid
            {
                par_putp5<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = C * lp_lon * (this->m_proj_parm.A - this->m_proj_parm.B * sqrt(1. + D * lp_lat * lp_lat));
                    xy_y = C * lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lat = xy_y / C;
                    lp_lon = xy_x / (C * (this->m_proj_parm.A - this->m_proj_parm.B * sqrt(1. + D * lp_lat * lp_lat)));
                }

                static inline std::string get_name()
                {
                    return "putp5_spheroid";
                }

            };
            

            // Putnins P5
            template <typename Parameters, typename T>
            inline void setup_putp5(Parameters& par, par_putp5<T>& proj_parm)
            {
                proj_parm.A = 2.;
                proj_parm.B = 1.;
                
                par.es = 0.;
            }

            // Putnins P5'
            template <typename Parameters, typename T>
            inline void setup_putp5p(Parameters& par, par_putp5<T>& proj_parm)
            {
                proj_parm.A = 1.5;
                proj_parm.B = 0.5;
                
                par.es = 0.;
            }

    }} // namespace detail::putp5
    #endif // doxygen

    /*!
        \brief Putnins P5 projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp5.gif
    */
    template <typename T, typename Parameters>
    struct putp5_spheroid : public detail::putp5::base_putp5_spheroid<T, Parameters>
    {
        template <typename Params>
        inline putp5_spheroid(Params const& , Parameters & par)
        {
            detail::putp5::setup_putp5(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Putnins P5' projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp5p.gif
    */
    template <typename T, typename Parameters>
    struct putp5p_spheroid : public detail::putp5::base_putp5_spheroid<T, Parameters>
    {
        template <typename Params>
        inline putp5p_spheroid(Params const& , Parameters & par)
        {
            detail::putp5::setup_putp5p(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_putp5, putp5_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_putp5p, putp5p_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(putp5_entry, putp5_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(putp5p_entry, putp5p_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(putp5_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(putp5, putp5_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(putp5p, putp5p_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_PUTP5_HPP


/* putp5.hpp
2oepmzLs1Ekq9beces+pnFrd0XslAzG7PBS7RYulDcLvKNbNsSu12Cq6rUSxXo69QYsNIOTpEKtmMAy4ZgQk3xDPCoITITmo7qo3zjM9P2hM/ZQ/g//XtzA/NDrEG2LNJBJrSkMsNcdNrua80M8Kt7aMX1ywdZYPqJSpwspLdTqdN0jEyYRYxvk5bmvz+GrKiMm08P7HubaNeR5f8pnyTiPZMMpB1UfAro+sluoDtysmvZlupPfA83M7kXaTLFsr09ceKD3zzl2Fqi78aPYKh9+MhO1e5kXx4hhS8M3WvmdUYQMNANB9LE2QnyH6TNTWEX932dY6QTYfJL+8w55pfAVEujoZUo7gZGBABiLKMN9yl7vQTDGjcCCvi0TyKoThCNik5KA2qa2eT5NUFSXKT0SNsw02B7WlLBsY26CylVwsgzNlcAiDe3Dw9mzaVsmPABvDtidXGEuYHOtTgTcjCEsDMk1nRKMMYJgYK0ilNSMoS3gcl45r3sDGDSCj0W/k53bj6O2U26V9U139tJf4eRvxyFliFTyBrROMPxGsPuCEEBqd7nAZ5XQWTPtPVILpp5UEb1k6Cab3qdezaRXvtj/XGZ80kJFRgLB9Tx9h/7u6fBPdPRysLC+XB932yzPod5UchZQUMiW35TlQkpKOM+K5XKJiSMEjsiiN1pKnEDRjDZLJa5DXhtKqdiglkPPl8YMR2EUMLE0BO5SBxQUPWhHoe/5ynUQtH59JzYeSRv+MdNLtYVX+WSdgvSzBZfUDbnX/c6DHJY9os1GKyEOFV1d0hFt8CG/lbBPMtHUPjT3Vc7Arbkd6x8XQO5vpffV4pLcT0htQ9J4YS+9kSW+hA72Fit75pxw0vU7vt908KXpSJdmVnFkfG3wAk2MMypzDuhAvQTZQXYUdHUc7Zm5t/mQtv9Ji2drier/+DCrGAZf4brG2Phf6tXiD5ySyQo/L+868uBx0HC3vr98Ny/tuA2h5n87LeykcwhzuWW1j1/0Hb1dbo9+n0Y96g0mo3z/I49KNoZJ4URxYtyV9mtDnp0I2PU8DsrTWSm+M9R5i2NqC/bsCTYrc5TRGnSnNSSqpMdho72PGJHGWnhNI44MqXpiY97PQZSiWQ83ZNdXIVmHjKfmitKP6ChCgT+0Y+j3k0OZ61qkXppkCBGCdKiAVd9AWom1x8nLkD70m2i1dHsAdT+K8XmR5aAN3wVXjvfbWz8LDmT72PgsD5NP++Wg4Lqd2E2e7grLVh87sq8wMlWNq+SIM+sUU9wwzpLHj1cQyUDGkTX1oiruJ6pSeAS8QxBDuxCeBR02p9ulhSIYwg1uN32jkh+lTgWoaCmIPCb2OisUDbBg4Q0YD3Z5NCnRC1+N7WJs5+F9r+8Py6P6wunX9wfEooeNpppAbuT0PmGBoSB/FqbIoIrfGpQma+9N4Ku5ED3XVySc22l75FP2ZHn+wdRc93qdPiH6vcdXAFt8HjQaSwUBoVtFfGh3Ysk1RDUroVI31DB3YuvcmHz81mv4b+xzMe57TY/Ln9zmI9ypHc3Y79zUDDu49T17/nGL0Dx6UiZU7pbIZmMiGTzyo5cPYToYw/42+MYcjXSNsni3dPhQpGS4OJKLTfvStSqt63ZefQhhm3U4G7d3NYD4HMGtzVXooSc5VQDKk7myDpNBIfn5YPufzE50/6O8/n6z1pzx/i+8dF+npP+jRuv436uTo/mP1auX7wI359rJMGc0+mT5BPEoKLiW/ZpjDxtOsOpq/dubR10BKqhk6z5T2wB+ABMwYvMQaDmLijDoenMA08qkgK38eIl5JzA69fRxEqmMaVpUdECf03YUd84pSUB7txpqCF58I6XFWry6vReI=
*/
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

 // Author: Gerald Evenden (1995)
 //         Thomas Knudsen (2016) - revise/add regression tests

// Last updated version of proj: 5.0.0

// Original copyright notice:

// Purpose:  Implementation of the aea (Albers Equal Area) projection.
// Author:   Gerald Evenden
// Copyright (c) 1995, Gerald Evenden

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_AEA_HPP
#define BOOST_GEOMETRY_PROJECTIONS_AEA_HPP

#include <boost/core/ignore_unused.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/math/special_functions/hypot.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_mlfn.hpp>
#include <boost/geometry/srs/projections/impl/pj_msfn.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/pj_qsfn.hpp>


namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace aea
    {

            static const double epsilon10 = 1.e-10;
            static const double tolerance7 = 1.e-7;
            static const double epsilon = 1.0e-7;
            static const double tolerance = 1.0e-10;
            static const int n_iter = 15;

            template <typename T>
            struct par_aea
            {
                T    ec;
                T    n;
                T    c;
                T    dd;
                T    n2;
                T    rho0;
                T    phi1;
                T    phi2;
                detail::en<T> en;
                bool ellips;
            };

            /* determine latitude angle phi-1 */
            template <typename T>
            inline T phi1_(T const& qs, T const& Te, T const& Tone_es)
            {
                int i;
                T Phi, sinpi, cospi, con, com, dphi;

                Phi = asin (.5 * qs);
                if (Te < epsilon)
                    return( Phi );
                i = n_iter;
                do {
                    sinpi = sin (Phi);
                    cospi = cos (Phi);
                    con = Te * sinpi;
                    com = 1. - con * con;
                    dphi = .5 * com * com / cospi * (qs / Tone_es -
                       sinpi / com + .5 / Te * log ((1. - con) /
                       (1. + con)));
                    Phi += dphi;
                } while (fabs(dphi) > tolerance && --i);
                return( i ? Phi : HUGE_VAL );
            }

            template <typename T, typename Parameters>
            struct base_aea_ellipsoid
            {
                par_aea<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid & spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T rho = this->m_proj_parm.c - (this->m_proj_parm.ellips
                                                                    ? this->m_proj_parm.n * pj_qsfn(sin(lp_lat), par.e, par.one_es)
                                                                    : this->m_proj_parm.n2 * sin(lp_lat));
                    if (rho < 0.)
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    rho = this->m_proj_parm.dd * sqrt(rho);
                    xy_x = rho * sin( lp_lon *= this->m_proj_parm.n );
                    xy_y = this->m_proj_parm.rho0 - rho * cos(lp_lon);
                }

                // INVERSE(e_inverse)  ellipsoid & spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T rho = 0.0;
                    if( (rho = boost::math::hypot(xy_x, xy_y = this->m_proj_parm.rho0 - xy_y)) != 0.0 ) {
                        if (this->m_proj_parm.n < 0.) {
                            rho = -rho;
                            xy_x = -xy_x;
                            xy_y = -xy_y;
                        }
                        lp_lat =  rho / this->m_proj_parm.dd;
                        if (this->m_proj_parm.ellips) {
                            lp_lat = (this->m_proj_parm.c - lp_lat * lp_lat) / this->m_proj_parm.n;
                            if (fabs(this->m_proj_parm.ec - fabs(lp_lat)) > tolerance7) {
                                if ((lp_lat = phi1_(lp_lat, par.e, par.one_es)) == HUGE_VAL)
                                    BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                            } else
                                lp_lat = lp_lat < 0. ? -half_pi : half_pi;
                        } else if (fabs(lp_lat = (this->m_proj_parm.c - lp_lat * lp_lat) / this->m_proj_parm.n2) <= 1.)
                            lp_lat = asin(lp_lat);
                        else
                            lp_lat = lp_lat < 0. ? -half_pi : half_pi;
                        lp_lon = atan2(xy_x, xy_y) / this->m_proj_parm.n;
                    } else {
                        lp_lon = 0.;
                        lp_lat = this->m_proj_parm.n > 0. ? half_pi : - half_pi;
                    }
                }

                static inline std::string get_name()
                {
                    return "aea_ellipsoid";
                }

            };

            template <typename Parameters, typename T>
            inline void setup(Parameters const& par, par_aea<T>& proj_parm) 
            {
                T cosphi, sinphi;
                int secant;

                if (fabs(proj_parm.phi1 + proj_parm.phi2) < epsilon10)
                    BOOST_THROW_EXCEPTION( projection_exception(error_conic_lat_equal) );
                proj_parm.n = sinphi = sin(proj_parm.phi1);
                cosphi = cos(proj_parm.phi1);
                secant = fabs(proj_parm.phi1 - proj_parm.phi2) >= epsilon10;
                if( (proj_parm.ellips = (par.es > 0.))) {
                    T ml1, m1;

                    proj_parm.en = pj_enfn<T>(par.es);
                    m1 = pj_msfn(sinphi, cosphi, par.es);
                    ml1 = pj_qsfn(sinphi, par.e, par.one_es);
                    if (secant) { /* secant cone */
                        T ml2, m2;

                        sinphi = sin(proj_parm.phi2);
                        cosphi = cos(proj_parm.phi2);
                        m2 = pj_msfn(sinphi, cosphi, par.es);
                        ml2 = pj_qsfn(sinphi, par.e, par.one_es);
                        if (ml2 == ml1)
                            BOOST_THROW_EXCEPTION( projection_exception(0) );

                        proj_parm.n = (m1 * m1 - m2 * m2) / (ml2 - ml1);
                    }
                    proj_parm.ec = 1. - .5 * par.one_es * log((1. - par.e) /
                        (1. + par.e)) / par.e;
                    proj_parm.c = m1 * m1 + proj_parm.n * ml1;
                    proj_parm.dd = 1. / proj_parm.n;
                    proj_parm.rho0 = proj_parm.dd * sqrt(proj_parm.c - proj_parm.n * pj_qsfn(sin(par.phi0),
                        par.e, par.one_es));
                } else {
                    if (secant) proj_parm.n = .5 * (proj_parm.n + sin(proj_parm.phi2));
                    proj_parm.n2 = proj_parm.n + proj_parm.n;
                    proj_parm.c = cosphi * cosphi + proj_parm.n2 * sinphi;
                    proj_parm.dd = 1. / proj_parm.n;
                    proj_parm.rho0 = proj_parm.dd * sqrt(proj_parm.c - proj_parm.n2 * sin(par.phi0));
                }
            }


            // Albers Equal Area
            template <typename Params, typename Parameters, typename T>
            inline void setup_aea(Params const& params, Parameters const& par, par_aea<T>& proj_parm)
            {
                proj_parm.phi1 = 0.0;
                proj_parm.phi2 = 0.0;
                bool is_phi1_set = pj_param_r<srs::spar::lat_1>(params, "lat_1", srs::dpar::lat_1, proj_parm.phi1);
                bool is_phi2_set = pj_param_r<srs::spar::lat_2>(params, "lat_2", srs::dpar::lat_2, proj_parm.phi2);

                // Boost.Geometry specific, set default parameters manually
                if (! is_phi1_set || ! is_phi2_set) {
                    bool const use_defaults = ! pj_get_param_b<srs::spar::no_defs>(params, "no_defs", srs::dpar::no_defs);
                    if (use_defaults) {
                        if (!is_phi1_set)
                            proj_parm.phi1 = 29.5;
                        if (!is_phi2_set)
                            proj_parm.phi2 = 45.5;
                    }
                }

                setup(par, proj_parm);
            }

            // Lambert Equal Area Conic
            template <typename Params, typename Parameters, typename T>
            inline void setup_leac(Params const& params, Parameters const& par, par_aea<T>& proj_parm)
            {
                static const T half_pi = detail::half_pi<T>();

                proj_parm.phi2 = pj_get_param_r<T, srs::spar::lat_1>(params, "lat_1", srs::dpar::lat_1);
                proj_parm.phi1 = pj_get_param_b<srs::spar::south>(params, "south", srs::dpar::south) ? -half_pi : half_pi;
                setup(par, proj_parm);
            }

    }} // namespace detail::aea
    #endif // doxygen

    /*!
        \brief Albers Equal Area projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel (degrees)
         - lat_2: Latitude of second standard parallel (degrees)
        \par Example
        \image html ex_aea.gif
    */
    template <typename T, typename Parameters>
    struct aea_ellipsoid : public detail::aea::base_aea_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline aea_ellipsoid(Params const& params, Parameters const& par)
        {
            detail::aea::setup_aea(params, par, this->m_proj_parm);
        }
    };

    /*!
        \brief Lambert Equal Area Conic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel (degrees)
         - south: Denotes southern hemisphere UTM zone (boolean)
        \par Example
        \image html ex_leac.gif
    */
    template <typename T, typename Parameters>
    struct leac_ellipsoid : public detail::aea::base_aea_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline leac_ellipsoid(Params const& params, Parameters const& par)
        {
            detail::aea::setup_leac(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_aea, aea_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_leac, leac_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(aea_entry, aea_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(leac_entry, leac_ellipsoid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(aea_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(aea, aea_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(leac, leac_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_AEA_HPP


/* aea.hpp
41zQwtrjPw1qJYdaCc3XYWv6wgez8FHho3vQL/v9CL0Pg6ZL0GUN0A+7tA354/no5jeHYwug3Z0noSf5feggZP9i/KN8iHorNr6J3Cf5+nklxG3I4Eu7YHPwE1v4/bIfyVnsRg5gAblK9gczdsJfxnc6eBYyNJEzQurs0060XYRvMtXT9vm93fGjwbvpNGQE23HJ3Az4B/mivdn440rO5/2ILYSXH2Nf9vF50KEDP3pHdBU26e0Z0KGTHPZEdIW6xzYIu46sdK0lt34ovlgnOYCnPe6AIUfkZf4Gb/VX9wNYv6fJff1UR94sB5s6LYN8CnuO04lfatABWfgi0+G3R7I4cwNvIwfNN5IfepwYmNg4shU42OrLx8FX5PqOOBzeps+hrFsne1mH/hM6YJOyoviCk6A1tuWBYz3uUDDPBew5opcHq3xHMfZtFby1XOV1GDP/wvDNK0uhJzKwxQ34Gqx/y4vQiT4ODuO/PJ+FLwFP7s18j6Cfs7ljQN7tQM769sGneeYKZH42Nu82fIH9ybPCB1e8ylrcgLz+Cjv2Pfb9mwzONUOP8eyzR+Dlt8lVbokv1UR+fgx+JXHbGfjVf57Bvwfgu2HoZ3gw1IYNJ6dQsCt66y184lnkDtrY538FHYasV7DGi+mvhLXY4WWP+9Gs2WLodCS+BH7mS7T5RhH9PoF9XUccy3pO3YXc5KXYxM8YVw48nYutYxy/xdZMQLefeAzxCTT7vJbz9tzJyNwO3bstfSHXT65gzNDyGGDPYBsWzyKPiMwPxpY+dz/2jzV9inzhyD2I3wawH8dabatk9Et8ZeLmCHTd8gTymPDSfr9B1q6Gn94mn0tOd+cP0TnQ6sVf4+t9wVyIG0+mjS+/5v7wzeinjehpDx+hEprAL98dgz3Df1jNPtE8ZGUjNLuQtXp5a/yABcgA8e2lS8iXfwQ9nscufYhuQs83Hs4YH0RHHIfNX05O69YM9rHpA390zd7EVTFEbyC5Azp77yDydsSWc+HTpy9F/7Gmn40l50M/p6JjnqGtUeSgz5kO7CzmeKI6f4SvQX6wCFk5n7g4FsPnxK8sySV2I+/w3S3IKHH0NW9xFmsv9Oov6PvR2O6V8Cd9fM98brqItUavrB1JOWvQWYXuRK9t9Vhexgz/oTGvnnG0Y9OWeb/8govGzyx+ElMV+P9O5PcR8Aho3hH2razK6MqGmH6XlyeF9DvbqjwjWV4e7TAg+16WhZW1hXklh/ecVXlWstw8ZuS3lSXx+bCH+rZmqddff+Oxw4xdPapVFSrgVdJFPBgTqqwqqS4pLyoxz2IFA9Ubb3+286ipDBXxAFchj3eBUVZRpVDnlM2e4+n5BMPLK6oWFMy38wrEmV+x2MwjGF5WvqhgfllxjzhFFQvLa/S782LemWreQehm1kEg5qzf7Wv3ku/29cnu6b3o2kg0FPef9vR/tW+J9jP1BnsZ+tvr/fm7L/86PPkeJ/l7yhT+FgH47f26429l8AdqfPNOqm1f4mI3De62Bnc4uH0MLjj0RYv95DtyfbxBps7gbPkmKXVS2kYvGbxhBm8MeP1E231FH/wT793187YzdUfIOYu6I7PlmDhLYPBHZae+wQ2u+aakfkOKPvX38+x36Lbk72yvdiWPRtl3sbambIRXG+Mpd0/9nc3fY71aXuOMewn4rl5tU4P5ewh/53p1HbEWv83h/D3Dq6O+btOWzfLqG/h0bXS155dtT9kcj2fQWmp59jukG5gOD23pkbbNTnJQpeYhXlpsjtZbVpIlcNRdRg7JjFQUhioK5/JiVai8pCbEk8UlsH95TVXF/FBJeUHh/BL7nm+PuAsKloQKC8qLF5cV1/gy3Kc=
*/
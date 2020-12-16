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

// Copyright (c) 2003   Gerald I. Evenden

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_STEREA_HPP
#define BOOST_GEOMETRY_PROJECTIONS_STEREA_HPP

#include <boost/math/special_functions/hypot.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_gauss.hpp>


namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace sterea
    {

            template <typename T>
            struct par_sterea
            {
                T phic0;
                T cosc0, sinc0;
                T R2;
                gauss<T> en;
            };

            template <typename T, typename Parameters>
            struct base_sterea_ellipsoid
            {
                par_sterea<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    T cosc, sinc, cosl_, k;

                    detail::gauss_fwd(m_proj_parm.en, lp_lon, lp_lat);
                    sinc = sin(lp_lat);
                    cosc = cos(lp_lat);
                    cosl_ = cos(lp_lon);
                    k = par.k0 * this->m_proj_parm.R2 / (1. + this->m_proj_parm.sinc0 * sinc + this->m_proj_parm.cosc0 * cosc * cosl_);
                    xy_x = k * cosc * sin(lp_lon);
                    xy_y = k * (this->m_proj_parm.cosc0 * sinc - this->m_proj_parm.sinc0 * cosc * cosl_);
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    T rho, c, sinc, cosc;

                    xy_x /= par.k0;
                    xy_y /= par.k0;
                    if((rho = boost::math::hypot(xy_x, xy_y)) != 0.0) {
                        c = 2. * atan2(rho, this->m_proj_parm.R2);
                        sinc = sin(c);
                        cosc = cos(c);
                        lp_lat = asin(cosc * this->m_proj_parm.sinc0 + xy_y * sinc * this->m_proj_parm.cosc0 / rho);
                        lp_lon = atan2(xy_x * sinc, rho * this->m_proj_parm.cosc0 * cosc -
                                        xy_y * this->m_proj_parm.sinc0 * sinc);
                    } else {
                        lp_lat = this->m_proj_parm.phic0;
                        lp_lon = 0.;
                    }
                    detail::gauss_inv(m_proj_parm.en, lp_lon, lp_lat);
                }

                static inline std::string get_name()
                {
                    return "sterea_ellipsoid";
                }

            };

            // Oblique Stereographic Alternative
            template <typename Parameters, typename T>
            inline void setup_sterea(Parameters const& par, par_sterea<T>& proj_parm)
            {
                T R;

                proj_parm.en = detail::gauss_ini(par.e, par.phi0, proj_parm.phic0, R);
                proj_parm.sinc0 = sin(proj_parm.phic0);
                proj_parm.cosc0 = cos(proj_parm.phic0);
                proj_parm.R2 = 2. * R;
            }

    }} // namespace detail::sterea
    #endif // doxygen

    /*!
        \brief Oblique Stereographic Alternative projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Spheroid
         - Ellipsoid
        \par Example
        \image html ex_sterea.gif
    */
    template <typename T, typename Parameters>
    struct sterea_ellipsoid : public detail::sterea::base_sterea_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline sterea_ellipsoid(Params const& , Parameters const& par)
        {
            detail::sterea::setup_sterea(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_sterea, sterea_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(sterea_entry, sterea_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(sterea_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(sterea, sterea_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_STEREA_HPP


/* sterea.hpp
vVAN3yPmwvC9mi4eoqxOrWoKo3hG5sYkCZcZRiy6OIFuN6O72gld/Q2Arq19gwtvl0WKk6MtRWxc22T0J6m6RhLZDXv5rCYVEIC4fLnFUzIKZp+F0qh8plZR8+BCDO6FJwncWgZHct5pseAw3KXoDK7/GevstjzeS0mJe0OTYS+Tq0IuWihMqd4ups+WtW9RjEzat2QGU9MnGM1/WZ4YKpxj2n2m+Xcs794OWa82rVNU97q4Eudfy7D6WCqpbJbxBFRqtX1Uj11GFRvHYRHaMvVQWNUuxPpYhaYSyYuE8UxkyRM0Bkwin4PkDacYRMYqOU/kNxlZmZnMoK+zVWhOYOjdnKBPQei4vVCHqlLDd7TFulrqLbBg6FioL1xj14i74NlinVLE0Y0AC2iZJgllKVtJlvxWQoU6n9YVIAhfyMutyfFu7AlBDCsIqJCTKbLEoTfxmx2cZhKsJWQZz+QyjlpH8kazjNdfD2VMUldV06qp/nPhCCp3CBBYnIy+N9DXFn1/QKK7yeVfAEWruTWgyx26DTJi8OaQw/o4wOvjTHN9LGPM2kX2hUuv+bk+Cy888O6yjJ5ufILazQqf79DczPcSNeulzFzpYsLlXAMjHndo5bJy4KOduNbGX6+0jDjgsOtRdPMztxj6w36aADH1CVuACLs95DrKIEKdNWonyQS++mfNFvIMqaelM4vFdXlLuty6ecnoYuJ6UJCuSnYjGAqAXhUHvUrkW1Bv4c4TlFwZTxzEyGz9OVt/+IasbPCxbRvukelCLTZ9m+to+iu2IunCiGx/7GGbQ0mx3TUdOqWZyGf2XKdERgpLpiDEqNQRjbkN2xsvr1I2NcrmIaP+AQ+Hfc9flJLk6Me5jU2dSF5fFHkS59RrCwCemmpL3SRIvsmMUUsD9COCIB7Iy3ASfEUWYFalkXhdV8oOFj+8AIqt0XwMCXhbNzBKllgY+tsD0ghWu0dx8dCwGRJLEG6V7KGX6Wq8sG98N2sOFHlFkbzwdA9dLMfONl+pWbphBdYcYV6Ec1oULrZRL7WC5QlRpqa5ecGDtLeHO+9q2Vm5hjiaT8leRzGYodo87n+amVfxo8i8LsEqKFLMa+tMedrx2ixL6rmBj8gu7spYHnwpYmChyMQ5N8r2EnPRaPqIfiMAcA5CnHZ9Fq2Cm74WPzpzXGwei7U2+K7EWipfv5im6w8w2Jf/MImBExii9fNbAkZfLfrsdzSAVF8qCN3xAHXAeOwS7mLDZt2GeGrbJQ9j2x6HymeXqLb98BqYmnvCJ4LKZFCRNWwKj79efzQSITHFkZtNsM8y2JyH2dqcAXYBgt0mnkzKqd0STycgXSEp6Cu+AZFCMaK8CFpEXj1Dv4st2km9uecZx+6HaPFo4hgKYMIXIgLBx/Nh7CMMpnvp/bEG8l5kcDc95EDy7qsBHF9xY8t40yzkDw6W8fJDL66QBwxfwuD6D1yA4P5gL/rfe4T6g6PGVDYrVXYIQkOGRm1l8RrzELFED7WharnqQVXLF6tq2VYKLbk/jjsIjF7x/tYQqt3inlgxwhBygYq8nKs+J6d2pByRan11832869zHOD2Ec5mJ8xTEWQU4zYU+JPyMH/1/ZY19xnbzVZaZjvZ9GOUSG9aExBs2cFccnVP7FUOoWUNdMQiYjF2ROoUzQaqDOK6wr5n48WscKuxWoKfhJS/ji4JNHZVqqppof2+FpZKZJOAf7LkJEKoYN61vSZaaibnGwN/pgzFM5ec9MkouaT+Skwg64VWVnQKoQ7blAPuXxMpqwQMCqhWX2E0ciGnimhXNN/HDy7mJfTza/KsdmviKGVBL93ucCsfzYfz0o6L2csSEtlfW7xBzhkP09so=
*/
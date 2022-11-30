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

// This implements the Quadrilateralized Spherical Cube (QSC) projection.
// Copyright (c) 2011, 2012  Martin Lambers <marlam@marlam.de>

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

// The QSC projection was introduced in:
// [OL76]
// E.M. O'Neill and R.E. Laubscher, "Extended Studies of a Quadrilateralized
// Spherical Cube Earth Data Base", Naval Environmental Prediction Research
// Facility Tech. Report NEPRF 3-76 (CSC), May 1976.

// The preceding shift from an ellipsoid to a sphere, which allows to apply
// this projection to ellipsoids as used in the Ellipsoidal Cube Map model,
// is described in
// [LK12]
// M. Lambers and A. Kolb, "Ellipsoidal Cube Maps for Accurate Rendering of
// Planetary-Scale Terrain Data", Proc. Pacfic Graphics (Short Papers), Sep.
// 2012

// You have to choose one of the following projection centers,
// corresponding to the centers of the six cube faces:
// phi0 = 0.0, lam0 = 0.0       ("front" face)
// phi0 = 0.0, lam0 = 90.0      ("right" face)
// phi0 = 0.0, lam0 = 180.0     ("back" face)
// phi0 = 0.0, lam0 = -90.0     ("left" face)
// phi0 = 90.0                  ("top" face)
// phi0 = -90.0                 ("bottom" face)
// Other projection centers will not work!

// In the projection code below, each cube face is handled differently.
// See the computation of the face parameter in the ENTRY0(qsc) function
// and the handling of different face values (FACE_*) in the forward and
// inverse projections.

// Furthermore, the projection is originally only defined for theta angles
// between (-1/4 * PI) and (+1/4 * PI) on the current cube face. This area
// of definition is named AREA_0 in the projection code below. The other
// three areas of a cube face are handled by rotation of AREA_0.

#ifndef BOOST_GEOMETRY_PROJECTIONS_QSC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_QSC_HPP

#include <boost/core/ignore_unused.hpp>
#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace qsc
    {

            /* The six cube faces. */
            enum face_type {
                face_front  = 0,
                face_right  = 1,
                face_back   = 2,
                face_left   = 3,
                face_top    = 4,
                face_bottom = 5
            };

            template <typename T>
            struct par_qsc
            {
                T a_squared;
                T b;
                T one_minus_f;
                T one_minus_f_squared;
                face_type face;
            };

            static const double epsilon10 = 1.e-10;

            /* The four areas on a cube face. AREA_0 is the area of definition,
             * the other three areas are counted counterclockwise. */
            enum area_type {
                area_0 = 0,
                area_1 = 1,
                area_2 = 2,
                area_3 = 3
            };

            /* Helper function for forward projection: compute the theta angle
             * and determine the area number. */
            template <typename T>
            inline T qsc_fwd_equat_face_theta(T const& phi, T const& y, T const& x, area_type *area)
            {
                static const T fourth_pi = detail::fourth_pi<T>();
                static const T half_pi = detail::half_pi<T>();
                static const T pi = detail::pi<T>();

                T theta;
                if (phi < epsilon10) {
                    *area = area_0;
                    theta = 0.0;
                } else {
                    theta = atan2(y, x);
                    if (fabs(theta) <= fourth_pi) {
                        *area = area_0;
                    } else if (theta > fourth_pi && theta <= half_pi + fourth_pi) {
                        *area = area_1;
                        theta -= half_pi;
                    } else if (theta > half_pi + fourth_pi || theta <= -(half_pi + fourth_pi)) {
                        *area = area_2;
                        theta = (theta >= 0.0 ? theta - pi : theta + pi);
                    } else {
                        *area = area_3;
                        theta += half_pi;
                    }
                }
                return theta;
            }

            /* Helper function: shift the longitude. */
            template <typename T>
            inline T qsc_shift_lon_origin(T const& lon, T const& offset)
            {
                static const T pi = detail::pi<T>();
                static const T two_pi = detail::two_pi<T>();

                T slon = lon + offset;
                if (slon < -pi) {
                    slon += two_pi;
                } else if (slon > +pi) {
                    slon -= two_pi;
                }
                return slon;
            }

            /* Forward projection, ellipsoid */

            template <typename T, typename Parameters>
            struct base_qsc_ellipsoid
            {
                par_qsc<T> m_proj_parm;

                // FORWARD(e_forward)
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();
                    static const T half_pi = detail::half_pi<T>();
                    static const T pi = detail::pi<T>();

                        T lat, lon;
                        T theta, phi;
                        T t, mu; /* nu; */ 
                        area_type area;

                        /* Convert the geodetic latitude to a geocentric latitude.
                         * This corresponds to the shift from the ellipsoid to the sphere
                         * described in [LK12]. */
                        if (par.es != 0.0) {
                            lat = atan(this->m_proj_parm.one_minus_f_squared * tan(lp_lat));
                        } else {
                            lat = lp_lat;
                        }

                        /* Convert the input lat, lon into theta, phi as used by QSC.
                         * This depends on the cube face and the area on it.
                         * For the top and bottom face, we can compute theta and phi
                         * directly from phi, lam. For the other faces, we must use
                         * unit sphere cartesian coordinates as an intermediate step. */
                        lon = lp_lon;
                        if (this->m_proj_parm.face == face_top) {
                            phi = half_pi - lat;
                            if (lon >= fourth_pi && lon <= half_pi + fourth_pi) {
                                area = area_0;
                                theta = lon - half_pi;
                            } else if (lon > half_pi + fourth_pi || lon <= -(half_pi + fourth_pi)) {
                                area = area_1;
                                theta = (lon > 0.0 ? lon - pi : lon + pi);
                            } else if (lon > -(half_pi + fourth_pi) && lon <= -fourth_pi) {
                                area = area_2;
                                theta = lon + half_pi;
                            } else {
                                area = area_3;
                                theta = lon;
                            }
                        } else if (this->m_proj_parm.face == face_bottom) {
                            phi = half_pi + lat;
                            if (lon >= fourth_pi && lon <= half_pi + fourth_pi) {
                                area = area_0;
                                theta = -lon + half_pi;
                            } else if (lon < fourth_pi && lon >= -fourth_pi) {
                                area = area_1;
                                theta = -lon;
                            } else if (lon < -fourth_pi && lon >= -(half_pi + fourth_pi)) {
                                area = area_2;
                                theta = -lon - half_pi;
                            } else {
                                area = area_3;
                                theta = (lon > 0.0 ? -lon + pi : -lon - pi);
                            }
                        } else {
                            T q, r, s;
                            T sinlat, coslat;
                            T sinlon, coslon;

                            if (this->m_proj_parm.face == face_right) {
                                lon = qsc_shift_lon_origin(lon, +half_pi);
                            } else if (this->m_proj_parm.face == face_back) {
                                lon = qsc_shift_lon_origin(lon, +pi);
                            } else if (this->m_proj_parm.face == face_left) {
                                lon = qsc_shift_lon_origin(lon, -half_pi);
                            }
                            sinlat = sin(lat);
                            coslat = cos(lat);
                            sinlon = sin(lon);
                            coslon = cos(lon);
                            q = coslat * coslon;
                            r = coslat * sinlon;
                            s = sinlat;

                            if (this->m_proj_parm.face == face_front) {
                                phi = acos(q);
                                theta = qsc_fwd_equat_face_theta(phi, s, r, &area);
                            } else if (this->m_proj_parm.face == face_right) {
                                phi = acos(r);
                                theta = qsc_fwd_equat_face_theta(phi, s, -q, &area);
                            } else if (this->m_proj_parm.face == face_back) {
                                phi = acos(-q);
                                theta = qsc_fwd_equat_face_theta(phi, s, -r, &area);
                            } else if (this->m_proj_parm.face == face_left) {
                                phi = acos(-r);
                                theta = qsc_fwd_equat_face_theta(phi, s, q, &area);
                            } else {
                                /* Impossible */
                                phi = theta = 0.0;
                                area = area_0;
                            }
                        }

                        /* Compute mu and nu for the area of definition.
                         * For mu, see Eq. (3-21) in [OL76], but note the typos:
                         * compare with Eq. (3-14). For nu, see Eq. (3-38). */
                        mu = atan((12.0 / pi) * (theta + acos(sin(theta) * cos(fourth_pi)) - half_pi));
                        // TODO: (cos(mu) * cos(mu)) could be replaced with sqr(cos(mu))
                        t = sqrt((1.0 - cos(phi)) / (cos(mu) * cos(mu)) / (1.0 - cos(atan(1.0 / cos(theta)))));
                        /* nu = atan(t);        We don't really need nu, just t, see below. */

                        /* Apply the result to the real area. */
                        if (area == area_1) {
                            mu += half_pi;
                        } else if (area == area_2) {
                            mu += pi;
                        } else if (area == area_3) {
                            mu += half_pi + pi;
                        }

                        /* Now compute x, y from mu and nu */
                        /* t = tan(nu); */
                        xy_x = t * cos(mu);
                        xy_y = t * sin(mu);
                }
                /* Inverse projection, ellipsoid */

                // INVERSE(e_inverse)
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T pi = detail::pi<T>();

                        T mu, nu, cosmu, tannu;
                        T tantheta, theta, cosphi, phi;
                        T t;
                        int area;

                        /* Convert the input x, y to the mu and nu angles as used by QSC.
                         * This depends on the area of the cube face. */
                        nu = atan(sqrt(xy_x * xy_x + xy_y * xy_y));
                        mu = atan2(xy_y, xy_x);
                        if (xy_x >= 0.0 && xy_x >= fabs(xy_y)) {
                            area = area_0;
                        } else if (xy_y >= 0.0 && xy_y >= fabs(xy_x)) {
                            area = area_1;
                            mu -= half_pi;
                        } else if (xy_x < 0.0 && -xy_x >= fabs(xy_y)) {
                            area = area_2;
                            mu = (mu < 0.0 ? mu + pi : mu - pi);
                        } else {
                            area = area_3;
                            mu += half_pi;
                        }

                        /* Compute phi and theta for the area of definition.
                         * The inverse projection is not described in the original paper, but some
                         * good hints can be found here (as of 2011-12-14):
                         * http://fits.gsfc.nasa.gov/fitsbits/saf.93/saf.9302
                         * (search for "Message-Id: <9302181759.AA25477 at fits.cv.nrao.edu>") */
                        t = (pi / 12.0) * tan(mu);
                        tantheta = sin(t) / (cos(t) - (1.0 / sqrt(2.0)));
                        theta = atan(tantheta);
                        cosmu = cos(mu);
                        tannu = tan(nu);
                        cosphi = 1.0 - cosmu * cosmu * tannu * tannu * (1.0 - cos(atan(1.0 / cos(theta))));
                        if (cosphi < -1.0) {
                            cosphi = -1.0;
                        } else if (cosphi > +1.0) {
                            cosphi = +1.0;
                        }

                        /* Apply the result to the real area on the cube face.
                         * For the top and bottom face, we can compute phi and lam directly.
                         * For the other faces, we must use unit sphere cartesian coordinates
                         * as an intermediate step. */
                        if (this->m_proj_parm.face == face_top) {
                            phi = acos(cosphi);
                            lp_lat = half_pi - phi;
                            if (area == area_0) {
                                lp_lon = theta + half_pi;
                            } else if (area == area_1) {
                                lp_lon = (theta < 0.0 ? theta + pi : theta - pi);
                            } else if (area == area_2) {
                                lp_lon = theta - half_pi;
                            } else /* area == AREA_3 */ {
                                lp_lon = theta;
                            }
                        } else if (this->m_proj_parm.face == face_bottom) {
                            phi = acos(cosphi);
                            lp_lat = phi - half_pi;
                            if (area == area_0) {
                                lp_lon = -theta + half_pi;
                            } else if (area == area_1) {
                                lp_lon = -theta;
                            } else if (area == area_2) {
                                lp_lon = -theta - half_pi;
                            } else /* area == area_3 */ {
                                lp_lon = (theta < 0.0 ? -theta - pi : -theta + pi);
                            }
                        } else {
                            /* Compute phi and lam via cartesian unit sphere coordinates. */
                            T q, r, s;
                            q = cosphi;
                            t = q * q;
                            if (t >= 1.0) {
                                s = 0.0;
                            } else {
                                s = sqrt(1.0 - t) * sin(theta);
                            }
                            t += s * s;
                            if (t >= 1.0) {
                                r = 0.0;
                            } else {
                                r = sqrt(1.0 - t);
                            }
                            /* Rotate q,r,s into the correct area. */
                            if (area == area_1) {
                                t = r;
                                r = -s;
                                s = t;
                            } else if (area == area_2) {
                                r = -r;
                                s = -s;
                            } else if (area == area_3) {
                                t = r;
                                r = s;
                                s = -t;
                            }
                            /* Rotate q,r,s into the correct cube face. */
                            if (this->m_proj_parm.face == face_right) {
                                t = q;
                                q = -r;
                                r = t;
                            } else if (this->m_proj_parm.face == face_back) {
                                q = -q;
                                r = -r;
                            } else if (this->m_proj_parm.face == face_left) {
                                t = q;
                                q = r;
                                r = -t;
                            }
                            /* Now compute phi and lam from the unit sphere coordinates. */
                            lp_lat = acos(-s) - half_pi;
                            lp_lon = atan2(r, q);
                            if (this->m_proj_parm.face == face_right) {
                                lp_lon = qsc_shift_lon_origin(lp_lon, -half_pi);
                            } else if (this->m_proj_parm.face == face_back) {
                                lp_lon = qsc_shift_lon_origin(lp_lon, -pi);
                            } else if (this->m_proj_parm.face == face_left) {
                                lp_lon = qsc_shift_lon_origin(lp_lon, +half_pi);
                            }
                        }

                        /* Apply the shift from the sphere to the ellipsoid as described
                         * in [LK12]. */
                        if (par.es != 0.0) {
                            int invert_sign;
                            T tanphi, xa;
                            invert_sign = (lp_lat < 0.0 ? 1 : 0);
                            tanphi = tan(lp_lat);
                            xa = this->m_proj_parm.b / sqrt(tanphi * tanphi + this->m_proj_parm.one_minus_f_squared);
                            lp_lat = atan(sqrt(par.a * par.a - xa * xa) / (this->m_proj_parm.one_minus_f * xa));
                            if (invert_sign) {
                                lp_lat = -lp_lat;
                            }
                        }
                }

                static inline std::string get_name()
                {
                    return "qsc_ellipsoid";
                }

            };

            // Quadrilateralized Spherical Cube
            template <typename Parameters, typename T>
            inline void setup_qsc(Parameters const& par, par_qsc<T>& proj_parm)
            {
                static const T fourth_pi = detail::fourth_pi<T>();
                static const T half_pi = detail::half_pi<T>();

                /* Determine the cube face from the center of projection. */
                if (par.phi0 >= half_pi - fourth_pi / 2.0) {
                    proj_parm.face = face_top;
                } else if (par.phi0 <= -(half_pi - fourth_pi / 2.0)) {
                    proj_parm.face = face_bottom;
                } else if (fabs(par.lam0) <= fourth_pi) {
                    proj_parm.face = face_front;
                } else if (fabs(par.lam0) <= half_pi + fourth_pi) {
                    proj_parm.face = (par.lam0 > 0.0 ? face_right : face_left);
                } else {
                    proj_parm.face = face_back;
                }
                /* Fill in useful values for the ellipsoid <-> sphere shift
                 * described in [LK12]. */
                if (par.es != 0.0) {
                    proj_parm.a_squared = par.a * par.a;
                    proj_parm.b = par.a * sqrt(1.0 - par.es);
                    proj_parm.one_minus_f = 1.0 - (par.a - proj_parm.b) / par.a;
                    proj_parm.one_minus_f_squared = proj_parm.one_minus_f * proj_parm.one_minus_f;
                }
            }

    }} // namespace detail::qsc
    #endif // doxygen

    /*!
        \brief Quadrilateralized Spherical Cube projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Spheroid
        \par Example
        \image html ex_qsc.gif
    */
    template <typename T, typename Parameters>
    struct qsc_ellipsoid : public detail::qsc::base_qsc_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline qsc_ellipsoid(Params const& , Parameters const& par)
        {
            detail::qsc::setup_qsc(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_qsc, qsc_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(qsc_entry, qsc_ellipsoid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(qsc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(qsc, qsc_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_QSC_HPP


/* qsc.hpp
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
*/
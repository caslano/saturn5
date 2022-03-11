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
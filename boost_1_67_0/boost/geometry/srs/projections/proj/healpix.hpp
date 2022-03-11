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

// Purpose: Implementation of the HEALPix and rHEALPix projections.
//          For background see <http://code.scenzgrid.org/index.php/p/scenzgrid-py/source/tree/master/docs/rhealpix_dggs.pdf>.
// Authors: Alex Raichev (raichev@cs.auckland.ac.nz)
//          Michael Speth (spethm@landcareresearch.co.nz)
// Notes:   Raichev implemented these projections in Python and
//          Speth translated them into C here.

// Copyright (c) 2001, Thomas Flemming, tf@ttqv.com

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_HEALPIX_HPP
#define BOOST_GEOMETRY_PROJECTIONS_HEALPIX_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_auth.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/pj_qsfn.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace healpix
    {

            /* Fuzz to handle rounding errors: */
            static const double epsilon = 1e-15;

            template <typename T>
            struct par_healpix
            {
                T qp;
                detail::apa<T> apa;
                int north_square;
                int south_square;
            };

            template <typename T>
            struct cap_map
            {
                T x, y; /* Coordinates of the pole point (point of most extreme latitude on the polar caps). */
                int cn; /* An integer 0--3 indicating the position of the polar cap. */
                enum region_type {north, south, equatorial} region;
            };
            template <typename T>
            struct point_xy
            {
                T x, y;
            };

            /* IDENT, R1, R2, R3, R1 inverse, R2 inverse, R3 inverse:*/
            static double rot[7][2][2] = {
                /* Identity matrix */
                {{1, 0},{0, 1}},
                /* Matrix for counterclockwise rotation by pi/2: */
                {{ 0,-1},{ 1, 0}},
                /* Matrix for counterclockwise rotation by pi: */
                {{-1, 0},{ 0,-1}},
                /* Matrix for counterclockwise rotation by 3*pi/2:  */
                {{ 0, 1},{-1, 0}},
                {{ 0, 1},{-1, 0}}, // 3*pi/2
                {{-1, 0},{ 0,-1}}, // pi
                {{ 0,-1},{ 1, 0}}  // pi/2
            };

            /**
             * Returns the sign of the double.
             * @param v the parameter whose sign is returned.
             * @return 1 for positive number, -1 for negative, and 0 for zero.
             **/
            template <typename T>
            inline T pj_sign (T const& v)
            {
                return v > 0 ? 1 : (v < 0 ? -1 : 0);
            }
            /**
             * Return the index of the matrix in {{{1, 0},{0, 1}}, {{ 0,-1},{ 1, 0}}, {{-1, 0},{ 0,-1}}, {{ 0, 1},{-1, 0}}, {{ 0, 1},{-1, 0}}, {{-1, 0},{ 0,-1}}, {{ 0,-1},{ 1, 0}}}.
             * @param index ranges from -3 to 3.
             */
            inline int get_rotate_index(int index)
            {
                switch(index) {
                case 0:
                    return 0;
                case 1:
                    return 1;
                case 2:
                    return 2;
                case 3:
                    return 3;
                case -1:
                    return 4;
                case -2:
                    return 5;
                case -3:
                    return 6;
                }
                return 0;
            }
            /**
             * Return 1 if point (testx, testy) lies in the interior of the polygon
             * determined by the vertices in vert, and return 0 otherwise.
             * See http://paulbourke.net/geometry/polygonmesh/ for more details.
             * @param nvert the number of vertices in the polygon.
             * @param vert the (x, y)-coordinates of the polygon's vertices
             **/
            template <typename T>
            inline int pnpoly(int nvert, T vert[][2], T const& testx, T const& testy)
            {
                int i;
                int counter = 0;
                T xinters;
                point_xy<T> p1, p2;

                /* Check for boundrary cases */
                for (i = 0; i < nvert; i++) {
                    if (testx == vert[i][0] && testy == vert[i][1]) {
                        return 1;
                    }
                }

                p1.x = vert[0][0];
                p1.y = vert[0][1];

                for (i = 1; i < nvert; i++) {
                    p2.x = vert[i % nvert][0];
                    p2.y = vert[i % nvert][1];
                    if (testy > (std::min)(p1.y, p2.y)  &&
                        testy <= (std::max)(p1.y, p2.y) &&
                        testx <= (std::max)(p1.x, p2.x) &&
                        p1.y != p2.y)
                    {
                        xinters = (testy-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
                        if (p1.x == p2.x || testx <= xinters)
                            counter++;
                    }
                    p1 = p2;
                }

                if (counter % 2 == 0) {
                    return 0;
                } else {
                    return 1;
                }
            }
            /**
             * Return 1 if (x, y) lies in (the interior or boundary of) the image of the
             * HEALPix projection (in case proj=0) or in the image the rHEALPix projection
             * (in case proj=1), and return 0 otherwise.
             * @param north_square the position of the north polar square (rHEALPix only)
             * @param south_square the position of the south polar square (rHEALPix only)
             **/
            template <typename T>
            inline int in_image(T const& x, T const& y, int proj, int north_square, int south_square)
            {
                static const T pi = detail::pi<T>();
                static const T half_pi = detail::half_pi<T>();
                static const T fourth_pi = detail::fourth_pi<T>();

                if (proj == 0) {
                    T healpixVertsJit[][2] = {
                        {-pi - epsilon,   fourth_pi},
                        {-3.0*fourth_pi,  half_pi + epsilon},
                        {-half_pi,        fourth_pi + epsilon},
                        {-fourth_pi,      half_pi + epsilon},
                        {0.0,             fourth_pi + epsilon},
                        {fourth_pi,       half_pi + epsilon},
                        {half_pi,         fourth_pi + epsilon},
                        {3.0*fourth_pi,   half_pi + epsilon},
                        {pi + epsilon,    fourth_pi},
                        {pi + epsilon,   -fourth_pi},
                        {3.0*fourth_pi,  -half_pi - epsilon},
                        {half_pi,        -fourth_pi - epsilon},
                        {fourth_pi,      -half_pi - epsilon},
                        {0.0,            -fourth_pi - epsilon},
                        {-fourth_pi,     -half_pi - epsilon},
                        {-half_pi,       -fourth_pi - epsilon},
                        {-3.0*fourth_pi, -half_pi - epsilon},
                        {-pi - epsilon,  -fourth_pi}
                    };
                    return pnpoly((int)sizeof(healpixVertsJit)/
                                  sizeof(healpixVertsJit[0]), healpixVertsJit, x, y);
                } else {
                    T rhealpixVertsJit[][2] = {
                        {-pi - epsilon,                                 fourth_pi + epsilon},
                        {-pi + north_square*half_pi - epsilon,          fourth_pi + epsilon},
                        {-pi + north_square*half_pi - epsilon,          3.0*fourth_pi + epsilon},
                        {-pi + (north_square + 1.0)*half_pi + epsilon,  3.0*fourth_pi + epsilon},
                        {-pi + (north_square + 1.0)*half_pi + epsilon,  fourth_pi + epsilon},
                        {pi + epsilon,                                  fourth_pi + epsilon},
                        {pi + epsilon,                                 -fourth_pi - epsilon},
                        {-pi + (south_square + 1.0)*half_pi + epsilon, -fourth_pi - epsilon},
                        {-pi + (south_square + 1.0)*half_pi + epsilon, -3.0*fourth_pi - epsilon},
                        {-pi + south_square*half_pi - epsilon,         -3.0*fourth_pi - epsilon},
                        {-pi + south_square*half_pi - epsilon,         -fourth_pi - epsilon},
                        {-pi - epsilon,                                -fourth_pi - epsilon}
                    };

                    return pnpoly((int)sizeof(rhealpixVertsJit)/
                                  sizeof(rhealpixVertsJit[0]), rhealpixVertsJit, x, y);
                }
            }
            /**
             * Return the authalic latitude of latitude alpha (if inverse=0) or
             * return the approximate latitude of authalic latitude alpha (if inverse=1).
             * P contains the relavent ellipsoid parameters.
             **/
            template <typename Parameters, typename T>
            inline T auth_lat(const Parameters& par, const par_healpix<T>& proj_parm, T const& alpha, int inverse)
            {
                if (inverse == 0) {
                    /* Authalic latitude. */
                    T q = pj_qsfn(sin(alpha), par.e, 1.0 - par.es);
                    T qp = proj_parm.qp;
                    T ratio = q/qp;

                    if (math::abs(ratio) > 1) {
                        /* Rounding error. */
                        ratio = pj_sign(ratio);
                    }

                    return asin(ratio);
                } else {
                    /* Approximation to inverse authalic latitude. */
                    return pj_authlat(alpha, proj_parm.apa);
                }
            }
            /**
             * Return the HEALPix projection of the longitude-latitude point lp on
             * the unit sphere.
            **/
            template <typename T>
            inline void healpix_sphere(T const& lp_lam, T const& lp_phi, T& xy_x, T& xy_y)
            {               
                static const T pi = detail::pi<T>();
                static const T half_pi = detail::half_pi<T>();
                static const T fourth_pi = detail::fourth_pi<T>();

                T lam = lp_lam;
                T phi = lp_phi;
                T phi0 = asin(T(2.0)/T(3.0));

                /* equatorial region */
                if ( fabsl(phi) <= phi0) {
                    xy_x = lam;
                    xy_y = 3.0*pi/8.0*sin(phi);
                } else {
                    T lamc;
                    T sigma = sqrt(3.0*(1 - math::abs(sin(phi))));
                    T cn = floor(2*lam / pi + 2);
                    if (cn >= 4) {
                        cn = 3;
                    }
                    lamc = -3*fourth_pi + half_pi*cn;
                    xy_x = lamc + (lam - lamc)*sigma;
                    xy_y = pj_sign(phi)*fourth_pi*(2 - sigma);
                }
                return;
            }
            /**
             * Return the inverse of healpix_sphere().
            **/
            template <typename T>
            inline void healpix_sphere_inverse(T const& xy_x, T const& xy_y, T& lp_lam, T& lp_phi)
            {                
                static const T pi = detail::pi<T>();
                static const T half_pi = detail::half_pi<T>();
                static const T fourth_pi = detail::fourth_pi<T>();

                T x = xy_x;
                T y = xy_y;
                T y0 = fourth_pi;

                /* Equatorial region. */
                if (math::abs(y) <= y0) {
                    lp_lam = x;
                    lp_phi = asin(8.0*y/(3.0*pi));
                } else if (fabsl(y) < half_pi) {
                    T cn = floor(2.0*x/pi + 2.0);
                    T xc, tau;
                    if (cn >= 4) {
                        cn = 3;
                    }
                    xc = -3.0*fourth_pi + (half_pi)*cn;
                    tau = 2.0 - 4.0*fabsl(y)/pi;
                    lp_lam = xc + (x - xc)/tau;
                    lp_phi = pj_sign(y)*asin(1.0 - math::pow(tau, 2)/3.0);
                } else {
                    lp_lam = -1.0*pi;
                    lp_phi = pj_sign(y)*half_pi;
                }
                return;
            }
            /**
             * Return the vector sum a + b, where a and b are 2-dimensional vectors.
             * @param ret holds a + b.
             **/
            template <typename T>
            inline void vector_add(const T a[2], const T b[2], T ret[2])
            {
                int i;
                for(i = 0; i < 2; i++) {
                    ret[i] = a[i] + b[i];
                }
            }
            /**
             * Return the vector difference a - b, where a and b are 2-dimensional vectors.
             * @param ret holds a - b.
             **/
            template <typename T>
            inline void vector_sub(const T a[2], const T b[2], T ret[2])
            {
                int i;
                for(i = 0; i < 2; i++) {
                    ret[i] = a[i] - b[i];
                }
            }
            /**
             * Return the 2 x 1 matrix product a*b, where a is a 2 x 2 matrix and
             * b is a 2 x 1 matrix.
             * @param ret holds a*b.
             **/
            template <typename T1, typename T2>
            inline void dot_product(const T1 a[2][2], const T2 b[2], T2 ret[2])
            {
                int i, j;
                int length = 2;
                for(i = 0; i < length; i++) {
                    ret[i] = 0;
                    for(j = 0; j < length; j++) {
                        ret[i] += a[i][j]*b[j];
                    }
                }
            }
            /**
             * Return the number of the polar cap, the pole point coordinates, and
             * the region that (x, y) lies in.
             * If inverse=0, then assume (x,y) lies in the image of the HEALPix
             * projection of the unit sphere.
             * If inverse=1, then assume (x,y) lies in the image of the
             * (north_square, south_square)-rHEALPix projection of the unit sphere.
             **/
            template <typename T>
            inline cap_map<T> get_cap(T x, T const& y, int north_square, int south_square,
                                     int inverse)
            {
                static const T pi = detail::pi<T>();
                static const T half_pi = detail::half_pi<T>();
                static const T fourth_pi = detail::fourth_pi<T>();

                cap_map<T> capmap;
                T c;
                capmap.x = x;
                capmap.y = y;
                if (inverse == 0) {
                    if (y > fourth_pi) {
                        capmap.region = cap_map<T>::north;
                        c = half_pi;
                    } else if (y < -fourth_pi) {
                        capmap.region = cap_map<T>::south;
                        c = -half_pi;
                    } else {
                        capmap.region = cap_map<T>::equatorial;
                        capmap.cn = 0;
                        return capmap;
                    }
                    /* polar region */
                    if (x < -half_pi) {
                        capmap.cn = 0;
                        capmap.x = (-3.0*fourth_pi);
                        capmap.y = c;
                    } else if (x >= -half_pi && x < 0) {
                        capmap.cn = 1;
                        capmap.x = -fourth_pi;
                        capmap.y = c;
                    } else if (x >= 0 && x < half_pi) {
                        capmap.cn = 2;
                        capmap.x = fourth_pi;
                        capmap.y = c;
                    } else {
                        capmap.cn = 3;
                        capmap.x = 3.0*fourth_pi;
                        capmap.y = c;
                    }
                } else {
                    if (y > fourth_pi) {
                        capmap.region = cap_map<T>::north;
                        capmap.x = (-3.0*fourth_pi + north_square*half_pi);
                        capmap.y = half_pi;
                        x = x - north_square*half_pi;
                    } else if (y < -fourth_pi) {
                        capmap.region = cap_map<T>::south;
                        capmap.x = (-3.0*fourth_pi + south_square*pi/2);
                        capmap.y = -half_pi;
                        x = x - south_square*half_pi;
                    } else {
                        capmap.region = cap_map<T>::equatorial;
                        capmap.cn = 0;
                        return capmap;
                    }
                    /* Polar Region, find the HEALPix polar cap number that
                       x, y moves to when rHEALPix polar square is disassembled. */
                    if (capmap.region == cap_map<T>::north) {
                        if (y >= -x - fourth_pi - epsilon && y < x + 5.0*fourth_pi - epsilon) {
                            capmap.cn = (north_square + 1) % 4;
                        } else if (y > -x -fourth_pi + epsilon && y >= x + 5.0*fourth_pi - epsilon) {
                            capmap.cn = (north_square + 2) % 4;
                        } else if (y <= -x -fourth_pi + epsilon && y > x + 5.0*fourth_pi + epsilon) {
                            capmap.cn = (north_square + 3) % 4;
                        } else {
                            capmap.cn = north_square;
                        }
                    } else if (capmap.region == cap_map<T>::south) {
                        if (y <= x + fourth_pi + epsilon && y > -x - 5.0*fourth_pi + epsilon) {
                            capmap.cn = (south_square + 1) % 4;
                        } else if (y < x + fourth_pi - epsilon && y <= -x - 5.0*fourth_pi + epsilon) {
                            capmap.cn = (south_square + 2) % 4;
                        } else if (y >= x + fourth_pi - epsilon && y < -x - 5.0*fourth_pi - epsilon) {
                            capmap.cn = (south_square + 3) % 4;
                        } else {
                            capmap.cn = south_square;
                        }
                    }
                }
                return capmap;
            }
            /**
             * Rearrange point (x, y) in the HEALPix projection by
             * combining the polar caps into two polar squares.
             * Put the north polar square in position north_square and
             * the south polar square in position south_square.
             * If inverse=1, then uncombine the polar caps.
             * @param north_square integer between 0 and 3.
             * @param south_square integer between 0 and 3.
             **/
            template <typename T>
            inline void combine_caps(T& xy_x, T& xy_y, int north_square, int south_square,
                                     int inverse)
            {
                static const T half_pi = detail::half_pi<T>();
                static const T fourth_pi = detail::fourth_pi<T>();

                T v[2];
                T c[2];
                T vector[2];
                T v_min_c[2];
                T ret_dot[2];
                const double (*tmpRot)[2];
                int pole = 0;

                cap_map<T> capmap = get_cap(xy_x, xy_y, north_square, south_square, inverse);
                if (capmap.region == cap_map<T>::equatorial) {
                    xy_x = capmap.x;
                    xy_y = capmap.y;
                    return;
                }

                v[0] = xy_x; v[1] = xy_y;
                c[0] = capmap.x; c[1] = capmap.y;

                if (inverse == 0) {
                    /* Rotate (xy_x, xy_y) about its polar cap tip and then translate it to
                       north_square or south_square. */

                    if (capmap.region == cap_map<T>::north) {
                        pole = north_square;
                        tmpRot = rot[get_rotate_index(capmap.cn - pole)];
                    } else {
                        pole = south_square;
                        tmpRot = rot[get_rotate_index(-1*(capmap.cn - pole))];
                    }
                } else {
                    /* Inverse function.
                     Unrotate (xy_x, xy_y) and then translate it back. */

                    /* disassemble */
                    if (capmap.region == cap_map<T>::north) {
                        pole = north_square;
                        tmpRot = rot[get_rotate_index(-1*(capmap.cn - pole))];
                    } else {
                        pole = south_square;
                        tmpRot = rot[get_rotate_index(capmap.cn - pole)];
                    }
                }

                vector_sub(v, c, v_min_c);
                dot_product(tmpRot, v_min_c, ret_dot);

                {
                    T a[2];
                    /* Workaround cppcheck git issue */
                    T* pa = a;
                    // TODO: in proj4 5.0.0 this line is used instead
                    //pa[0] = -3.0*fourth_pi + ((inverse == 0) ? 0 : capmap.cn) *half_pi;
                    pa[0] = -3.0*fourth_pi + ((inverse == 0) ? pole : capmap.cn) *half_pi;
                    pa[1] = half_pi;
                    vector_add(ret_dot, a, vector);
                }

                xy_x = vector[0];
                xy_y = vector[1];
            }

            template <typename T, typename Parameters>
            struct base_healpix_ellipsoid
            {
                par_healpix<T> m_proj_parm;

                // FORWARD(e_healpix_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    lp_lat = auth_lat(par, m_proj_parm, lp_lat, 0);
                    return healpix_sphere(lp_lon, lp_lat, xy_x, xy_y);
                }

                // INVERSE(e_healpix_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    /* Check whether (x, y) lies in the HEALPix image. */
                    if (in_image(xy_x, xy_y, 0, 0, 0) == 0) {
                        lp_lon = HUGE_VAL;
                        lp_lat = HUGE_VAL;
                        BOOST_THROW_EXCEPTION( projection_exception(error_invalid_x_or_y) );
                    }
                    healpix_sphere_inverse(xy_x, xy_y, lp_lon, lp_lat);
                    lp_lat = auth_lat(par, m_proj_parm, lp_lat, 1);
                }

                static inline std::string get_name()
                {
                    return "healpix_ellipsoid";
                }

            };

            template <typename T, typename Parameters>
            struct base_healpix_spheroid
            {
                par_healpix<T> m_proj_parm;

                // FORWARD(s_healpix_forward)  sphere
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    return healpix_sphere(lp_lon, lp_lat, xy_x, xy_y);
                }

                // INVERSE(s_healpix_inverse)  sphere
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    /* Check whether (x, y) lies in the HEALPix image */
                    if (in_image(xy_x, xy_y, 0, 0, 0) == 0) {
                        lp_lon = HUGE_VAL;
                        lp_lat = HUGE_VAL;
                        BOOST_THROW_EXCEPTION( projection_exception(error_invalid_x_or_y) );
                    }
                    return healpix_sphere_inverse(xy_x, xy_y, lp_lon, lp_lat);
                }

                static inline std::string get_name()
                {
                    return "healpix_spheroid";
                }

            };

            template <typename T, typename Parameters>
            struct base_rhealpix_ellipsoid
            {
                par_healpix<T> m_proj_parm;

                // FORWARD(e_rhealpix_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    lp_lat = auth_lat(par, m_proj_parm, lp_lat, 0);
                    healpix_sphere(lp_lon, lp_lat, xy_x, xy_y);
                    combine_caps(xy_x, xy_y, this->m_proj_parm.north_square, this->m_proj_parm.south_square, 0);
                }

                // INVERSE(e_rhealpix_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    /* Check whether (x, y) lies in the rHEALPix image. */
                    if (in_image(xy_x, xy_y, 1, this->m_proj_parm.north_square, this->m_proj_parm.south_square) == 0) {
                        lp_lon = HUGE_VAL;
                        lp_lat = HUGE_VAL;
                        BOOST_THROW_EXCEPTION( projection_exception(error_invalid_x_or_y) );
                    }
                    combine_caps(xy_x, xy_y, this->m_proj_parm.north_square, this->m_proj_parm.south_square, 1);
                    healpix_sphere_inverse(xy_x, xy_y, lp_lon, lp_lat);
                    lp_lat = auth_lat(par, m_proj_parm, lp_lat, 1);
                }

                static inline std::string get_name()
                {
                    return "rhealpix_ellipsoid";
                }

            };

            template <typename T, typename Parameters>
            struct base_rhealpix_spheroid
            {
                par_healpix<T> m_proj_parm;

                // FORWARD(s_rhealpix_forward)  sphere
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    healpix_sphere(lp_lon, lp_lat, xy_x, xy_y);
                    combine_caps(xy_x, xy_y, this->m_proj_parm.north_square, this->m_proj_parm.south_square, 0);
                }

                // INVERSE(s_rhealpix_inverse)  sphere
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    /* Check whether (x, y) lies in the rHEALPix image. */
                    if (in_image(xy_x, xy_y, 1, this->m_proj_parm.north_square, this->m_proj_parm.south_square) == 0) {
                        lp_lon = HUGE_VAL;
                        lp_lat = HUGE_VAL;
                        BOOST_THROW_EXCEPTION( projection_exception(error_invalid_x_or_y) );
                    }
                    combine_caps(xy_x, xy_y, this->m_proj_parm.north_square, this->m_proj_parm.south_square, 1);
                    return healpix_sphere_inverse(xy_x, xy_y, lp_lon, lp_lat);
                }

                static inline std::string get_name()
                {
                    return "rhealpix_spheroid";
                }

            };

            // HEALPix
            template <typename Parameters, typename T>
            inline void setup_healpix(Parameters& par, par_healpix<T>& proj_parm)
            {
                if (par.es != 0.0) {
                    proj_parm.apa = pj_authset<T>(par.es); /* For auth_lat(). */
                    proj_parm.qp = pj_qsfn(1.0, par.e, par.one_es); /* For auth_lat(). */
                    par.a = par.a*sqrt(0.5*proj_parm.qp); /* Set par.a to authalic radius. */
                    pj_calc_ellipsoid_params(par, par.a, par.es); /* Ensure we have a consistent parameter set */
                } else {
                }
            }

            // rHEALPix
            template <typename Params, typename Parameters, typename T>
            inline void setup_rhealpix(Params const& params, Parameters& par, par_healpix<T>& proj_parm)
            {
                proj_parm.north_square = pj_get_param_i<srs::spar::north_square>(params, "north_square", srs::dpar::north_square);
                proj_parm.south_square = pj_get_param_i<srs::spar::south_square>(params, "south_square", srs::dpar::south_square);
                /* Check for valid north_square and south_square inputs. */
                if ((proj_parm.north_square < 0) || (proj_parm.north_square > 3)) {
                    BOOST_THROW_EXCEPTION( projection_exception(error_axis) );
                }
                if ((proj_parm.south_square < 0) || (proj_parm.south_square > 3)) {
                    BOOST_THROW_EXCEPTION( projection_exception(error_axis) );
                }
                if (par.es != 0.0) {
                    proj_parm.apa = pj_authset<T>(par.es); /* For auth_lat(). */
                    proj_parm.qp = pj_qsfn(1.0, par.e, par.one_es); /* For auth_lat(). */
                    par.a = par.a*sqrt(0.5*proj_parm.qp); /* Set par.a to authalic radius. */
                    // TODO: why not the same as in healpix?
                    //pj_calc_ellipsoid_params(par, par.a, par.es);
                    par.ra = 1.0/par.a;
                } else {
                }
            }

    }} // namespace detail::healpix
    #endif // doxygen

    /*!
        \brief HEALPix projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Spheroid
         - Ellipsoid
        \par Example
        \image html ex_healpix.gif
    */
    template <typename T, typename Parameters>
    struct healpix_ellipsoid : public detail::healpix::base_healpix_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline healpix_ellipsoid(Params const& , Parameters & par)
        {
            detail::healpix::setup_healpix(par, this->m_proj_parm);
        }
    };

    /*!
        \brief HEALPix projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Spheroid
         - Ellipsoid
        \par Example
        \image html ex_healpix.gif
    */
    template <typename T, typename Parameters>
    struct healpix_spheroid : public detail::healpix::base_healpix_spheroid<T, Parameters>
    {
        template <typename Params>
        inline healpix_spheroid(Params const& , Parameters & par)
        {
            detail::healpix::setup_healpix(par, this->m_proj_parm);
        }
    };

    /*!
        \brief rHEALPix projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - north_square (integer)
         - south_square (integer)
        \par Example
        \image html ex_rhealpix.gif
    */
    template <typename T, typename Parameters>
    struct rhealpix_ellipsoid : public detail::healpix::base_rhealpix_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline rhealpix_ellipsoid(Params const& params, Parameters & par)
        {
            detail::healpix::setup_rhealpix(params, par, this->m_proj_parm);
        }
    };

    /*!
        \brief rHEALPix projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - north_square (integer)
         - south_square (integer)
        \par Example
        \image html ex_rhealpix.gif
    */
    template <typename T, typename Parameters>
    struct rhealpix_spheroid : public detail::healpix::base_rhealpix_spheroid<T, Parameters>
    {
        template <typename Params>
        inline rhealpix_spheroid(Params const& params, Parameters & par)
        {
            detail::healpix::setup_rhealpix(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI2(srs::spar::proj_healpix, healpix_spheroid, healpix_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI2(srs::spar::proj_rhealpix, rhealpix_spheroid, rhealpix_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI2(healpix_entry, healpix_spheroid, healpix_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI2(rhealpix_entry, rhealpix_spheroid, rhealpix_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(healpix_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(healpix, healpix_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(rhealpix, rhealpix_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_HEALPIX_HPP


/* healpix.hpp
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
*/
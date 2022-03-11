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

#ifndef BOOST_GEOMETRY_PROJECTIONS_CHAMB_HPP
#define BOOST_GEOMETRY_PROJECTIONS_CHAMB_HPP

#include <cstdio>

#include <boost/geometry/srs/projections/impl/aasincos.hpp>
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
    namespace detail { namespace chamb
    {

            //static const double third = 0.333333333333333333;
            static const double tolerance = 1e-9;

            // specific for 'chamb'
            template <typename T>
            struct vect_ra { T r, Az; };
            template <typename T>
            struct point_xy { T x, y; };

            template <typename T>
            struct par_chamb
            {
                struct { /* control point data */
                    T phi, lam;
                    T cosphi, sinphi;
                    vect_ra<T> v;
                    point_xy<T> p;
                    T Az;
                } c[3];
                point_xy<T> p;
                T beta_0, beta_1, beta_2;
            };

            /* distance and azimuth from point 1 to point 2 */
            template <typename T>
            inline vect_ra<T> vect(T const& dphi, T const& c1, T const& s1, T const& c2, T const& s2, T const& dlam)
            {
                vect_ra<T> v;
                T cdl, dp, dl;

                cdl = cos(dlam);
                if (fabs(dphi) > 1. || fabs(dlam) > 1.)
                    v.r = aacos(s1 * s2 + c1 * c2 * cdl);
                else { /* more accurate for smaller distances */
                    dp = sin(.5 * dphi);
                    dl = sin(.5 * dlam);
                    v.r = 2. * aasin(sqrt(dp * dp + c1 * c2 * dl * dl));
                }
                if (fabs(v.r) > tolerance)
                    v.Az = atan2(c2 * sin(dlam), c1 * s2 - s1 * c2 * cdl);
                else
                    v.r = v.Az = 0.;
                return v;
            }

            /* law of cosines */
            template <typename T>
            inline T lc(T const& b, T const& c, T const& a)
            {
                return aacos(.5 * (b * b + c * c - a * a) / (b * c));
            }

            template <typename T, typename Parameters>
            struct base_chamb_spheroid
            {
                par_chamb<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T third = detail::third<T>();

                    T sinphi, cosphi, a;
                    vect_ra<T> v[3];
                    int i, j;

                    sinphi = sin(lp_lat);
                    cosphi = cos(lp_lat);
                    for (i = 0; i < 3; ++i) { /* dist/azimiths from control */
                        v[i] = vect(lp_lat - this->m_proj_parm.c[i].phi, this->m_proj_parm.c[i].cosphi, this->m_proj_parm.c[i].sinphi,
                            cosphi, sinphi, lp_lon - this->m_proj_parm.c[i].lam);
                        if (v[i].r == 0.0)
                            break;
                        v[i].Az = adjlon(v[i].Az - this->m_proj_parm.c[i].v.Az);
                    }
                    if (i < 3) /* current point at control point */
                        { xy_x = this->m_proj_parm.c[i].p.x; xy_y = this->m_proj_parm.c[i].p.y; }
                    else { /* point mean of intersepts */
                        { xy_x = this->m_proj_parm.p.x; xy_y = this->m_proj_parm.p.y; }
                        for (i = 0; i < 3; ++i) {
                            j = i == 2 ? 0 : i + 1;
                            a = lc(this->m_proj_parm.c[i].v.r, v[i].r, v[j].r);
                            if (v[i].Az < 0.)
                                a = -a;
                            if (! i) { /* coord comp unique to each arc */
                                xy_x += v[i].r * cos(a);
                                xy_y -= v[i].r * sin(a);
                            } else if (i == 1) {
                                a = this->m_proj_parm.beta_1 - a;
                                xy_x -= v[i].r * cos(a);
                                xy_y -= v[i].r * sin(a);
                            } else {
                                a = this->m_proj_parm.beta_2 - a;
                                xy_x += v[i].r * cos(a);
                                xy_y += v[i].r * sin(a);
                            }
                        }
                        xy_x *= third; /* mean of arc intercepts */
                        xy_y *= third;
                    }
                }

                static inline std::string get_name()
                {
                    return "chamb_spheroid";
                }

            };

            template <typename T>
            inline T chamb_init_lat(srs::detail::proj4_parameters const& params, int i)
            {
                static const std::string lat[3] = {"lat_1", "lat_2", "lat_3"};
                return _pj_get_param_r<T>(params, lat[i]);
            }
            template <typename T>
            inline T chamb_init_lat(srs::dpar::parameters<T> const& params, int i)
            {
                static const srs::dpar::name_r lat[3] = {srs::dpar::lat_1, srs::dpar::lat_2, srs::dpar::lat_3};
                return _pj_get_param_r<T>(params, lat[i]);
            }

            template <typename T>
            inline T chamb_init_lon(srs::detail::proj4_parameters const& params, int i)
            {
                static const std::string lon[3] = {"lon_1", "lon_2", "lon_3"};
                return _pj_get_param_r<T>(params, lon[i]);
            }
            template <typename T>
            inline T chamb_init_lon(srs::dpar::parameters<T> const& params, int i)
            {
                static const srs::dpar::name_r lon[3] = {srs::dpar::lon_1, srs::dpar::lon_2, srs::dpar::lon_3};
                return _pj_get_param_r<T>(params, lon[i]);
            }

            // Chamberlin Trimetric
            template <typename Params, typename Parameters, typename T>
            inline void setup_chamb(Params const& params, Parameters& par, par_chamb<T>& proj_parm)
            {
                static const T pi = detail::pi<T>();

                int i, j;

                for (i = 0; i < 3; ++i) { /* get control point locations */
                    proj_parm.c[i].phi = chamb_init_lat<T>(params, i);
                    proj_parm.c[i].lam = chamb_init_lon<T>(params, i);
                    proj_parm.c[i].lam = adjlon(proj_parm.c[i].lam - par.lam0);
                    proj_parm.c[i].cosphi = cos(proj_parm.c[i].phi);
                    proj_parm.c[i].sinphi = sin(proj_parm.c[i].phi);
                }
                for (i = 0; i < 3; ++i) { /* inter ctl pt. distances and azimuths */
                    j = i == 2 ? 0 : i + 1;
                    proj_parm.c[i].v = vect(proj_parm.c[j].phi - proj_parm.c[i].phi, proj_parm.c[i].cosphi, proj_parm.c[i].sinphi,
                        proj_parm.c[j].cosphi, proj_parm.c[j].sinphi, proj_parm.c[j].lam - proj_parm.c[i].lam);
                    if (proj_parm.c[i].v.r == 0.0)
                        BOOST_THROW_EXCEPTION( projection_exception(error_control_point_no_dist) );
                    /* co-linearity problem ignored for now */
                }
                proj_parm.beta_0 = lc(proj_parm.c[0].v.r, proj_parm.c[2].v.r, proj_parm.c[1].v.r);
                proj_parm.beta_1 = lc(proj_parm.c[0].v.r, proj_parm.c[1].v.r, proj_parm.c[2].v.r);
                proj_parm.beta_2 = pi - proj_parm.beta_0;
                proj_parm.p.y = 2. * (proj_parm.c[0].p.y = proj_parm.c[1].p.y = proj_parm.c[2].v.r * sin(proj_parm.beta_0));
                proj_parm.c[2].p.y = 0.;
                proj_parm.c[0].p.x = - (proj_parm.c[1].p.x = 0.5 * proj_parm.c[0].v.r);
                proj_parm.p.x = proj_parm.c[2].p.x = proj_parm.c[0].p.x + proj_parm.c[2].v.r * cos(proj_parm.beta_0);

                par.es = 0.;
            }

    }} // namespace detail::chamb
    #endif // doxygen

    /*!
        \brief Chamberlin Trimetric projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Projection parameters
         - lat_1: Latitude of control point 1 (degrees)
         - lon_1: Longitude of control point 1 (degrees)
         - lat_2: Latitude of control point 2 (degrees)
         - lon_2: Longitude of control point 2 (degrees)
         - lat_3: Latitude of control point 3 (degrees)
         - lon_3: Longitude of control point 3 (degrees)
        \par Example
        \image html ex_chamb.gif
    */
    template <typename T, typename Parameters>
    struct chamb_spheroid : public detail::chamb::base_chamb_spheroid<T, Parameters>
    {
        template <typename Params>
        inline chamb_spheroid(Params const& params, Parameters & par)
        {
            detail::chamb::setup_chamb(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_chamb, chamb_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(chamb_entry, chamb_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(chamb_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(chamb, chamb_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_CHAMB_HPP


/* chamb.hpp
u+/+Y1jcEJpfxLajCNC8AzX98vQCPzsAf+9n5Q52d9YJdjSHV1cj0xiqXAUWkdogTtgmQFZSwFIAXVrMe6dcYG82LXpMqMuj7o164dBpkmSsRYe8r9Q3NNXFDzwQPdcx10RWdp58R54yI3ANCOsfv0JB9/cU+ZspOg9xLy7Be2mbOBmMKSWhq4U5vRUPHgwTz1tsYof6KHf/NWwsitkVr5X912iXD/7hPVJjsieOdsVO675H7SnDzY37pfvDdHFUJH1Id8GfwkZ0m+i3P7ZbSumASfrQy7eJmi8AKZaUxYW1CqrhC4COovc/Db3UekRK2/FyGAOv+psS5LsEixAo25IP1dfdb5o314pwkP2CeyezxEAKFp0EpNTfZKWEobEEOyU4IgnwPDbuOTXu+ZrIs3qoDHko3kvC9x8lD8uvPggbdAQbmUz00ESc1UbXp9E8a8G+QVN94j6a6qzGBVkHsz3H5eF4S4w6H8yiFTagOJESdrN5uA8IKWH2Ls6356RciXTorF6Fk4+0CHN6vgodJd24nEfhTYID8hC3FKbDDHgt31H+ORYIj1Ug19MuD3WrMt6dY4VcF+TuptxU5TqguxSmJoNVkCeKBIeYJ+qhIFBxDQv2QflfvR/GG/fOHg/j3v3BJn7fPRGi7h9iL011WWmbaI8FHpUb1BGUxN94+DTFmX/4zSmj9MORwFn+kG23LGDB5BpDGcLP3o3n8lKtwiykKGoMlqo0o9fcScoyNtMObws9KoZKrJiX59MZreKPHj6L6yKH5Tl470r0T4+VU/LkYXnK5F19n6a4Qsm7uvDPkF3t8KeAHwUyXODDGK/bgee9hmACmnCkdK/aIXS389pPw2TUkNs6GVjfZxg4tfazFJMBorD/kf0CeYdBNNfh5jRuENFD1F3motvk0nVcQWl6sBfdMseZOhWdOFJyvSb1MhWPklqlPqZmw8MtUpipM+hhwDy3i15CpZdCiXxp0Bgo5dAWCCgzE9vEUxcpJCnTBOVV9WDA6+UnwtXlDivzpuk76F4CcauY1Faveduh4XV470PmOryXGMxj51vH5gYsZmyQ+ni7BfrUg1vEWYuJVH0/+ZkKD4POe0vhm8zbYvVu1XdMpbxq4YNqvUXZhu505U1bOPOMpqys6WfKNi24ZcUIdjEzuBVkc91iIPtMZSuQdZ2btOhqENwvksRIZoXVurJFD64XZ0TW2/apuxDFoNpv1IM7gWABdb2Z37DCXtsxTenQCjtDdB5U6bVhLLymdNr2AdY0dBOGM6VWHcpInCKlxLbszvr6gK0e2XV7vYnTNl1ZLw4l1/MXbgfrE4bobYFRqsE1ANp6Ai2FFa6JB21jZgy09QjamAgYtlYBiFbYFRpzObxR0AhMDgBeDl3Ct0B38rZB0K0E6O4nFK6GJzqB7F0dA5IpLk3ZYDsZgVPZzNBPCVi0IUAADlP6MnsBJtuHoVE2DFE3077RpE5bCwKodIFSejmMFgDzW2D0DoZxrengY97UOPR5N2d610bg8m5g3h7oA0G7zvah5u1AX+exzMK1eG1fYScr7MtsRWyOwztJw5jfAtU1vLS0Ew8AQ5UuAPYSGBO+HcbfToqDsaaxMlBzsPIJExwTkCTqNWRjhT2Ih8IOWyviB/CyF0C5nKYsl9FUcqQ3z6DePq58Enr7weDehgDxhIZgHJ+g3g7bPqITs8Mr9ZbwLb19lCl6k/YzbyuMbTn09mykN+jqGhgYU8KZrZknaVQ4Glg1R4BWFYwhzEQ6tfXizCNhIDhXooCEbx/vLBMC6P7jSgW6fzqu+7HYC9D/XuzlG+wFSS00FheKgsEBJyOjJ6j+l+6/DQGHb40LcRg6BT3caZbLd63Na+D9+o489FcPugp+kyV6GN6tIujyBKbifnCm6kMTbp2PnlOJgWJ1TepBTPYZO+haeMphdyErFZGTnxInljKUaxkjtsuwnPOtlnzz6oZPsxoNZaKu9JgDSq8Htg/d+8x3HjfA0C1xA5yYhQOMHqpCiWEVEiNgC9jipAbIjFT0/aSBSicilcFutXd3ZF0wmhre/CwSvIhSTOznTzSUFBG5hxLyzPaLhialoLi2ohfXtsDtdVTY0PoF00x9vM9S5NdnDLWCHoO3Ayq9+i5EgljteGEFaDWg6lDGRDND30XCQ4g7toMQIxDICNkslawX0TxbN5H08zBjk/BBEW3lmW1Z2WyqiPEetzCcHyvNDGNTKGVetFmzI2pcdKfNmqctm8/UhdjdD6bgeQ8lBVCt5UzjE6eCLguIGLP1RjwOjPO4yLm+EYWvK0JVLvW+nd9LdVlA5pLUFIK/HkQCyX4w5GwtsIoBDVIYbGGGoh8kCt6FgAtB6sVZYzMoFWYrDdMG8KfvUqWARP+/rBaoPfL/QSfg/186ARc6wc7LdQLvfpDdEVVgrZA9h29RdjPCC1MaM5VWPcVBKkODFtzMgrszz2mFOzWlUQuuqTFAO/g0s7Ch5mNn3cwE1A4aUDvAa0rU4GaL7GGFazHvlxQ+DfrVTlMzAXmrSVuQW7zJ8EbUdpC++wglAfySQsAS8qjBDZbKxwHbgypChUxpA9RFttOaWbhBK2wnGR2pXNiB/IVrGAkj9Ih2YElRJkQcZ0tkQT46ARdkC6oLlUvV4EZL5RNMSr2kw22Z0kaoq0lbaXd+PxsQ8VAoyzYiu0Ox15fpPYxdeTujAoxfqUc+3uwRsJPOCvcjdhrIjK78HlKHJPgImiuhNODFwIgfgjyJ8kDIRHLFGNsRg50kbTpQ2nTpIpj9Csz1x9ixsr+mv3I2K0T+LpoMgwQHrdJ2BKpk7kMv5wCMgdg4tWWKC36lJtOoycPQ5BzR5EwBJd7xcQDbQ40AgTyAKOtEBSHWaMK3NNqcEccj7bdHhABuS06w+FGdX/yPU4Z5TUGuI3I1AfxOpN+p8LuoOTcPKa45dzaZ2qYv5NB9dCWdnf/P30/R4VCHlpus5bq03BQtN1XLTdNy07XcDC13Ih6JyJ2s5U4BUzJ3qpY7TcvN1nJncNkQR8bZdLta3gcWn/NdK1rWS9Cb8shiM14BumhOPAyMmbvuvCAOjtRhwDlHT5D6BklU9Q06JMEO8N7FcVfKDYeXUnKW/exs32XW+UvoKGpcHBfBrDjA1D6u2fx6rt0H+OOjhdNJPeDQl5PwwFgT83x12UR9+UTxNFVfPpXWYV6eNiuPZc9epOXMLmFN8TYxukBBnvhJoDh0RkNQDbyVlB7xCmCMaXBWV8RY9Lo4Fr0uwqIL5jOGLNrv12ZNQzC15VP4auDP7mCy7ECwy84OgFmJ0Uv34cTJQ2kwP3n0jOEmTiTfxVTzioXMql10fhM5yg26l+cHMG5n3o20Z3zVE2rwXLqSJK7MyhByCozgGzvJ8TZMcD8hwvJEVqLIKo7oCaQBxMn6iBjDK6JVIckGTMlnVakNFcWaVSUxppIYE8qGSgJMnUeKfrJFns/WTSIxhunaDvGMwkNbN4VwN43Sp1H6bEon0aISMCrJ13DmLmwv84C2i0pQ63h/QrZwv85rWIW0OKkEaRFp/fUEvGcWnzIWnDF072b+9YBhnmba7DMJ8w94/s27JUKbe3v5ic5TBv9hiSDNP2GTZcXRcByk7Yjf/3lcEnUpVnE9whaoRnuo0N+vr7pg8FElkZBj3gb9NicOfCZ8kM1WfOrehNUjIQovGrEQhe39fbETyebq+GphZHUs6b98dbyCq+Pfiwf5rrAPfm9cs4/GNduwuj3+sNR+Vfg+xcoUx1eaE/e3R29njBx7iT9EnfkPPKNXZEYxZSQMOkkbvSA+Z0EkrDx6bKZhS7Tz/HwKMdpOd+lSqU6L8ANG9h9885ilJO42rbgv4IDmsr01qvXGXTsNTBTj1xdlfZRdwndNpCDcF1EyZzXWfCzb2L4mpm0VDtxEVtVIR0yqdlosUeYiLkHTly3FdnMq6tld2CxovJCOZ3+Zir5UbaZdp6UJGSJ1LaUmYzBgjJ0c50XsLryISlxDhW0HXPPpqxQ1/ZH7qI7vi9yemhNL/GLI5s9TXB0Hv6BrqTr2Hf+QV86yW7QkLPLFiZDji8+PHzz+Ifw/+JcP/7KXfw8zZ9rNi6vMk0MRCvr9o0BBuHfCv9N3KQUl+ngvuj8XPRYhIbw22s/OGs9OLkVS4R/d0m9knaB7gK43w8UxvBVVbUfkjoiK7nXQvPvXSETKBD68C+mjoKAgpg66zKIvLQZq6X6cDI74K7oQL6SLe05djpgZscQrIObxh/FGxTCWuQJmZlLugImZo1n9fImfjo04WQt/7q3Txm9xB1i25rqvo8ttHQIe6Isf5yYAP53tOaXkMcllk1ILRECkFI77HEmaTUopMN7F0b9qKANoFYcxwmsAy1w8Fs7sLcoH04MvGx02QkubJTywYAF4k+BxNPlrsAWzYezk2Fl8gRYcxy7ibY1asSOUiFtu4qyWNFBQ4IM+XhV9UqxmFKR86I0c5kvH43dFgEOmmhF5iRT1rHhFHI5/0Je7UkQAJ187QJu9Q9y5pfJNsdXLnskGyhsFOtjEUvT1Rh3KdIuNSe7G9oXol7Zi777JuAqiKb4psM7wuSne9xx0ZDWyk+7K5IAVD+5JYXFwPeuEVpm8lzvVTrDPHJ7z6FovoChXtO58KawdL5dSgw6LPFzIvCl4CxeWsIkQbvruBcovZPmeTbjAndUvUfzNVhHQMkZcvI2hLdAY3tZxbPt54OlvCuYwhG+8Co+c7BSl56qLl1pYHb7hpdPGWtxlwPtA0vAOL0x2l5fJ12jlZZFCflNUmMeh3tkZYXO+JdqenRS2MFML9oVs8BcA+L5amWZRRl46plkawa4uX2pRHjCPda4kyTpgEf1q5Uvl1MhjrPcrdKsGwxb5u+qerWRNT2BH+N/O0W7ruMg9/blL0Qd+GFKjB2DUygyLnEJVrzKeSRb44a+PwA8F9Fmg5wjCrjJMexZPB4AAgENLAQCA/3/7Amnhs9MJr2gE7qXfLmMMSxbVHHRWv2ZW2SDQPNPYgVmlpX8FvlM43tw9ucOvb4vd9xfH7Bfhp0yQF0k9QHLRK3jla5mKzTRnyzQD1KbA6RKmErx4Cr0/ZGMwTKAXgseMTscjCkDpw4tg/YirvRJFa5EL9p74TtzFprCq/Iyms8aQCwv42rOGOOJ+Ahqfnx53Cm4twlIgGn0MWp2orpAt8nfUJ2UM16YJilJbMih8DnFz8NwlkUuIKaQWC1BIrZwLEx8323QVhkkF8r9EDoIKYe3Jt4G+X5nM28L0IbMb3OXpsvh0g9+kiP8Mx1FELNw25dKDSPozcd8eZMdjH1W4lR3iCm7Z9wJqr2O56TDIq/E+0Z58mLVkmDXiJ66JcV+GuJhuBntWmTNmbYq7S0AvOW2wlbtdwFACUxtOoqp2+zworOAlVEpHTb8yXFcbyN3dAXw0ejkbGGboE7qa1N2IIlDEa+pQFWznP/xtNCKojal5ItpQcatYEjgUMkbek0Yn4K/PR8XUjxeE3eHsJ90S9526+nC3v5HnjsJbi0HrMKie3CK6wyum+P0/h95G+/AZPxKWQY2MgQqRG8emOPG+onb6YFgsvueN5H4ROMQf6+nDqKHd9E0oq7AQkjF2yDUWkRxKyOo3lA4zbCi95hwYR9wdbBOhO1f7/X66IQkkSLvxkgiq6SjinxSQZRYoMHec85lGEmEjWDyRO5uLkzHGUz1vKIlsE7JzoMUvnWtepTAyfHe+QJezeh3GO1vNtb1fJNC1GWIm73FXpsh3uvdgBTp7MtNDz8EHWO38hOjZE1FazjBzKz4V16aLjhQ8XYNRYz/bf94IXa0+kWIJfcl9404b6A5zFPBdv8F7dLKj22T0uYKR3wdC2ZhPURqgzxnli0TbK/ylGKnJE0J9g7fnhwYsfMejYnOe1eGQEKta3iQTFqqtDPchJOEmgGRowOrz8/tjnfMhc2Nb+CDQaxrLR3tIFAaHM42Ga6/CguY9TebZF8INnqORTNzcF8XN4DODhBo6MzhPBN3NvP8c2Nu4uC2LmnNThC+A331t7DDUwkuOlCBnoU9cFOjkltGKdwttPKvRTfJSfoCuRlsWuaiaEIGu4J0+/pNKvAmCSY3u6fbKlFjWmz7ur4zcV20ou3Xvm6xd9POjE7Z80RPo+J759hXXQL7Iwmuqo1lsvl18NLGW5mgcy51H7EGfkWNDFnEizWQRUgNgda6HigUfZnWEqGlV2CodFBaWxW6MiXqTYqKo15Fm0haRBL0ZUgO0Jdqp+G3oBW65Joa1JYOdkyjHcKx0cxDGILZqSru2fJq23Kctn0fHbQ57jsouDErq9PFZQcAFhvzhwUHc5HPvovVSN8ZKu8qrS6wYN0hp+lxiT+YoPDnzg9fjF6qk3ZoE6NivSS26slttJv9G9wc0ttbYQDHEAweUBw9WfEilbDoRBG94VYLUqVztlrqUkZr0piZt06SdgGVdeTP0u9gHV8exIkfm1VphpzsnXR5JH0U7v/AMjmGmjxV2sly7DXjkLJ8tZ57tKk3abEOf4EaASpO2otNri65sJGeL1OmWOlaIk5NteJbHi5/p8UxPrkwyryrGYEOlPRu/SCsQsCaEd1EtT7fIN/EPPkNbAu1MCkMPIyQ2g/+YYLE1W7HZjiItJy/2rdstFvE5IO4WzdWtg4SQg985Fm8rwRN7faKjYI+JZXtV9HQS+gAHfcbobnKAdqjBwzB9fZXXMm9XacUJPOGUhsHB8lCW47NJh61SDwt2wfjFWdp6hpt8rcjHcLM7cuRPDO9ZgyIc9eVLqeSsMpu3jeUsteXkabPKicS1HBkp/Ow1g25RFzv2aJ8y8QkavTA8F0nXlXUQppUR05ji2VsxzxzfbLZDUFEtTszgjQ3oObtelKs4DAYvS7Ttg271XWhYI1wAxazZ2iy7Nsthfv9uzKBvLYuTVVh/TnlWQU1/+WwPvQVnsFXUa9q2+BuvleHssXR38QCQQvHAnOeOPsaAkLxkIoXPtGfOXLpIn+EwSmoa8SrHg028ekxs7WUMViC9yZq3w+11OF8gjgxKs3PNJhLmztUYzOVhYh2hXGIF89i+M+22xsycsiITHcl1tpxy9lBGpuTKnFXmz/wwcolkovp4lyVko81MBxBQyCbopcDE5yyTXvCEZxeIZ03pFFQj9sXqzTvNg51ivk1S8Egdle9Gz46OTxWn0/jrKbEBkm/AE0xe8XQBfgG14ofu4uSKJUXsDKD1Bx6yooKPsSrqPGUbezA988FUT/uKBNae61GSK4+zZoDyXlOu3MleFAV/pv8kVezv4N6D7ZSmhHEX6qepYu6l5MqDJY8tQgLjV6fEf39X34NEEPtucprYVvNHVezh4iPB3avIkikw5VU2yKsyU16VmvIqrWEQEaSgvp6TGq+vK5kRMdaoBl0WOQuL5C4cpNLfIPoLXYMqtQ3XwCFxXUMoiT82Gg8VUKR4siXqxolJ0fuuoGGkNahNqQVRqEaK8RVEQRodAakJOG/kuorm0Gn+P6MieGIvkgLUWFTzceU4wP4Nnn3BcWy7oI9aj+KQHdmefRV/hwZEDPuOUXEoPpvV76bVUvldmOI7zJVzC9qwtHhwnHhMnvQmvMQpVxSpOCbGyR+Pby022LthsA+Yg70HP0xXK1pz0QHcZGGcr11DQkcZGRnlh6gkFe9z0UdKTvOho2KUmT5Y7MHSAE3ouHkwmuTyo/qOK/vi1uGUZR0Elrx+b75gWcZL1RbxgT7Szs1EYpGx/Y8xEbGOS6/YXHqFV2LVnfHdKaDbRnqjj66YPSVGrl+OZ8IVr3VL6Dq9fmRsqGlxXAYHGR1i5aNFfgDlByYojyHHMcFJrtK8XfL1+tOXf3YdJACeVSItkO4IqRayLiboKn4X5QrOFPNyA911paPQBEWmuEJioXmCIqoqFxhrLWJC0yMT+mf3JkxSRpjrJonf5cJVEu+dHNQ2npe+22z79mjbJv0NWAaTyyeCXOwmuXzu/FaQ8SPguWaz9w8GGT35kQaPC6OUlmLVAYS4CK/xO8S3NJw3IoezlzmvSPGToAu32cUdEXJPjgGfF9dPm9AtmRXANzZjDr/OOeiUfdQmyTSbvGmQTRJ3yl7YJOI8fPtVkXPjem0ruYUjnGVUpMfot6On+v+FfjKu3E/ZVVEJbH6fxr1pGzm38FJeN1lGlUvwZM8XMZNMP0aOL6EIbCh1PTQGAyvbR4M1iafw2FGgd35wNCozyg1uaUC51r0KfX7yKKFUlgoNtQYDSXNEmxUbo2OYBmNYZo7hR1HuKlo+xH9CzcpXiUhf0ZLyQGRU+wdh4jazlfGDMFF6JUxgYOeSEYNwoe5BRFj8zupf4XCpcOgRaLbIbHZODDhCwSH+51ERFBxCFBwYRSgYhyi42q0iCpTBgMuPPPcfZstTeVfyaQOaP2M2//VlY39m1BXGfscjz31oNnEj1H7PrL190JiXirJDHnmuwxytIFD6dGJdNhTk35t8zohib4KI36eWbh3UEt7pGMHc5zHiNzbTZY83JsdQmHUCv7VbnIzBXehszp2fiSrQgKdJ/jEmOyhlADUih5Y736S1eeZnj6lr72VEtmxkHJE5+BJ4Rd6p2MVtGwOglQZQzUCtKUJa/2EequDqcDzLk9dw/T4w2v85nYz2Opxk0JAOKU7ctXIYap7d6N4F+CqtfmWMiydAD6IQHmv66QOmj+ZNrl8A3f8oXuZb9Am5aN7kr1v6jayDnibny3s1qR2aHMJd0GUgwRizGLU4akYvbEFfEF68SsdhLHHJndFklTBsIQ99q1bcQxf79mrF3Fn3JfLOE+VbTBxtFDjS7RvY1IiltjRqmJoGHL7p3hZhr5n44ze76CxiTRV6SE38jqY0+R4mtbilHjSyegR8OPdhKwbyHgZDb4XvslSQ46F71WCHRbmJL/ww3sTSKyzJ5KZKfiRiYrVQ+73Yfi9DU4ebk+Vcc6OB97K1Iz4LDDSvesC6rLTRZd1tHqzDoI5CV3JqiSD9wAKEwjZAU66dz8IPnhzgf8uOuUguc4B8q1SaF8fYPxvE2DGHzxga4cn+S5nyONPZYDoa8NZehyko7/4XmPOkKzPnTxxXlE//6xh83zoGzOEro01SMBS/DQ3HoIP1ei7KCp34SFSfKLPQx5vXio/MuXOXyteR81jLXWq8hI5hN3nAlST1dfI=
*/
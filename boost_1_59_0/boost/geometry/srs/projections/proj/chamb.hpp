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
h+VpWXQKuDP4KluYCxef4OXeuTc7GiJYF1JNijywizyClvdai3MNV08ngMRVQrMGCRWLZhqr6qnrTE3SivpOcCaPJE/bt8JyTTe+8vdqSGqyD/poRWrxcxmlgEONo7xo/hhp7+d8ofWNx/6rSQ+XpKTyIoboQnzacVBBQusZ//6y+7HWfLAL4h6uYuRvrfIeApVqsEt5RfgVZEvUcEW7eOW6CQipBNaUoN67ewYVSmRp+LyI9LmBz58v0agQ+edlIb6A7BayQ+kWNMhR9NddFoLWtKuqxuMKbBYhglwg6HOnsd759Vur0Kmp7W9yLaGfAh4JwC/d0qNGqSOxoDMb6hO/yQXjo9sUjYyIf34GdQTHHPfOP76Rjz+y0g369t0lq3LPgUyb7C4czkvsRSS24DQhpbr3FCfFsqqqacczritugzaB9sRHF7CL0ucOWgusNKAboJG70CIPKagz9eC2Rx9Q3K5G6eKuJYD6uwzrw/LoueQyF9UqVCTHpkQWCbz7AEUjVLOFxHxZoCa5Kinz7EzpjEKgAFkgkC1uf6mFQSPX4NMB8dxVXtwxwG9M7/o9M1Czpy9ZNe1RJHiwLSiZKs+LGANv8jE5ZsBP7pTYXgCmjz49riHYnNDnMMr/8UWXicr5lH+ENE7jGQrWbc8wb8Y2FBiRzw4GV4GLexCcFbZ2krFh7I8B/EumpotKfsEX2C9V2K5IeqE4yi8kY0OQjlke3E8aeBJdkspYwRWw9cCW3Y+pFrg4Dmp7PVGfPZ06ye7F4y2A8+KC83q7wc8VcsRI4HY+9TUgy02yoLRR5FPRtCcYMIrhTOmiSQumfKOEUGtU1dxDkhDxuGyMefXhWhdAQajhctSBUhZS+/eFDcpFmPQvWqnX/Jh7/X57RVpkAZPCwzV6rsl/TIctai+hdx/1phOEoCpeeXRzxtvX+/LLim2fejJERcfYMbKJtvYGE8AoVsir5XUi5SHGrKX1LH0GY87mbrzhBCNegxTRBU3NZjhKvLmjUGVJbQ746uuwi5hZFQ+l2XL+CDIWYaYK6ziKz798FqsSFbRiKXC/22oa1fjonWyCZ4ktUfjRZKkJizRoKwPL8oN+7PIIDwOap5QZm81Z7Z5cslFz2/NADjSsZwuroiI+QqvP/doZfUlQaC8/oe5KESsmQcmkVLk8iGobySf8T5czX4hi8os1UVcayVPJ6lx+ajemoa7+X7xS8U9siytG/LdCv0LVCuBKDmKTnQrNrqxCSxrUC0bFZ9F6+yDTe/aexkEl4JbGVQysSZ8vDEIEJra9FUu/tBnFU6F1CozZbLOW+9LhOcyz1aF3e2lN3kfHrOURY3jwUKSpC8Xo6ZcINI3KzO2sm3B9XvJlJORR7o/ESpvMOIy9Esa4U1EXF6WsTtGM0X5Kz46JKTXFGKX3LRMitPFuppydHeQcV5lOuVAzrEwCO3ruHoi8xMdbvxZZQyYjF0kjTvBDep/03qMe09EgKGXg/RDmAY3C6wlxkY5/1SRRwzOz0S5Rcwo4RM7CeNL8DApbT6SDy2emY47i3l+nuGsr40K6N5XF3c+kL02I3tyGsteWo6553aiOumvnwlrmw9KiqgquuosdjDN6aEpOLSBb7DXS5za47R00RZxHAVswVATmcjGWpgqinl71Bf/WD1RGD6wX5xRXitUILAvFq86zWl9bSo62QV/6Ay25L7OAynqnsPfJrec4E5YsICJvfTUXRbEY0jWae3Pfe43HgFddWRk+Rx7kEYouAsltmuQKovGnzUKaEVr+SVRg1EDvUIfaPda/wkPSBQ0HvGqhCGvMKosoqHLnf18TO9JdvcBr/dg9nXPkgVF/TwpD8v5puebphuH8vcvvMTFRzQjGNUsqUMhGTV697eaxvIzYm9HnpCMtZzfyaK7npVPtUiWYBDlmJIvTyIWTNog7W/g2a1463RuUwggfPUY9rRPmCKPpg58LElRYcZwmksnd35/QJpQuj1dTtd02EKq2cWNjdqrMbFeFbhE5odrDQTApy9PRf7acw3nyNOvgU46NPjh6B0suxogTKmxSEhN8zTeXu01QpCOe2onXp4HdZCFfdbec+W9lSfx/RrQRP21pwwP/Ad6+kPTORGdpBc9S+NWMh2BULeUvJ462KpcR2pOolp3LVxSHtrOQK3/0K28kL29JfOncFXXY5c7WAYIgs22Qn0HSXMCRSYpaGZ/S8A6GtWkuSrLgBzV/lmYyqSjoKxyR+mwWdMV2ILwf2cHQBK6Gi89QjFOVVo3Bd67zqlppT6EQe8BbA3XEikLh4i8NrdbY+1CIRDoRvt8gbgo59Pe+iD/cXgUHHX0g0G+We0uQYk7WzZJWUP214cZOU9xsTupLJeslKqPvxSO9nYkwupUUDwwH1DnfgOxVAetUpf9bFWrWPOgtWQcQOii4YA7osHdShjJ4eaiMEGO19kqtEefLlrjsyYpa6K5x79HjYmrQ9XZtALyjPai61fX3mEN5yGv3MNthD042suGU69HRVV+BN3N25nZo7Itq8YPg9ISgCka8sEn8Zq/P3F5m4Qn+qZa3LdT4dK8sCTdmx55/fCsBxKcY1ue+ke1oG+bWnTGxdwbsNVOh17ad7pVZfJe3VTBgx90euxNjF08cjBdn94eJGeNzEipQNxXEpwjWRx/o07cR/rWHtBdNiMc9rfeHETYHxM9uSefueyUxzaeKCmo5EDdpuUDCsqbTbMWhNtEP4ArfRH5jra8KHH7aCyf7JYwe7YLSUe2w4IGzJtb5+gPU+/MphLRJ2OrtzT46MYqtG0WSYd8VYgaVC8bIBcsq88YsHMvfG0pN991/Li7fYC2xSAyrQk1O6BxaxwC4z6koT8Yr1PKpFIV0H2aQ9VaV+EKDhNvfa9BtnAmhTEJV4AV34m+aHKb0HzwYxOj5paHCfkhY1oony0u0vj2TNwvlGoaZQpUOwRL57BumMpG8Yw6OD/aly5DztXC9ljQDlm/GBQheXGxCXdogMTaZdOVXuRBNLZY0o8yXTCJbAxJX6bxkJg5ZQrs1KaD29thnQoc+baeSPnybmSUKQHnyGzCGo6rasQOEUBpMIsA8hWmG0agXoHl63zy3A83BYABTv8j+Szijuf37Nmzm4GtMP7fiDQDDt6o4ctrIKWXgfFMJq5uFzDpY/Umkp3CaCUJZoLePYjqM8qMF8VSDe0WsyRUtiU8tZ/Vq+/Skd+C9d+CmPQ9J6s6KqIfwZbphXBdAhR35c8/BQ2kRwQYOH0mcze9ni7xy78vdrUol4dPFU5obuuHqnQbJ9sBiOeXqPzza4kbSsbQCBLMXW7gtoXBBWUVtXgZuW3IP2whbHRCDnOe55O5ZC+CTaYS/OxereAAdoDrrWKPKlYWEpd+vZFR2hIyB2uIhRfUNPGdYgRFiruZbWRPlnjAr4jSwxgkNZoNCSUsOi73U6NZQ5dEwsAi9NqlDzCfmy6Eq4KMaFGuHeDL/iqX5yJqDA/qaOebXcjGF2x2IE6svErHz4tmYLjs3AAgs99NzPtlfNrogxZknk/kn6O1By/rYsW7GeH0Sp24m+NvpO/OG9UEX/Ez8lVM7s03eFqnWjBEvusm0AtBGgANpy0b86rm8sJpG5repWBwVLx01/sJzW9qWTllBGEUA7QPLg0sv3IFpjF5syII5cGlMp9RpFf2NjK6564csYPg5p7uO6nPjwRgO8YUBJjXSsNf4luQwe0PLWDonjOc14sP3FTelrDSd6NxjEdoidJtMFu3nBNerJAeydEymSKWAcZcQTJfAMhQbNvLz55oGdOQeDCftw+PxJtJSnA5viMWAmdMyQh8PGuC4Xg1ddEVRTX+l+MvhEhOBRcT90Pj6jJWBauNUOjJUEUuwTSLbKeS7hGVhODqYz78b/grM/U3lXk+Ai50I2A8AAPQL+BfIL9BfYL/Af0H8+vML8hfUL+hfML9gf8H9gv+F8AvxF9Iv5F8ov1B/of1C/4XxC/MX1i/sXzi/cH/h/cL/RfCL8BfRL+JfJL9If5H9Iv9F8evvL8pfVL+of9H8ov1F94v+F8Mvxl9Mv5h/sfxi/cX2i/0Xxy/OX1y/uH/x/OL9xfeL/5fAL8FfQr+Ef4n8Ev0l9kv8l8QvyV9Sv6R/yfyS/SX3S/6Xwi/FX0q/lH+p/FL9pfZL/ZfGL81fWr+0f+n80v2l90v/l8Evw19Gv4x/mfwy/WX2y/yXxS/LX1a/rH/Z/LL9ZffL/pfDL8dfTr+cf7n8cv3l9sv9l8cvz19ev7x/+fzy/eX/C8zFvg07Syf2nPIcsiOngV+nbI2tgI8pkTgz1Fyha7RS9KF9fabdyVf9oBQz1oWOcD2DbLNVJRCc6F4GB2xs4TvKHcHnVfvsApPphYigExM7X3APO+nahdpN/iN+9+9ZtSpldtDHihjPtzBzAxv3qZ2nZaLBj3mDmO1KIk1X2zqKNno55uzqRkc6bBIH23PHmnPVinSWkCxrlcytGGtfJXrQqeUi1JkFmZGRNnTOtbTmcqtbEG8IOAqZDFEMPpR6ebnsQDMI3MGPvuwBwdfX3FtxFzmua1Q25GLmiWRLQH2rLXo1cgUVYVWC4Tlx3LBRAS3OP6+1Z/IFJ7rMHiupQXFciW6zRPrzvGOBMc1Is140+5nHInjYiWqBLdDw6DiYZel382vaaKN8gF4dLDLbxU7CA2YM8Wmb7DX9gj73QxWIB+KHFhGxS1UNzn6945PB1C42Q7HJWDlPtpP2CDVNquDFm3HBbDHVdLQ/T9qttDwaE3XSN0AimYLmlArrEsnNXEVVUlIbE4OO2RL5APrS4J0VYkWM28rlCbD+0guSmiIiwqKDE7jEP4j/EMazF0vWd/UkbSjwlNzZMsxSU/BydZLvvf/BKRQpgm7Q616+wSA6v9hVDGyew7dw9FY95xWWAl8NYqXhslID7bhPw90mI43UdKQ+0UpQOGBIeuZ7prpUtCZxhX7cZBzmynCHCMPJWUl1uUqB1sksaRMZG/W640c5iO8qUYPixjBfjxLflzEU8A1Gzy1orDp4w3DX2Eee/GyGJt3ldbHEyv37EcLiDzPYGjBtlGsYgLeYZnTquLeW3ZpjIMS7si2pskV4UxnkJa+xz8HUFkBFwzoq8twdnqWziJh2nCXtBAEUXsqoMGpro55yr/f2nUhKkHC8INbSUmOJq3SIq5mY+g2l1a/WiknLHVvtF8suNbYxugLEF6+fpYWfzEHulXcNH4fuQW6MmqezcE+Rlrhwz3eXl2ipTcaDq4W7QW715LFwT5lJQndNb+qc1pNcs+9lDOlNVgJU+14dnOJZnirFoywb9TxUDVoki/hCDhd4RnEoGPO+ytkjCPJeQs/+iSYGkqkKniRVBX0byRFax/t12WY1SVy6FpOyBqlyc1FDwUdv+w/vcAV5qtQTgupKMVK32RUENuK5a2bHy7pRDV0AdRIdeYRgV5o9tN0nUyRzreZPpHll1PiArC3r1Qxv0ch5AwUNK4lIYXP6CaYZMQThgLUgTGt2CS4dXi8NIlj4jvo4Rj/ACmZ3Dxgmg/b9A331lHHJAlgt3OrFcYluSIMzfIMx6rapTQ71rxQKpfc0Aj0nhIdXeFaw7P2LHTGKiKKUg9fZhwpd5Hoso9X+KRstJFp+m75hBFZrLwy7NBHa7sKsl3w/3416/UNbNKoSqxJRKEhF3OhQzsqt2xsUZREK6HOUlc5rErpJaEJiShJJNUQHdNWtnsbwuuQdd+JFZ/Q1jwY3j3dONpawLaqUfLHBv8ix/PqQiGMNhMNMCxnfJUavcsltIn+xbHTFS57mnrLGRxEaUVgPQUtqGdnvNiPMuLsP+l/xBczKH7Iws3kiJ60ZJafBTOdeEqaVoSRN0jW3LKLL3N5bAlm82pS9M820x3SwbOgVMhk8ms/xu/QKaPW84dK79gfXFjSErRKZ54xSnMDmkwi3CCYM4CNvpPOA1BmAqkVUgzWoh3eVtgBXndkWuYJag88HQEILiWwH+Qai2pXRgO55qoSrStypWVMa0zRNA5i/1Jm5/2REdfnC9mgFGaDEkJlT4sgAJZPw3Cb2w7hFRyZi9334JJznj8XAX5Zds0aiuRCuuZblcRbI1a/+VDUU7SCb+9O49k9mtTrXciLFsXVB9wc4ht+gsqJW1sa/L67aMG1injOkMqFyvZZNZ7MgAe2bGh7QrxWP1pECtUxNrpulv44zaGPhLDbN3a1HAFkL57SqJKrUySGN4S+9SRh3qzGwMFdCMkj4twwqY3Zute3YwjoXel8tjixHe8p4s9noRr/WePLOCVTPMxnlU6gVqhDVXuVzd53ZBFRf94HX0PlCLFsWkL3PivsAGHYibGcsgUqc8Rj8GS/3JnVOyGDBO/vQBh1Tzr2Mp92N6LVYvjEE00+0cfEtt+938U1HTGqCselh1clgqSqkpNs+IGhWDvar82Ya/rJ6LUMnXMrxyZqMh+/f0ubpPbu2xg7zifFRL12OFxKXGNJyxo1XlMQd/YB0hs22sxyYiJZIlgsAvtxRNgYDufvQj1H/qHIbB19BckwYnwa1NlXep9tLMFJvHBogtsUowBjcD0vVIzbcbL3e9/4pY2n0gDaFesdnRGiAx2ilu0sX2ouk3994/xH1omTcH2x5Ehh8uWtJf5UaGzQlAxlUTicqBWsCt9Q9vGi1t+jkkVQfOI1TUgUMqxiXXDTG5NeG23LUOZeIlFfFlF/x9aHLaMdsO3b0Px9TlNqJ90aSZs46UYPfn7P999IJn3+z8c+xjkpooL0QCraHyMEB5pLXME0kXNQVinByGbBoO6p8jNNLKkOgJoOrujlF7GFdv+1NzPCKhncylI7w4D3pXafo26z1nO7EcPxw1sCoOHOPSx2Ra93DfuxOGUn8dAnSFZ7FgIzfXvjnL4016flB76FCRnVy8b4kcOFy+mK5/62VI0+TExRocGT75BzPIjikiTzcfh1SSdOp8XreKWetLQ6FO5lMR5D74ab16LqTUMiqSRkU9d44IQnleIypYroBzICpaixgC3IMPVGBlR528EgXhCrUVJefrOTymcGQh8Vpi8Z3HTKBPVxmfmLctbbXxU2J8dT4WJ4N47gAGCiaXI+aJ++7bmmUmjHUDM2oTFbXHP2fmKoasZfKzbxF60Cc3jY2fXThoby/T60p5/fTKWCx5N51sp5bj3WPNcrWdtyBg6f8eytWXXRmTKpeah9lw8lVCliD9cFvDgj6nzhC6LwpNAvMXuV2NI0u1LtOoQOiCEPn2pLlhzRcR1AzURrWaDmJXud9WTDlV6/jeZbEfrrb2BxdxHGSPzpYaUI/2+i1sz2MQBiPNwZasUVtlTVpmRsv4LxxvsCsof/gQXYzBD9NAHvehH0W+mx1IliB2yxDEXYWLCxVqMxBgnVcAMc3iAUdx1vsaAOCsg0+MtDb12m4JCDLAKu7PCpvKoqyPE7PH5Grc6/5r+ckEh19W/L0OOM9i6TLCsFRixg0y34jA+osaDXRzFxh899CqwpmuhSYba561XFE8sLREql1tar+3zz2GXkx6AqWJQeVgOBIscyaepCfEoFyjTs8iTPwk+8Ebn/JxXrQoaU1OxFGsGJU1ZN9RY1eDXktY1jc+SJUxrPGMZuRSi7cQN0CitsiI6kwuKR/
*/
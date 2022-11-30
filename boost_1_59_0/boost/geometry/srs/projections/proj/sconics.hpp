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

#ifndef BOOST_GEOMETRY_PROJECTIONS_SCONICS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_SCONICS_HPP


#include <boost/geometry/util/math.hpp>
#include <boost/math/special_functions/hypot.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace sconics
    {

            enum proj_type {
                proj_euler  = 0,
                proj_murd1  = 1,
                proj_murd2  = 2,
                proj_murd3  = 3,
                proj_pconic = 4,
                proj_tissot = 5,
                proj_vitk1  = 6
            };
            static const double epsilon10 = 1.e-10;
            static const double epsilon = 1e-10;

            template <typename T>
            struct par_sconics
            {
                T   n;
                T   rho_c;
                T   rho_0;
                T   sig;
                T   c1, c2;
                proj_type type;
            };

            /* get common factors for simple conics */
            template <typename Params, typename T>
            inline int phi12(Params const& params, par_sconics<T>& proj_parm, T *del)
            {
                T p1, p2;
                int err = 0;

                if (!pj_param_r<srs::spar::lat_1>(params, "lat_1", srs::dpar::lat_1, p1) ||
                    !pj_param_r<srs::spar::lat_2>(params, "lat_2", srs::dpar::lat_2, p2)) {
                    err = -41;
                } else {
                    //p1 = pj_get_param_r(par.params, "lat_1"); // set above
                    //p2 = pj_get_param_r(par.params, "lat_2"); // set above
                    *del = 0.5 * (p2 - p1);
                    proj_parm.sig = 0.5 * (p2 + p1);
                    err = (fabs(*del) < epsilon || fabs(proj_parm.sig) < epsilon) ? -42 : 0;
                }
                return err;
            }

            template <typename T, typename Parameters>
            struct base_sconics_spheroid
            {
                par_sconics<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T rho;

                    switch (this->m_proj_parm.type) {
                    case proj_murd2:
                        rho = this->m_proj_parm.rho_c + tan(this->m_proj_parm.sig - lp_lat);
                        break;
                    case proj_pconic:
                        rho = this->m_proj_parm.c2 * (this->m_proj_parm.c1 - tan(lp_lat - this->m_proj_parm.sig));
                        break;
                    default:
                        rho = this->m_proj_parm.rho_c - lp_lat;
                        break;
                    }
                    xy_x = rho * sin( lp_lon *= this->m_proj_parm.n );
                    xy_y = this->m_proj_parm.rho_0 - rho * cos(lp_lon);
                }

                // INVERSE(s_inverse)  ellipsoid & spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    T rho;

                    rho = boost::math::hypot(xy_x, xy_y = this->m_proj_parm.rho_0 - xy_y);
                    if (this->m_proj_parm.n < 0.) {
                        rho = - rho;
                        xy_x = - xy_x;
                        xy_y = - xy_y;
                    }

                    lp_lon = atan2(xy_x, xy_y) / this->m_proj_parm.n;

                    switch (this->m_proj_parm.type) {
                    case proj_pconic:
                        lp_lat = atan(this->m_proj_parm.c1 - rho / this->m_proj_parm.c2) + this->m_proj_parm.sig;
                        break;
                    case proj_murd2:
                        lp_lat = this->m_proj_parm.sig - atan(rho - this->m_proj_parm.rho_c);
                        break;
                    default:
                        lp_lat = this->m_proj_parm.rho_c - rho;
                    }
                }

                static inline std::string get_name()
                {
                    return "sconics_spheroid";
                }

            };

            template <typename Params, typename Parameters, typename T>
            inline void setup(Params const& params, Parameters& par, par_sconics<T>& proj_parm, proj_type type) 
            {
                static const T half_pi = detail::half_pi<T>();

                T del, cs;
                int err;

                proj_parm.type = type;

                err = phi12(params, proj_parm, &del);
                if(err)
                    BOOST_THROW_EXCEPTION( projection_exception(err) );

                switch (proj_parm.type) {
                case proj_tissot:
                    proj_parm.n = sin(proj_parm.sig);
                    cs = cos(del);
                    proj_parm.rho_c = proj_parm.n / cs + cs / proj_parm.n;
                    proj_parm.rho_0 = sqrt((proj_parm.rho_c - 2 * sin(par.phi0))/proj_parm.n);
                    break;
                case proj_murd1:
                    proj_parm.rho_c = sin(del)/(del * tan(proj_parm.sig)) + proj_parm.sig;
                    proj_parm.rho_0 = proj_parm.rho_c - par.phi0;
                    proj_parm.n = sin(proj_parm.sig);
                    break;
                case proj_murd2:
                    proj_parm.rho_c = (cs = sqrt(cos(del))) / tan(proj_parm.sig);
                    proj_parm.rho_0 = proj_parm.rho_c + tan(proj_parm.sig - par.phi0);
                    proj_parm.n = sin(proj_parm.sig) * cs;
                    break;
                case proj_murd3:
                    proj_parm.rho_c = del / (tan(proj_parm.sig) * tan(del)) + proj_parm.sig;
                    proj_parm.rho_0 = proj_parm.rho_c - par.phi0;
                    proj_parm.n = sin(proj_parm.sig) * sin(del) * tan(del) / (del * del);
                    break;
                case proj_euler:
                    proj_parm.n = sin(proj_parm.sig) * sin(del) / del;
                    del *= 0.5;
                    proj_parm.rho_c = del / (tan(del) * tan(proj_parm.sig)) + proj_parm.sig;
                    proj_parm.rho_0 = proj_parm.rho_c - par.phi0;
                    break;
                case proj_pconic:
                    proj_parm.n = sin(proj_parm.sig);
                    proj_parm.c2 = cos(del);
                    proj_parm.c1 = 1./tan(proj_parm.sig);
                    if (fabs(del = par.phi0 - proj_parm.sig) - epsilon10 >= half_pi)
                        BOOST_THROW_EXCEPTION( projection_exception(error_lat_0_half_pi_from_mean) );
                    proj_parm.rho_0 = proj_parm.c2 * (proj_parm.c1 - tan(del));
                    break;
                case proj_vitk1:
                    proj_parm.n = (cs = tan(del)) * sin(proj_parm.sig) / del;
                    proj_parm.rho_c = del / (cs * tan(proj_parm.sig)) + proj_parm.sig;
                    proj_parm.rho_0 = proj_parm.rho_c - par.phi0;
                    break;
                }

                par.es = 0;
            }


            // Euler
            template <typename Params, typename Parameters, typename T>
            inline void setup_euler(Params const& params, Parameters& par, par_sconics<T>& proj_parm)
            {
                setup(params, par, proj_parm, proj_euler);
            }

            // Tissot
            template <typename Params, typename Parameters, typename T>
            inline void setup_tissot(Params const& params, Parameters& par, par_sconics<T>& proj_parm)
            {
                setup(params, par, proj_parm, proj_tissot);
            }

            // Murdoch I
            template <typename Params, typename Parameters, typename T>
            inline void setup_murd1(Params const& params, Parameters& par, par_sconics<T>& proj_parm)
            {
                setup(params, par, proj_parm, proj_murd1);
            }

            // Murdoch II
            template <typename Params, typename Parameters, typename T>
            inline void setup_murd2(Params const& params, Parameters& par, par_sconics<T>& proj_parm)
            {
                setup(params, par, proj_parm, proj_murd2);
            }

            // Murdoch III
            template <typename Params, typename Parameters, typename T>
            inline void setup_murd3(Params const& params, Parameters& par, par_sconics<T>& proj_parm)
            {
                setup(params, par, proj_parm, proj_murd3);
            }            

            // Perspective Conic
            template <typename Params, typename Parameters, typename T>
            inline void setup_pconic(Params const& params, Parameters& par, par_sconics<T>& proj_parm)
            {
                setup(params, par, proj_parm, proj_pconic);
            }

            // Vitkovsky I
            template <typename Params, typename Parameters, typename T>
            inline void setup_vitk1(Params const& params, Parameters& par, par_sconics<T>& proj_parm)
            {
                setup(params, par, proj_parm, proj_vitk1);
            }

    }} // namespace detail::sconics
    #endif // doxygen
    
    /*!
        \brief Tissot projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel
         - lat_2: Latitude of second standard parallel
        \par Example
        \image html ex_tissot.gif
    */
    template <typename T, typename Parameters>
    struct tissot_spheroid : public detail::sconics::base_sconics_spheroid<T, Parameters>
    {
        template <typename Params>
        inline tissot_spheroid(Params const& params, Parameters& par)
        {
            detail::sconics::setup_tissot(params, par, this->m_proj_parm);
        }
    };

    /*!
        \brief Murdoch I projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel
         - lat_2: Latitude of second standard parallel
        \par Example
        \image html ex_murd1.gif
    */
    template <typename T, typename Parameters>
    struct murd1_spheroid : public detail::sconics::base_sconics_spheroid<T, Parameters>
    {
        template <typename Params>
        inline murd1_spheroid(Params const& params, Parameters& par)
        {
            detail::sconics::setup_murd1(params, par, this->m_proj_parm);
        }
    };

    /*!
        \brief Murdoch II projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel
         - lat_2: Latitude of second standard parallel
        \par Example
        \image html ex_murd2.gif
    */
    template <typename T, typename Parameters>
    struct murd2_spheroid : public detail::sconics::base_sconics_spheroid<T, Parameters>
    {
        template <typename Params>
        inline murd2_spheroid(Params const& params, Parameters& par)
        {
            detail::sconics::setup_murd2(params, par, this->m_proj_parm);
        }
    };

    /*!
        \brief Murdoch III projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel
         - lat_2: Latitude of second standard parallel
        \par Example
        \image html ex_murd3.gif
    */
    template <typename T, typename Parameters>
    struct murd3_spheroid : public detail::sconics::base_sconics_spheroid<T, Parameters>
    {
        template <typename Params>
        inline murd3_spheroid(Params const& params, Parameters& par)
        {
            detail::sconics::setup_murd3(params, par, this->m_proj_parm);
        }
    };

    /*!
        \brief Euler projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel
         - lat_2: Latitude of second standard parallel
        \par Example
        \image html ex_euler.gif
    */
    template <typename T, typename Parameters>
    struct euler_spheroid : public detail::sconics::base_sconics_spheroid<T, Parameters>
    {
        template <typename Params>
        inline euler_spheroid(Params const& params, Parameters& par)
        {
            detail::sconics::setup_euler(params, par, this->m_proj_parm);
        }
    };

    /*!
        \brief Perspective Conic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel
         - lat_2: Latitude of second standard parallel
        \par Example
        \image html ex_pconic.gif
    */
    template <typename T, typename Parameters>
    struct pconic_spheroid : public detail::sconics::base_sconics_spheroid<T, Parameters>
    {
        template <typename Params>
        inline pconic_spheroid(Params const& params, Parameters& par)
        {
            detail::sconics::setup_pconic(params, par, this->m_proj_parm);
        }
    };

    /*!
        \brief Vitkovsky I projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel
         - lat_2: Latitude of second standard parallel
        \par Example
        \image html ex_vitk1.gif
    */
    template <typename T, typename Parameters>
    struct vitk1_spheroid : public detail::sconics::base_sconics_spheroid<T, Parameters>
    {
        template <typename Params>
        inline vitk1_spheroid(Params const& params, Parameters& par)
        {
            detail::sconics::setup_vitk1(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_euler, euler_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_murd1, murd1_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_murd2, murd2_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_murd3, murd3_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_pconic, pconic_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_tissot, tissot_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_vitk1, vitk1_spheroid)
        
        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(euler_entry, euler_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(murd1_entry, murd1_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(murd2_entry, murd2_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(murd3_entry, murd3_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(pconic_entry, pconic_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(tissot_entry, tissot_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(vitk1_entry, vitk1_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(sconics_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(euler, euler_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(murd1, murd1_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(murd2, murd2_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(murd3, murd3_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(pconic, pconic_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(tissot, tissot_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(vitk1, vitk1_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_SCONICS_HPP


/* sconics.hpp
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
*/
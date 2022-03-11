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
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
TAv448cQ0F8LOAqxdNECuu0z5qFToQRHgbsIXCm4anB3gHsI3CvgNoF7e8AP462tsC+28nPVHPlKgU8o0yTLNVxFyCPPCRMT5270iCf9oTnGvUXNsXawaA5UU7NKugplm2TkeCxer5N2uRz14zCbx85mqWzVqF53nMwru+4p9CVtTvfG3F47d4LKfYIHF3flEI3c0k7RVqUYhPDnuA9AW1+m7dBY2v5hIW0yL5sJn3kGAwJKibbj+ZPZrLpvNVqRNJjizSejTArnIpb3RFS+w05gAvAAIrKdXUCvyh7E7CsFM80P3fRFRHtTfaAjzOQB9bzIHIhQ25f05j8KeBsFPEyrDozuALAIQc/PaDORKhPHq8TPYGJq6Y42LJ+KXoaT2jlu1dL5VH+UvqudPk6lv8ItygT7gYMo0yAuTN9my9QN6fgT+LhYgxjH+E+pWF1ji/Uh/vcAp3cuGayh+WZ2K3vtrS6sKNVFusT0ifCM8JgDRU8MH4LAk+24dioOrIa1lboVXLTGvU2kw9aBlTKm/gO3UJ9jmnvVFuqppyyXMP+VBtYNOoE5iyxwS8G9AG4aDP8jwJ0+mP2vDuS/0S486MfnZ/9rP93+wSetWEt0Tpwb1iwePPIGMeSsDMGQxSSf3F72ALLbx2eRT4AvNn6ZsbCkK6bUYTvKpB1IO1N+dVQZp1DG6NB8R3DuEgUu0QCX5DKT18BFxCQYeUYChsxHrNGhew6wcirpZ1JS5zEK1smgpDOBVBpD0aHha4zVVB+ZwE1qQjzlp7zXFOHEJ8qT0lwjV0oM/eF+4d5OoF58V4BSS4jE3q5zhnrJzQY3MiPW3aqF7wMTTSXw/Sq498GNg+8J4NAE1MZhP59xGfO+NPRz9axstds+mqX2H7JZROSgqLM18rxbwk1R5zGdn7Ra9z5LAWflXM+td84Vha4/57GxLZL5WtYnCX2k4ZvQOnzrPorC17f1+Ep1fAM3WK167+bojw62Ps38npj8VU8cKD/neqWBcoWON9I6wV/REA3/yvUHQ9/5MflD66zWvwfVvyG6/de1pj0KqP1DlFe/UJ+Vrp6XiF4B4cLeMSZVLvNZ5NwO1wy89m3L/K+zZcMkGUAZyvvktRhPSYEeiRVRKK3tlnyAW1R+YM5qx+/l78X1RSYJfdWd4DMft2Dd4yY1GTUJhUcjUUQJq/cmMIQX30cI15kQuiOEU90moZKMulqhlRtNaFCm2LXRwgIRRr75fkQNLin3dKpo7FRM9Hdh7HmE/UGXgf3O3wP2N5E7ZzMEC19ZYQidKxo7M/3dGUJbgnC/CeEMgECKtFz7OZB/JOfvU9HYp3gg5u8jyv8e5l/jMssP+cOnY2ZGnms3Nd/5xKmOZOZZ+UJmns7griVwuSa4Fx8DcELI3BWl41madHzbX35imfhP+dP2vqv36nvf2mzamw2R+wf8hNmFjqq6xgSW+vgKzyMux70jN8IEYy8irrJjQHW2baR7EfkrtvjxuHrIi3hZdukGGsZffU0sAUz/bN5hyduaR9mkIKYeoPNOzyj0xSYFTYyItJ3Bq/tv9tIItI+KDvL6fIs/47xS1uxv3m+Keb8Q7qFSH2wb+3wqrndQZ49JXgTdi+67cQ2PkoNa3i3sr2694/Ed/I/ZCkLTGyORMfB13XlQryLsZgijekelQTebs2UkI+Awg8z+16rWI87FypkLkCnIK8t+PojyyHvMheFKPu0bA/7Eygre+w2FbX0UqPkdnn3G62oBGOWpKduDOvJlpGPjAGd76+AEKJBvXP/Y7dzan9Ef5Ew17l3ZH7LV+0f2ffS1NPAuZOYyaI84ehPa+PZLcspeDHcbHkDTEJU/D08t+TVRlTE=
*/
// Boost.Geometry - gis-projections (based on PROJ4)

// Copyright (c) 2008-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020, Oracle and/or its affiliates.
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

#ifndef BOOST_GEOMETRY_PROJECTIONS_OB_TRAN_HPP
#define BOOST_GEOMETRY_PROJECTIONS_OB_TRAN_HPP

#include <type_traits>

#include <boost/geometry/util/math.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/geometry/core/static_assert.hpp>

#include <boost/geometry/srs/projections/impl/aasincos.hpp>
#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_ell_set.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail {
    
        // fwd declaration needed below
        template <typename T>
        inline detail::dynamic_wrapper_b<T, projections::parameters<T> >*
            create_new(srs::detail::proj4_parameters const& params,
                       projections::parameters<T> const& parameters);

        template <typename T>
        inline detail::dynamic_wrapper_b<T, projections::parameters<T> >*
            create_new(srs::dpar::parameters<T> const& params,
                       projections::parameters<T> const& parameters);

    } // namespace detail

    namespace detail { namespace ob_tran
    {

            static const double tolerance = 1e-10;

            template <typename Parameters>
            inline Parameters o_proj_parameters(srs::detail::proj4_parameters const& params,
                                                Parameters const& par)
            {
                /* copy existing header into new */
                Parameters pj = par;

                /* get name of projection to be translated */
                pj.id = pj_get_param_s(params, "o_proj");
                if (pj.id.is_unknown())
                    BOOST_THROW_EXCEPTION( projection_exception(error_no_rotation_proj) );

                /* avoid endless recursion */
                if( pj.id.name == "ob_tran")
                    BOOST_THROW_EXCEPTION( projection_exception(error_failed_to_find_proj) );

                // Commented out for consistency with Proj4 >= 5.0.0
                /* force spherical earth */
                //pj.one_es = pj.rone_es = 1.;
                //pj.es = pj.e = 0.;

                return pj;
            }

            template <typename T, typename Parameters>
            inline Parameters o_proj_parameters(srs::dpar::parameters<T> const& params,
                                                Parameters const& par)
            {
                /* copy existing header into new */
                Parameters pj = par;

                /* get name of projection to be translated */
                typename srs::dpar::parameters<T>::const_iterator
                    it = pj_param_find(params, srs::dpar::o_proj);
                if (it != params.end())
                    pj.id = static_cast<srs::dpar::value_proj>(it->template get_value<int>());
                else
                    BOOST_THROW_EXCEPTION( projection_exception(error_no_rotation_proj) );

                /* avoid endless recursion */
                if( pj.id.id == srs::dpar::proj_ob_tran)
                    BOOST_THROW_EXCEPTION( projection_exception(error_failed_to_find_proj) );

                // Commented out for consistency with Proj4 >= 5.0.0
                /* force spherical earth */
                //pj.one_es = pj.rone_es = 1.;
                //pj.es = pj.e = 0.;

                return pj;
            }

            template <typename ...Ps, typename Parameters>
            inline Parameters o_proj_parameters(srs::spar::parameters<Ps...> const& /*params*/,
                                                Parameters const& par)
            {
                /* copy existing header into new */
                Parameters pj = par;

                /* get name of projection to be translated */
                typedef srs::spar::parameters<Ps...> params_type;
                typedef typename geometry::tuples::find_if
                    <
                        params_type,
                        srs::spar::detail::is_param_t<srs::spar::o_proj>::pred
                    >::type o_proj_type;

                static const bool is_found = geometry::tuples::is_found<o_proj_type>::value;
                BOOST_GEOMETRY_STATIC_ASSERT((is_found),
                    "Rotation projection not specified.",
                    params_type);

                typedef typename o_proj_type::type proj_type;
                static const bool is_specialized = srs::spar::detail::proj_traits<proj_type>::is_specialized;
                BOOST_GEOMETRY_STATIC_ASSERT((is_specialized),
                    "Rotation projection not specified.",
                    params_type);

                pj.id = srs::spar::detail::proj_traits<proj_type>::id;

                /* avoid endless recursion */
                static const bool is_non_resursive = ! std::is_same<proj_type, srs::spar::proj_ob_tran>::value;
                BOOST_GEOMETRY_STATIC_ASSERT((is_non_resursive),
                    "o_proj parameter can not be set to ob_tran projection.",
                    params_type);

                // Commented out for consistency with Proj4 >= 5.0.0
                /* force spherical earth */
                //pj.one_es = pj.rone_es = 1.;
                //pj.es = pj.e = 0.;

                return pj;
            }

            // TODO: It's possible that the original Parameters could be used
            // instead of a copy in link.
            // But it's not possible with the current implementation of
            // dynamic_wrapper_b always storing params

            template <typename T, typename Parameters>
            struct par_ob_tran
            {
                template <typename Params>
                par_ob_tran(Params const& params, Parameters const& par)
                    : link(projections::detail::create_new(params, o_proj_parameters(params, par)))
                {
                    if (! link.get())
                        BOOST_THROW_EXCEPTION( projection_exception(error_unknown_projection_id) );
                }

                inline void fwd(T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    link->fwd(link->params(), lp_lon, lp_lat, xy_x, xy_y);
                }

                inline void inv(T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    link->inv(link->params(), xy_x, xy_y, lp_lon, lp_lat);
                }

                boost::shared_ptr<dynamic_wrapper_b<T, Parameters> > link;
                T lamp;
                T cphip, sphip;
            };

            template <typename StaticParameters, typename T, typename Parameters>
            struct par_ob_tran_static
            {
                // this metafunction handles static error handling
                typedef typename srs::spar::detail::pick_o_proj_tag
                    <
                        StaticParameters
                    >::type o_proj_tag;

                /* avoid endless recursion */
                static const bool is_o_proj_not_ob_tran = ! std::is_same<o_proj_tag, srs::spar::proj_ob_tran>::value;
                BOOST_GEOMETRY_STATIC_ASSERT((is_o_proj_not_ob_tran),
                    "o_proj parameter can not be set to ob_tran projection.",
                    StaticParameters);

                typedef typename projections::detail::static_projection_type
                    <
                        o_proj_tag,
                        // Commented out for consistency with Proj4 >= 5.0.0
                        //srs_sphere_tag, // force spherical
                        typename projections::detail::static_srs_tag<StaticParameters>::type,
                        StaticParameters,
                        T,
                        Parameters
                    >::type projection_type;

                par_ob_tran_static(StaticParameters const& params, Parameters const& par)
                    : link(params, o_proj_parameters(params, par))
                {}

                inline void fwd(T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    link.fwd(link.params(), lp_lon, lp_lat, xy_x, xy_y);
                }

                inline void inv(T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    link.inv(link.params(), xy_x, xy_y, lp_lon, lp_lat);
                }

                projection_type link;
                T lamp;
                T cphip, sphip;
            };

            template <typename T, typename Par>
            inline void o_forward(T lp_lon, T lp_lat, T& xy_x, T& xy_y, Par const& proj_parm)
            {
                T coslam, sinphi, cosphi;
                
                coslam = cos(lp_lon);
                sinphi = sin(lp_lat);
                cosphi = cos(lp_lat);
                lp_lon = adjlon(aatan2(cosphi * sin(lp_lon), proj_parm.sphip * cosphi * coslam +
                    proj_parm.cphip * sinphi) + proj_parm.lamp);
                lp_lat = aasin(proj_parm.sphip * sinphi - proj_parm.cphip * cosphi * coslam);

                proj_parm.fwd(lp_lon, lp_lat, xy_x, xy_y);
            }

            template <typename T, typename Par>
            inline void o_inverse(T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat, Par const& proj_parm)
            {
                T coslam, sinphi, cosphi;

                proj_parm.inv(xy_x, xy_y, lp_lon, lp_lat);
                if (lp_lon != HUGE_VAL) {
                    coslam = cos(lp_lon -= proj_parm.lamp);
                    sinphi = sin(lp_lat);
                    cosphi = cos(lp_lat);
                    lp_lat = aasin(proj_parm.sphip * sinphi + proj_parm.cphip * cosphi * coslam);
                    lp_lon = aatan2(cosphi * sin(lp_lon), proj_parm.sphip * cosphi * coslam -
                        proj_parm.cphip * sinphi);
                }
            }

            template <typename T, typename Par>
            inline void t_forward(T lp_lon, T lp_lat, T& xy_x, T& xy_y, Par const& proj_parm)
            {
                T cosphi, coslam;

                cosphi = cos(lp_lat);
                coslam = cos(lp_lon);
                lp_lon = adjlon(aatan2(cosphi * sin(lp_lon), sin(lp_lat)) + proj_parm.lamp);
                lp_lat = aasin(- cosphi * coslam);

                proj_parm.fwd(lp_lon, lp_lat, xy_x, xy_y);
            }

            template <typename T, typename Par>
            inline void t_inverse(T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat, Par const& proj_parm)
            {
                T cosphi, t;

                proj_parm.inv(xy_x, xy_y, lp_lon, lp_lat);
                if (lp_lon != HUGE_VAL) {
                    cosphi = cos(lp_lat);
                    t = lp_lon - proj_parm.lamp;
                    lp_lon = aatan2(cosphi * sin(t), - sin(lp_lat));
                    lp_lat = aasin(cosphi * cos(t));
                }
            }

            // General Oblique Transformation
            template <typename T, typename Params, typename Parameters, typename ProjParameters>
            inline T setup_ob_tran(Params const& params, Parameters & /*par*/, ProjParameters& proj_parm)
            {
                static const T half_pi = detail::half_pi<T>();

                T phip, alpha;

                // Commented out for consistency with Proj4 >= 5.0.0
                //par.es = 0.; /* force to spherical */

                // proj_parm.link should be created at this point

                if (pj_param_r<srs::spar::o_alpha>(params, "o_alpha", srs::dpar::o_alpha, alpha)) {
                    T lamc, phic;

                    lamc    = pj_get_param_r<T, srs::spar::o_lon_c>(params, "o_lon_c", srs::dpar::o_lon_c);
                    phic    = pj_get_param_r<T, srs::spar::o_lon_c>(params, "o_lat_c", srs::dpar::o_lat_c);
                    //alpha   = pj_get_param_r(par.params, "o_alpha");
            
                    if (fabs(fabs(phic) - half_pi) <= tolerance)
                        BOOST_THROW_EXCEPTION( projection_exception(error_lat_0_or_alpha_eq_90) );

                    proj_parm.lamp = lamc + aatan2(-cos(alpha), -sin(alpha) * sin(phic));
                    phip = aasin(cos(phic) * sin(alpha));
                } else if (pj_param_r<srs::spar::o_lat_p>(params, "o_lat_p", srs::dpar::o_lat_p, phip)) { /* specified new pole */
                    proj_parm.lamp = pj_get_param_r<T, srs::spar::o_lon_p>(params, "o_lon_p", srs::dpar::o_lon_p);
                    //phip = pj_param_r(par.params, "o_lat_p");
                } else { /* specified new "equator" points */
                    T lam1, lam2, phi1, phi2, con;

                    lam1 = pj_get_param_r<T, srs::spar::o_lon_1>(params, "o_lon_1", srs::dpar::o_lon_1);
                    phi1 = pj_get_param_r<T, srs::spar::o_lat_1>(params, "o_lat_1", srs::dpar::o_lat_1);
                    lam2 = pj_get_param_r<T, srs::spar::o_lon_2>(params, "o_lon_2", srs::dpar::o_lon_2);
                    phi2 = pj_get_param_r<T, srs::spar::o_lat_2>(params, "o_lat_2", srs::dpar::o_lat_2);
                    if (fabs(phi1 - phi2) <= tolerance || (con = fabs(phi1)) <= tolerance ||
                        fabs(con - half_pi) <= tolerance || fabs(fabs(phi2) - half_pi) <= tolerance)
                        BOOST_THROW_EXCEPTION( projection_exception(error_lat_1_or_2_zero_or_90) );

                    proj_parm.lamp = atan2(cos(phi1) * sin(phi2) * cos(lam1) -
                        sin(phi1) * cos(phi2) * cos(lam2),
                        sin(phi1) * cos(phi2) * sin(lam2) -
                        cos(phi1) * sin(phi2) * sin(lam1));
                    phip = atan(-cos(proj_parm.lamp - lam1) / tan(phi1));
                }

                if (fabs(phip) > tolerance) { /* oblique */
                    proj_parm.cphip = cos(phip);
                    proj_parm.sphip = sin(phip);
                } else { /* transverse */
                }

                // TODO:
                /* Support some rather speculative test cases, where the rotated projection */
                /* is actually latlong. We do not want scaling in that case... */
                //if (proj_parm.link...mutable_parameters().right==PJ_IO_UNITS_ANGULAR)
                //    par.right = PJ_IO_UNITS_PROJECTED;

                // return phip to choose model
                return phip;
            }

            template <typename T, typename Parameters>
            struct base_ob_tran_oblique
            {
                par_ob_tran<T, Parameters> m_proj_parm;

                inline base_ob_tran_oblique(par_ob_tran<T, Parameters> const& proj_parm)
                    : m_proj_parm(proj_parm)
                {}

                // FORWARD(o_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    // NOTE: Parameters ignored, m_proj_parm.link has a copy
                    o_forward(lp_lon, lp_lat, xy_x, xy_y, this->m_proj_parm);
                }

                // INVERSE(o_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    // NOTE: Parameters ignored, m_proj_parm.link has a copy
                    o_inverse(xy_x, xy_y, lp_lon, lp_lat, this->m_proj_parm);
                }

                static inline std::string get_name()
                {
                    return "ob_tran_oblique";
                }

            };

            template <typename T, typename Parameters>
            struct base_ob_tran_transverse
            {
                par_ob_tran<T, Parameters> m_proj_parm;

                inline base_ob_tran_transverse(par_ob_tran<T, Parameters> const& proj_parm)
                    : m_proj_parm(proj_parm)
                {}

                // FORWARD(t_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    // NOTE: Parameters ignored, m_proj_parm.link has a copy
                    t_forward(lp_lon, lp_lat, xy_x, xy_y, this->m_proj_parm);
                }

                // INVERSE(t_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    // NOTE: Parameters ignored, m_proj_parm.link has a copy
                    t_inverse(xy_x, xy_y, lp_lon, lp_lat, this->m_proj_parm);
                }

                static inline std::string get_name()
                {
                    return "ob_tran_transverse";
                }

            };

            template <typename StaticParameters, typename T, typename Parameters>
            struct base_ob_tran_static
            {
                par_ob_tran_static<StaticParameters, T, Parameters> m_proj_parm;
                bool m_is_oblique;

                inline base_ob_tran_static(StaticParameters const& params, Parameters const& par)
                    : m_proj_parm(params, par)
                {}

                // FORWARD(o_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    // NOTE: Parameters ignored, m_proj_parm.link has a copy
                    if (m_is_oblique) {
                        o_forward(lp_lon, lp_lat, xy_x, xy_y, this->m_proj_parm);
                    } else {
                        t_forward(lp_lon, lp_lat, xy_x, xy_y, this->m_proj_parm);
                    }
                }

                // INVERSE(o_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    // NOTE: Parameters ignored, m_proj_parm.link has a copy
                    if (m_is_oblique) {
                        o_inverse(xy_x, xy_y, lp_lon, lp_lat, this->m_proj_parm);
                    } else {
                        t_inverse(xy_x, xy_y, lp_lon, lp_lat, this->m_proj_parm);
                    }
                }

                static inline std::string get_name()
                {
                    return "ob_tran";
                }

            };

    }} // namespace detail::ob_tran
    #endif // doxygen

    /*!
        \brief General Oblique Transformation projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
        \par Projection parameters
         - o_proj (string)
         - Plus projection parameters
         - o_lat_p (degrees)
         - o_lon_p (degrees)
         - New pole
         - o_alpha: Alpha (degrees)
         - o_lon_c (degrees)
         - o_lat_c (degrees)
         - o_lon_1 (degrees)
         - o_lat_1: Latitude of first standard parallel (degrees)
         - o_lon_2 (degrees)
         - o_lat_2: Latitude of second standard parallel (degrees)
        \par Example
        \image html ex_ob_tran.gif
    */
    template <typename T, typename Parameters>
    struct ob_tran_oblique : public detail::ob_tran::base_ob_tran_oblique<T, Parameters>
    {
        template <typename Params>
        inline ob_tran_oblique(Params const& , Parameters const& ,
                               detail::ob_tran::par_ob_tran<T, Parameters> const& proj_parm)
            : detail::ob_tran::base_ob_tran_oblique<T, Parameters>(proj_parm)
        {
            // already done
            //detail::ob_tran::setup_ob_tran(this->m_par, this->m_proj_parm);
        }
    };

    /*!
        \brief General Oblique Transformation projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
        \par Projection parameters
         - o_proj (string)
         - Plus projection parameters
         - o_lat_p (degrees)
         - o_lon_p (degrees)
         - New pole
         - o_alpha: Alpha (degrees)
         - o_lon_c (degrees)
         - o_lat_c (degrees)
         - o_lon_1 (degrees)
         - o_lat_1: Latitude of first standard parallel (degrees)
         - o_lon_2 (degrees)
         - o_lat_2: Latitude of second standard parallel (degrees)
        \par Example
        \image html ex_ob_tran.gif
    */
    template <typename T, typename Parameters>
    struct ob_tran_transverse : public detail::ob_tran::base_ob_tran_transverse<T, Parameters>
    {        
        template <typename Params>
        inline ob_tran_transverse(Params const& , Parameters const& ,
                                  detail::ob_tran::par_ob_tran<T, Parameters> const& proj_parm)
            : detail::ob_tran::base_ob_tran_transverse<T, Parameters>(proj_parm)
        {
            // already done
            //detail::ob_tran::setup_ob_tran(this->m_par, this->m_proj_parm);
        }
    };

    /*!
        \brief General Oblique Transformation projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
        \par Projection parameters
         - o_proj (string)
         - Plus projection parameters
         - o_lat_p (degrees)
         - o_lon_p (degrees)
         - New pole
         - o_alpha: Alpha (degrees)
         - o_lon_c (degrees)
         - o_lat_c (degrees)
         - o_lon_1 (degrees)
         - o_lat_1: Latitude of first standard parallel (degrees)
         - o_lon_2 (degrees)
         - o_lat_2: Latitude of second standard parallel (degrees)
        \par Example
        \image html ex_ob_tran.gif
    */
    template <typename StaticParameters, typename T, typename Parameters>
    struct ob_tran_static : public detail::ob_tran::base_ob_tran_static<StaticParameters, T, Parameters>
    {
        inline ob_tran_static(StaticParameters const& params, Parameters const& par)
            : detail::ob_tran::base_ob_tran_static<StaticParameters, T, Parameters>(params, par)
        {
            T phip = detail::ob_tran::setup_ob_tran<T>(params, par, this->m_proj_parm);
            this->m_is_oblique = fabs(phip) > detail::ob_tran::tolerance;
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        template <typename SP, typename CT, typename P>
        struct static_projection_type<srs::spar::proj_ob_tran, srs_sphere_tag, SP, CT, P>
        {
            typedef static_wrapper_fi<ob_tran_static<SP, CT, P>, P> type;
        };
        template <typename SP, typename CT, typename P>
        struct static_projection_type<srs::spar::proj_ob_tran, srs_spheroid_tag, SP, CT, P>
        {
            typedef static_wrapper_fi<ob_tran_static<SP, CT, P>, P> type;
        };

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_BEGIN(ob_tran_entry)
        {
            Parameters parameters_copy = parameters;
            detail::ob_tran::par_ob_tran<T, Parameters> proj_parm(params, parameters_copy);
            T phip = detail::ob_tran::setup_ob_tran<T>(params, parameters_copy, proj_parm);

            if (fabs(phip) > detail::ob_tran::tolerance)
                return new dynamic_wrapper_fi<ob_tran_oblique<T, Parameters>, T, Parameters>(params, parameters_copy, proj_parm);
            else
                return new dynamic_wrapper_fi<ob_tran_transverse<T, Parameters>, T, Parameters>(params, parameters_copy, proj_parm);
        }
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_END

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(ob_tran_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(ob_tran, ob_tran_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_OB_TRAN_HPP


/* ob_tran.hpp
Mcb+ZQ2mgbIAZtMmZ1GH7qOdFKSf2T1UipKTpcE2pCvk2H2J+3OlEmvfKoP1/eTCYdc12Mf4euGTFrcm6FD6nI72pseFgwa0/mVA54YmqO9bsTTWhQofXXhSXxG8dkJ7Ha4N08ExiDzxrB8+8tkuiVY8qUg9v8YCBTX0RLEfD78JsZcxvSE1eFQ2KaqSt93lvv3IfXviswCRN8VwHVPh53ctruVWoLRZjtfTFUi840WFx150IuKJeS18qCyRBbnPYHKHlJYmbPb40WWMjnrBjdHkQYG9G8CscSrUzSsNwlfXiznUyqevedFLTp/ONb8e6w3qAt8+dzBtu8GKxeutyL1Jj0tJepy6rMfd3QqIosUY+UaOtGM61OG5IcQCoryTPCvJi4g9XuiIuw28mHxWisL73RDe8FIbejHyiwg51WJke0c9dVGK9pekmKNyYgP5gbG5MugrMo4xYNPdEC86tzGkabIv8GMb11dr8UPHPVKA2MF53M15XMR5nMJ5vJkY4uOBuXjJGOZmPBhZR4jYc9zvB5SIq6dD3YkGrOC5lPOh8hMZQ3w30u6Gl9qhhNaDQcmhewuvW+EUa9D2ogZfVCasjXBj8V43dpI/XrCF4u3gCBNsn6yI2EdNxXTIIjfs1I7fP1qhZdnfcx/ADZb92PufZbHNvcj6mXNFjTn8U0gTNlseOnf7kDuIp9yrrn1ynCYfXH5JgwIacju/Cdpi1LlFTOhzyYozPhMelzUFNeKsyR48456vrwlpy9LZJcHP26JXiDBtghKJp13IeNaF4x9UuFdbjehBajQO16BYNi3WTtKiUCZqOrUOc5/J8f2WBU+sbmzM7cR47klsdFMreJBjqAclRnlwcGvoHkmu0Oe3n6jRlrhD+fTBauRk7On4wIudZ6QYkaLBHosJz2QmpKs00FzQYJmS2r6QCSLO8VzOsfaeBYPpexwFTJgp0eCyx4TC1BK9TzMmXdbgIscedlOJpqOU6Ec9V6C2CQvvqmFzqNArTIWHQk2wP9m/C+FiXK90XAbzD+qhKXLowpVBux7/llp3hxZ1zuvRcagB+xnfUjm3a7lPJxFbyXfjHofeo9ooVYobBXXoLPHjyCIhepI3LF0lxb31cjSKl8NqVuLxBSU+sD89H6mQB3o8mqdH1sIGZKBurUKeqCY/bD1FgXGHvXhPn9CcdtKCtvHo05/fRCNkV2VYUpE+qIkB2k8OCLPZ0I86/XyUEGUGiWHs6EVzux/1aOtXfotw+LIMoxnzvpxWIpZa4EuUBiYN+UNHA7KRf1yhHrhI/Tc88JnjNgWqr7fgPH2FXyyD/2qIwx1u7EUmaovhh4T4RX61fLkSWz8qkTZDhX7U4mdm6yFMsuDNIA+iqdsHdZPR51LjrhIi7akb8mke9Cf/q0xMJj88PlVGju7GLPLA9oS0rBy3yAfv0h9FvraivtqDmtT0XXU2tFhsh2EnNV5xG3Jn9WN9lBSLe8kgWSJDoZJyVKssx7t7KvwykM9TzxznunTuLcZ0cpSsjKnXutBfMqaulclwlH31cS2bD7RhPP3ttmQL0mtKsYJ+dIRdha8DxDhzSxbMR15W4fYKHZxSPTRz9Wjb14DjOxTo1zI0J4/zSVDqPTWqPfSbucFYQ71/tooaOur78/21GJRGm5EZUclmxNMmrMuY1Ya+4zH9xlWjCD/uObAsRoeMz8nRvG78nuSBMbMUjYd50KKSCXe2B/4G042mm2To8FAW9FllqNd2snz6ATnmZJGjargC2+j3G7VSoBb1fRLnZRh1/Afq+LnU8IF/Hb5L0JA8JYBRFiE8fjXizqpxi7rmL7cWKrMOGrZb47gKa1NUkNIPmMx6xGhs2EpfEXivf2DMk+0efA5TIvyTCiMEOvQ8rMPC0YYg3zxpCf2mTq40AcZ6hBi8J/BOVnGQE93L7sdS9i28qxeqEX5k7iHDBGqBRMayDbSr4oy7U6mLlc1EeLpOgg2MBUUfSBHdmbFsuRxLL5Kf0ub2xanwZIMW2cjH8h9RYM9MHXmMDldv6qAcoEeHigZoqJ9Pkg/XFxixmHxYxniYIY8cqexjgKdZuM8CfRo6TYGvG70o1lQJj8GHD4f8KEmbWO/S4+FaC37vtGBpcyu+DrIi7bML3Rh7T/aT4RnnZ9M8HxLysW/cq6foc2vXII9TeBEe+FvyZCUWVg5xnMCcFfjhxNexoWflBwaSe9+XYi11+axDOlSi31yVTwa5T4yhjLUzk2X42CvE9w5bRejnE6FIPLUsr8nXQ46mtMvkB6rgeaVIjxdGA4qcNeBu88DfmVmRk7a5k7w8A/1LgTQtHpOzPp1HfyRwYuolcuR0FY5/s2LDR3Ln71ZkLShDU3KrwLPI5GwmHGvN2P4jxPkXNLJiCnXYEiKithXdq4hRnxzav0KIGxIxVl2nnVF3hr1RIKYs/dE1Fcb90mDHZi2Kbtfh1h49ls0JPcf++7ll77wG5N4Z+i7fv6OuT4ryC6g/ipB/lpfjLx535nGPfAaYi8rhr0Cuw3ypWko8ym/A9U4GHGS8XVfXAGdBAxawfAnTLeQ10+KlqDRTigbESfr0GVWVuFVPiS3kzimNdfh+QIcimQyYtsaAOuTKpVZb8aioDx1Yv8406mqmY4hZhCTcjw7Unse6cOwGKaaTP/cif/5K7n5vvDyIwFpsZ3zJWd2F/HnccM51oQnzk/IxJjO/iv2M7+9BJXKaGuSlOZ94ceORF13IzzKRl0URy1h+kBrnVHfxPzpowFchFjIu3WM8CpyL2qmCV0LeHK1GCrV8ZD/G4EQttnzjHuaYqh/UY7fZELz2RVVF8BrtVCsyb6L2yuLHED85psGDu4M9GH2KcZk22ZFwn/RgJdPOd71Yzn757nnxqpEXP3j8ZQj3+wAndIzhfdjHS1o/Nvk5N3F+lBnjh3mxDLfYdts8UhzksaO7DIPGhf4mrAh5lp9xKT/PjxrvR7lGoXssYbqb6e+GtDOmPXg8ian/qgbbdSYcOUSezv0jZZr9tAevqVl19BMJ5LzbyHmfcN5iOWf9iYUE2P+7Jzy40UgJMeNmJRE1FjXA+hVejMvqwEWm0dlC6UceB8ofM42g/9rGvdr0z149bwnD/JFh6LjAjPLvzFjgtKBbVhnC65rQiTbrumXEStrEWSKd8BPWWVKUJtoTz34YMFRpRDanEZOiTdg3WIydjH9FLwpR4xD5+SYtPtr1aDzZgGsHFME52jddiXL9lCjBfrcmKpLPFKVuuEy+MKSHHjV7G0Kf5ZFXrT0beiYS+O7kOqMf76xK1D5Hn7hLiw8r9Nh72oBju7xY6vBhwtXQM+F+4V7Mf2LBApsNBrsNP7kOVdfIkMo9d32IDFenyVB7gDCo4c972RebHopCBiQ0sKIJfeEYkRQ1R/rRl+XLe9C3Mi4vqqZAn1mK4HkrY23NpaG/V3V+cED+IfRbAJer+DBlnxd7iK8vXXj21oX4NHLJNy5cfOVCA6YZWLbutQv2z+TVPju2F7Ajpogd/Yva8VNtx8sHNqyab0et8TZ0nmBDGWIC0XCLE9cjnRhT0oPKxT34VYI8nIhYY8cgly74tzxTnjox7rkbjkwi7C4ows1ZTnSf70TpRU5kpG1MW2DHLakLIpULqY80qFrbjXGRItS5ZMRNjQvNicvdPWj+528vM5HPJn11osMbJ2YzHl5b5URkHS8eXPVim8KJzdQcO58L0GyCGIcmiunnJLiTRQpphBR5e8vQjFi/VIbrxLTsckTlJecmmhSXYxzRK1qOxcTFMgr8tUkBqcWGxG8yzInSY2BOPQq8sWB9WT1OE1dK6THvcej3hPReD/4qpMfx9+TCby3U0xZkSrPAxONuxPRceuzMq0d4Hj28kXosLEofQTwop8f4uz4cKuQKonvhEGQTJCg9kX1nWrwM7a6sBC3q+TGwoCuI4/VE0Nb2I0esH2OI17Tr1claSJO9+OudC9lKe9BXoETGZi6c1wgxtoEDE01ONH9GvhNrxVtp+D8wNRUhZqMEZR4rIH5mDO7BJjtswXOBfOC3agK/U/N3HJ2w1o2lGXzoeM6Hi01cCKtlRT/WXV+V+rSaFx+UfrT0SjG6ixf5y1JDD/Vjb08ZOakf4+bI0GUcuSs5sWWsCi+faBG7UofTc/zIS27Qlr5lMH1LvyUKjL3khWuMNdiGuwJ9YkEf9vGe/c74MPqED5JTPmw6EdItgb4d6OnG4bM+lOFYYzlWK8eqnWREmYlGmPbasbypA8nLDKhSzYiRTQO/U+lDdDsX8s6SYMcZOb6etaNwnACvfllwd6wA05gOf+dA9CIfhtH/VGS/3bEidLgmQSK595zVUrQL/B36IiVaFNLhYX0dNtw1InV5aK6G/uXDxI8CNK9rxe9aDoz3ihGdRUx/IkYvaoOvQupj8vBbvbxwcI5SWtE2B/rRa7oMrgkCvG4v5P4Q4sgFIdaJRIjNJsJFrpWY/ydSB++8KIHyGX3yJRnWPZHh8gA5zFrqpcNKvKUmqEmNtIia13FAhWoRGiSn69B3qx7tihgw6BP1hsuIy+T80/XUCuT9mUvaELFLgeEfGUN/OLB7lwVatxetGJPvtjSg+Ck3RsU4UKsu+dV1L2qmSCFL9eLNKDcmRHhQSsI49lCJj5EajFOKcaSNAcPL+SFKU2FRmgSf2dZG8qvKHyRYES5Gw68S9PgmQeFbYnxQWLHomwVZWefHSw9e5nOgrNeLe2yz0mglsvd3I6yHDxk7+4JpbabOVx5clbnwcAS16lwbXs2mb51jwxymB4m9zD8h7i2wIcNCG9qwzmRCQxQh7hPyef+qX5D5dkQ55rsQpXjtdKLDv7X597l5rHfxnRcrbnlx6KwH8bvcyKjmfL5yY9sbN+Zes6LyQC8U6VYkLHNj0hIP9uzxIC3VhpzXbXhqcGGn0QUzcYT5KkzLsa0RBa3QZLdhwCYHbq51IPMGB16f8yBDZTeaDQn9ff0ygxNvhdzXxP1fThwkFOS2r78H3tEswjjq4o5l3dh8zIpld9zIH+mGa4AX58U2VB/hwqVtNpizuYPvpti50oMa4VbqZSuGMD5Eb3Piyh4f0jKwP6lO3OjlQTmvDrWJRuHUGEyH+nXI4dNByvSbzItRz5y4W1GP9NxW3K6kx5gqjFGEj5Bns6JkZT3u1uD+jfFAU8cDd3MPKkbrcVHmhkXixmqhG+WvOFG3ngfTclix67wI23l+ENsyE/ZIKzqxnTCBC/7MLuAFff9zJ5aw3f2EpKoela850eomy7hva3PfJqi9GChlHLxmx8xPQsysacCTR2qU9huRHmXEr4taNLZoEbXfgMFXtGhH7j53vR7nLOT6fhEqbJHjDTWmhrpjIfV8xqVilI/yYzK1h7cv9e5yGZ5Qgz9JpN+cLYftsgJblqnwoS31HPl+t706lPuqw5z9ejwdYcUWuQffGWcyH+YaUiv31nownXq5xSk5Th/1A13UKPhKgyzdtJD98sAg8iKS6a7MtAmxF7WeWKEfEYmfeUPfySlD2y/cw4phxfwQd1BirFyIttS6TTQSVBtmwu8kBUa0F6ODUYqMixU4NMmA5MFavNBoUeWCAYub+7CqmQ+Xs+twIloHAdvf47ZDetqODUWEQbx550aEhfZRxoPj8GBN4HnZYw3KZPDgAfVno+FOzNRZcbO9C+KmUnz7ZIHya+h7CPeiuHd6ev/juzw7aMdvv5GDVHLj50w3KtCe5btCnwG7Efo+0PeKgffFUH88smMbfXExxp0BZ6w4SM4kyabDZqcN7sUuqCa5ce6YG5UyKJD7shhJlRVo2UaBXjnJSQQ2CKJDvzWfqbgD1mLU7ecs2GcVYpQpPKjDt4ld+Fhci5WXtRhZy4N2jT0oQFhSnFh1VY8Lka4gXuT5g/yuf8r67lSiZAU1Wmq12FVCiz3HtVj+SouCPnIYtvWN7QTyu/3UIQt1KDRYjo0f9Fi1QIGaM1T4dEGNyo31OLxXhXeT9Xj2UoGy19Tods+A0+9UuNpWiahJerypqEBcEz0W51bjQXkhZszQ40tRK2xlQtB6Xf+kP6OtKJstdCyqZsWZQwIkHxCiyn7Gj7ZyKNP12PzSiAmvjBDNV6DgCQPiB4hRVqaCc7oKOXvTRg1+bG4gh0jiQrtlTpQlTxORp227IkLtl1p00kih19BHMm6l5Baj2Fk54tn/uR5XEBUiXFh7W4zlvGcXxuwAdv3BaY4xbaUbvbdbEOvXknu5gtieL4S65D5xRUNIeSVDg5yh39GLCvC4HHJ89ivwqJICR7YqkCxVIQtRaIIeGamnr2SmDwznXnwuRpYICXpb5LjxW44PjaiHhymwpgDt/6mA2keMZHJBeS8ZWpH/jSDfyE3OV5F8b14uBTb2sqLVaj/CJhiQM1KCnEOlOH9HimpHXHBlN6BTG8ZUrkXeckI0Lkm+Xk6Co1znAPZw7AauT8Hn5Gn0CymDTDiTz4nlntBvi6fQ3vK8NaJKRyFERWyIviZC6ksbhly0QhEejrI2IcYbwiE1huPJQOr2JXaEv9fjAK9pwfUKPM9ZXU2N2EFaHLmkRcamYrS5IMZAtQRL8knQ+AZ5BudJVUqBcY2J4Qp83cC5OepB0WxO+J0evD+qQAWNHiM6KbGevialohZXGvlQlPH/bmMtTtwSoJBUAl1WCdo3UcDq1CCpmRaDOqkxb5kSsQP02FHcjhXbyZOyh9YnVegJxpEA8k3zYMJ8F3Z8Jle6IUTcTzeu7JWieh8DZvUy4C77PXCRBB+O2bF0oi24P43dhMhwToafPL99nQG5Uo1oN1GAC1OVMM9X4nJ7JYSPlfRdatzsIUKz8hJ86WtDgRM6PCePvT7ZhpGvxJghVuBYsiP43qD6PUK/pTh6DbVIMxGe5JbgV04Jet2htnruQXamHrMCs0oqcI8YrfNB/VOO+Vzzv36IMc8ogSJFjARy/Us3RRhLX2Is4UD5mkqc2KbFlE4GHD8kQ4vzMuwYKsemWgYUeyBBv2JSlFrmQzp1yplW1KblPMj8VoRW5vDg/DR570Zdqwe96U8VGanHCXuaHWnpdng0Dhz4YIdJ5cCK93YMVztw9Kcds3/b0fuzHWdYfvqJHaef2ZH+JlRv0LtQulzgwLjHdlh4LoHnThFVib7EcaUDb4mF8RJknSZB2ccmrH8jgtMRjmzvbNiSQJ3HuRmSQ4IsJdxY8NGCKQ4vcsk8kBI7yWEHTHFheUsvmn/1olEOG170MaK2O/SOpn0FbCixyYZtMzxou9mGaTulaDTRiaMrnZgjtiJzVydmXTUCHg8kyTZMnOlBdc7nLvplc+B9G4M9uN/BC9sGPfLnUWHWWhlqFjHh9XMZVkc48YRao9dfHrwa6EFsWIiz7DgnQq1hBnxua8CkSBV+ZZNjfQcFUsZQo0cKse2dAF+YTmwlQsnuIqS1ciKhlxg3hnLPJIqxtKMTX/cwXtWSwXRGhsFN5BhD7bMnuwq6CyrOuRZVd+rxIRu1AuT44ZJDd5285KEcoxIVkHCNjww0YV+qBfOJ+8SxUxY8Teexh3vslQTmTW4kMkbWeyyB9IUbuTs7MZlQxPjxoogDTcvSnqr5cZVp7Bopzr0WI3MtP/z53MFnWderudCB+2ldVzkuDZcj+/DQ8+PA
*/
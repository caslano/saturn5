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

#ifndef BOOST_GEOMETRY_PROJECTIONS_OB_TRAN_HPP
#define BOOST_GEOMETRY_PROJECTIONS_OB_TRAN_HPP

#include <boost/geometry/util/math.hpp>
#include <boost/shared_ptr.hpp>

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

            template <BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX, typename Parameters>
            inline Parameters o_proj_parameters(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& /*params*/,
                                                Parameters const& par)
            {
                /* copy existing header into new */
                Parameters pj = par;

                /* get name of projection to be translated */
                typedef srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> params_type;
                typedef typename geometry::tuples::find_if
                    <
                        params_type,
                        srs::spar::detail::is_param_t<srs::spar::o_proj>::pred
                    >::type o_proj_type;

                static const bool is_found = geometry::tuples::is_found<o_proj_type>::value;
                BOOST_MPL_ASSERT_MSG((is_found), NO_ROTATION_PROJ, (params_type));

                typedef typename o_proj_type::type proj_type;
                static const bool is_specialized = srs::spar::detail::proj_traits<proj_type>::is_specialized;
                BOOST_MPL_ASSERT_MSG((is_specialized), NO_ROTATION_PROJ, (params_type));

                pj.id = srs::spar::detail::proj_traits<proj_type>::id;

                /* avoid endless recursion */
                static const bool is_non_resursive = ! boost::is_same<proj_type, srs::spar::proj_ob_tran>::value;
                BOOST_MPL_ASSERT_MSG((is_non_resursive), INVALID_O_PROJ_PARAMETER, (params_type));

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
                static const bool is_o_proj_not_ob_tran = ! boost::is_same<o_proj_tag, srs::spar::proj_ob_tran>::value;
                BOOST_MPL_ASSERT_MSG((is_o_proj_not_ob_tran), INVALID_O_PROJ_PARAMETER, (StaticParameters));

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
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
*/
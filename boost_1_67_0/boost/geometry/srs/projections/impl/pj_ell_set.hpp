// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018, 2019.
// Modifications copyright (c) 2017-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Geometry Library by
//     Barend Gehrels (Geodan, Amsterdam)
//     Adam Wulkiewicz

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_ELL_SET_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_ELL_SET_HPP

#include <string>
#include <vector>

#include <boost/geometry/formulas/eccentricity_sqr.hpp>
#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/dpar.hpp>
#include <boost/geometry/srs/projections/impl/pj_datum_set.hpp>
#include <boost/geometry/srs/projections/impl/pj_ellps.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/proj4.hpp>
#include <boost/geometry/srs/projections/spar.hpp>


namespace boost { namespace geometry { namespace projections {

namespace detail {

/* set ellipsoid parameters a and es */
template <typename T>
inline T SIXTH() { return .1666666666666666667; } /* 1/6 */
template <typename T>
inline T RA4() { return .04722222222222222222; } /* 17/360 */
template <typename T>
inline T RA6() { return .02215608465608465608; } /* 67/3024 */
template <typename T>
inline T RV4() { return .06944444444444444444; } /* 5/72 */
template <typename T>
inline T RV6() { return .04243827160493827160; } /* 55/1296 */

template <typename T>
inline T pj_ell_b_to_es(T const& a, T const& b)
{
    return 1. - (b * b) / (a * a);
}

/************************************************************************/
/*                          pj_ell_init_ellps()                         */
/************************************************************************/

// Originally a part of pj_ell_set()
template <typename T>
inline bool pj_ell_init_ellps(srs::detail::proj4_parameters const& params, T &a, T &b)
{
    /* check if ellps present and temporarily append its values to pl */
    std::string name = pj_get_param_s(params, "ellps");
    if (! name.empty())
    {
        const pj_ellps_type<T>* pj_ellps = pj_get_ellps<T>().first;
        const int n = pj_get_ellps<T>().second;
        int index = -1;
        for (int i = 0; i < n && index == -1; i++)
        {
            if(pj_ellps[i].id == name)
            {
                index = i;
            }
        }

        if (index == -1) {
            BOOST_THROW_EXCEPTION( projection_exception(error_unknown_ellp_param) );
        }

        pj_ellps_type<T> const& pj_ellp = pj_ellps[index];
        a = pj_ellp.a;
        b = pj_ellp.b;

        return true;
    }

    return false;
}

template <typename T>
inline bool pj_ell_init_ellps(srs::dpar::parameters<T> const& params, T &a, T &b)
{
    /* check if ellps present and temporarily append its values to pl */
    typename srs::dpar::parameters<T>::const_iterator
        it = pj_param_find(params, srs::dpar::ellps);
    if (it != params.end())
    {
        if (it->template is_value_set<int>())
        {
            const pj_ellps_type<T>* pj_ellps = pj_get_ellps<T>().first;
            const int n = pj_get_ellps<T>().second;
            int i = it->template get_value<int>();
        
            if (i < 0 || i >= n) {
                BOOST_THROW_EXCEPTION( projection_exception(error_unknown_ellp_param) );
            }

            pj_ellps_type<T> const& pj_ellp = pj_ellps[i];
            a = pj_ellp.a;
            b = pj_ellp.b;
        }
        else if (it->template is_value_set<T>())
        {
            a = it->template get_value<T>();
            b = a;
        }
        else if (it->template is_value_set<srs::spheroid<T> >())
        {
            srs::spheroid<T> const& s = it->template get_value<srs::spheroid<T> >();
            a = geometry::get_radius<0>(s);
            b = geometry::get_radius<2>(s);
        }
        else
        {
            BOOST_THROW_EXCEPTION( projection_exception(error_unknown_ellp_param) );
        }

        return true;
    }

    return false;
}

template
<
    typename Params,
    int I = geometry::tuples::find_index_if
        <
            Params,
            srs::spar::detail::is_param_tr<srs::spar::detail::ellps_traits>::pred
        >::value,
    int N = boost::tuples::length<Params>::value
>
struct pj_ell_init_ellps_static
{
    template <typename T>
    static bool apply(Params const& params, T &a, T &b)
    {
        typedef typename boost::tuples::element<I, Params>::type param_type;
        typedef srs::spar::detail::ellps_traits<param_type> traits_type;
        typedef typename traits_type::template model_type<T>::type model_type;

        param_type const& param = boost::tuples::get<I>(params);
        model_type const& model = traits_type::template model<T>(param);

        a = geometry::get_radius<0>(model);
        b = geometry::get_radius<2>(model);

        return true;
    }
};
template <typename Params, int N>
struct pj_ell_init_ellps_static<Params, N, N>
{
    template <typename T>
    static bool apply(Params const& , T & , T & )
    {
        return false;
    }
};

template <typename T, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX>
inline bool pj_ell_init_ellps(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& params,
                              T &a, T &b)
{
    return pj_ell_init_ellps_static
        <
            srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX>
        >::apply(params, a, b);
}

/************************************************************************/
/*                             pj_ell_init()                            */
/************************************************************************/

/* initialize geographic shape parameters */
// This function works differently than the original pj_ell_set().
// It doesn't push parameters defined in ellps into params list.
// Instead it tries to use size (a, R) and shape (es, e, rf, f, b) parameters
// and then if needed falls back to ellps, then to datum and then to the default WGS84
template <typename Params, typename T>
inline void pj_ell_init(Params const& params, T &a, T &es)
{
    /* check for varying forms of ellipsoid input */
    a = es = 0.;

    /* R takes precedence */
    if (pj_param_f<srs::spar::r>(params, "R", srs::dpar::r, a)) {
        /* empty */
    } else { /* probable elliptical figure */

        // Set ellipsoid's size parameter
        a = pj_get_param_f<T, srs::spar::a>(params, "a", srs::dpar::a);
        bool is_a_set = a != 0.0;

        // Set ellipsoid's shape parameter
        T b = 0.0;
        bool is_ell_set = false;
        if (pj_param_f<srs::spar::es>(params, "es", srs::dpar::es, es)) {/* eccentricity squared */
            /* empty */
            is_ell_set = true;
        } else if (pj_param_f<srs::spar::e>(params, "e", srs::dpar::e, es)) { /* eccentricity */
            es = es * es;
            is_ell_set = true;
        } else if (pj_param_f<srs::spar::rf>(params, "rf", srs::dpar::rf, es)) { /* recip flattening */
            if (es == 0.0) {
                BOOST_THROW_EXCEPTION( projection_exception(error_rev_flattening_is_zero) );
            }    
            es = 1./ es;
            es = es * (2. - es);
            is_ell_set = true;
        } else if (pj_param_f<srs::spar::f>(params, "f", srs::dpar::f, es)) { /* flattening */
            es = es * (2. - es);
            is_ell_set = true;
        } else if (pj_param_f<srs::spar::b>(params, "b", srs::dpar::b, b)) { /* minor axis */
            es = pj_ell_b_to_es(a, b);
            is_ell_set = true;
        } /* else es == 0. and sphere of radius a */

        // NOTE: Below when ellps is used to initialize a and es
        // b is not set because it only has sense together with a
        // but a could have been set separately before, e.g. consider passing:
        // a=1 ellps=airy (a=6377563.396 b=6356256.910)
        // after setting size parameter a and shape parameter from ellps
        // b has to be recalculated

        // If ellipsoid's parameters are not set directly
        //   use ellps parameter
        if (! is_a_set || ! is_ell_set) {
            T ellps_a = 0, ellps_b = 0;
            if (pj_ell_init_ellps(params, ellps_a, ellps_b)) {
                if (! is_a_set) {
                    a = ellps_a;
                    is_a_set = true;
                }
                if (! is_ell_set) {
                    es = pj_ell_b_to_es(ellps_a, ellps_b);
                    is_ell_set = true;
                }
            }
        }

        // If ellipsoid's parameters are not set
        //   use ellps defined by datum parameter
        if (! is_a_set || ! is_ell_set)
        {
            const pj_datums_type<T>* datum = pj_datum_find_datum<T>(params);
            if (datum != NULL)
            {
                pj_ellps_type<T> const& pj_ellp = pj_get_ellps<T>().first[datum->ellps];
                if (! is_a_set) {
                    a = pj_ellp.a;
                    is_a_set = true;
                }
                if (! is_ell_set) {
                    es = pj_ell_b_to_es(pj_ellp.a, pj_ellp.b);
                    is_ell_set = true;
                }
            }
        }

        // If ellipsoid's parameters are still not set
        //   use default WGS84
        if ((! is_a_set || ! is_ell_set)
         && ! pj_get_param_b<srs::spar::no_defs>(params, "no_defs", srs::dpar::no_defs))
        {
            pj_ellps_type<T> const& pj_ellp = pj_get_ellps<T>().first[srs::dpar::ellps_wgs84];
            if (! is_a_set) {
                a = pj_ellp.a;
                is_a_set = true;
            }
            if (! is_ell_set) {
                es = pj_ell_b_to_es(pj_ellp.a, pj_ellp.b);
                is_ell_set = true;
            }
        }

        if (b == 0.0)
            b = a * sqrt(1. - es);

        /* following options turn ellipsoid into equivalent sphere */
        if (pj_get_param_b<srs::spar::r_au>(params, "R_A", srs::dpar::r_au)) { /* sphere--area of ellipsoid */
            a *= 1. - es * (SIXTH<T>() + es * (RA4<T>() + es * RA6<T>()));
            es = 0.;
        } else if (pj_get_param_b<srs::spar::r_v>(params, "R_V", srs::dpar::r_v)) { /* sphere--vol. of ellipsoid */
            a *= 1. - es * (SIXTH<T>() + es * (RV4<T>() + es * RV6<T>()));
            es = 0.;
        } else if (pj_get_param_b<srs::spar::r_a>(params, "R_a", srs::dpar::r_a)) { /* sphere--arithmetic mean */
            a = .5 * (a + b);
            es = 0.;
        } else if (pj_get_param_b<srs::spar::r_g>(params, "R_g", srs::dpar::r_g)) { /* sphere--geometric mean */
            a = sqrt(a * b);
            es = 0.;
        } else if (pj_get_param_b<srs::spar::r_h>(params, "R_h", srs::dpar::r_h)) { /* sphere--harmonic mean */
            a = 2. * a * b / (a + b);
            es = 0.;
        } else {
            T tmp;
            bool i = pj_param_r<srs::spar::r_lat_a>(params, "R_lat_a", srs::dpar::r_lat_a, tmp);
            if (i || /* sphere--arith. */
                pj_param_r<srs::spar::r_lat_g>(params, "R_lat_g", srs::dpar::r_lat_g, tmp)) { /* or geom. mean at latitude */

                tmp = sin(tmp);
                if (geometry::math::abs(tmp) > geometry::math::half_pi<T>()) {
                    BOOST_THROW_EXCEPTION( projection_exception(error_ref_rad_larger_than_90) );
                }
                tmp = 1. - es * tmp * tmp;
                a *= i ? .5 * (1. - es + tmp) / ( tmp * sqrt(tmp)) :
                    sqrt(1. - es) / tmp;
                es = 0.;
            }
        }
    }

    /* some remaining checks */
    if (es < 0.) {
        BOOST_THROW_EXCEPTION( projection_exception(error_es_less_than_zero) );
    }
    if (a <= 0.) {
        BOOST_THROW_EXCEPTION( projection_exception(error_major_axis_not_given) );
    }
}

template <typename Params>
struct static_srs_tag_check_nonexpanded
{
    typedef typename boost::mpl::if_c
        <
            geometry::tuples::exists_if
                <
                    Params, srs::spar::detail::is_param_t<srs::spar::r>::pred
                >::value
         || geometry::tuples::exists_if
                <
                    Params, srs::spar::detail::is_param<srs::spar::r_au>::pred
                >::value
         || geometry::tuples::exists_if
                <
                    Params, srs::spar::detail::is_param<srs::spar::r_v>::pred
                >::value
         || geometry::tuples::exists_if
                <
                    Params, srs::spar::detail::is_param<srs::spar::r_a>::pred
                >::value
         || geometry::tuples::exists_if
                <
                    Params, srs::spar::detail::is_param<srs::spar::r_g>::pred
                >::value
         || geometry::tuples::exists_if
                <
                    Params, srs::spar::detail::is_param<srs::spar::r_h>::pred
                >::value
         || geometry::tuples::exists_if
                <
                    Params, srs::spar::detail::is_param_t<srs::spar::r_lat_a>::pred
                >::value
         || geometry::tuples::exists_if
                <
                    Params, srs::spar::detail::is_param_t<srs::spar::r_lat_g>::pred
                >::value,
            srs_sphere_tag,
            // NOTE: The assumption here is that if the user defines either one of:
            // b, es, e, f, rf parameters then he wants to define spheroid, not sphere
            typename boost::mpl::if_c
                <
                    geometry::tuples::exists_if
                        <
                            Params, srs::spar::detail::is_param_t<srs::spar::b>::pred
                        >::value
                 || geometry::tuples::exists_if
                        <
                            Params, srs::spar::detail::is_param_t<srs::spar::es>::pred
                        >::value
                 || geometry::tuples::exists_if
                        <
                            Params, srs::spar::detail::is_param_t<srs::spar::e>::pred
                        >::value
                 || geometry::tuples::exists_if
                        <
                            Params, srs::spar::detail::is_param_t<srs::spar::rf>::pred
                        >::value
                 || geometry::tuples::exists_if
                        <
                            Params, srs::spar::detail::is_param_t<srs::spar::f>::pred
                        >::value,
                    srs_spheroid_tag,
                    void
                >::type
        >::type type;
};

template <typename Params>
struct static_srs_tag_check_ellps
{
    typedef typename geometry::tag
        <
            typename srs::spar::detail::ellps_traits
                <
                    typename geometry::tuples::find_if
                        <
                            Params,
                            srs::spar::detail::is_param_tr<srs::spar::detail::ellps_traits>::pred
                        >::type
                >::template model_type<double>::type // dummy type
        >::type type;
};

template <typename Params>
struct static_srs_tag_check_datum
{
    typedef typename geometry::tag
        <
            typename srs::spar::detail::ellps_traits
                <
                    typename srs::spar::detail::datum_traits
                        <
                            typename geometry::tuples::find_if
                                <
                                    Params,
                                    srs::spar::detail::is_param_tr<srs::spar::detail::datum_traits>::pred
                                >::type
                        >::ellps_type
                >::template model_type<double>::type // dummy type
        >::type type;
};

template
<
    typename Params,
    typename NonExpandedTag = typename static_srs_tag_check_nonexpanded
                                <
                                    Params
                                >::type,
    typename EllpsTag = typename static_srs_tag_check_ellps
                            <
                                Params
                            >::type,
    typename DatumTag = typename static_srs_tag_check_datum
                            <
                                Params
                            >::type
>
struct static_srs_tag
{
    // User passed one of the non-ellps, non-datum parameters
    typedef NonExpandedTag type;
};

template <typename Params, typename EllpsTag, typename DatumTag>
struct static_srs_tag<Params, void, EllpsTag, DatumTag>
{
    // User didn't pass neither one of the non-ellps, non-datum parameters
    // but passed ellps
    typedef EllpsTag type;
};

template <typename Params, typename DatumTag>
struct static_srs_tag<Params, void, void, DatumTag>
{
    // User didn't pass neither one of the non-ellps, non-datum parameters
    // nor ellps parameter but passed datum parameter
    typedef DatumTag type;
};

template <typename Params>
struct static_srs_tag<Params, void, void, void>
{
    // User didn't pass any parameter defining model
    // so use default or generate error
    typedef typename boost::mpl::if_c
        <
            geometry::tuples::exists_if
                <
                    Params, srs::spar::detail::is_param<srs::spar::no_defs>::pred
                >::value,
            void,
            srs_spheroid_tag // WGS84
        >::type type;

    static const bool is_found = ! boost::is_same<type, void>::value;
    BOOST_MPL_ASSERT_MSG((is_found), UNKNOWN_ELLP_PARAM, (Params));
};


template <typename T>
inline void pj_calc_ellipsoid_params(parameters<T> & p, T const& a, T const& es) {
/****************************************************************************************
    Calculate a large number of ancillary ellipsoidal parameters, in addition to
    the two traditional PROJ defining parameters: Semimajor axis, a, and the
    eccentricity squared, es.

    Most of these parameters are fairly cheap to compute in comparison to the overall
    effort involved in initializing a PJ object. They may, however, take a substantial
    part of the time taken in computing an individual point transformation.

    So by providing them up front, we can amortize the (already modest) cost over all
    transformations carried out over the entire lifetime of a PJ object, rather than
    incur that cost for every single transformation.

    Most of the parameter calculations here are based on the "angular eccentricity",
    i.e. the angle, measured from the semiminor axis, of a line going from the north
    pole to one of the foci of the ellipsoid - or in other words: The arc sine of the
    eccentricity.

    The formulae used are mostly taken from:

    Richard H. Rapp: Geometric Geodesy, Part I, (178 pp, 1991).
    Columbus, Ohio:  Dept. of Geodetic Science
    and Surveying, Ohio State University.

****************************************************************************************/

    p.a = a;
    p.es = es;

    /* Compute some ancillary ellipsoidal parameters */
    if (p.e==0)
        p.e = sqrt(p.es);  /* eccentricity */
    //p.alpha = asin (p.e);  /* angular eccentricity */

    /* second eccentricity */
    //p.e2  = tan (p.alpha);
    //p.e2s = p.e2 * p.e2;

    /* third eccentricity */
    //p.e3    = (0!=p.alpha)? sin (p.alpha) / sqrt(2 - sin (p.alpha)*sin (p.alpha)): 0;
    //p.e3s = p.e3 * p.e3;

    /* flattening */
    //if (0==p.f)
    //    p.f  = 1 - cos (p.alpha);   /* = 1 - sqrt (1 - PIN->es); */
    //p.rf = p.f != 0.0 ? 1.0/p.f: HUGE_VAL;

    /* second flattening */
    //p.f2  = (cos(p.alpha)!=0)? 1/cos (p.alpha) - 1: 0;
    //p.rf2 = p.f2 != 0.0 ? 1/p.f2: HUGE_VAL;

    /* third flattening */
    //p.n  = pow (tan (p.alpha/2), 2);
    //p.rn = p.n != 0.0 ? 1/p.n: HUGE_VAL;

    /* ...and a few more */
    //if (0==p.b)
    //    p.b  = (1 - p.f)*p.a;
    //p.rb = 1. / p.b;
    p.ra = 1. / p.a;

    p.one_es = 1. - p.es;
    if (p.one_es == 0.) {
        BOOST_THROW_EXCEPTION( projection_exception(error_eccentricity_is_one) );
    }

    p.rone_es = 1./p.one_es;
}


} // namespace detail
}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_ELL_SET_HPP

/* pj_ell_set.hpp
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
*/
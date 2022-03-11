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
// PROJ4 is converted to Geometry Library by Barend Gehrels (Geodan, Amsterdam)

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_INIT_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_INIT_HPP

#include <cstdlib>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/if.hpp>
#include <boost/range.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/condition.hpp>

#include <boost/geometry/srs/projections/dpar.hpp>
#include <boost/geometry/srs/projections/impl/dms_parser.hpp>
#include <boost/geometry/srs/projections/impl/pj_datum_set.hpp>
#include <boost/geometry/srs/projections/impl/pj_datums.hpp>
#include <boost/geometry/srs/projections/impl/pj_ell_set.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/pj_units.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/proj4.hpp>
#include <boost/geometry/srs/projections/spar.hpp>


namespace boost { namespace geometry { namespace projections
{


namespace detail
{

/************************************************************************/
/*                           pj_init_proj()                             */
/************************************************************************/

template <typename T>
inline void pj_init_proj(srs::detail::proj4_parameters const& params,
                         parameters<T> & par)
{
    par.id = pj_get_param_s(params, "proj");
}

template <typename T>
inline void pj_init_proj(srs::dpar::parameters<T> const& params,
                         parameters<T> & par)
{
    typename srs::dpar::parameters<T>::const_iterator it = pj_param_find(params, srs::dpar::proj);
    if (it != params.end())
    {
        par.id = static_cast<srs::dpar::value_proj>(it->template get_value<int>());
    }
}

template <typename T, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX>
inline void pj_init_proj(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& ,
                         parameters<T> & par)
{
    typedef srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> params_type;
    typedef typename geometry::tuples::find_if
        <
            params_type,
            srs::spar::detail::is_param_tr<srs::spar::detail::proj_traits>::pred
        >::type proj_type;

    static const bool is_found = geometry::tuples::is_found<proj_type>::value;

    BOOST_MPL_ASSERT_MSG((is_found), PROJECTION_NOT_NAMED, (params_type));

    par.id = srs::spar::detail::proj_traits<proj_type>::id;
}

/************************************************************************/
/*                           pj_init_units()                            */
/************************************************************************/

template <typename T, bool Vertical>
inline void pj_init_units(srs::detail::proj4_parameters const& params,
                          T & to_meter,
                          T & fr_meter,
                          T const& default_to_meter,
                          T const& default_fr_meter)
{
    std::string s;
    std::string units = pj_get_param_s(params, Vertical ? "vunits" : "units");
    if (! units.empty())
    {
        static const int n = sizeof(pj_units) / sizeof(pj_units[0]);
        int index = -1;
        for (int i = 0; i < n && index == -1; i++)
        {
            if(pj_units[i].id == units)
            {
                index = i;
            }
        }

        if (index == -1) {
            BOOST_THROW_EXCEPTION( projection_exception(error_unknow_unit_id) );
        }
        s = pj_units[index].to_meter;
    }

    if (s.empty())
    {
        s = pj_get_param_s(params, Vertical ? "vto_meter" : "to_meter");
    }

    // TODO: numerator and denominator could be taken from pj_units
    if (! s.empty())
    {
        std::size_t const pos = s.find('/');
        if (pos == std::string::npos)
        {
            to_meter = geometry::str_cast<T>(s);
        }
        else
        {
            T const numerator = geometry::str_cast<T>(s.substr(0, pos));
            T const denominator = geometry::str_cast<T>(s.substr(pos + 1));
            if (numerator == 0.0 || denominator == 0.0)
            {
                BOOST_THROW_EXCEPTION( projection_exception(error_unit_factor_less_than_0) );
            }
            to_meter = numerator / denominator;
        }
        if (to_meter == 0.0)
        {
            BOOST_THROW_EXCEPTION( projection_exception(error_unit_factor_less_than_0) );
        }
        fr_meter = 1. / to_meter;
    }
    else
    {
        to_meter = default_to_meter;
        fr_meter = default_fr_meter;
    }
}

template <typename T, bool Vertical>
inline void pj_init_units(srs::dpar::parameters<T> const& params,
                          T & to_meter,
                          T & fr_meter,
                          T const& default_to_meter,
                          T const& default_fr_meter)
{
    typename srs::dpar::parameters<T>::const_iterator
        it = pj_param_find(params, Vertical ? srs::dpar::vunits : srs::dpar::units);
    if (it != params.end())
    {
        static const int n = sizeof(pj_units) / sizeof(pj_units[0]);
        const int i = it->template get_value<int>();
        if (i >= 0 && i < n)
        {
            T const numerator = pj_units[i].numerator;
            T const denominator = pj_units[i].denominator;
            if (numerator == 0.0 || denominator == 0.0)
            {
                BOOST_THROW_EXCEPTION( projection_exception(error_unit_factor_less_than_0) );
            }
            to_meter = numerator / denominator;
            fr_meter = 1. / to_meter;
        }
        else
        {
            BOOST_THROW_EXCEPTION( projection_exception(error_unknow_unit_id) );
        }
    }
    else
    {
        it = pj_param_find(params, Vertical ? srs::dpar::vto_meter : srs::dpar::to_meter);
        if (it != params.end())
        {
            to_meter = it->template get_value<T>();
            fr_meter = 1. / to_meter;
        }
        else
        {
            to_meter = default_to_meter;
            fr_meter = default_fr_meter;
        }
    }
}

template
<
    typename Params,
    bool Vertical,
    int UnitsI = geometry::tuples::find_index_if
        <
            Params,
            boost::mpl::if_c
                <
                    Vertical,
                    srs::spar::detail::is_param_t<srs::spar::vunits>,
                    srs::spar::detail::is_param_tr<srs::spar::detail::units_traits>
                >::type::template pred
        >::value,
    int ToMeterI = geometry::tuples::find_index_if
        <
            Params,
            boost::mpl::if_c
                <
                    Vertical,
                    srs::spar::detail::is_param_t<srs::spar::vto_meter>,
                    srs::spar::detail::is_param_t<srs::spar::to_meter>
                >::type::template pred
        >::value,
    int N = boost::tuples::length<Params>::value
>
struct pj_init_units_static
    : pj_init_units_static<Params, Vertical, UnitsI, N, N>
{};

template <typename Params, bool Vertical, int UnitsI, int N>
struct pj_init_units_static<Params, Vertical, UnitsI, N, N>
{
    static const int n = sizeof(pj_units) / sizeof(pj_units[0]);
    static const int i = srs::spar::detail::units_traits
                    <
                        typename boost::tuples::element<UnitsI, Params>::type
                    >::id;
    static const bool is_valid = i >= 0 && i < n;

    BOOST_MPL_ASSERT_MSG((is_valid), UNKNOWN_UNIT_ID, (Params));

    template <typename T>
    static void apply(Params const& ,
                      T & to_meter, T & fr_meter,
                      T const& , T const& )
    {
        T const numerator = pj_units[i].numerator;
        T const denominator = pj_units[i].denominator;
        if (numerator == 0.0 || denominator == 0.0)
        {
            BOOST_THROW_EXCEPTION( projection_exception(error_unit_factor_less_than_0) );
        }
        to_meter = numerator / denominator;
        fr_meter = 1. / to_meter;
    }
};

template <typename Params, bool Vertical, int ToMeterI, int N>
struct pj_init_units_static<Params, Vertical, N, ToMeterI, N>
{
    template <typename T>
    static void apply(Params const& params,
                      T & to_meter, T & fr_meter,
                      T const& , T const& )
    {
        to_meter = boost::tuples::get<ToMeterI>(params).value;
        fr_meter = 1. / to_meter;
    }
};

template <typename Params, bool Vertical, int N>
struct pj_init_units_static<Params, Vertical, N, N, N>
{
    template <typename T>
    static void apply(Params const& ,
                      T & to_meter, T & fr_meter,
                      T const& default_to_meter, T const& default_fr_meter)
    {
        to_meter = default_to_meter;
        fr_meter = default_fr_meter;
    }
};

template <typename T, bool Vertical, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX>
inline void pj_init_units(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& params,
                          T & to_meter,
                          T & fr_meter,
                          T const& default_to_meter,
                          T const& default_fr_meter)
{
    pj_init_units_static
        <
            srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX>,
            Vertical
        >::apply(params, to_meter, fr_meter, default_to_meter, default_fr_meter);
}

/************************************************************************/
/*                           pj_init_pm()                               */
/************************************************************************/

template <typename T>
inline void pj_init_pm(srs::detail::proj4_parameters const& params, T& val)
{
    std::string pm = pj_get_param_s(params, "pm");
    if (! pm.empty())
    {
        int n = sizeof(pj_prime_meridians) / sizeof(pj_prime_meridians[0]);
        for (int i = 0; i < n ; i++)
        {
            if(pj_prime_meridians[i].id == pm)
            {
                val = pj_prime_meridians[i].deg * math::d2r<T>();
                return;
            }
        }

        // TODO: Is this try-catch needed?
        // In other cases the bad_str_cast exception is simply thrown
        BOOST_TRY
        {
            val = dms_parser<T, true>::apply(pm).angle();
            return;
        }
        BOOST_CATCH(geometry::bad_str_cast const&)
        {
            BOOST_THROW_EXCEPTION( projection_exception(error_unknown_prime_meridian) );
        }
        BOOST_CATCH_END
    }
    
    val = 0.0;
}

template <typename T>
inline void pj_init_pm(srs::dpar::parameters<T> const& params, T& val)
{
    typename srs::dpar::parameters<T>::const_iterator it = pj_param_find(params, srs::dpar::pm);
    if (it != params.end())
    {
        if (it->template is_value_set<int>())
        {
            int n = sizeof(pj_prime_meridians) / sizeof(pj_prime_meridians[0]);
            int i = it->template get_value<int>();
            if (i >= 0 && i < n)
            {
                val = pj_prime_meridians[i].deg * math::d2r<T>();
                return;
            }
            else
            {
                BOOST_THROW_EXCEPTION( projection_exception(error_unknown_prime_meridian) );
            }
        }
        else if (it->template is_value_set<T>())
        {
            val = it->template get_value<T>() * math::d2r<T>();
            return;
        }
    }

    val = 0.0;
}

template
<
    typename Params,
    int I = geometry::tuples::find_index_if
        <
            Params,
            srs::spar::detail::is_param_tr<srs::spar::detail::pm_traits>::pred
        >::value,
    int N = boost::tuples::length<Params>::value
>
struct pj_init_pm_static
{
    template <typename T>
    static void apply(Params const& params, T & val)
    {
        typedef typename boost::tuples::element<I, Params>::type param_type;

        val = srs::spar::detail::pm_traits<param_type>::value(boost::tuples::get<I>(params));
    }
};
template <typename Params, int N>
struct pj_init_pm_static<Params, N, N>
{
    template <typename T>
    static void apply(Params const& , T & val)
    {
        val = 0;
    }
};

template <typename T, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX>
inline void pj_init_pm(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& params, T& val)
{
    pj_init_pm_static
        <
            srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX>
        >::apply(params, val);
}

/************************************************************************/
/*                              pj_init()                               */
/*                                                                      */
/*      Main entry point for initialing a PJ projections                */
/*      definition.                                                     */
/************************************************************************/
template <typename T, typename Params>
inline parameters<T> pj_init(Params const& params)
{
    parameters<T> pin;

    // find projection -> implemented in projection factory
    pj_init_proj(params, pin);
    // exception thrown in projection<>
    // TODO: consider throwing here both projection_unknown_id_exception and
    // projection_not_named_exception in order to throw before other exceptions
    //if (pin.name.empty())
    //{ BOOST_THROW_EXCEPTION( projection_not_named_exception() ); }

    // NOTE: proj4 gets defaults from "proj_def.dat".
    // In Boost.Geometry this is emulated by manually setting them in
    // pj_ell_init and projections aea, lcc and lagrng
    
    /* set datum parameters */
    pj_datum_init(params, pin);

    /* set ellipsoid/sphere parameters */
    pj_ell_init(params, pin.a, pin.es);

    pin.a_orig = pin.a;
    pin.es_orig = pin.es;

    pin.e = sqrt(pin.es);
    pin.ra = 1. / pin.a;
    pin.one_es = 1. - pin.es;
    if (pin.one_es == 0.) {
        BOOST_THROW_EXCEPTION( projection_exception(error_eccentricity_is_one) );
    }
    pin.rone_es = 1./pin.one_es;

    /* Now that we have ellipse information check for WGS84 datum */
    if( pin.datum_type == datum_3param
        && pin.datum_params[0] == 0.0
        && pin.datum_params[1] == 0.0
        && pin.datum_params[2] == 0.0
        && pin.a == 6378137.0
        && geometry::math::abs(pin.es - 0.006694379990) < 0.000000000050 )/*WGS84/GRS80*/
    {
        pin.datum_type = datum_wgs84;
    }

    /* set pin.geoc coordinate system */
    pin.geoc = (pin.es && pj_get_param_b<srs::spar::geoc>(params, "geoc", srs::dpar::geoc));

    /* over-ranging flag */
    pin.over = pj_get_param_b<srs::spar::over>(params, "over", srs::dpar::over);

    /* longitude center for wrapping */
    pin.is_long_wrap_set = pj_param_r<srs::spar::lon_wrap>(params, "lon_wrap", srs::dpar::lon_wrap, pin.long_wrap_center);

    /* central meridian */
    pin.lam0 = pj_get_param_r<T, srs::spar::lon_0>(params, "lon_0", srs::dpar::lon_0);

    /* central latitude */
    pin.phi0 = pj_get_param_r<T, srs::spar::lat_0>(params, "lat_0", srs::dpar::lat_0);

    /* false easting and northing */
    pin.x0 = pj_get_param_f<T, srs::spar::x_0>(params, "x_0", srs::dpar::x_0);
    pin.y0 = pj_get_param_f<T, srs::spar::y_0>(params, "y_0", srs::dpar::y_0);

    /* general scaling factor */
    if (pj_param_f<srs::spar::k_0>(params, "k_0", srs::dpar::k_0, pin.k0)) {
        /* empty */
    } else if (pj_param_f<srs::spar::k>(params, "k", srs::dpar::k, pin.k0)) {
        /* empty */
    } else
        pin.k0 = 1.;
    if (pin.k0 <= 0.) {
        BOOST_THROW_EXCEPTION( projection_exception(error_k_less_than_zero) );
    }

    /* set units */
    pj_init_units<T, false>(params, pin.to_meter, pin.fr_meter, 1., 1.);
    pj_init_units<T, true>(params, pin.vto_meter, pin.vfr_meter, pin.to_meter, pin.fr_meter);

    /* prime meridian */
    pj_init_pm(params, pin.from_greenwich);

    return pin;
}


} // namespace detail
}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_INIT_HPP

/* pj_init.hpp
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
*/
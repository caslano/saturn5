// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020, Oracle and/or its affiliates.
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
#include <type_traits>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/tuple/tuple.hpp>

#include <boost/geometry/core/static_assert.hpp>

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

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/condition.hpp>


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

template <typename T, typename ...Ps>
inline void pj_init_proj(srs::spar::parameters<Ps...> const& ,
                         parameters<T> & par)
{
    typedef srs::spar::parameters<Ps...> params_type;
    typedef typename geometry::tuples::find_if
        <
            params_type,
            srs::spar::detail::is_param_tr<srs::spar::detail::proj_traits>::pred
        >::type proj_type;

    static const bool is_found = geometry::tuples::is_found<proj_type>::value;

    BOOST_GEOMETRY_STATIC_ASSERT((is_found), "Projection not named.", params_type);

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
            std::conditional_t
                <
                    Vertical,
                    srs::spar::detail::is_param_t<srs::spar::vunits>,
                    srs::spar::detail::is_param_tr<srs::spar::detail::units_traits>
                >::template pred
        >::value,
    int ToMeterI = geometry::tuples::find_index_if
        <
            Params,
            std::conditional_t
                <
                    Vertical,
                    srs::spar::detail::is_param_t<srs::spar::vto_meter>,
                    srs::spar::detail::is_param_t<srs::spar::to_meter>
                >::template pred
        >::value,
    int N = geometry::tuples::size<Params>::value
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
                        typename geometry::tuples::element<UnitsI, Params>::type
                    >::id;
    static const bool is_valid = i >= 0 && i < n;

    BOOST_GEOMETRY_STATIC_ASSERT((is_valid), "Unknown unit ID.", Params);

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
        to_meter = geometry::tuples::get<ToMeterI>(params).value;
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

template <typename T, bool Vertical, typename ...Ps>
inline void pj_init_units(srs::spar::parameters<Ps...> const& params,
                          T & to_meter,
                          T & fr_meter,
                          T const& default_to_meter,
                          T const& default_fr_meter)
{
    pj_init_units_static
        <
            srs::spar::parameters<Ps...>,
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
    int N = geometry::tuples::size<Params>::value
>
struct pj_init_pm_static
{
    template <typename T>
    static void apply(Params const& params, T & val)
    {
        typedef typename geometry::tuples::element<I, Params>::type param_type;

        val = srs::spar::detail::pm_traits<param_type>::value(geometry::tuples::get<I>(params));
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

template <typename T, typename ...Ps>
inline void pj_init_pm(srs::spar::parameters<Ps...> const& params, T& val)
{
    pj_init_pm_static
        <
            srs::spar::parameters<Ps...>
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
0dliEgsNS6FlofpIRolwfEPbXWM7RqO/DnEYOP1ld+iZBz1JGK6muIX/k6Us97bRNpdLWApzNyjNLyvX6leRtW9hr8qsWqUMw9kuz5+x4tBCGiyvZXSdhnuJRo97kYr40rZ4q5pVlc67H9SLsHCp5SDHJznmgDVxj0NTWROyA1I7eCksHZy3IEDlJ6vAYJ+E4wz3Mbv1nK4A1rekrbnZahbp7Sy1iS7fPOz7ikB5HZtyUBVhtbmt7bH4kNtI/7oB/5k7hw7DaPRY+jScNnMN/aTjO9cEd74bL1yZObz3g0dF3NP7D3GntYioh3q/gv9lYJqNOuJLrfCIA193k4VtB9FSaGjJQo+njRUlfsf2gm644AO86tG6JwYCX6kB4JguUPZB7d8D9ECww0uyLM5oHxNyrM1ylFrPbTjFM2AltwdOsOqRXrOASjZWEMyVtLvDoQcp9WF3EqTnj1jxFqs0DtPhl7X/uSnyfum3d8I6zdZV7doWH2JCZTsq3lbS0pVVxcaN/N7zGmBsxjdL2wbj2o1hJQEFlzl35H2A5gGzGbVZ7E76FZt1VOyaXmPJUPoVs7VU7JpfY8VkGR3bnzcq+YoDjZLsMUaz5ni2j5YriKoMw41LVrX3mFQ/Y1PHg6AawaqiIEU+Ci7yzLtWSXR/sEzGIedCsEZNXdxj8tPIV4ara4BYM7JBPpE6DQgiJjMOogH9oFy81vaNTdL3Q1Jq67/KNWNTVqJYVhTHondpPRBBYdPz6vMJW/uq3XcR7nHNk7i5fuzCH4+peuBKW851Chl8kiUNpofWK6XR7g53U7nmC+UeIoKHD5DHTOsTSoISg2g88SMnKY6q8+U70RH8UeWnW9MQ/tkzta9R5V4J8wDEzJez8EUyqNhgoozjXzrJH5iZ80gPxnvbuqcJfAUIq1vWapTHsTbhle2mIS8dnLKLYc6FcSWwyOis4oggzE7s+jaqOGv9NqrhXJtZ1ULrmQ4WDBRFtlTp1h+iENxt9m8qT72P30LNKje9Zn/Fb3rt1nS6e4W6ZW9yq7eJZk6OI1p7lEdx7eSUy8ORju0cd3gZ3iW+u5vx47B67+Ss/RG/9I/tr3Ijfjq1PsgPeufXb0ixmtBNp08gDS8q45DihthGtIx20OS+PWYx07qQqzwN6928nu81rZr9vLq4RPl5BbvF+L88m4casTKtvx5dc5biH4RDyZ+bYlCyLQ5+rg+Fd0EzrrhD2VOqSDkl/aZcSG+seWOjKmOrS8WDBsC15JmPWptzzMZvrHinUnYWvTIoawdd87OzsyHtY7WUCuMA5jtebSvSG1jw/8wk+fltCNqP7X1qiMeLtbdDQyOk57e45Q88lV98MHC4Z3pfDAfv0LmwwB2T6jwqqshbR9/X+hTMF7dSCDvItlO5ytxYvPTiWKMR52Cc784t02KJkWlA4riOyrYT+SHg9XHRnIZ9N3nW9l197vAznoIpXzg+6qixNEssbLHTWcWNIIjWWKLuUMnpL9yhktK8kZrof73ZItjzQLUDh8euOmIO3czhN9KR4InvHnOBlJuoQs2e0RNOlcOlwr+tr8j+6cEMDiDGu5EOND7hmYm5W80byuUQ/DlZxX6mFxkRrcKVqI/yabMjhgxSqULyFwObJhPU0DIvRhB0KlXngyTitca+LDOetYvxZahuikprpQ9b/s54uu+qEGXE7nrnteeK2bVjPpVuB2MKqo2ct1S6+WZC0zHc7G9/kDUMrf+8xlyLULBNYbGd54c8zSN208jG7V6Yj9MQVW0LAPK3Tf4HHt+1Vfqiec6qmu9xKwCBuY5OSsNzW/TyfaN88g0+G91btOIFoKponwkrvt8fXGeso07RusZv7voo+JG0pohjOr3Bbt6o46m0oGtj9XHaWXyVrH/0x+k0LQ5p4nKaqW8Ri+aKVYeeuo0C8INFZgR1ZeY3nFsbZ3DZBaFZprJUvbDhtkNmPhagftagflrQ1uhZg2sgtsRHTbE3sTdS3cFbFbW5KeB0zh5FyN8g3sx1Yvoob957iEVuN82JRsfhtrV+FN7cFhAbYHJfF01V3yk9UHLAWTpWGh8w8oTPlzA1begTq2rTQaLhosPbBRkBxBS8xCqHz5l8lt44cL4KScOKtSf8sM3pKx7KamgMXvahX6+VoNIgWJ/iXleCsCei57CLpTMK5Cv5qRRwv6mQ4GkDZWTQOc42iB83eD5ouV3uR35FtZO2wK3wRCT/cVirNNjnck2K1rrWfWCi/5KnCVdOfIV6V0A/NfAhJA5TJ35eUm6jGMAgAaosWx3mQehMcoqNbQ5c9bAZ9EegnE18RbDCrLT8imUKyJOZhiU4tdwgCsz5liHgGJtnrywlqGFk1VXGcjUBsx6JonFisQp8c4OGEWSZsQ3ZXM8/VogJXFkHZLD2X7BfADBCuZ68LUQUXnFxbn4bGPGjLg1bhutaEx1ka50yLt55uaAnzB1ccIMgq68PpSSpV0UK3YqpxBhOYoHqWaDYeQGvgjpGtFWRi7f6olyvwp3kYX868Dh205H7pPQZZ0Aez/xyLMHrsmLgbXFEf3DJsMWewh0lvCbiGQN1E76asdTaOz0hZHOLOk3Gze6T+DMIt39LCckyDoRQkYYReBcXWfcUQcPz/HA2NJSSbavMeGfpDS1yUzFiMHs47GVCRTJqQ8G6Ty5XpzMsHJGJSf3NrmZ/3YFQbyvPEyaSVKEkhWrfdhRTBB+j/GUGY5mQEu82aCGxKdmmT+vcFXPHghP/h2DkexxQ2+RiDWNfN6JqJSZ1VVM/r2oMF+QK+NEsKG7kVqIZDLfLlILEjgSCn+BRavPtydCZ8NtlWAHT1oekePSGkPEtKER1rTg2gtmVkHvDV0XGJZ23YmS8DWDKHhWXfAx9Gxr5MXHeuk2eRavrkaA7XsHTDYw8XZlRIOS0nmbRJUw87j6Zx6mrspdNMjeKkKU2cwOWZxHXeR4ZR8+S7+0Su71M06/0Xh1T/lnRG1s+Z683zv+gdsB/63OF+kLX4EoAdr+eCg1r11LJQiNt+J1Bw5exBxhzeGOFtPoVzgC183Qu5u1qOXtFVhijlXzbbF4biMmALxKv9o/EQf3YEIssKWfZ0lSDTif2PqMYX1bCAoTBKM2Zvcwgf60sk/f2iFEUyRj+sTQBWYb5UFzARNiQMbi8wLqbMjcW/Z5mzAdjbr+e3QoZv3ImnxBW7loyBMEhjXsmIrcb0MwpFTHZLc6mCQ/k5nEy39oB6WaMeOBuZi1UAVgbycScE5jK4RgeixGvB7XMnEuABdLOyYFgtR+Ne7rswtdKiWWH9jyJXLecM96UK34vXRUM/8/fHaWgO/5PMJ7IlxmDAIq0oVEwpOgcSgcJT2k/eSiq5acrawOdBSOpicE8o6GVr/CjRjdlXYlpb7PcrPPlQfsBWGHGbOx1zC2jchEiqNwfLukjOmU94i4YmU0WwIdPuIBRwrLyMKQMAvSq5JOeH9pIoK7yCUI+VqKD5/6KiHpg/aGndMFXxQrUaqJJ+yUkFd25JgbdSU6o2ybRV6qAWA6ish9cwjv+RYat6XnVs6q2kIk1WyXMsbEXZouudotrEpaxYrf6TKeoo3ZflTz2BS59L9jKkyFv4PI0ApCpXSBFbyLVyuSbC/r8K9zWys4qXI8k60ONkXH0I2+RSQKLdWc+XCTRxxDS3RfEm7fOv08c2BQbJ/zzqfLn++VR2z0Ig/fGYlaWVB+cDhwmPGvPuYtBGH8s5nY2n5dCIXVEmkd2m918C3Q3N8Bh9SCL/+2yjjpswGKorjjgekK+G/F3pK5J+eyBwZTp4Vn0+r4phOPIdd9bS5BAKQ9SOodkW7qgD1nZhkUzVdvytOeMTWspy7IYX9hQ6XujAtX/8/NO3FFiXQ1qrREBPaqJd+YPvcxJVG4cz6lo0mwIJpUjbonKDUQ0hsmAMZ6kmm7JLkPy9oMgHASvyACHlp7Wp49LzFNnaK7QLpGkY2vfQ2ZesBvJulox+pj9dPAyX1ZNSKi/luQpDeKwjeKFtQj0ULAcCMAHMnAnMdzy48Zr3/tZpKxizYJG3Za0v6VtGbe5G7b2Nri2ZnlUyQkLtnOXiOnksiQVX2aPJSSsGsFkwRl+EzCwAm+rSnYPsOfJ0jRdYHPKi47wNXbNWI2GPizKLnG1ilqW5GzSy5C+gM0u94VC5qYRpXERy4gvN8IVi2jrVfAxx0G8SKLuY/G9cWHwPZgR3HmF8Z3IOhHfaR3gfPRtJQ7vsRDP4OuVPLCxAiYc+ziscE54EZXc1iI6UvWn87Q2trzfnvpz2D8HVlYpo/gSinO+nflHWHeHeuDZkOB5zthdIbHpbd44UJWFMzPdXN/QqGp1zda0uTiy/egzAvII6SEVhnGhMfLuZJ6ZNDNnLinnQzCe/k/OB/Pjp9fo29MWtbMzxPvBBKfvy8Mf5aCEJVOp8suGBpuKdT2zCrhmWKVDob/K+HERgx+oOazeQ+QeHVXiXqbnKMLc/FjF+FMLPxnouUq4tAxam8t+jSMPn2Nl0MxRayeePcO+98HJIiqoi8xzhMvfdwzqmDuXOPp4/XT1k/DE5dxO8Q8aIEzEnUluOptL4PaxXNja2P3AgXAaoz2WIC+CsCqruJsnw3ZEp2rZXld85DQIegFqfNtOCWx3T7NANmjGjL1T6Bc/74iyEq3Y69cA2ijqOSr84bD8/en2kbmbB04une8WZcxqyxjU5pjUwv/G28cIA/Wa6u6ANhlVmnD6Zt0FdlSDYZ8sNu1jLy5etd4BpdjFx1sT3sKesp8Wkfctdb02ZrdZ8EHDVvGehJjpM8IH+80Tdi12Po4J0LF7aLKTPUdZrnyQBxNfgVkvCc0fzLDD/9b+pNf3iVHZFdiwlYquxUKvXp/C1e9uC7qJ49CedJpWMs85WTXYDR+DTf+1B5/mdEmS9cgvfxg6d4h5xqZbXWADfvJ5tjVKZudA0yTnxWKKURlLhRPn1Pu0yn8L8zBRzB9cTJyyoSuPn6Gi7ZWdZEXV0KZxSd8cOLZp7ZFm1D14ibthM0tNy+YRaZe+kMMzwQbz0Do8jqilqA6CA3e3YY9GjF5jK5z87NeydFMscad8YuNRdCL9cCwtnadeQ+UxrYQcRky3cAs0bd7XIk0s993qwvORo/mYlhwfhrlkM09VO7ohU7JKGjxtN+PJqSzgu8DVgcPt5T7vZz9rpRkCr+6NpPZhR3U3Er40rbVAdYSK03K8aPrEW0eqXp+u90Qbd9D6wFPcXfuhdkcdQDDyc/PAo6K+LVn1gMd/OOYI5SGhguRboF6farC0PGJZq6KCFLcqmzvMnlBqAnb/s10t8WaAZ/TqtTmAANwkOaaaWiqfxFy1Fw4YdnWaLBXjYfQj8KcaDIuv1NIbPi6wMstPfsMvi8DX35BwY67lK+7KAprXNvtz97GpWdqcn+O1hBFSjGNRj4V5UPDYZBZaPqKH64E2uCPcb/iRul+wq7mGMp57zVqPLRDgyvjTSCu3wdBMXLVBMUlE5p/5d8gDWyUFCHkxvggRUtoGSDD9UlQYLrezy9Dn4QnGUyEbuafocDedOKpM+lMhcVmyG6sTeaqUdOpnJ//R59e0TOVU7QxajgOIYwlPvV7W7BrusSWyZ7mbd253O9WiGfghMuv6Td510LmXZYWjhpqEggTccQH5ziqNHk2RIhw42DAIApJ9oFxaqoLVng79wMu9pvKGFEpOqDFS9HzRFM1t/pRaorELMXXecXE5S6lQxj5rlOYR2T+mh1P57Cc6yadFoaqH9gOTuScVFi6WWcMR8qr8HZr3UIIJCLeRvVszh8tKzIaJOe6SyzGlv0zAw3ux/47vVaMGG5XDnZkynM1211lIUBHru3Ky6es2Hk+4C2smyZ3pIs8355lmqO3n0NcQjv9I92T9uH3zYUGYxZBPOt9zP/Tj+5xkVwj9UHgqbfZ8yN+oPvJhShSPTLujOY8a8BPSkxlJU/XA0i2nQLkRVMQtwp7ppybDyrHA4hClR8CyWcoADCzz02WjZsjQFLEzQG/RapYd0I0JrS3UXQWiKuGyaduW54CCKVZOedp188t3y9y4l/vhyMQufmSfh0bgFKZ3Dof/HDmRRA9jUAWjvRFn4sDfcYq+WTwTMVizXLOoIiICu6PBcRVcFh/BjLm3Wn+9oLFWSq26gQ/rGTjBCZ1QevWq085+SDd99uHbhc2XqXIR9QuKyL4LudSsKeviXqM8TUVyFTC4tS4HntSrV14tSOO8C5UOEhxX8AoT+8VmWkzq4isAyb6uOzS2tHHD7wEd+gL9cAp+rhE8F1DPJgJPlrZjOwK83ySDnnCdHdm3PqL6vEvSC7vkUGFc3sLv87MTfxO+CgYTilXjm4WpAGpM/20mfTITppSbOrLG/KJmtyYXqULfWAsBOKW0hYINVt0fVDcUMYAPbjxFL9jReZ+q/RSAXhVmktWooO/JQCcYqmv77JdO+T3pKIqrS9bNg5Hs1jPVxRjvFiKKuxc0AnnuyV2qVRRP5SsSyEFjLOZ2lIqIB3Pmfmtrb/n8t2VdtsDxN8jFkX3XO09aaqjXOItlrepdMU91bAVnIgEgt7T15PFWdVqG8C6vmRkENNWbKqt3NF+76fkgjn6eJSrSE1dXYSysVHJ9gvSJR0tQQ8f882qWEY8ZdePSG/s9QFeZZLEli2AQ1ppEZrRBhrQzEE1uecd/BXqd3mWF+nrntS2xP1pJo4Cl45kIse53Od3TbK+e0izwMOqIPs9eXkEW6vWCSua/tAhpyVu8PNHoUT/OnO+NcnDxiACkMlXBQaC/mQU6ze8myFHFL5gt8LESwdvu8M8umy8D/rpL1e8sEAz7DXDKnq/bckeJiNcWt7Y96AWehbHJ2ee3YFpbkh6fx16aVXN8l/ncal8YfMkODiUAnDy6S0Fn89ailX7lfVkjVheTsyn300Ztd899FswBZT7talzJLNI2DeLXb5uurt7XS2cZ/6FIwN9MZ4JyJL1ow3i+RsA0211z55wMMPJLdEJveOg5ZJ3n6E9tGHIdpC9eKXPLEMxNfBrDPEWIzgDfggzE6rYy3oVPra1gVwlBcSW64h1I7VXONmsXnNHzomH4w3F3qS1AjzxJNTxKfEpNMn1YrELQDccYgdpdDp7r00eQcJHeP0N0mUwEEzltHO6KkcAwpw+50APU5OH1yPHnctBv14NqAnn5LByqZ9+hhmuigwJ4c1CM8zLNsw5QBJKYTk4xxXnMdyvSeVY1K7k7vfFDeY155XrlKZu49uczmi953I7QW89ujkVTJHzYvLNTV9qObOzdWLdHWF+m8m34VrKVYET+dWRgBlE8hWcJFU35x3l+PEet4yFA4MbF/YQynsZK7rJmAp8lb56t2xTGdrnfigVp8xvO0Ui6PnhIT3h4eAkULo3MH832nserpXHD1YYr8eVqBlaDgH6WscVrwKhw3ZcttlCZJcf5PpprA39DDmixZiAxL/9JYsgnrtEpKNjDsUVoo2n/tYn5/fAHnIHKNpKF5v8/D5p04TVSVDvwDQLiL2xinjSVY2mXUxa1/pj3B0U3tzEA0xIAD+E/6DfziVR9LfwdApkPYyudsWz2el5/PmlBXXk2c+2sFNOFRTC9lR/PoKTCWrHg1quLLtag5XrxneHcmXwz
*/
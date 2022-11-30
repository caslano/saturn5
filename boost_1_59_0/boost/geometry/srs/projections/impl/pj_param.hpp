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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PJ_PARAM_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PJ_PARAM_HPP


#include <iterator>
#include <string>
#include <type_traits>
#include <vector>

#include <boost/geometry/core/static_assert.hpp>

#include <boost/geometry/srs/projections/exception.hpp>

#include <boost/geometry/srs/projections/impl/dms_parser.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/proj4.hpp>
#include <boost/geometry/srs/projections/dpar.hpp>
#include <boost/geometry/srs/projections/spar.hpp>


namespace boost { namespace geometry { namespace projections {


namespace detail {

inline bool pj_param_pred(srs::detail::proj4_parameter const& p, std::string const& name)
{
    return p.name == name;
}

template
<
    typename T, typename Id,
    std::enable_if_t<! std::is_convertible<Id, std::string>::value, int> = 0
>
inline bool pj_param_pred(srs::dpar::parameter<T> const& p, Id const& id)
{
    return p.is_id_equal(id);
}

/* input exists */
template <typename Params, typename Name>
inline typename Params::const_iterator
    pj_param_find(Params const& params, Name const& name)
{
    typedef typename Params::const_iterator iterator;
    for (iterator it = params.begin(); it != params.end(); it++)
    {
        if (pj_param_pred(*it, name))
        {
            //it->used = true;
            return it;
        }
        // TODO: needed for pipeline
        /*else if (it->name == "step")
        {
            return pl.end();
        }*/
    }

    return params.end();
}

/*
template
<
    typename StaticParams,
    typename IsParamPred,
    int I = tuples_find_index_if<StaticParams, typename IsParamPred::pred>::value,
    int N = geometry::tuples::size<StaticParams>::value
>
struct pj_param_find_static
{
    typedef geometry::tuples::element<I, StaticParams> type;
    typedef const type* result_type;
    static result_type get(StaticParams const& params)
    {
        return boost::addressof(boost::get<I>(params));
    }
};

template <typename StaticParams, typename IsParamPred, int N>
struct pj_param_find_static<StaticParams, IsParamPred, N>
{
    typedef void type;
    typedef const type* result_type;
    static result_type get(StaticParams const& ) { return NULL; }
};*/


/* input exists */
template <typename Params, typename Name>
inline bool pj_param_exists(Params const& params, Name const& name)
{
    return pj_param_find(params, name) != params.end();
}

template <typename Param, typename ...Ps>
inline bool pj_param_exists(srs::spar::parameters<Ps...> const& )
{
    return geometry::tuples::is_found
        <
            typename geometry::tuples::find_if
                <
                    srs::spar::parameters<Ps...>,
                    srs::spar::detail::is_param<Param>::template pred
                >::type
        >::value;
}

template <template <typename> class Param, typename ...Ps>
inline bool pj_param_exists(srs::spar::parameters<Ps...> const& )
{
    return geometry::tuples::is_found
        <
            typename geometry::tuples::find_if
                <
                    srs::spar::parameters<Ps...>,
                    srs::spar::detail::is_param_t<Param>::template pred
                >::type
        >::value;
}


template <typename T>
inline void set_value(T & val, srs::detail::proj4_parameter const& p)
{
    val = geometry::str_cast<T>(p.value);
}

template <typename T, typename T2>
inline void set_value(T & val, srs::dpar::parameter<T2> const& p)
{
    val = p.template get_value<T>();
}

template <typename T>
inline void set_value_r(T & val, srs::detail::proj4_parameter const& p)
{
    val = dms_parser<T, true>::apply(p.value.c_str()).angle();
}

template <typename T>
inline void set_value_r(T & val, srs::dpar::parameter<T> const& p)
{
    val = p.template get_value<T>() * math::d2r<T>();
}

template <typename Name>
inline void check_name(Name const&)
{
    static const bool is_ok = std::is_convertible<Name, std::string>::value
                           || std::is_same<Name, srs::dpar::name_i>::value
                           || std::is_same<Name, srs::dpar::name_f>::value
                           || std::is_same<Name, srs::dpar::name_r>::value;
    BOOST_GEOMETRY_STATIC_ASSERT((is_ok), "Invalid argument.", Name);
}


/* integer input */
template <typename Params, typename Name>
inline bool _pj_param_i(Params const& params, Name const& name, int & par)
{
    check_name(name);
    typename Params::const_iterator it = pj_param_find(params, name);
    if (it != params.end())
    {
        set_value(par, *it);
        return true;
    }    
    return false;
}

/* floating point input */
template <typename T, typename Params, typename Name>
inline bool _pj_param_f(Params const& params, Name const& name, T & par)
{
    check_name(name);
    typename Params::const_iterator it = pj_param_find(params, name);        
    if (it != params.end())
    {
        set_value(par, *it);
        return true;
    }    
    return false;
}

/* radians input */
template <typename T, typename Params, typename Name>
inline bool _pj_param_r(Params const& params, Name const& name, T & par)
{
    check_name(name);
    typename Params::const_iterator it = pj_param_find(params, name);        
    if (it != params.end())
    {
        set_value_r(par, *it);
        return true;
    }    
    return false;
}

/* bool input */
inline bool _pj_get_param_b(srs::detail::proj4_parameters const& pl, std::string const& name)
{
    srs::detail::proj4_parameters::const_iterator it = pj_param_find(pl, name);        
    if (it != pl.end())
    {
        switch (it->value[0])
        {
        case '\0': case 'T': case 't':
            return true;
        case 'F': case 'f':
            return false;
        default:
            BOOST_THROW_EXCEPTION( projection_exception(error_invalid_boolean_param) );
            return false;
        }
    }    
    return false;
}

template <typename T>
inline bool _pj_get_param_b(srs::dpar::parameters<T> const& pl, srs::dpar::name_be const& name)
{
    bool result = false;
    typename srs::dpar::parameters<T>::const_iterator it = pj_param_find(pl, name);
    if (it != pl.end())
        set_value(result, *it);
    return result;
}

/* string input */
inline bool pj_param_s(srs::detail::proj4_parameters const& pl, std::string const& name, std::string & par)
{
    srs::detail::proj4_parameters::const_iterator it = pj_param_find(pl, name);        
    if (it != pl.end())
    {
        par = it->value;
        return true;
    }    
    return false;
}

template
<
    typename Params,
    template <typename> class IsSamePred,
    int I = geometry::tuples::find_index_if<Params, IsSamePred>::value,
    int N = geometry::tuples::size<Params>::value
>
struct _pj_param_x_static
{
    static const bool result = true;
    template <typename T>
    static void apply(Params const& params, T & out)
    {
        // TODO: int values could be extracted directly from the type
        out = geometry::tuples::get<I>(params).value;
    }
};

template
<
    typename Params,
    template <typename> class IsSamePred,
    int N
>
struct _pj_param_x_static<Params, IsSamePred, N, N>
{
    static const bool result = false;
    template <typename T>
    static void apply(Params const& , T & )
    {}
};

template <template <int> class Param, typename ...Ps>
inline bool _pj_param_i(srs::spar::parameters<Ps...> const& params, int & par)
{
    typedef _pj_param_x_static
        <
            srs::spar::parameters<Ps...>,
            srs::spar::detail::is_param_i<Param>::template pred
        > impl;
    impl::apply(params, par);
    return impl::result;
}

template <template <typename> class Param, typename ...Ps, typename T>
inline bool _pj_param_f(srs::spar::parameters<Ps...> const& params, T & par)
{
    typedef _pj_param_x_static
        <
            srs::spar::parameters<Ps...>,
            srs::spar::detail::is_param_t<Param>::template pred
        > impl;
    impl::apply(params, par);
    return impl::result;
}

template <template <typename> class Param, typename ...Ps, typename T>
inline bool _pj_param_r(srs::spar::parameters<Ps...> const& params, T & par)
{
    typedef _pj_param_x_static
        <
            srs::spar::parameters<Ps...>,
            srs::spar::detail::is_param_t<Param>::template pred
        > impl;
    impl::apply(params, par);
    if (impl::result)
        par *= math::d2r<T>();
    return impl::result;
}

template <typename Param, typename ...Ps>
inline bool _pj_get_param_b(srs::spar::parameters<Ps...> const& params)
{
    return pj_param_exists<Param>(params);
}

//template <typename T, typename Name, typename Value>
//inline bool pj_param_id(srs::dpar::parameters<T> const& pl, Name const& name, Value & par)
//{
//    typename srs::dpar::parameters<T>::const_iterator it = pj_param_find(pl, name);
//    if (it != pl.end())
//    {
//        par = static_cast<Value>(it->template get_value<int>());
//        return true;
//    }    
//    return false;
//}

// NOTE: In the original code, in pl_ell_set.c there is a function pj_get_param
// which behavior is similar to pj_param but it doesn't set `user` member to TRUE
// while pj_param does in the original code. In Boost.Geometry this member is not used.
template <typename Params, typename Name>
inline int _pj_get_param_i(Params const& pl, Name const& name)
{
    int res = 0;
    _pj_param_i(pl, name, res);
    return res;
}

template <template <int> class Param, typename Params>
inline int _pj_get_param_i(Params const& pl)
{
    int res = 0;
    _pj_param_i<Param>(pl, res);
    return res;
}

template <typename T, typename Params, typename Name>
inline T _pj_get_param_f(Params const& pl, Name const& name)
{
    T res = 0;
    _pj_param_f(pl, name, res);
    return res;
}

template <typename T, template <typename> class Param, typename Params>
inline T _pj_get_param_f(Params const& pl)
{
    T res = 0;
    _pj_param_f<Param>(pl, res);
    return res;
}

template <typename T, typename Params, typename Name>
inline T _pj_get_param_r(Params const& pl, Name const& name)
{
    T res = 0;
    _pj_param_r(pl, name, res);
    return res;
}

template <typename T, template <typename> class Param, typename Params>
inline T _pj_get_param_r(Params const& pl)
{
    T res = 0;
    _pj_param_r<Param>(pl, res);
    return res;
}

inline std::string pj_get_param_s(srs::detail::proj4_parameters const& pl, std::string const& name)
{
    std::string res;
    pj_param_s(pl, name, res);
    return res;
}


// ------------------------------------------------------------------------- //

template <typename Param, typename Name>
inline bool pj_param_exists(srs::detail::proj4_parameters const& pl,
                            std::string const& sn,
                            Name const& )
{
    return pj_param_exists(pl, sn);
}
template <template <typename> class Param, typename Name>
inline bool pj_param_exists(srs::detail::proj4_parameters const& pl,
                            std::string const& sn,
                            Name const& )
{
    return pj_param_exists(pl, sn);
}
template <typename Param, typename T, typename Name>
inline bool pj_param_exists(srs::dpar::parameters<T> const& pl,
                            std::string const& ,
                            Name const& n)
{
    return pj_param_exists(pl, n);
}
template <template <typename> class Param, typename T, typename Name>
inline bool pj_param_exists(srs::dpar::parameters<T> const& pl,
                            std::string const& ,
                            Name const& n)
{
    return pj_param_exists(pl, n);
}
template <typename Param, typename ...Ps, typename Name>
inline bool pj_param_exists(srs::spar::parameters<Ps...> const& pl,
                            std::string const& ,
                            Name const& )
{
    return pj_param_exists<Param>(pl);
}
template <template <typename> class Param, typename ...Ps, typename Name>
inline bool pj_param_exists(srs::spar::parameters<Ps...> const& pl,
                            std::string const& ,
                            Name const& )
{
    return pj_param_exists<Param>(pl);
}

template <typename Param>
inline bool pj_get_param_b(srs::detail::proj4_parameters const& pl,
                           std::string const& sn,
                           srs::dpar::name_be const& )
{
    return _pj_get_param_b(pl, sn);
}
template <typename Param, typename T>
inline bool pj_get_param_b(srs::dpar::parameters<T> const& pl,
                           std::string const& ,
                           srs::dpar::name_be const& n)
{
    return _pj_get_param_b(pl, n);
}
template <typename Param, typename ...Ps>
inline bool pj_get_param_b(srs::spar::parameters<Ps...> const& pl,
                           std::string const& ,
                           srs::dpar::name_be const& )
{
    return _pj_get_param_b<Param>(pl);
}

//#define BOOST_GEOMETRY_GET_PARAM_B(PARAMS, NAME) pj_get_param_b(PARAMS, #NAME, srs::dpar::NAME)

template <template <int> class Param>
inline bool pj_param_i(srs::detail::proj4_parameters const& pl,
                       std::string const& sn,
                       srs::dpar::name_i const& ,
                       int & par)
{
    return _pj_param_i(pl, sn, par);
}
template <template <int> class Param, typename T>
inline bool pj_param_i(srs::dpar::parameters<T> const& pl,
                       std::string const& ,
                       srs::dpar::name_i const& n,
                       int & par)
{
    return _pj_param_i(pl, n, par);
}
template <template <int> class Param, typename ...Ps>
inline bool pj_param_i(srs::spar::parameters<Ps...> const& pl,
                       std::string const& ,
                       srs::dpar::name_i const& ,
                       int & par)
{
    return _pj_param_i<Param>(pl, par);
}

//#define BOOST_GEOMETRY_PARAM_I(PARAMS, NAME, PAR) pj_param_i(PARAMS, #NAME, srs::dpar::NAME, PAR)

template <template <int> class Param>
inline int pj_get_param_i(srs::detail::proj4_parameters const& pl,
                          std::string const& sn,
                          srs::dpar::name_i const& )
{
    return _pj_get_param_i(pl, sn);
}
template <template <int> class Param, typename T>
inline int pj_get_param_i(srs::dpar::parameters<T> const& pl,
                          std::string const& ,
                          srs::dpar::name_i const& n)
{
    return _pj_get_param_i(pl, n);
}
template <template <int> class Param, typename ...Ps>
inline bool pj_get_param_i(srs::spar::parameters<Ps...> const& pl,
                           std::string const& ,
                           srs::dpar::name_i const& )
{
    return _pj_get_param_i<Param>(pl);
}

//#define BOOST_GEOMETRY_GET_PARAM_I(PARAMS, NAME) pj_get_param_i(PARAMS, #NAME, srs::dpar::NAME)

template <template <typename> class Param, typename T>
inline bool pj_param_f(srs::detail::proj4_parameters const& pl,
                       std::string const& sn,
                       srs::dpar::name_f const& ,
                       T & par)
{
    return _pj_param_f(pl, sn, par);
}
template <template <typename> class Param, typename T>
inline bool pj_param_f(srs::dpar::parameters<T> const& pl,
                       std::string const& ,
                       srs::dpar::name_f const& n,
                       T & par)
{
    return _pj_param_f(pl, n, par);
}
template <template <typename> class Param, typename ...Ps, typename T>
inline bool pj_param_f(srs::spar::parameters<Ps...> const& pl,
                       std::string const& ,
                       srs::dpar::name_f const& ,
                       T & par)
{
    return _pj_param_f<Param>(pl, par);
}

//#define BOOST_GEOMETRY_PARAM_F(PARAMS, NAME, PAR) pj_param_f(PARAMS, #NAME, srs::dpar::NAME, PAR)

template <typename T, template <typename> class Param>
inline T pj_get_param_f(srs::detail::proj4_parameters const& pl,
                        std::string const& sn,
                        srs::dpar::name_f const& )
{
    return _pj_get_param_f<T>(pl, sn);
}
template <typename T, template <typename> class Param>
inline T pj_get_param_f(srs::dpar::parameters<T> const& pl,
                        std::string const& ,
                        srs::dpar::name_f const& n)
{
    return _pj_get_param_f<T>(pl, n);
}
template <typename T, template <typename> class Param, typename ...Ps>
inline T pj_get_param_f(srs::spar::parameters<Ps...> const& pl,
                        std::string const& ,
                        srs::dpar::name_f const& )
{
    return _pj_get_param_f<T, Param>(pl);
}


//#define BOOST_GEOMETRY_GET_PARAM_F(PARAMS, NAME) pj_get_param_f<T>(PARAMS, #NAME, srs::dpar::NAME)

template <template <typename> class Param, typename T>
inline bool pj_param_r(srs::detail::proj4_parameters const& pl,
                       std::string const& sn,
                       srs::dpar::name_r const& ,
                       T & par)
{
    return _pj_param_r(pl, sn, par);
}
template <template <typename> class Param, typename T>
inline bool pj_param_r(srs::dpar::parameters<T> const& pl,
                       std::string const& ,
                       srs::dpar::name_r const& n,
                       T & par)
{
    return _pj_param_r(pl, n, par);
}
template <template <typename> class Param, typename ...Ps, typename T>
inline bool pj_param_r(srs::spar::parameters<Ps...> const& pl,
                       std::string const& ,
                       srs::dpar::name_r const& ,
                       T & par)
{
    return _pj_param_r<Param>(pl, par);
}

//#define BOOST_GEOMETRY_PARAM_R(PARAMS, NAME, PAR) pj_param_r(PARAMS, #NAME, srs::dpar::NAME, PAR)

template <typename T, template <typename> class Param>
inline T pj_get_param_r(srs::detail::proj4_parameters const& pl,
                        std::string const& sn,
                        srs::dpar::name_r const& )
{
    return _pj_get_param_r<T>(pl, sn);
}
template <typename T, template <typename> class Param>
inline T pj_get_param_r(srs::dpar::parameters<T> const& pl,
                        std::string const& ,
                        srs::dpar::name_r const& n)
{
    return _pj_get_param_r<T>(pl, n);
}
template <typename T, template <typename> class Param, typename ...Ps>
inline T pj_get_param_r(srs::spar::parameters<Ps...> const& pl,
                        std::string const& ,
                        srs::dpar::name_r const& )
{
    return _pj_get_param_r<T, Param>(pl);
}

//#define BOOST_GEOMETRY_GET_PARAM_R(PARAMS, NAME) pj_get_param_r<T>(PARAMS, #NAME, srs::dpar::NAME)

} // namespace detail
}}} // namespace boost::geometry::projections

#endif

/* pj_param.hpp
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
*/
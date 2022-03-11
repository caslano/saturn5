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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PJ_PARAM_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PJ_PARAM_HPP


#include <string>
#include <vector>

#include <boost/geometry/srs/projections/exception.hpp>

#include <boost/geometry/srs/projections/impl/dms_parser.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/proj4.hpp>
#include <boost/geometry/srs/projections/dpar.hpp>
#include <boost/geometry/srs/projections/spar.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_same.hpp>
#include <iterator>


namespace boost { namespace geometry { namespace projections {


namespace detail {

inline bool pj_param_pred(srs::detail::proj4_parameter const& p, std::string const& name)
{
    return p.name == name;
}

template <typename T, typename Id>
inline bool pj_param_pred(srs::dpar::parameter<T> const& p, Id const& id,
                          typename boost::disable_if_c<boost::is_convertible<Id, std::string>::value>::type * = 0)
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
    int N = boost::tuples::length<StaticParams>::value
>
struct pj_param_find_static
{
    typedef boost::tuples::element<I, StaticParams> type;
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

template <typename Param, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX>
inline bool pj_param_exists(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& )
{
    return geometry::tuples::is_found
        <
            typename geometry::tuples::find_if
                <
                    srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX>,
                    srs::spar::detail::is_param<Param>::template pred
                >::type
        >::value;
}

template <template <typename> class Param, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX>
inline bool pj_param_exists(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& )
{
    return geometry::tuples::is_found
        <
            typename geometry::tuples::find_if
                <
                    srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX>,
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
    static const bool is_ok = boost::is_convertible<Name, std::string>::value
                           || boost::is_same<Name, srs::dpar::name_i>::value
                           || boost::is_same<Name, srs::dpar::name_f>::value
                           || boost::is_same<Name, srs::dpar::name_r>::value;
    BOOST_MPL_ASSERT_MSG((is_ok), INVALID_ARGUMENT, (Name));
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
    int N = boost::tuples::length<Params>::value
>
struct _pj_param_x_static
{
    static const bool result = true;
    template <typename T>
    static void apply(Params const& params, T & out)
    {
        // TODO: int values could be extracted directly from the type
        out = boost::tuples::get<I>(params).value;
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

template <template <int> class Param, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX>
inline bool _pj_param_i(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& params, int & par)
{
    typedef _pj_param_x_static
        <
            srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX>,
            srs::spar::detail::is_param_i<Param>::template pred
        > impl;
    impl::apply(params, par);
    return impl::result;
}

template <template <typename> class Param, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX, typename T>
inline bool _pj_param_f(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& params, T & par)
{
    typedef _pj_param_x_static
        <
            srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX>,
            srs::spar::detail::is_param_t<Param>::template pred
        > impl;
    impl::apply(params, par);
    return impl::result;
}

template <template <typename> class Param, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX, typename T>
inline bool _pj_param_r(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& params, T & par)
{
    typedef _pj_param_x_static
        <
            srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX>,
            srs::spar::detail::is_param_t<Param>::template pred
        > impl;
    impl::apply(params, par);
    if (impl::result)
        par *= math::d2r<T>();
    return impl::result;
}

template <typename Param, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX>
inline bool _pj_get_param_b(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& params)
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
template <typename Param, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX, typename Name>
inline bool pj_param_exists(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& pl,
                            std::string const& ,
                            Name const& )
{
    return pj_param_exists<Param>(pl);
}
template <template <typename> class Param, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX, typename Name>
inline bool pj_param_exists(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& pl,
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
template <typename Param, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX>
inline bool pj_get_param_b(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& pl,
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
template <template <int> class Param, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX>
inline bool pj_param_i(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& pl,
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
template <template <int> class Param, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX>
inline bool pj_get_param_i(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& pl,
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
template <template <typename> class Param, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX, typename T>
inline bool pj_param_f(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& pl,
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
template <typename T, template <typename> class Param, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX>
inline T pj_get_param_f(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& pl,
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
template <template <typename> class Param, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX, typename T>
inline bool pj_param_r(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& pl,
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
template <typename T, template <typename> class Param, BOOST_GEOMETRY_PROJECTIONS_DETAIL_TYPENAME_PX>
inline T pj_get_param_r(srs::spar::parameters<BOOST_GEOMETRY_PROJECTIONS_DETAIL_PX> const& pl,
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
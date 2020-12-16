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
Pk28nRN/PXQ9b7FtxNjosr61Zd2pJF9N51FifEySr+x9/xX11TFzNXfKfeY1TfNjTMlivA06v1XcWV7pU76mpXrJ/Lkt8cDd2X1cmX5yu6gv0973XmHs7mjcbtYWvFSI2InWUjripalWf1tg74r9Xs57EvQo4cizJEgw2u5RH5X69lsTJ1Gj8TR3tWeY9ik3nwhli/MCtk57qW4pDxjUVMj714MpXWFjI9tevr4yKsz1Cfll9gMHsvSJprzUMw3VKfPVcDY00Hecx1LfhMrI1vzgRs2lFVi+6SHpFNo47Kf1j/wAWmudskl28p6H8nAK9o1GcfccE57X0lbGe5uxtsQRz0/kncfTm5rTpkuc+M8TyPheNr7UnZz2r/Z3vGHTuRgxkCNZRqaywKyoN5snDbeJ9AEK14Co292jL+/ct3mzleVr8f5KIm2YGWeX4HTMCJ82Fcbdg4O+ekl7R2y+JYLg5ZGaRt3It6tfnmmcTXV1jTJlpE/L8b+r7pzb7kqW6bn623Tp7n27/Zuax+Ta6JnaEnJpE+w4mIoFbSfZeB/h7S5/HnIpVntwNVre9atIuapdm0oU53iDIky+d2fLr+7g2K3dMivTK2W6ftK2KblveFayba32U5c2R6TZz1yfGjm3pHtjTreKvsadnK5aGM1vrtMlJNJ7wQSt5ux5UVObedlsiTmnicr0egte/+ifkEOz1QbfnZ3Mzt6q/OAjMuvP4nwtm2X7OjD929paCuHmMwXa31Z3bm6/uz7xbgxhcY+OeYU0uZfdjJTmOReX6ceVNTEK8pz3II0Xn0lqmuYqF58NHzIMUk4Q5/jI5eNMeNvcpg58d0tmMPpWCfvlbJGt+cUcl1g70r5JtaUYpwld9HeeO1MvZG51sf94SPp92dOb2mvdIeZgfF7aInzbbGRIvgOLp9Dek92XdqargrwmrZfSYWFfdKW/hX1RFV2UQs8BSZvFJok3j0RaTM8CA3bQdsl0/bp0s2EaYctnOz4Snwv5t4NLF58LPhyWxuYpsefu+4kxHBEYH2k6dEX28Sm6vrJxSXtTrSOca4OwiTT5iAcX+n74ngO0PfAvxsVwyWfmzIBP2w/MHVXJt1xmW5tsoKBJ5o8kL9LaID+A3lp+DLLyw52xFed4B2f7/t6X7V0622Yn9+7n0t8tB/rp/lqnp7JIb3b+YD398Q+ZN7fov51ab7e7O1NEeieTlFYoF6tbN58n8qXJtXa8uOdlaLaslWPV9px1alxyzp9tx4Y5v+uzjpNnPHcgrGmjs8r7G4dlaxr4ebfJ9vu/k85raSrp+EjgPPSI7K7eFA++fWXf8bBjpMvYRbTZtiVw5thvy27kS3uOsJvzRF3v7rZed6Y6QJvR2bJf9oy1zXtCfz+NvyZtrMAO5Zh02d7xlnanWQy689n2fqUjU+45qZ2bkKMLjF6Lt7oTPSI+k3iWjQ7uaGlVibhBxNU0dcSlHZWt6hbNkjKO8AEiPEKnI2vkN7vqPIG4HJ3PPAWmZWS7sO3ImyZ+AvH6hSZ3RZ607UhzNpB7s3hRdWPLIgzFupZFIr4AerjXV2x8tn4b1NJFxps90aqxuoMXvlo7O8T7oDquorODSGkHzDHxxdwY0WbeZ+zHYE0UMq1R6buDqmpmVOrnx/b30SRjwNLstOfZiqcEbvubOLF4injKT5ckI/LW+cDcy/Rf9Pagtg8mQRvZaluXic9WrTpex9k3ZTK9vQUt89aliaFCuo6P72qtuKaRyz30623mUxnh1oX3zU6uC+dZHp+XQkfj0fQ7KOjRS7W6hvjHU3165GdrWrW6ilLtSBvvZnvoRnu+rkD0PftHwoPWP+7+9MBatthXMr++2X8=
*/
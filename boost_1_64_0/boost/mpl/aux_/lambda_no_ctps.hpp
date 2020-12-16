
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_AUX_LAMBDA_NO_CTPS_HPP_INCLUDED
#define BOOST_MPL_AUX_LAMBDA_NO_CTPS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/lambda_fwd.hpp>
#   include <boost/mpl/bind_fwd.hpp>
#   include <boost/mpl/protect.hpp>
#   include <boost/mpl/is_placeholder.hpp>
#   include <boost/mpl/if.hpp>
#   include <boost/mpl/identity.hpp>
#   include <boost/mpl/bool.hpp>
#   include <boost/mpl/aux_/na_spec.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>
#   include <boost/mpl/aux_/template_arity.hpp>
#   include <boost/mpl/aux_/value_wknd.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if    !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER lambda_no_ctps.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/default_params.hpp>
#   include <boost/mpl/aux_/preprocessor/repeat.hpp>
#   include <boost/mpl/aux_/preprocessor/enum.hpp>
#   include <boost/mpl/aux_/config/msvc.hpp>
#   include <boost/mpl/aux_/config/workaround.hpp>

#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

#   define AUX778076_LAMBDA_PARAMS(i_, param) \
    BOOST_MPL_PP_PARAMS(i_, param) \
    /**/

namespace aux {

#define n_ BOOST_MPL_LIMIT_METAFUNCTION_ARITY
template<
      BOOST_MPL_PP_DEFAULT_PARAMS(n_,bool C,false)
    >
struct lambda_or
    : true_
{
};

template<>
struct lambda_or< BOOST_MPL_PP_ENUM(n_,false) >
    : false_
{
};
#undef n_

template< typename Arity > struct lambda_impl
{
    template< typename T, typename Tag, typename Protect > struct result_
    {
        typedef T type;
        typedef is_placeholder<T> is_le;
    };
};

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(1, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/aux_/lambda_no_ctps.hpp>))
#include BOOST_PP_ITERATE()

} // namespace aux

template<
      typename T
    , typename Tag
    , typename Protect
    >
struct lambda
{
    /// Metafunction forwarding confuses MSVC 6.x
    typedef typename aux::template_arity<T>::type arity_;
    typedef typename aux::lambda_impl<arity_>
        ::template result_< T,Tag,Protect > l_;

    typedef typename l_::type type;
    typedef typename l_::is_le is_le;
    
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3, lambda, (T, Tag, Protect))
};

BOOST_MPL_AUX_NA_SPEC2(1, 3, lambda)

template<
      typename T
    >
struct is_lambda_expression
    : lambda<T>::is_le
{
};

#   undef AUX778076_LAMBDA_PARAMS

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_LAMBDA_NO_CTPS_HPP_INCLUDED

///// iteration, depth == 1

#else

#define i_ BOOST_PP_FRAME_ITERATION(1)

#   define AUX778076_LAMBDA_TYPEDEF(unused, i_, F) \
    typedef lambda< \
          typename F::BOOST_PP_CAT(arg,BOOST_PP_INC(i_)) \
        , Tag \
        , false_ \
        > BOOST_PP_CAT(l,BOOST_PP_INC(i_)); \
    /**/

#   define AUX778076_IS_LE_TYPEDEF(unused, i_, unused2) \
    typedef typename BOOST_PP_CAT(l,BOOST_PP_INC(i_))::is_le \
        BOOST_PP_CAT(is_le,BOOST_PP_INC(i_)); \
    /**/

#   define AUX778076_IS_LAMBDA_EXPR(unused, i_, unused2) \
    BOOST_PP_COMMA_IF(i_) \
    BOOST_MPL_AUX_MSVC_VALUE_WKND(BOOST_PP_CAT(is_le,BOOST_PP_INC(i_)))::value \
    /**/

#   define AUX778076_LAMBDA_RESULT(unused, i_, unused2) \
    , typename BOOST_PP_CAT(l,BOOST_PP_INC(i_))::type \
    /**/

template<> struct lambda_impl< int_<i_> >
{
    template< typename F, typename Tag, typename Protect > struct result_
    {
        BOOST_MPL_PP_REPEAT(i_, AUX778076_LAMBDA_TYPEDEF, F)
        BOOST_MPL_PP_REPEAT(i_, AUX778076_IS_LE_TYPEDEF, unused)

        typedef aux::lambda_or<
              BOOST_MPL_PP_REPEAT(i_, AUX778076_IS_LAMBDA_EXPR, unused)
            > is_le;

        typedef BOOST_PP_CAT(bind,i_)<
              typename F::rebind
            BOOST_MPL_PP_REPEAT(i_, AUX778076_LAMBDA_RESULT, unused)
            > bind_;

        typedef typename if_<
              is_le
            , if_< Protect, mpl::protect<bind_>, bind_ >
            , identity<F>
            >::type type_;
    
        typedef typename type_::type type;
    };
};

#   undef AUX778076_LAMBDA_RESULT
#   undef AUX778076_IS_LAMBDA_EXPR
#   undef AUX778076_IS_LE_TYPEDEF
#   undef AUX778076_LAMBDA_TYPEDEF

#undef i_

#endif // BOOST_PP_IS_ITERATING

/* lambda_no_ctps.hpp
F7lrbV328rR7lOMD4yXHFYjalBMNqmZbN53edU7IOTeufJH5hPhFh+ljXVWHENu1ErVOBioEPZ+w4fWoNLOLlzQdjBvGL891TSv3OltqpF96QT133m2V+u/3bxWVyBArbh1qyXNZljVk2yWPh3dfPKs0fSZWPbJkPDl83Lqb6YY/V3uMOll/dlrOD7OL3+y6lao/73B4qjV66JYrI381KyT8WietqbBxe9CGVx3vdpwpnxaSX3w//4LsLOFrZySiqI2hng9otnvJd6Xi3teb12wddDl3q1vIm1Qjo03qu+rWV9WPMs6tUvucsMKGLaacabzHlZ5w+cYTo+SS1bvG1unpZ293ihdvVv3UKO37zO3VuifP1CrSgsvj51ndCzupOIiqOrrrxoO1S7KHdn6f8mXYt2HJRvsNx+ZvIN0rmxy8sO1I4buk6VvGDYorYz1Yvj5484tKl/MLlbM83eQn30y4dOtms5j8bCOhygaHbXM+l3T5HColSOcHv7yiefH7g0tjqZGyCUNJlFPpFXfPjNqRfO+qlYxPVaP1oMBLh03bjjpp7qCbXkgud/xxI+94SmBgEt39992lT1a3rDzx89DseYd+us0odlbKXNlJaooqIf5sePcosv1hVu6LGft1NUUn7GoWKTYKcj/r/zKlvLFu7ZTmxBIzwv/N/83/zT/FkGAF9Sqsuf+ttb7gSLDIYTW8KrOwxi9Ixzo4KJKuYUlH9yAxMwU9GCI8no0sR0bAUSqgphQEWkrx0UlMVBFE46+eFzz0b4cfip4dzH9qMpvBJCSFMJGzalPpuvQefRlMx4sBMKDABf0QnMPCx9PGzsFHH/LuYyXG+dbIDFwLpDxWoCuRyq3jHBTMADVwXr3nv712ismTmchReO637CNZ2Fk4PQJFzlzmxRD+enhGUmIiruw+EtT9Afyj9Aj9Gl07lXcvxw2ZwIut5/O38fmHW3PxwjZQq00/uyyAF2gW9LgDkzErHv344K+WOQZpO8Y99AjQubQccNy8mqSiJChhF+w3sMi0+iQyzTOVTFsANnA2+BeSabTFZNpVsD38mKwHkFZYAMLKk5Y8pJUFaRksIdPoy8m0XLCVYGkrIK3VZNqJNWSa9dretJBTG7D0Btg+wwJigJ8nTRqkSfkN325CvG1ZkM46SG89lBMsbQOUFWw92N59ljhdVGcVOfTAxYPOhh0v5Psj2G4ZkG4ano84cHnyIQP5yIR8eG6E9MAGbiLTssBWIu5mcMG2ge3hR3sOV7pwPpy/JnOmGR1gx8TQUOj5HJ02ZJtGWzNkNKh86qB4eliIJaqnJpDOCYeeQScwYH90jAJnD7K0uRDhoeDn42GwE2P4cGg+6ImhsGuGfVDJSYMficfJj4Z0+XFoOvw4kD2dAVt6wfAZDyTPOQ4CRl06FEdHrKdfMZBz09ic04mQpwX+ZQYLl3lAEIMRin7HxuOHA8twv429vTe6JYb7e9INQDIGOA4+Pi4ONA57/UDugZGycsEBSH8OiGQSuHGQBOzKhaDpcuORoyh6/MgZO6FxvXTsaQMeTCYBsUHRobBlF5mI0bFs98IB0NxCuf2xobFIJ+7lQSqQGzYg9NLQiuT3G3D86LE9aMlgLEsm9OKTesuORo/B6EgVCiXj9aP9igeHalfw+iPZuB/NAmfM6q0RpC5QHw5zt4GQcNAZAV1JNhPNDj+OU0pEVmgcOIxy42MWf3ogR05AHx83jtyxtsR1jh20P6Q4dAA4x8UEhdEhSjbnWRAbHBmeFJ/EoiOyRE++AXnCsUA94zN0sTBkaEJOlQrFcYnx0YBgRjIxBNYW8YSxvoZEFpyGfCTXf+JonwQRo1xoWAF4diJs/II=
*/
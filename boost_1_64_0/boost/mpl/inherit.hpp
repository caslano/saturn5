
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_INHERIT_HPP_INCLUDED
#define BOOST_MPL_INHERIT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
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
#   include <boost/mpl/empty_base.hpp>
#   include <boost/mpl/aux_/na_spec.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER inherit.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/default_params.hpp>
#   include <boost/mpl/aux_/preprocessor/enum.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/config/dtp.hpp>

#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/dec.hpp>
#   include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

// 'inherit<T1,T2,..,Tn>' metafunction; returns an unspecified class type
// produced by public derivation from all metafunction's parameters 
// (T1,T2,..,Tn), except the parameters of 'empty_base' class type; 
// regardless the position and number of 'empty_base' parameters in the 
// metafunction's argument list, derivation from them is always a no-op;
// for instance:
//      inherit<her>::type == her
//      inherit<her,my>::type == struct unspecified : her, my {};
//      inherit<empty_base,her>::type == her
//      inherit<empty_base,her,empty_base,empty_base>::type == her
//      inherit<her,empty_base,my>::type == struct unspecified : her, my {};
//      inherit<empty_base,empty_base>::type == empty_base

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< 
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    > 
struct inherit2
    : T1, T2
{
    typedef inherit2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1,T2))
};

template< typename T1 > 
struct inherit2<T1,empty_base>
{
    typedef T1 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (T1,empty_base))
};

template< typename T2 > 
struct inherit2<empty_base,T2>
{
    typedef T2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base,T2))
};

// needed to disambiguate the previous two in case when both 
// T1 and T2 == empty_base
template<> 
struct inherit2<empty_base,empty_base>
{
    typedef empty_base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base,empty_base))
};

#else

namespace aux {

template< bool C1, bool C2 >
struct inherit2_impl
{
    template< typename Derived, typename T1, typename T2 > struct result_ 
        : T1, T2
    {
        typedef Derived type_;
    };
};

template<>
struct inherit2_impl<false,true>
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T1
    {
        typedef T1 type_;
    };
};

template<>
struct inherit2_impl<true,false>
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T2 
    {
        typedef T2 type_;
    };
};

template<>
struct inherit2_impl<true,true>
{
    template< typename Derived, typename T1, typename T2 > struct result_
    {
        typedef T1 type_;
    };
};

} // namespace aux

template< 
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    > 
struct inherit2
    : aux::inherit2_impl<
          is_empty_base<T1>::value
        , is_empty_base<T2>::value
        >::template result_< inherit2<T1,T2>,T1,T2 >
{
    typedef typename inherit2::type_ type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1,T2))
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

BOOST_MPL_AUX_NA_SPEC(2, inherit2)

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(3, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/inherit.hpp>))
#include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_INHERIT_HPP_INCLUDED

///// iteration

#else
#define n_ BOOST_PP_FRAME_ITERATION(1)

template<
      BOOST_MPL_PP_DEFAULT_PARAMS(n_, typename T, na)
    >
struct BOOST_PP_CAT(inherit,n_)
    : inherit2<
          typename BOOST_PP_CAT(inherit,BOOST_PP_DEC(n_))<
              BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(n_), T)
            >::type
        , BOOST_PP_CAT(T,n_)
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          n_
        , BOOST_PP_CAT(inherit,n_)
        , (BOOST_MPL_PP_PARAMS(n_, T))
        )
};

BOOST_MPL_AUX_NA_SPEC(n_, BOOST_PP_CAT(inherit,n_))

#if n_ == BOOST_MPL_LIMIT_METAFUNCTION_ARITY
/// primary template
template<
      BOOST_MPL_PP_DEFAULT_PARAMS(n_, typename T, empty_base)
    >
struct inherit
    : BOOST_PP_CAT(inherit,n_)<BOOST_MPL_PP_PARAMS(n_, T)>
{
};

// 'na' specialization
template<>
struct inherit< BOOST_MPL_PP_ENUM(5, na) >
{
    template<
#if !defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
          BOOST_MPL_PP_DEFAULT_PARAMS(n_, typename T, empty_base)
#else
          BOOST_MPL_PP_PARAMS(n_, typename T)
#endif
        >
    struct apply
        : inherit< BOOST_MPL_PP_PARAMS(n_, T) >
    {
    };
};

BOOST_MPL_AUX_NA_SPEC_LAMBDA(n_, inherit)
BOOST_MPL_AUX_NA_SPEC_ARITY(n_, inherit)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(n_, n_, inherit)
#endif

#undef n_
#endif // BOOST_PP_IS_ITERATING

/* inherit.hpp
uS4XXPepFhuuSzB6KbG6ih1K++snH2S+ywffvfe0Dd8lGT0xJRJiSgS+4F5v3mr/6Wkbzksxegmxtop93boR3q8y740C7618uk/e41vxpYvO3W/y3jee7pP3WPie/o/PbjN57/in++Q9nhqP7Xr+JJP33vprn7zHK/8dz3w/ZvLe1r9m8B4e8aHRDVAabuAH3BuoA1C9ZWNc1uImfC09h4ZrR3G17kX9NVDWrsHL8TXqat0PGq8GvNXRMtJbrqY+dU6KD92fD32GPkOfoY+N/cF3T7O1Pwgq+4NjspztD/Yelm5/UHm41f7Ak5tuf/DF0wdofzAO/m9OtcXvZODXVqqfebQtfsi7KijxaxP43V4o8BuD3G/npOP3s4kDxM8L/w+EH9+Re5V1QBGuGrtdC3LpEXrWddPxdyThRXdnT5ydvdjQqlB9XPCx4QPqkt/U7FJ9eqO4EEQ0sYZsYSsRznKJRJhiyFvPIlUSIfcDM+rciNTp8fCla88TH+jWTfi/aHTxB3ezRQyowlsx41G3EeS2dqabcLtXtER5x9Uhr4nvQIVn8ZtEXt93uqb/v08JfwFe41J1LQdlBq3Ku88o1+ZNNHxawytA7XQtu0zXREPYV8g7Tre46n0MTmwVAHHIyKi+80+ojovNFO5X/didiEtrF7qe3vFs4ZNkiwsDw1eEe1KE8vyA8O8lh+guZAMu2q4cL1vnm9neAPVzBBbKj8X7Hbv+fJjemzD/P5nmvxShy7i/5EQD36vrvSqeGf8tCWuF1bvh59fPN6DLK+FP24/LSz8ScQmKdIdc7ZC5QdtcI7RyLTJvzeHIZxmJiF4mEZtrjxjSHXK1Q+YGbXONiNkic9koRsyI1HwXElcVMGKWyUGh9PP9x/2EmaNp8iNI3wmLkakj/CZXULGZbjJDQrknx8j6sJiZ6Q3AZoYMhaYfAwFYexfH8GOmhGPolWcKUeeuRWy/slpEdqMnSok3pY8zBHUoFJVlIcKM5Yh+rlEZQQJLa2tnc7b+Q1TuNRbFYixEYL10ahQLakQRYc+IvksDi6yZYpQzyFUsyBXFD9Gf6PLr+Tvak4Y8CGJItjzIIXMeaxEyEepXKa1fpYJ9lLqyb6Su7BdSV/YLqSv7gxTzRiBai+938cBIYyvkkr0VcoiBrUXIjKtfpbR+lQr2UWpu30jN7RdSc/uF1Nx+INWZTx5TxV7gRycPYC8w9On7Y/o/PcH0l3XW7nkcNnfsEnxZWubSKo8wF3fvjJ5RnM5GTSewyyPs8EZTmCdKVJ60e0bt+BsVgdfNgQQQ4/hUZ7XL5vHl6s9kNt8umy8QTdWLptCEHbw2wDthCb7cO4XgHZ3mlRdAOI+dx5ajS4dLV8bYMugnniR8rZ8B93BBlYedxruFyCMSHG2SwES1A7h5+9l9S3yuk+ALSjO2LNPfYyHvFU79NZFWVSjt6/oe39HHG+OLBo60+GueoX/pEwDUeQdnwwu/zDa9vM1GWxr182oiXEnYP+9oyhsvyOAhjPRfvgsM6WdsuhFehDM6T7R646s8WVEHhrNvPobNlapg9Dc+HO0NhHmc6Sm83hUw20a9IGw+Ib+ujX9nUYepAIefAmNFR6C5Q/AnjzK4Hgy4fjKdeeROuq/ypwIZL9diXIBJHnuzK2BUgEgem+oxIv2yuDTj/5H9sXWS6JUnpBH9MGpTnGjK9CWPguT9Ie2/2bsW+DarKp6kaZe16fKVpaOOAdMNQcp0mPnAgXazUcRF29EIKogP0NDhi7W8XGGlmzYNFR+goKCoqPgEFXHTgd2cWzcndlClatVuVPxK6gxaNWpZ/Z///e6X78tj62C8lPx+W5P7PPfec88599xzz0E=
*/
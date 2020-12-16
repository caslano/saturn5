
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_ARG_HPP_INCLUDED
#define BOOST_MPL_ARG_HPP_INCLUDED

// Copyright Peter Dimov 2001-2002
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
#   include <boost/mpl/arg_fwd.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/na_assert.hpp>
#   include <boost/mpl/aux_/arity_spec.hpp>
#   include <boost/mpl/aux_/arg_typedef.hpp>
#endif

#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER arg.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/default_params.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/config/lambda.hpp>
#   include <boost/mpl/aux_/config/dtp.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>

#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

// local macro, #undef-ined at the end of the header
#if !defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#   define AUX778076_ARG_N_DEFAULT_PARAMS(param,value) \
    BOOST_MPL_PP_DEFAULT_PARAMS( \
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        , value \
        ) \
    /**/
#else
#   define AUX778076_ARG_N_DEFAULT_PARAMS(param,value) \
    BOOST_MPL_PP_PARAMS( \
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        ) \
    /**/
#endif

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/arg.hpp>))
#include BOOST_PP_ITERATE()


#   undef AUX778076_ARG_N_DEFAULT_PARAMS

BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(1,int,arg)

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_ARG_HPP_INCLUDED

///// iteration

#else
#define i_ BOOST_PP_FRAME_ITERATION(1)

#if i_ > 0

template<> struct arg<i_>
{
    BOOST_STATIC_CONSTANT(int, value = i_);
    typedef arg<BOOST_PP_INC(i_)> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          AUX778076_ARG_N_DEFAULT_PARAMS(typename U, na)
        >
    struct apply
    {
        typedef BOOST_PP_CAT(U,i_) type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

#else

template<> struct arg<-1>
{
    BOOST_STATIC_CONSTANT(int, value = -1);
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          AUX778076_ARG_N_DEFAULT_PARAMS(typename U, na)
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

#endif // i_ > 0

#undef i_
#endif // BOOST_PP_IS_ITERATING

/* arg.hpp
oq0tLKv+1O4jHDXqB1/fqGEaMYacfoaaw8+w0+ln2Ob0M0w4/QxjTj/DFqefYZPTz7DB6We4RXgctdse/R39Hf39O3/m/ed/JnvvIS4UIO/SUvpE5YZpnjvkS/oRT+1Ajxq2xuQ/Hd+//9PwiPPzoAnn50HjDkPykPPzoINOK7LmtCL3O63IMacVuc/5edBe5+dBe9jGiwmwI3Ey+9Ti1qeOvadg+Ryni5869p1sXN3UkTgFmEFgTgZGA+YUYPqBET4xC58+C59eC58eg8+qUDInPZSQOwooOj0QJx2x7+PUzG6a6aZO6qG/uLkgTilow0AzHnmTUXQXoncgOk4zH2UmPTSIFeiQIzWlGKT80dRK8yrRttT4srpGWU4P9vO2LaA5Umu0+KRSpNNOArsKR2pKEUPO++g4l2hH6hgd2yLnvVQNZMR0pCaTfS9y3oM3SnodqSlFjyNFT6tbtbEsupyjKoMv6OnYm2Xe5ZRV5fEizIuwnbstQX6qXWpcx2wXLt3pEgf1jtNZpFnCjuMwtL4QhVFMvCNxIq0/OnalH9MhcdvHURxlg/Tekch83K23xSCFHY96OVa/Piqdw3xuhE3iKollHtMt+I4JKm6wY1+6XkLiSGFZ1O469h6j5+MYyQcqNIfrbdc4Ix8elQ+tI6EuoDpW5UPr2DdR53uc8EWtn6DzzRa+ek4zKNWGUD9liOq7I5GlMztemKE9eHVmJyhm/VBubOduQ7c5So+xjr3jdTk+kYM2k62znaTYxjr2nURNhDRl6OVEpZe+jn2ZusiTRCQa1rE6X7/w5dQJ4tfbsSvD0MvJSi+9HYkMXeYpIhOtz6PzPVX4cuq9lM+ejt3jjLLkqrL0dOxN02VOVjJ7OhITdb7vEL6cet8J6lofTnv0g/dv0c+Yf66MDTu+d2/eJkTfG9+EywERbL9k6MWEHuOlmCzjgqGM+1RweXsBx1jT/LlBcStvX0uRXuNqorVLtO2WyEKRVigfPc9TmcgyeBZK9i5LpI6BtD1fMyPX4tPnKpPPpopBJjKFoXyovHL38Fv2oXLSv6jBvNHp59+xKMCp7iZL5FrnrU53USRu/zkieZe/lrw5ryVviiWygCNN/R06J871z0uj218WHU79ghnxtXycHaopzqN2jYSa2YHQFTGE2rODUvypzto+8PX7qYpxls5VNVLtcQE7YwrJOP8KYoQrPpmPPPaqYGhFWpOkWUsfZ5RIaUmzY292S1L37bZsZDEZqgw/k0dVUY/Jo5417U55RD5S1Mc63H/R56wPXMYwx6VfTFEhX/Rn67hx69ny3x+yeNb7fefW2esWlaOdI6GOpuaT0EOqTumj826bPn4oj4rbHfI4xvtufW4u/4vW8m/jr+mpayZA8/JfiCf5b976CynH6VGmsx87vny3DqtaGmizRnTsy7DGPTnwyNbKs5i1TQLQuGDBlHDR+qLsp+oYK6mzn1qU2Za+vboOrBZNarMEl3dkVUUZugEJ2vdlVBHBkRDGS5SogJceS5/DUtnJbBuo0GfiixgKBHFO79Ln7IuqiDnqruIANIhcGxdOILNPp0XqzFzPXX+Znq/HKOlioTdPe3pnojCKD7Ev0R5U15/wI1pGlEyhHPOpvcSGY/hR2syc/WgHA1/h7qlHaJccQGAUrrKUugF8v7VPQnHSVKhHatXCQBehR2qlOjbKj6Z8wepi9EjtQ4IVMUYeZghWxMjAWivAVG0nDW3HoiO9fVB1LLHpSJSiVaaJjnDqtNha9tkyU1nl+vcpHaFXbn3xkL3yv+dn3v/96+ERy14m+7GMiZvFzm1eN8uh7s2PZGnXEviYQOIYZQo3djaM8G5+xKsFHAi2ZIY=
*/
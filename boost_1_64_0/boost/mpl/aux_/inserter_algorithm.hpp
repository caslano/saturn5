
#ifndef BOOST_MPL_AUX_INSERTER_ALGORITHM_HPP_INCLUDED
#define BOOST_MPL_AUX_INSERTER_ALGORITHM_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/front_inserter.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/front_inserter.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/common_name_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/preprocessor/default_params.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#   define BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(arity, name) \
BOOST_MPL_AUX_COMMON_NAME_WKND(name) \
template< \
      BOOST_MPL_PP_DEFAULT_PARAMS(arity, typename P, na) \
    > \
struct name \
    : aux::name##_impl<BOOST_MPL_PP_PARAMS(arity, P)> \
{ \
}; \
\
template< \
      BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), typename P) \
    > \
struct name< BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P),na > \
    : if_< has_push_back< typename clear<P1>::type> \
        , aux::name##_impl< \
              BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P) \
            , back_inserter< typename clear<P1>::type > \
            > \
        , aux::reverse_##name##_impl< \
              BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P) \
            , front_inserter< typename clear<P1>::type > \
            > \
        >::type \
{ \
}; \
\
template< \
      BOOST_MPL_PP_DEFAULT_PARAMS(arity, typename P, na) \
    > \
struct reverse_##name \
    : aux::reverse_##name##_impl<BOOST_MPL_PP_PARAMS(arity, P)> \
{ \
}; \
\
template< \
      BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), typename P) \
    > \
struct reverse_##name< BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P),na > \
    : if_< has_push_back<P1> \
        , aux::reverse_##name##_impl< \
              BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P) \
            , back_inserter< typename clear<P1>::type > \
            > \
        , aux::name##_impl< \
              BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P) \
            , front_inserter< typename clear<P1>::type > \
            > \
        >::type \
{ \
}; \
BOOST_MPL_AUX_NA_SPEC(arity, name) \
BOOST_MPL_AUX_NA_SPEC(arity, reverse_##name) \
/**/

#else

#   define BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(arity, name) \
BOOST_MPL_AUX_COMMON_NAME_WKND(name) \
template< \
      BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), typename P) \
    > \
struct def_##name##_impl \
    : if_< has_push_back<P1> \
        , aux::name##_impl< \
              BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P) \
            , back_inserter< typename clear<P1>::type > \
            > \
        , aux::reverse_##name##_impl< \
              BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P) \
            , front_inserter< typename clear<P1>::type > \
            > \
        >::type \
{ \
}; \
\
template< \
      BOOST_MPL_PP_DEFAULT_PARAMS(arity, typename P, na) \
    > \
struct name \
{ \
    typedef typename eval_if< \
          is_na<BOOST_PP_CAT(P, arity)> \
        , def_##name##_impl<BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P)> \
        , aux::name##_impl<BOOST_MPL_PP_PARAMS(arity, P)> \
        >::type type; \
}; \
\
template< \
      BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), typename P) \
    > \
struct def_reverse_##name##_impl \
    : if_< has_push_back<P1> \
        , aux::reverse_##name##_impl< \
              BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P) \
            , back_inserter< typename clear<P1>::type > \
            > \
        , aux::name##_impl< \
              BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P) \
            , front_inserter< typename clear<P1>::type > \
            > \
        >::type \
{ \
}; \
template< \
      BOOST_MPL_PP_DEFAULT_PARAMS(arity, typename P, na) \
    > \
struct reverse_##name \
{ \
    typedef typename eval_if< \
          is_na<BOOST_PP_CAT(P, arity)> \
        , def_reverse_##name##_impl<BOOST_MPL_PP_PARAMS(BOOST_PP_DEC(arity), P)> \
        , aux::reverse_##name##_impl<BOOST_MPL_PP_PARAMS(arity, P)> \
        >::type type; \
}; \
BOOST_MPL_AUX_NA_SPEC(arity, name) \
BOOST_MPL_AUX_NA_SPEC(arity, reverse_##name) \
/**/

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_AUX_INSERTER_ALGORITHM_HPP_INCLUDED

/* inserter_algorithm.hpp
4e67d8+uUKJEw80//VSh/s2bFwu8eZPy26xZVdzy5SuzVas9FXXx4rLEb7/N+Zfp0902zJlTrUzJko2/Gz++oPrBg0Ntjx0bn+bntzyuYkXvodevL5kyaZLVmwULeoxOTMxV2N6+6KWdOzU17907f6BFi7GbQkNP7G3efMzq2bMrDa5WrWc+B4eSv69ePeyDr+/Sc1u3hjcsVKgq/JfAfyz8Z8N/Mvzt4b8d/mvg7wt/b/hbwX8Z/EfAvwj8A+F/D/4/wt8T/vPg3wz+4+FfEP4p8D8E/zzwfwT//vD/CP+H8N8J/9fw/wH+veC/B/7F4b8K/gPg3xP+zeFvCf9O8O8N/xfwrw1/W/h/D/8Y+PvAvyn87eDfBf4a+PeFf0X4L4C/A/zXwz8X/OvCfw783eFfHv5a+B+F/8/wLwb/n+Cvg391+FeD/1r4/wH/9/B/Bf8O8A+A/zH4D4N/E/gPgv9M+L+Ef6jkH/5V4d8P/qXgnwz/x/DfAf9W8L8I//bwvwb/M/A3wL8d/AfCvzL878K/EPz3w/88/P3gPx3+x+HvCP8c8I+Hfyr8PeC/Bf634f8c/p/gvwv+E+G/Ev7b4N8G/tbwvw7/3fDXwz8I/q7wLwr/vPAPh78X/J3gXwf+NeB/E/4L4X8E/g3g3w3+z+A/Bv6t4b8C/vfhXwX+M+A/H/6z4H8S/qPgHwL/kfD/K/wT4H8Y/pXgfxr+jeE/BP634F8C/rHwbwT/rvDvCP+S8L8M/9zwD4P/Hfj3gX8E/J/A/xf4L4X/YvjXg38S/GvBvyX8e8B/I/wnwT8Y/qfgfwP+6+D/Dv454V8O/r/C/1v4P4C/M/zPwn8C/CPhHw1/F/g/hf9B+HeGf1n4D4f/XPiXhv9V+F+B/zfwHwf/qfBvAf998F8O/wvwt4G/Bfzzw38R/P3h/xb+J+A/Df7d4V8B/pvhXx/+BeD/G/zd4L8V/lHwT4T/X+C/Af5l4P8d/NXwbwv/NPjHwX8o/KfA/w38R8O/MPwvwb8m/A/AfxP898J/NfwHwz8f/H+H/wf4n4N/Q/gHwX84/AfDfxj8n8F/IPwj4b8f/q7wt4B/f/hXgf8n+J+H/1/hHwv/w/AfA/9D8B8B/3fw7wH/1vBPhf9K+J+B/0L4/wr/ufBfDP9o+O+C/0b4f4T/9/AvD/+68G8K/9fwPwL/2vBfAv+78H8K/0HwvwD/mvAvCH9r+B+Ef1n474W/M/x/gL8N/H+Ef07454f/aPjfgn8K/CvAfy389fDPBf8E+FeFf1H4F4N/BPx7wn8+/LvAvxH8z8H/N/hXgv9t+NeA/1j4+8D/pPC/u+pj+Kvh/wH+a+DfC/4D4P87/HfAvwH828HfC/7d4X8c/ifg/wT+y+H/Hv4t4d8B/m7wHwd/T/i/hb8l/EfB3xv+jeH/M/yXwr8z/BfBvxn8p8D/O/jPg399+L+E/zb4b4D/JfiXhr8j/NPg/xz+p+B/FP528C8A/0fw94f/TPh7wL8w/PfB/y/wHwl/d/gHw78P/IvAPwb+/eAfD/9O8L8C/zLwrwz/qfCfAP9W8P8D/pvg7wT/a/DvC/888L8M/xvwrwX/hvDPDf+28M8Bfxf494b/Hvifhv8K+AfCfxr8Z8D/DvyHwP8+/JPhXw/+4fCfDP+z8O8I/2XwD4N/V/i/gP9D+GvgPxT+q+BvC/8t8I+Dfzn4V4d/cfj/Av918D8AfwP8r8JfB/9S8G8P/+3wT4L/RPhHwb8J/NfDPwT+beBvBf9X8M8L/wD414F/N/hvhv838N8N/xLw/wn+N+H/Bv6z4J8P/lr4X4T/t/CfDv858C8J//HwfwD/Y/D3g39F+F+H/yT4L4A=
*/
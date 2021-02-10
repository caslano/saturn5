
#ifndef BOOST_MPL_SET_AUX_SET0_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_SET0_HPP_INCLUDED

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

#include <boost/mpl/long.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/overload_names.hpp>
#include <boost/mpl/aux_/config/operators.hpp>

#include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_USE_OPERATORS_OVERLOADING)

#   define BOOST_MPL_AUX_SET0_OVERLOAD(R, f, X, T) \
    friend R BOOST_PP_CAT(BOOST_MPL_AUX_OVERLOAD_,f)(X const&, T) \
/**/

#   define BOOST_MPL_AUX_SET_OVERLOAD(R, f, X, T) \
    BOOST_MPL_AUX_SET0_OVERLOAD(R, f, X, T) \
/**/

#else

#   define BOOST_MPL_AUX_SET0_OVERLOAD(R, f, X, T) \
    static R BOOST_PP_CAT(BOOST_MPL_AUX_OVERLOAD_,f)(X const&, T) \
/**/

#   define BOOST_MPL_AUX_SET_OVERLOAD(R, f, X, T) \
    BOOST_MPL_AUX_SET0_OVERLOAD(R, f, X, T); \
    using Base::BOOST_PP_CAT(BOOST_MPL_AUX_OVERLOAD_,f) \
/**/

#endif

template< typename Dummy = na > struct set0
{
    typedef set0<>          item_;
    typedef item_           type;
    typedef aux::set_tag    tag;
    typedef void_           last_masked_;
    typedef void_           item_type_;
    typedef long_<0>        size;
    typedef long_<1>        order;

    BOOST_MPL_AUX_SET0_OVERLOAD( aux::no_tag, ORDER_BY_KEY, set0<>, void const volatile* );
    BOOST_MPL_AUX_SET0_OVERLOAD( aux::yes_tag, IS_MASKED, set0<>, void const volatile* );
};

}}

#endif // BOOST_MPL_SET_AUX_SET0_HPP_INCLUDED

/* set0.hpp
PfXbTPKKMokrqIcEFmuUYIShXjHYMgVviDlcqa3QV4S+N1hDUUihBRepQ0Zu4Fp/74FF/udhLbMU4QJM7xZ5WU3D2vmLDLXP2vZl/X8DUEsDBAoAAAAIAC1nSlKV4p3nIQMAACQGAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0ODY4VVQFAAG2SCRgzVVLk9o4EL6riv/Qm9ScZieeCZNNivJQaYMHnOVhY0OKXFJGFrbBWMSyh3V+/bYMA5Nsqrb2tjpY6tbXr08t2SyFKnmoRJeZab6WNG1FfZBFpLrMnbpt5qM/aj6A82AIk2A0ZrPH3t379r2e393SbBoXI9M4+mGv2WvwRfEkihuVRoKZhdhnNQFUo+S7qMteuLTd0fIY4vokBNlsHCwmwRzRQhqWdBz89XiA65fwXqOMae7rRW8Qxzbyd3e4XPTjesIvhoN7XMVY66V3OyY7D72DRVY22rH1iPYBfc8K0LbR0/Kjh77etGJcHqwN9u4x9GgezPELWhkOlziKrQqHlMUBldav0NrjcIxLz0q1HFEh2u5f7Y+VPbT+SUdT1QBxSZnosdT5fD4XZR2aqhEdHDYKR5MhfuIskY6Ffe/7eGPfjb87f/2S2P6mnah21d7cbuNP33rFaHz9
*/
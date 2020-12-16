
#ifndef BOOST_MPL_SET_AUX_HAS_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_HAS_KEY_IMPL_HPP_INCLUDED

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

#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/has_key_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/overload_names.hpp>
#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl {

template<>
struct has_key_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
    || BOOST_WORKAROUND(__EDG_VERSION__, <= 245)
    {
        BOOST_STATIC_CONSTANT(bool, value = 
              ( sizeof( BOOST_MPL_AUX_OVERLOAD_CALL_IS_MASKED(
                    Set
                  , BOOST_MPL_AUX_STATIC_CAST(aux::type_wrapper<T>*, 0)
                  ) ) == sizeof(aux::no_tag) )
            );

        typedef bool_<value> type;

#else // ISO98 C++
        : bool_< 
              ( sizeof( BOOST_MPL_AUX_OVERLOAD_CALL_IS_MASKED(
                    Set
                  , BOOST_MPL_AUX_STATIC_CAST(aux::type_wrapper<T>*, 0)
                  ) ) == sizeof(aux::no_tag) )
            >
    {
#endif
    };
};

}}

#endif // BOOST_MPL_SET_AUX_HAS_KEY_IMPL_HPP_INCLUDED

/* has_key_impl.hpp
uRGsv8z/we4JPo62GXNFHcTCxhxbWZd9KFeX+/hh6LKDc34c8W5in0+g7mRmp1F3J+t3FvrJXNCPaE/muC8ZC5dinX83FinNLO8N1t5YzmUhY858PJ4WuQH303mI3WLM9VfWr5Qxj4zZ5Y155VreZSzQgK9pqqM9mbuubSwqPteHL8IaGwsKa2osIhrcj3LCHoIv8ryx5Q04l3FsTxhziH9twOpy3XbGfOJLR2ggduMR7wXOW3f4UpOP6V7GQh/x+OIzFifzDH2Rtzg+fgehnPTJ4cjRCX7u8iL8K8h2xyAOOedNQHsSxyRoWp/7+BvG/L24vbeQSz/7NxOxSXtzoMFyjnehMbfMbywFm8THzEr4fJB9Xgef83K5EHz+kjX4GLos4nx8hn4g81I7UVfG073w+VnW+RD8K8ZxfI4cyX3KV9BlJds9Bbtybfs9YtvNsZ1He3KN/jPKyTF4Gawp+5LnRvNP7gMKGss8xLEVNhaReXmnscCv/MzmVmNRmUcvZyx4hHWpbMwhz9CqGfPexnHcDl86sy/1jMUN4/7SCDb683h1N/z7geO9z1joMPvyoDHPKrb7KGzInFsrY345pp8y5hL2rDGnsOdho4zM/0H7jZyjRMRbSub/EIecP1JhQ+bcMlAuwD4PRHtyrTwMGsh18V/RnoxrL8E/8Xk8dJ7MNl41FpF1Mq+jvWdY5zehaYBzPgM2NrCN2fC5NOdtAdrbyTaCqCs6rzDmkPuKtWhPzm8fIh+t+NyzGe1tZhufIr/jmP0dOovdPdDgE753Pgg2kY+FY4gjxMfbl/BlIffxb2AjH+t3BuVac2znjPk7so2fUK4Dl/sNdvPz8eG4yfxL49gKGPM9w/7dBBZmrW5G3cFct6Sx8Dj2pawxt8RWyZirGt9L3gZ2hH2uZSz6It//1jWWKZo2hH9yjXQX/PuT6zZDuVJ879LcWPAy98lHjHln8rXjX8AOsV2vsZDM1T+D9rrJ/B/YIq7bBUyurxKgwUaOIwnl7P9fy1Kg6aecj3Rj/kKctwHQagr7MhRxZPK4MRJa5WUbo40F9rMv42DjtIPYK9AgD/sy5Ups3N502JBzd6Yxj6y7mQX/5Fn+fNiV/rIEGkzlHC03Fh3H7a2BpnPZvw2ou4nj+AhsF7OtsFuA6+5AuYis/4POJ9nnA4hXrqWOGgt35Xx8Ycyp83/QYDzH8R206iLr/1B3Hte9aMxxiev+ijgus39/olw57vf5C5uN8jzu3mgsTp5DFDPmkrWcJYyFDnC8ZYyFZe66ItgCjqOqseAIHktqotwUznkd2O3AdRsYc2Sw3SbwpS/7d6+xwJt8fHiMuYfwtdTDsHEHj1ePQ4O3WIMnjWXOZ03bGvPKM83njEX6sQad4bOcj7rB7hMcR0/koxD719uY734eN9JQ915Z/wdNK7J+Q6Cp5HIEfBEN/mYsWpD7wcvQ6h62EUBs+WX+D+w4xzYNdZ/mc9k78O8RtvseNL2NfZ4HtlHW/yEfCbL+z5j9EFsNX0pwvB8Y88vagE3GQlXZxhbYlbn67dBF7O5Ce9I39iO2fhybPYK1OW5uLwK7u7jcSeS8JLNv0d4+Wf+H2C7ysX8B/n3L+fgF2suz1D9gQ9bJ5Cti5Q5xf77BWLiazP8Z83/HNoob8z0t83/G4prK+j9jjvrcx6sYi47JQ6yGsdDfON47jGX+xHOqbrTXnnN+J+q+xXXvKYJ7e+6TDxhzbud+0AI2pO8+hvYu8z1Oa2ORtTL/Z8wTYP3aoz1ZY9PJmLcw97WuKFeQx6seaE/m9ZKNOcZwvH1Qbjn70s+YS9ZHDEbe8rMNP8qNYP9GQaso99OxV+pyziciv6PZxmQ=
*/
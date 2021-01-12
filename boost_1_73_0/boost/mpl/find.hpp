
#ifndef BOOST_MPL_FIND_HPP_INCLUDED
#define BOOST_MPL_FIND_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct find
    : find_if< Sequence,same_as<T> >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,find,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, find)

}}

#endif // BOOST_MPL_FIND_HPP_INCLUDED

/* find.hpp
PIJH8AQexVP4Fdr7C69y9/6vjkvZ/AT64El8FL/GJngaO+KZArQNusNSVv8w98tN26unNJg7q7/v3H/Uf9tdVn9Yy+r5ZHQgL++FE8wEW1k9hpAxkOv2wAcrr69jmTGU03diFiFP93CX1fc84HsV7jK6e3AP7sE9PPzD3/79f0zcGL3JbC38/0Vlf1sfwBkEX8LbBKXsX6OcpuwvK7+f75QLUtb8fdlfvl0mDbJGKRuq5U/t
*/

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
9DV8wD9E/5UW0nltbT59L7DpC5ifsuuFCruMwt/3zyyBhjBTSuGA9BKYpe0KOnhOXVexy6EitXY0tKLPcg/R0/Krn+pshGtzjb09CPllVAMQi2xDmP+dPa86YmWensJCsiib/Bwinf9NkadAdlU2BZPMyRzFMyBfn9dFnweO8s6EZZvJuv6WkJhOFOZZCYglNA5QELZXPcI7tVSWPkQJECASArjPZhmZ3vY5z7pVnsGqf+4vMXEJ1TK6oKXE93Z3z6hLQQV0WTWhtFhMtthBXCvdkrnw0EjZTunW6PS9xQmbjOQmzlb9Zpb8RomJHcg3+B2/ZvUxY2l4nI5vH5eZlbIS2HNowpP64PhYzRh7xekan/c/QKwNvKTDpxAryYtKFBsAFcCITkDWWEUD25IDtbOD77uY+dg0PPxVsYB7BvYUpAO9Wd+WOvtHqO0jCLm3uDiW2l+dOcbl4SpAlr7JEEBLCmQf56QuwZrPbtwVOXvwmMR9vdCJj5Llm6IpSOspD++jN9BuLQzbuKFO3i3h3pPo0hqwjZaipBn7MayZtVDytiEQfwG+YTlDUw==
*/

#ifndef BOOST_MPL_FRONT_HPP_INCLUDED
#define BOOST_MPL_FRONT_HPP_INCLUDED

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

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/aux_/front_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct front
    : front_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,front,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, front)

}}

#endif // BOOST_MPL_FRONT_HPP_INCLUDED

/* front.hpp
R1RMfuqIBThwN8emgPwZyGrhJ7YE5ApHbHtzkyOaJSsd8Wr2VY7Ytm21I5a1/dwR296sdcQOCescMe3sVpC45eNtjtiW7b9A4qtA14OsAvlLR7w+EpomsRtAwhOBb8N2pyMGqqFoj+He6BsdMW1sE0icT78Z5GSQj4CMevjMh9gvQD4K8m6Qu0D+1sO3koo9APIJkC95+NZAsSMg94DEfUWfBIn1jL0gk0E+DTIF5H6QWSAPYLwg4Vccm+jlg/8=
*/
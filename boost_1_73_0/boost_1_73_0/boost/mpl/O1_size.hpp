
#ifndef BOOST_MPL_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_O1_SIZE_HPP_INCLUDED

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

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/O1_size_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

// returns sequence size if it's an O(1) operation; otherwise returns -1
template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct O1_size
    : O1_size_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, O1_size, (Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, O1_size)

}}

#endif // BOOST_MPL_O1_SIZE_HPP_INCLUDED

/* O1_size.hpp
cKtp3FR7PWhu+75cx3fYVHkLzmeea2xAl+hMgpIreEQUMFCl1AMSbxzWDqSbajUhDz/9c9k88ybDzJ83Ukt2MCQPdxW3q5mwg8Ur+yqVtZnRDtd1uE2RR6ZSaQZ/T+KRW6ORf1yYbo1N66am+3dnN4uL2fXWagZDOuzs2BUx7WVyrX8LahiEsDCapmUlCpj3SPU2B73cpmqvO5RRarl7Y2zaPZK9J+u1TfTyvYlG/f9E8y7RzdtEp31W612it1v6z/jm/4jvxjgEVhhR2Ji8dApuZevszavaJE7RB9V/uD32YHjffL0XlG4N7oAxfU0H3f2UfgFQSwMECgAAAAgALWdKUoFMijA9AQAABgIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNzAzVVQFAAG2SCRgfVFBTsMwELz7FaugHIuhkaAgtweglZA4cKD0iFxnQywSu7LdllyphPgS7+lHWCeNckOy5d3xzK53LAL6oKTHGRPaFJaOD2z21uV+xhaPT3Mm+AAI3nGYcLipGgJyGeSMFdYyAFhLx+KmMCI1bcE7huAnBTuD+0qjCSOvc2RCtQkRPLodOqqlK4J5n4oCZdg6pO5Lo5UlzV6bbEyU4UYYWdMEa+m1gljglvP2hL0OJSxf
*/
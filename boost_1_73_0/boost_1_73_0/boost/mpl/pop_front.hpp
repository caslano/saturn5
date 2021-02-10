
#ifndef BOOST_MPL_POP_FRONT_HPP_INCLUDED
#define BOOST_MPL_POP_FRONT_HPP_INCLUDED

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

#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/aux_/pop_front_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct pop_front
    : pop_front_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,pop_front,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, pop_front)

}}

#endif // BOOST_MPL_POP_FRONT_HPP_INCLUDED

/* pop_front.hpp
nzFf2zSEbsBYnCoD5lgAGFEZ2GpNMlyhET8VTnrGmaq5To88XgjgmEOWWlsQ/HyFKBdbdEphZ1S+dk0Dka/g1Dh4VzaFQtAiU5QbQyzuaBBJvd0S1gUOOTe7Aktbak1bOxEb5JIHdwPwl5DpNXX9jyiP9wO0HmeLeDoPW3Xy+ew1prou4aJEZQh1lvvmR2JzyD6laPwcPS8mDS5Oh27QGwS3ncGg16Am6YbKV4ir//OWp0OnUeODL/Hyn3m6Z17E69prCSjsrkSymzMifbi8kNTTaGhkb1iqpIJ6liASSxO2KUJtdkiFgSViDk2Tattk0f6IpQAU02qpsyEjv8MX7T872WOP2tgQPuE89ps84Y/WVBPZcFdmvPU2eV1MZ788NpISC3q+4Tcem9da/I+mfUIs/FGm9hRlfPRMWLuze+8a4jGP5F7LjfhFA7/+0H8BUEsDBAoAAAAIAC1nSlJBg9MZtwEAAK8EAAAdAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MThVVAUAAbZIJGC1lE1vm0AQhu8r8R9GVL5EpQumBwttkaIoiaNEtWWTXCMMY4MCu4RdUqEo/73Dh+1DpPZAKyGWhXefmXlnF2FQmyTWGDKRy72i4QXbX6pOdciWUbTub3B7
*/
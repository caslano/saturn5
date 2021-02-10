
#ifndef BOOST_MPL_INDEX_OF_HPP_INCLUDED
#define BOOST_MPL_INDEX_OF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright Eric Friedman 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/index_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct index_of
    : index_if< Sequence,same_as<T> >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,index_of,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, index_of)

}}

#endif // BOOST_MPL_INDEX_OF_HPP_INCLUDED

/* index_of.hpp
g4ttLfwH1obmTo/BYyprp24Gd22jfLTDXd0oMMlGXLYBTraRxgHO2FFGsOAoJXTFU4KbZXAZbcFWRHpRbaEQBfAMt94WATAygk9c0LZAHTy6MYdHZSqtUcGfn/b7DxK/YNH7UtU+DpSLTWLRCxQTlvSeuEANkldxz8gUrlLh0Tlk7sYQJpmQYrSpXSY7aB3I2VClh3d1qNfvP076af/xvaTeqXJd9zJv7Bdm301QVw22K5glUELl80AvY58REzxwT+VBmevMFYshUyFXxzD63/udoN9+3x9QSwMECgAAAAgALWdKUgA1ZFXsAQAAbwMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTkxVVQFAAG2SCRgdVPRbpswFH23xD/cpepL1cxQdQ9BXqQozZZoXRKlzl4rx1wGCtgIm2T062cDSx7avRjdew73nHsMzKKxUhicEparVLvHEduzrhMzJUvOt90B2z0n8/3uebPlr77Bd7PV82L3+m2/nvPVZv0h+DTjM8LodR6jvQS5gResT1iPTZ4gYTVWRevgRFgBSssM5fHrqEUz6j3Q6HMID2EImx9gzkYW2iB5EhZj4A3eQziBtT45RhRC9Bg/TmLH/f6Tk14lBr/k2HQFTcXRSVKv5R0N
*/
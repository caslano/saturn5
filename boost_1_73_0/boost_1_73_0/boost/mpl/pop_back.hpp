
#ifndef BOOST_MPL_POP_BACK_HPP_INCLUDED
#define BOOST_MPL_POP_BACK_HPP_INCLUDED

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

#include <boost/mpl/pop_back_fwd.hpp>
#include <boost/mpl/aux_/pop_back_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct pop_back
    : pop_back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,pop_back,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, pop_back)

}}

#endif // BOOST_MPL_POP_BACK_HPP_INCLUDED

/* pop_back.hpp
nBYpb4vEnWhSUXjfcMRlmeSofdcil2/aY+OJz8YtSKyuMR39BCmzYKYnCBqQUWkPoAc/5MVX4PCGrEOWUEEDEkN1rW0WGGKlpktWXG3i6SC/WT/vBhdAdtwolo51o53rszGlzGDyp7OvWJXDMGHUD0menovlavfYlvkRBndA554ZfYEw3BootIMXRAsTV5BnibfTtyzQtOTJUJWKU6EnlkuvI7Ek52P4jzgSvxlV3h44dQymays13T88b1frX5G4NQYb3p6p2djbR7QHX8Qw/7fdummqMrin3mXf9zKntpYsidZQhllo+YiZqA92Nf4RfwFQSwMECgAAAAgALWdKUjdTegWUAQAA0gIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNzhVVAUAAbZIJGClklFvmzAQx98t8R1OrfJSjTlM1dYiK1LVdU21rYka1nfPXGJUsJF9Sca33wFp0mqPQwg487///e50ijCS0RFnQlVu7fn1gt3ehzLOxLwolsMD7u8KoeTpj5KjWJyLc1hh2GFIY1WiUAHbumNBqUmPDjL7mMGn6RQW3yHuo6l9RPFVE+ZQbPEDTK/h0e9YkU0hu8wvr3PW3v8sxK13hI7SH+g2ZHNIPx+Piq7ldMI/JC01tfi2
*/
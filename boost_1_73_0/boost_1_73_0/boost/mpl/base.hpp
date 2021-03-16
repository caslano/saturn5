
#ifndef BOOST_MPL_BASE_HPP_INCLUDED
#define BOOST_MPL_BASE_HPP_INCLUDED

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

#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct base
{
    typedef typename T::base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,base,(T))
};

BOOST_MPL_AUX_NA_SPEC(1, base)

}}

#endif // BOOST_MPL_BASE_HPP_INCLUDED

/* base.hpp
S9+i9Or3WGXHHaPcos9f+f51yw5lb42yZYeyZYf6MmVHer2yTmXfEP+nc2fuG/IFahV7Q75wuRG0Fx90zKcjsl4ry/1a5HgrPAs8Sv7NtJtAVneZfRAaaaAuXAR/t+W+CRvqWxOf96t5IvO1iCsStDR2jfLBUPoDKveNOWLLlCMB81aIbJuV5VCFiS5iDP6pOXusQoGG5s7I8QZQXzWMv2+mXTxVAtTYOoY2wRh57+LLruf98XZ/zWjDP5RuZs8=
*/
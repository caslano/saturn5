/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    holder.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_HOLDER_H
#define BOOST_HOF_GUARD_HOLDER_H

namespace boost { namespace hof { namespace detail {

template<class... Ts>
struct holder
{
    typedef void type;
};

template<template<class...> class T>
struct template_holder
{
    typedef void type;
};

}}} // namespace boost::hof

#endif

/* holder.hpp
B77qqoq/t72Nx/bgPWTglIlTUMkhoWBiUALxjMzVNplSUaIC/UQSgjekAmGM1R6PV1BQWFhUVFRUVGiD0MAIplGikWJSTKL6rbdy6YqJ6Pqe77n3994bA+nP51N92vt89nbfvefee+655/4799xzfOkHj6fZL6xs+J0YPSoHA1SHZJHiSRdxoipGrE/rbyaYwG53jTSJVpISOTQF536bJA6pK5mNC7XpryWPtUImbk/MfM0j
*/
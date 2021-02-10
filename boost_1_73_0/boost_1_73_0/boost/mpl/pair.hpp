
#ifndef BOOST_MPL_PAIR_HPP_INCLUDED
#define BOOST_MPL_PAIR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/msvc_eti_base.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct pair
{
    typedef pair type;
    typedef T1 first;
    typedef T2 second;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,pair,(T1,T2))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(P)
    >
struct first
{
#if !defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)
    typedef typename P::first type;
#else
    typedef typename aux::msvc_eti_base<P>::first type;
#endif
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,first,(P))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(P)
    >
struct second
{
#if !defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)
    typedef typename P::second type;
#else
    typedef typename aux::msvc_eti_base<P>::second type;
#endif
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,second,(P))
};


BOOST_MPL_AUX_NA_SPEC_NO_ETI(2, pair)
BOOST_MPL_AUX_NA_SPEC(1, first)
BOOST_MPL_AUX_NA_SPEC(1, second)

}}

#endif // BOOST_MPL_PAIR_HPP_INCLUDED

/* pair.hpp
dh0NV500rdQyl9WQWI/CP0qu7ReQC3NzMbzQPSC/zKXTkzvTPgarEtu5/Xp9czm6CshJnmNjlnfZbvDCcwe9znbxdeIwkfO64O0qpW+Mw2KCvNuJ8qKfByQgb+U+z15zOBPK2FNoIesYnhBwHgm9oUILvjHV/+mz9mg42HwKabjxaPhctFftaqm+15zvORGlgXHR1j0J2xiTbf+JfwFQSwMECgAAAAgALWdKUqn5KLv+AQAAbAMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNzRVVAUAAbZIJGBlU+9r2zAQ/S7w/3Bk5EuZorh0Xec5gVIGDayLqbN+1+RLrNWRPEmpm/++Jzs/ygrG0ulO7957PucBfVDS45zl2qwtLc+476yr/Jzdr1ZF/4JiWa5YLs6pXAzV7BOU6F7Qca8rZLnDttlTupJBDgAinaRwOZ3CHzQb8J1XjfWYsOFaBg9aOevtOvDFohTXk2nCbnehRhO0kkFbwxfUKYNCet9aF9LJFQQjtzh7KItY+fkUFc6uz9GdNZ5QzgclqlifMMoEyvDVvsUMAr4GUYdt8x1ULZ3HMNPe8pubL994ei7+SfRDncHldcIStqq1B3qMDUBkwaFsoJUbskAM2nNx8IIsumt0hBgs
*/
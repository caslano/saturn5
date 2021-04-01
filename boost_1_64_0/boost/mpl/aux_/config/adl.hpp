
#ifndef BOOST_MPL_AUX_CONFIG_ADL_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_ADL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/intel.hpp>
#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// agurt, 25/apr/04: technically, the ADL workaround is only needed for GCC,
// but putting everything expect public, user-specializable metafunctions into
// a separate global namespace has a nice side effect of reducing the length 
// of template instantiation symbols, so we apply the workaround on all 
// platforms that can handle it

#if !defined(BOOST_MPL_CFG_NO_ADL_BARRIER_NAMESPACE) \
    && (   BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840)) \
        || BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3202)) \
        || BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, BOOST_TESTED_AT(810)) \
        )

#   define BOOST_MPL_CFG_NO_ADL_BARRIER_NAMESPACE

#endif

#endif // BOOST_MPL_AUX_CONFIG_ADL_HPP_INCLUDED

/* adl.hpp
jhPkG8N5OtbM5Zo5yqF6nX2u2+8rhhgpNMS81JGKSmq2Hc74WWAElvxJm53Y9DRjOnGrsbQ3mnFF/pkrnxn15mMEHzOHIKup3p5CPyQI2dCczRvYawtNUB/QksGxxwoQSLm1xKMhX7qWE3cU8H9ypaKOunc3wIX2pZP4Z3y+LkXLLnhzBjNP2VHKWH11QuxodiLTFu2qd4UHGbX8jtNfyxUYQ2xSe55SDPiVYn9TAU2p1J6rh5SBvRyihfoCKbblgeYzHkgviMmxUfyJBhthI6lUoN1wXZIILY9XtcLFZ+6CTgFcuaQ7Vxycy38GNIIM5sZD5/9DoKFUouE9bsMoedNEjIcILnmGHnI6BsxnOnGpDSCq88en17/P0odiebKWt108AT6BoqNxYBKb1yK+nHZpOvLWZiqvH5oagvTXI22/FEkS+VLB1vPONu7tPa8o4tn1yMF88BGqFnNMzeT82QGU7WcQPbaSJ1yEBafXgmuXSXEOX0oHGWA5ugyLi/zJfdLIqGjvabtwrLsBQ2/1onL7F5tlrG2KjT+eF4u7BC/G0KotWCff/WIiEg==
*/
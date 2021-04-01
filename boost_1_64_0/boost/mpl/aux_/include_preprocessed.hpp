
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2000-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/compiler.hpp>
#include <boost/mpl/aux_/config/preprocessor.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_PREPROCESSED_HEADER \
    BOOST_MPL_CFG_COMPILER_DIR/BOOST_MPL_PREPROCESSED_HEADER \
/**/
#else
#   define AUX778076_PREPROCESSED_HEADER \
    BOOST_PP_CAT(BOOST_MPL_CFG_COMPILER_DIR,/)##BOOST_MPL_PREPROCESSED_HEADER \
/**/
#endif

#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING BOOST_PP_STRINGIZE(boost/mpl/aux_/preprocessed/AUX778076_PREPROCESSED_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include BOOST_PP_STRINGIZE(boost/mpl/aux_/preprocessed/AUX778076_PREPROCESSED_HEADER)
#endif

#   undef AUX778076_PREPROCESSED_HEADER

#undef BOOST_MPL_PREPROCESSED_HEADER

/* include_preprocessed.hpp
Z62vg4iED27yGSSTsJ8nTpLZ3NQvURIKbdM95K8IH6Ssyk2ua73u+I86FGt+wAmGw++Snw70Q2J845vad13JwvJPae/DNMCxBeGxC7J1VqT2YOYTemKh+E0W3fS+lDOdip+dNVaF9gWmINrsY5eKuE7lqmWu1Um/F2aju7E5aV7hnqaq71XBSv+IxfwVjCjCRGJXB4yzBloq60mc+j1gcw7gCJB8RHtdLQPkUTekrue/46mKGKGJuJEs1g2IjJ32ruAaKjigzlTPN7Hu8Hssjdin5Ev3aQZ/xWOesJHdbemYLYkgCbToqmLhSzKPHu4c4O/uyOTj1xxjkX0Z5w1HKOQuFkLmz/Ow6qLRepE0pbVljVEq10brZjs5kublCoZUNy2RudxCBiElT25bOl4id51Q4ZjpA+5y53u/nJdzgeTJsE+5kwPrmFmrdaNc/9QfYHnfYaRrioAoj20ExDATxEWqGaSbO4z+aKCOgyl5g28yGksT97Vo7w9v+7SS/8GtaV15StCEj4jgmTeY2kLr0Q3ERK+Cz0f4Y4dfD1WLcr10hwxL9mPPi6UoZg==
*/
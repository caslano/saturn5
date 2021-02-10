
// Copyright Aleksey Gurtovoy 2001-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#   define AUX778076_HEADER \
    aux_/preprocessed/plain/BOOST_MPL_PREPROCESSED_HEADER \
/**/

#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING BOOST_PP_STRINGIZE(boost/mpl/list/AUX778076_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include BOOST_PP_STRINGIZE(boost/mpl/list/AUX778076_HEADER)
#endif

#   undef AUX778076_HEADER

#undef BOOST_MPL_PREPROCESSED_HEADER

/* include_preprocessed.hpp
9d6DMJIbD+K3KMSlB3L5HiJH89ys+93zyzL2OOBRXvijp3/8Y79QSwMECgAAAAgALWdKUpjqBcVhAQAAOQIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q3MTJVVAUAAbZIJGBFUk1PwzAMvVvqf7CYOI4wJDSEogo0ipg4rCxlCG5Z69JqbTM12Uf/PW46tlMc+73n5zjSkXWpthTCaM1HhibPsU/i9HaKOnfU4nr3iy1tTetwNLmbPIAsm9yEIDfUHUyb2RBekxjiZ7WCZZQsQS1m7+oepLgApBg4IxihonZP7diWGYFk4arjeqadDsGWVdVhahpHjWPSkJXihPL0WVVy8URP/YUh1ouGkLstWJNubN//P4my0TV5m5iTSws8lK7A8XjbmmOHlhw6gwPtUQjGi4GAMjV1rZvMC3Pp+m2hknn8eM1S8WKZiOnk7qLzL3BG+ZfocchuzlIcnmz7gVbUlnmH/aynF3cFDUsotMU1UYNXtjDuCuTeY1mCOzqTmiqETxUtUTem6Wqzs0G/B4Xs9omOut5WdMN9Ofv1EkAUq1UAyXcc4TwANf+JkP0HfmtD9PE5TwI2eJGX4txTXH7LH1BLAwQKAAAACAAtZ0pScuq5m3oBAABqAgAAHgAJAGN1
*/
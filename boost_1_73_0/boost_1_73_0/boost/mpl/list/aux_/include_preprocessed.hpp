
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
j73qH3onpp0qQNvnTBgm43i1TUvSXPjLjEh+L3T3Dm9LZ9BFZkDaVix1PDmMJ2eTse4kth98XQ0jLobADHnhYB6pbkfQA0eZ9tJLpObjw5EoGdbN76Tqh3HH17JCCzsijoBaN/MgVx0hV7vD7Y7Q3u5o9WjLw7RVZ0HamvjQyLAGGUnG4tQp+pMvGPW0QlNjszQFeN9L0pYPSVmLrgh7jJCY8ZXWjIt0FNsLM2G4cxk0BoUvTwXnXQIrpk4qAd0=
*/
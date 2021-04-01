
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
wl4FcWhEDFgJL/T7abfZD5UfWeeD/nHweR77lv48z1GkCcdGoHd3jBejIrgH30kPwQAjzb2N5w1SlX/KQoCVkJ3xUJoUuB3CFu9+HBqjDOZysP8EyBZTTG+KY3ANCMJzE88khHKz8BaTHkcAVw7xIIdD3AOubqa72wAg2bi3/VCgof6KC+A7V+PUSoFduHXdicIiAVD2uD0oqYj6cyWIu29ZUsbKf0AWjIq6q6HCVxLfW97jqh9aE8eRu7hgZaT/1wUaqTXOJR6KkvDt1odEp46+eSHfSlLCq9ABVCBMvb+l1FNh3xwsyjxbs51+o4WtrD4xWrZI4OUdg8bIkcgbl6gcjiRGMvuOmON3kRS5gAvKuqQf6cqg2mEFOSABb4W/RWNKVXYh6vpmvOspB95wFfmJLF2e63TjS9/dGAWNZ7XodxzjivogkiHGkyiHdwKut+5R6AyLdV5mIfT62xU1Tzk4Xr+0pz/80SA7agG2VHpusQWymzHhkWpsiwjsiX6HqqqoULjHXIOE1Fz3SaPGwXIevZm6VMf5dJzj+ntp/d+7PzaUdHb874VBUQ==
*/
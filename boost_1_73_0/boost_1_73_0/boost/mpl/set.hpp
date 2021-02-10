
#ifndef BOOST_MPL_SET_HPP_INCLUDED
#define BOOST_MPL_SET_HPP_INCLUDED

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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/limits/set.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_SET_HEADER \
    BOOST_PP_CAT(set, BOOST_MPL_LIMIT_SET_SIZE).hpp \
    /**/
#else
#   define AUX778076_SET_HEADER \
    BOOST_PP_CAT(set, BOOST_MPL_LIMIT_SET_SIZE)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/set/AUX778076_SET_HEADER)
#   undef AUX778076_SET_HEADER
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER set.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/set.hpp>

#   define AUX778076_SEQUENCE_NAME set
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_SET_SIZE
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_SET_HPP_INCLUDED

/* set.hpp
ZXN0cy9kYXRhL3Rlc3QxOTA4VVQFAAG2SCRgpVVhb+M2DP0uoP+B83DAXbFEcZN2q88JUGTptVh7LS5egWHdCkVmYi+25LPkJL5fP0pOkw0DtmFLDDiSHsnHR1KJLRorhcEJi3O11PRaY7vVdWombPrjp7vbj9cPL7Pr69k0uX2avdAOi/kREvPOin0Nc6w3WPdMniKLa6yKlo5TYQUoLTOU63HQogkm7CZJHnnYD+FsMICHH8BszUI3SiL7XliMIGnwGxhcwke9IUg4gHAUjS4jAn+4T1gXJgJHvGf8gi/FGtlUK4vK9pK2Qne8szyzZcGuG6XaXoYijYAI0OMiykKbo80dqpXNIhgwUZDXjYwgOxsHw3SxSNHudLsdKVNdyKGUo/ML/duZaM2FGQ3xy+6LWe52dT7Mznef0z7uRFkVGI1Gw+A9lGI8DM+HFwP6vIcKa5MbOw4ZyeaE8bIlWW6AHpshGJRapVCjqbQiel6+8B/0c0kolDbXKoJ/lVYX5u+4vjIMXYX3tSSu0yJ3brsSS78gQFeECcusrQj+uiR8jZ+bvEZIcdGswGhKUljYcwEpFFAbrUETHqpC5Ap0kYLLj8VLFLYhJSav3Jn3QgGOJ7ESJR4A5FA6EcUGQSwt+SQQWpurlVc3Eyot
*/

#ifndef BOOST_MPL_MAP_HPP_INCLUDED
#define BOOST_MPL_MAP_HPP_INCLUDED

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
#   include <boost/mpl/limits/map.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_MAP_HEADER \
    BOOST_PP_CAT(map, BOOST_MPL_LIMIT_MAP_SIZE).hpp \
    /**/
#else
#   define AUX778076_MAP_HEADER \
    BOOST_PP_CAT(map, BOOST_MPL_LIMIT_MAP_SIZE)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/map/AUX778076_MAP_HEADER)
#   undef AUX778076_MAP_HEADER
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER map.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/map.hpp>

#   define AUX778076_SEQUENCE_NAME map
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_MAP_SIZE
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_MAP_HPP_INCLUDED

/* map.hpp
YXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTY1NVVUBQABtkgkYE2PQQoCMQxF9zlFYNbSC4RudOEtpLQpU9QE2o7i7c1YtK7Cz3/k/1Dn1mNo7IGKZLVx5ddTa2oeNil99yHpCuSmQW6wsMCCx1th6YdWEgPFjzCicX1w9SAqtnZfSZlD3yr/Xz/p2YhpIEm48wBwJzBrRetwYYlqKUhuEOR+eW4+8gZQSwMECgAAAAgALWdKUq+vdT45AgAAbgQAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNjZVVAUAAbZIJGCVVGFv2jAU/G6J//BGhbShpSZQIZGmaFW7jmpbQSXrvk0yyQtYhDiyDQhpP37P8SiMbpUWRbFs3ztf7l4SWzQ2FQaHLJZlrmhY4m6rdGaGbJQkk/oBk/E0YTE/bMXco9kZTFFvUAdGZshijVWxo+1MWOEJeHgeQrfTgfFnMFuTFsoguxUWI0jW+B46A3hQG0KEHQgvootBRNhPXxPmeSNwCgNTT3gulshuVGmxtMEXLOd2EUHYYWxWCH+TMn92zH9rIYk3hXQFXmJaTwjgOYdsYW1F8P0U4lKs0IuHXOlVpYwFAbksELbSLsBUIkUDsgSHpALuKyBO1WolysxzRpy3RmTc
*/
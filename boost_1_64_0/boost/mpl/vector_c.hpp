
#ifndef BOOST_MPL_VECTOR_C_HPP_INCLUDED
#define BOOST_MPL_VECTOR_C_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
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
#   include <boost/mpl/limits/vector.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_VECTOR_C_HEADER \
    BOOST_PP_CAT(BOOST_PP_CAT(vector,BOOST_MPL_LIMIT_VECTOR_SIZE),_c).hpp \
    /**/
#else
#   define AUX778076_VECTOR_C_HEADER \
    BOOST_PP_CAT(BOOST_PP_CAT(vector,BOOST_MPL_LIMIT_VECTOR_SIZE),_c)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/vector/AUX778076_VECTOR_C_HEADER)
#   undef AUX778076_VECTOR_C_HEADER
#   include <climits>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER vector_c.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/vector.hpp>

#   define AUX778076_SEQUENCE_NAME vector_c
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_VECTOR_SIZE
#   define AUX778076_SEQUENCE_NAME_N(n) BOOST_PP_CAT(BOOST_PP_CAT(vector,n),_c)
#   define AUX778076_SEQUENCE_CONVERT_CN_TO(z,n,TARGET) TARGET(BOOST_PP_CAT(C,n))
#   define AUX778076_SEQUENCE_INTEGRAL_WRAPPER
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_VECTOR_C_HPP_INCLUDED

/* vector_c.hpp
4ok+R5MPjMzOmorMe/Ce4iNTV1HcH01lCNb3sP6HwvvW+DKT4AncgD4CBeY6wp6NQldn4UU/AWNX/hES+T8g1dVIe1Vf+WYntrlPU023g2zA/Spdlwo+SFJ8bIunMngMglQNKDKPcdvvxfj+0Z9yJ7k/4XDAR38JmdBfH3TmOkb0OpJ7HUbv1jTZWjL++zOkMmvXp/JC/mt2Almo9bnd4IpAvnyQT2Hm51gJVj15mjYtZichfXas3iwsNbjy92jCaK/SQZm++fWBxmKGFCy2LfmvgKtM8ut3Ci5Wz0tkGKBuxeZjzCHEBcdme92074bqp0T9semNaUFIGuKrE/S1eO4lWp2gLN2uTmDmA2UprzGYzWF4BEiweqcr2swHtl4GpMiiWLvw3Sjkn/meeAvB2YL/J0B5tvdxlyTxdHLj5QPO5oVeBpLmoeuMpni+4bac+b60nqko8icln+399UkCj69Ra1HxJ7PJS/XOA3HjJ3mE1K7Iy+CTEI/BT9BeTrGZuyG6PWPyLx0+RX8zC3ZTOlC4BC92/H9i5uBkD0VosSyYd38808X6gn4jQx0OFfbWdGAz+ew48PRwC81TBYlhtGx01r7fjlMlRQsuyXgphA50y8PYT5b/A2IaE+SQ2Pmkr5dgS4zCh1FEKAdDGuIP56HUz6ie86bmBAJY+rXhJsTZkUcm4BBjbWjdZ19nHy57qFn4CVDR2U1tqYO0fH/WGwUN5JqjmWrCj4PdMYLomeVqRPRQ34DWr2nc14Va62BMlwpSZd7zUcQsU+/QDFSUUG/zO2hm1GAX1VQU9IQ6QNvACDQDgfsdaMJL63OxVAsGZdVSM59PD/wCpXGDnc+lVamnOWK7cMWlRmJwkjWSfyP5w+dB6GAKJIZ/zQHTXfGC+INf2pcwe2N+aVrNgaT8xs9QJj4/tNPHifNLvkjOL+34jnxMNub//joB//er6PH0+1vy8bRKMp5zfpc4f+GGxPmtfx2f3134RWJ+941fJId/7N8S9z9/R+L8dw7GzA90wGEAGK+F9XJY+cdb+T1/G52P/QgGpYv8Q5bKvRhF//0Z9B/L70ECSpn8q8xxxlGKz4+A9Rw0Th2Wwim+QeFUq6P6dK5f5+Y20Ae5XcQ3ECaKv+T9Ab0jFyQJcJhCBm/YcnHyA5MwF8jvT+qXv8F0IL8/8q+w8geQPtJWK3+AhmwwSl5l0e9EN27nksgfpiFHjOCjimKi4zHzb198fga/SkDg9hdr5wQibw7Ct6cI2CzrJoz/7E29P4V2J78adSR0vmBDPaWzo/cLh33UlAPdK0OeV5s/hfJ+orMPpTyRo03ZKV5ceuN1sgvSNftDq8YROta86ckDDVakhpaasjjGcoJn7l95oCE17pid/7kP5w2xfu9gsW60/ooqcIZL09LH4WDK9MkuSz+jDroRueG3OPSz8/Bcr1n233sZvrlC6QO6rgEn9thIijv8iVTUmw4iS5irlnUIjDJ20YExaj+loMjXvIzj0sjkHQF4pkXxvg5BPTglfh7kyY3ne/ce2/qep1+6cNztDfbC6+Qa7GgtdspWUT39byBdSdx8yD28Yej9VmiHpys1rYzevcFjVAAu89gXsLPiUjNoj3EjCqhb+6Sn9WaPc589eiDxfVf+m+T3Xeu/WL1E+78iLjQmdfp7elLZFipTkOC++cS3uDZwg4j/RiQ420KRh7lsqYfrsxzk/uUL5YsDc9KE7eRTmm3bfO/+lOc76JFn229ON3G29Zm+OezBicbB8wIAc6JpKYgMhA6oJIRByb7yRxwE5LZH6z7ZukdhDCG564isDBkRwxP0onL/rQeOPNq2pf9J8tAAq87c8ghgVkPra3znUDM=
*/
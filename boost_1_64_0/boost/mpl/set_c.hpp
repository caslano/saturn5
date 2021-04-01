
#ifndef BOOST_MPL_SET_C_HPP_INCLUDED
#define BOOST_MPL_SET_C_HPP_INCLUDED

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
#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_SET_C_HEADER \
    BOOST_PP_CAT(BOOST_PP_CAT(set,BOOST_MPL_LIMIT_SET_SIZE),_c).hpp \
    /**/
#else
#   define AUX778076_SET_C_HEADER \
    BOOST_PP_CAT(BOOST_PP_CAT(set,BOOST_MPL_LIMIT_SET_SIZE),_c)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/set/AUX778076_SET_C_HEADER)
#   undef AUX778076_SET_C_HEADER
#   include <climits>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER set_c.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/set.hpp>

#   define AUX778076_SEQUENCE_NAME set_c
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_SET_SIZE
#   define AUX778076_SEQUENCE_NAME_N(n) BOOST_PP_CAT(BOOST_PP_CAT(set,n),_c)
#   define AUX778076_SEQUENCE_INTEGRAL_WRAPPER
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_SET_C_HPP_INCLUDED

/* set_c.hpp
hAv3C0lSfJqHUuiQBqroG6AzZ2VXMjSIKY9NBAJS92X+HU4n1ds3QlQd3dUlXxlkKQadjXCJyXyWYnJj3DeKMRNtRXS/yfsr600qr7xp8uwLKiwGWManGx31alM2I/JIY17xZ6bmDLzHyWtpsqtCCr+ScQzinwu35JlI0WlQ79R747BUS44/r/qKBcoQoeZt3MLKEgo7z/n1XW/btI9fPPcyBeP9en9asRKsVx+hvFbpub00nmkPWkpTg3APIP3fDkgWzflxFi0JAP/QqbwmHBVnorrE3n7nv1LmUn8yNezc04M+WYBe24tBe0RzE7JzbtfBnTBG5dLa3f/fUKCZkC7ceiJy7HDfk7MlFX2IJ1cSawM3lDFQSZVhDwsPEfVajcZjRlzKat9q7IfW5H7vK0oy5s5Z7SmTcZsS8DXjIabmyskk9/sYgN4fMt2x0894efFPC8tVGFSuC82V+Zos+NshZJAlx5SUu01KHspe0uTQ+yDpDwTnkLrpgaTgsol9oHDIueAsmH3NdSci0nRnHRPJOhruYOnan3ON11ReWrmz9zcPcFH9GsVFJg==
*/
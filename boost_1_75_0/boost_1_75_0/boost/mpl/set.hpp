
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
GGiqq85Hcap/jfogYHNSzhZTfHJBToSBtHi9/mIuP+xj9fYLY7nMZzJQB440SFoaxeiwXyrASNtMAiDKY6jdb2HstEBAUK2KIt4Lv4/muKzBWGRA1oSs0DQe8xDeeHycV15mYm+sn6mN7ufRqHShNVnrserlh/1Zql93Z+wTh4k2kUV28k9GZsYzt4LLOGSIxWcvhJKiUA8kDKHg6hMpzavZQsKhTQvj9KQO5JQsoXoh06E+nG2BF8r2DZlbLs9VAPulvW5OffmGmdKyY7QuZPca90xYaGzQboN4NjzIgonhW0bqDx0s97MtnUajx1SfEsZKUo6DuOCsjsZ+gBUl+AWbxNZtfKm8HPE5E/NyNn6U/ralRVOzt8FpeZ/DSxiIv12jVOPHT5K4y4HwbDF+P94vU3KSlyXSQxzCONmNba85Y6QJ5Z6YIr4rc+HQOAlioH3pqjbkvcam9WWWT9QCdsgf2pdbZdbfJd/TDhofTimO2Q4KXqphe9JH1MhJZki+H6KJHeURbjHKiNhDk28oc9sQQPSjeaLv2/gaAbEILFUrZcXhJXWkpowikXctORFYt2Z0/s5CTiufQaB3upBCOcc0uOF6M+WuEaja0Lutv2AxBCr5ZrW7z5cKB4LHhwMZSdSoUwO5zedjDHjFwMXi2knP7VoMxYlBwwppDHlV4k86x/cGX0xIAzTL9H3tfVVccathJ2qEWpbNtSLW
*/
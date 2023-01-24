
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
Z742pVrY80ZnSK3rZMmu88RbabnMBgTYjA9CsF534B7DeC4dw9Vugwibo5cBDUIT0GIQ/I4AAZ8w7XoGp9F1PYKhXdf3gI3AwwkoYvtw0/d5HfC8lQJAnrRLaDWLVSMKlyOGVi4cvm77zcPgi0sHJ0h+MVWvRGGYkHWW3PJtHcSnze/mqy9nCXaDbopCEJ5Gad0Ir3NHxoXks/rM5scJDH24C1xFONmzUOw3cQoLMyZzdgoLf5y678yucKFvheJmWpfxIC554JhVGfVks1Se1BBT7+BkB6yDIoWpKd24ueYgHPeZwrFw9bgcwtSvjhYU6nY+BqHWNC3AWdIy/1zuWTHPr1tr0ENeuyoa5iEarhOwSgTBNViZAlr9PFf+rrN7LyXe7hXV+yhPT3eK27H12Ils71o/d9l8DygXvDD82u/W5/uFsUv+wKNz7ZLAG2/+uIEVmXnuJwYy7RHkfnqW77wAtN74PPPv759evmvjejTsrDQeMDAL89fTfjx23ccMgR6MBPVAWw4FJimQOkh7cXnCzWCHuft3B48J+ZJ0E2lB/dBcZBk08/wcGFGlO8mcUG7fv7il3/auPX1ynVMPoZjbtfxZMnBoJV4uKPMw2q91s8ch1B8hXlj0EpYATjKdvcvdPPYDG3dcupkhd/lqm17CwszvFdv5NE47TwICKNJNhLTtHzNI6IMkS27VRvTuTUvJ2GGI09iaQKT7
*/
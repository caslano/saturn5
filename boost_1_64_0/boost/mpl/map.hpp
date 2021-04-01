
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
v1dIWKN4OmGqqv0cG6q2PRTT8CVBHp45XncX+9OJE03iKsmcOgvKcMAql9ry9Gocj9L38ijenqm3JHFFQcpBgTVAi4/GsdI+7XOJed2eiheREPG3uX7MgDKeXjAmiSo06e0GiWEUaCkr7g6182c2GN8VAN+MSkpnE8cYwV6FYZQQy13+auvGOWb78VpVau1CZorox6bhJblDOEhh5o8UbOcEomrwMXw+p5pX78FKFKtajveJDjhbMLVmTPOEdCT7SFZdB1nJfRHPVRtbVELi0QDprKP7SXMJWzoJ0XHUYLXlVA/dzg2V228BbDZs73SiAhYh+L26cZ3qIAhKTMNwJlfIZY1i2R5Nr7ER03vFb7xqhTuMkhEF3V6OnE6I+oQNUlAx7baAaiMNaM0WnV1ZinwcHbVw8bobFKR3i8pmXjK1cYUaBb7sufXhd9nuQGZHlJ0OBbefac4gsjvlfxHNhERlHbtkbT97vU6sI/LB85FCb6wS3+Q5LkRlFqQbLspEie1rrLvkDobUPYyMhPe/j2/qhq2WatG+YDpKKpRhVcwxC+5JEQm3f7tpSg==
*/
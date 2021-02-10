
#ifndef BOOST_MPL_LIST_C_HPP_INCLUDED
#define BOOST_MPL_LIST_C_HPP_INCLUDED

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
#   include <boost/mpl/limits/list.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_LIST_C_HEADER \
    BOOST_PP_CAT(BOOST_PP_CAT(list,BOOST_MPL_LIMIT_LIST_SIZE),_c).hpp \
    /**/
#else
#   define AUX778076_LIST_C_HEADER \
    BOOST_PP_CAT(BOOST_PP_CAT(list,BOOST_MPL_LIMIT_LIST_SIZE),_c)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/list/AUX778076_LIST_C_HEADER)
#   undef AUX778076_LIST_C_HEADER
#   include <climits>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER list_c.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/list.hpp>

#   define AUX778076_SEQUENCE_NAME list_c
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_LIST_SIZE
#   define AUX778076_SEQUENCE_NAME_N(n) BOOST_PP_CAT(BOOST_PP_CAT(list,n),_c)
#   define AUX778076_SEQUENCE_INTEGRAL_WRAPPER
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_LIST_C_HPP_INCLUDED

/* list_c.hpp
5wzmJgckdS1qzWsNaquSUihuke9M8xCWTJ+CFyBpif5OAM5F6AVhcAG3s9giXVXCPidE9YfeBXx9rIvXY6hE+kvnUmhdcuoP3aEH8+mcBugUtJcZw6asC+oNg6FjkXs82jORFlnB0xDiDcfQPszYPvQ49PzQDbrQNzFbhzAY+WM3YDZPRnbgjLLMz7yBRa4SUzB7YSqlQljtsP8W6ZO073m91nkI7vj8YIx3DeZbbUpdmMZS86Ytv/oGK7GpUyZ3l4EzZr535vpeYhGL2PYfhj2UbqE0f9U011V5uGjxejptm6l/PnYN0ptxfMeNs//FbZXzAYyY+m9E27ZQ2p0aItqrA5V0XRYGrdV4lLQHdOhkOiG51g26748Q1azinZx6nW4LnfcVLHlnU+hHO0eIElFVrE47qJDSo+nDMr6bh0cGY/6wiOmW1Zq6ZwHY8tMYYNSPp/jZE0PCT1wW2Q5MJsAy7BfonIOZdciZghXHyRqoXOgBiV5aXwTAydAiEeWE4LjDIeR+LiwyFUqH8A87iyw+1fnywM8ij1gV+2qNvEJINrKkR083i+Xdw4+9FEM4oSemHxE9xI/oByl6+EH9BlBLAwQKAAAACAAtZ0pS69IHimECAABNBAAAHgAJAGN1cmwtbWFzdGVyL3Rl
*/
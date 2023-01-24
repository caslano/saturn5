
#ifndef BOOST_MPL_LIST_HPP_INCLUDED
#define BOOST_MPL_LIST_HPP_INCLUDED

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
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_LIST_HEADER \
    BOOST_PP_CAT(list,BOOST_MPL_LIMIT_LIST_SIZE).hpp \
    /**/
#else
#   define AUX778076_LIST_HEADER \
    BOOST_PP_CAT(list,BOOST_MPL_LIMIT_LIST_SIZE)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/list/AUX778076_LIST_HEADER)
#   undef AUX778076_LIST_HEADER
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER list.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/list.hpp>

#   define AUX778076_SEQUENCE_NAME list
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_LIST_SIZE
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_LIST_HPP_INCLUDED

/* list.hpp
munqx37604TewkG+omByJnm+ainS6qOtrlnxQe6wGje9Y1OoXbZi8dkb5gRF5jeWvD9VeFNYaSLIhGfBifG3erNF2wTCrFvnl2t+oHkWfQM7gfOGn9tA2HlAtt9k6yHQ7xJ6/oy4qIRDTTtdb6sHOmpMU7/bt7J9cmJlxKM4+UNIG2HAlcEX45YTIVF2hWXW11E5e/s54sdhB1rJH2XBX81INdDn0MpDBEYxZMRqyJZQKjCdpp6NHiVoF4u/+Gx//x6S3Mv1xBAtxMV8AMDA6HvxKd309ozc5vSrJUxd2yMjbRH4oe7SKwpUrFkgAtCxsmJ4q2lOQpJc1547wGpLksGkSCgnbCAZmF8zseyWnn/LfWqudQzuPhSJWGsX80Mbo6sXmHtJdW2wJVBjBNvtpulN3ZxGhDRPeA2AzGGyf4Pz56cHEeHBZ8JNi0dT6LlJCN6J7usgFucmf+DTfTlCRJc5x/vSPMegyh9fsJp3H7S3utC4ess0SWoaY1P/KLgxmNewhAJLM79fM1TLTPwT5jafChp5/HFZhowFCR13HJIBkFpkMP/AevYrffB7o2MESG38AulPtvbS4Q8nNKcXTqjvUTNRTeDNqJ5bnmY4NTolAi4sUygOxH+Tc/w1jDOUC7ITh+Vwb8GpP4RQWKZwW4LJzAimsBtQ/UL8gj23TMxytmyo6IWD1brxvFHebaF7U9wUeeSkz8c9BG6h
*/
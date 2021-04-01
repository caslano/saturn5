
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
b34JNFjdiu2VAqiMRqdaIWkT7L4cOv9zisxrfIfHLt2lJ0ioj9oCxMH9o+OwReVrijayU5we1+noyC4uWx1t1e+tfObCcN1qDS+ed7p7CNU68gErRtf8HwkRn6ixVn9UsaaJcMVsM5REZXhrE23UiQwHPPNMI3TsJhRo13GMztl8nXZIttYzjhpKByBRZFqdBWjVwxgKmJ8RZCG5pQ2Ua/2p1jLlEG6LYsb25sNHpr83xU6WkKzeAaiNK2bAYNYT2+603kmsnPzmj5Ffywe0WIV7lhjAFLia+aZhFAd8onIh98po9lVUMs+hVw5RTVbjhhsgJp4d/weO1E8tNqApQeVD2zUSS5sX46QpTxmzD3wwcaANfPSYQQJtLNFm1nujHw9f+thIo77HmBJYTvMFUutbBsok2IWYjw0CQ6+Hrx89RAct3GWhjGmgu4COydOmobDZZfcyCUIQr5O0RaMStNeqc2IlhOSGCd1rBgAhcmtQNlGva1C/O0XcqXUB+2dpXAFsA7p5cZxlgvxoNSVN1uhuocoodJUv8mWjfNOq0GpWoBnpqfo86Mssfg==
*/
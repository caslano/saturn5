
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
iDjvrIg3ibSZEM+S+qcj2ZNNXYCQEisLV+R3Tn7/wM9zc3PxcnWXzJ+mL27DFUZkgc+9cxlbrYsJK/JFeDn4jg66NYmmy5JoTNibm4d5cvsYvXEOHh8+JXyPPCDo515hYviEdb5swY9Tl5vLyM0ApWVggaggMJm2xGLjseSgqrXV0gX+MEvAB4DX5jlhN9rYCP7C44Rd+ewjOOWnJ+zkf9nG/MghNrbOq2VeoJPcL0A31ifyNm2pKLl8B7irfMfQTQDLWpf+2Bkd2sdtUGGtr5ulihtm+HPw9udfn4NfTt89Bzy5vZ/Nk6v7R+5Kcowaez+u+uOg0CtOfUNt03O5BVDqlLbdtRE4fj/ppoY/NVYfXIObiHPXI32DPNXS8D2m7++a/Tj7OFuqywoV1pRKCosWqBuc5VcwS3OaAguti6G3CurcrPssCyE8+7Y/oG8IB01pYuE/30NAsw0HOSCkm4DmpxODH/qEH/8EfgdQSwMECgAAAAgALWdKUqcUOYa2AQAAZgMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxOTA5VVQFAAG2SCRgtVPBauMwEL0L/A+DSy5lvYoX9lDjGEopTemyCY23d1kex6aKxkhyS/5+JcVpYLuHvezFtqQ37715
*/
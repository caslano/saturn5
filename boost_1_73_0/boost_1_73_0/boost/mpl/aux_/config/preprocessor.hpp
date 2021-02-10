
#ifndef BOOST_MPL_AUX_CONFIG_PREPROCESSOR_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_PREPROCESSOR_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/workaround.hpp>

#if !defined(BOOST_MPL_CFG_BROKEN_PP_MACRO_EXPANSION) \
    && (   BOOST_WORKAROUND(__MWERKS__, <= 0x3003) \
        || BOOST_WORKAROUND(__BORLANDC__, < 0x582) \
        || BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(502)) \
        )

#   define BOOST_MPL_CFG_BROKEN_PP_MACRO_EXPANSION

#endif

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)
#   define BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES
#endif

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING) \
    && BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))
#   define BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING
#endif


#endif // BOOST_MPL_AUX_CONFIG_PREPROCESSOR_HPP_INCLUDED

/* preprocessor.hpp
q0Or4GSYUJaNWEh9P0sSIumI0cA/CllAZXLkUxHLKMAzQoIR5SSQjESBz5PQT0YiEzHBrnlh1zW6mAw73p2PqVVl0CYKs4Td0pCILItHyS0VPKExSQRj9EgQjJGIOBqFERGxCGJKOYupzKgfRzy7peRJPz+qpWfd/HKBU2+Xw9R7SKy3+0/+CVBLAwQKAAAACAAtZ0pSqLotEdMCAABYBwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwNjRVVAUAAbZIJGDlVdtu2kAQfbfkf5hSRWqjGmMDDrgmEkrSEqlqENDkeb0e41WM191dh9Kv79iG0LRV1ahPVSUEu/aZMzNnLkQGteFM47kViSKV9HOPu61UiT63ZqvVvPmC91er9nAp1mQArDKZFblHaOS21i9hieoBlaNFglaksMx39DZhhrV8rtf1YNDzYEoUUomvzAhZwAI/V0JhYlutfQjTkvEMCd7v+mfw6pKprShew3w2dwddr+vb1t3dnVOzYGEEZwbDQ3QKWb6ZdOrUmmPnDRSy4Djp+L1hP+gNvMGQnrF8TQGYjKDL2dTxh0HHti5kYYjQWe1KIjT4xbiZ2eRvgWdMaTQToaUzGg3HjncEf8BibbIQ/MC2bGuVCQ30KaQBiq4J
*/
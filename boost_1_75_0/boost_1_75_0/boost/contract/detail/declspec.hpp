
#ifndef BOOST_CONTRACT_DETAIL_DECLSPEC_HPP_
#define BOOST_CONTRACT_DETAIL_DECLSPEC_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// IMPORTANT: Indirectly included by contract_macro.hpp so trivial headers only.
#include <boost/contract/core/config.hpp> // No compile-time overhead.
#include <boost/config.hpp>

/* PUBLIC */

// IMPORTANT: In general, this library should always and only be compiled and
// used as a shared library. Otherwise, lib's state won't be shared among
// different user programs and user libraries. However, this library can be
// safely compiled and used as a static or header-only library only when it is
// being used by a single program unit (e.g., a single program with only
// statically linked libraries that check contracts).

#ifdef BOOST_CONTRACT_DYN_LINK
    #ifdef BOOST_CONTRACT_SOURCE
        #define BOOST_CONTRACT_DETAIL_DECLSPEC BOOST_SYMBOL_EXPORT
    #else
        #define BOOST_CONTRACT_DETAIL_DECLSPEC BOOST_SYMBOL_IMPORT
    #endif
#else
    #define BOOST_CONTRACT_DETAIL_DECLSPEC /* nothing */
#endif

#ifdef BOOST_CONTRACT_HEADER_ONLY
    #define BOOST_CONTRACT_DETAIL_DECLINLINE inline
#else
    #define BOOST_CONTRACT_DETAIL_DECLINLINE /* nothing */

    // Automatically link this lib to correct build variant (for MSVC, etc.).
    #if     !defined(BOOST_ALL_NO_LIB) && \
            !defined(BOOST_CONTRACT_NO_LIB) && \
            !defined(BOOST_CONTRACT_SOURCE)
        #define BOOST_LIB_NAME boost_contract // This lib (static or shared).
        #if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_CONTRACT_DYN_LINK)
            #define BOOST_DYN_LINK // This lib as shared.
        #endif
        #include <boost/config/auto_link.hpp> // Also #undef BOOST_LIB_NAME.
    #endif
#endif

#endif // #include guard


/* declspec.hpp
6bVl8QVV1erxcVa/XfxzH0/tvjEspCk/oJf1XNFMtdPvQMK8t7DKuyAMhnIt7rsANZ+YkkTo1gUdgfLdR9Mw5G/piVO9ylu2+3vQGMfeuEdzka8yznZrz4l2BleijVHWSgYme7Yo1geybAvsMiorj83Naq+gGdt5iy/2WFaNxUr4Ic0LBG/XXlhQIeZVXC++eXOHhKK32LU4cVv65l3u7yZPytEMn6QcohVtdvKWwLDZC8saECQyXpO/fmqrepfsS/tNHRWEddEnTGklxbEtGJq2xG3mr6c5uyX3mkul5Ei7q0aS+j859IE6uYTwNZG/w1GCFtIk5STHmbCWHXZb6QnYW0SvlZsQN1SpqKqula8vmvKokxXa6u3cybXDIEJbS4sAY/55+YYaSjHTd/wFl+5N2o3xw/7mGUw79e4Ck7ejliXEFUd7nBaipBvpsBvebcaYkW+j3x0/IEpF3KnCeGdgycZx5tEDXbuPXGo5tUXGmQ98lJVIJqmklIUlvKI0HtelY28TVpHM0fWnE/i4HbIIXqRha5Yb1hke2lOvTaFA87LqhnzAHnMJjQ3Cx1Mq1VsSXfrPz1WPEJ40KDnAQK5mraB+zqQld7rQ9l6iWf8T+26nc9F2VMQYnds1ZDU1VVhMeIVTxXkN8ckRukHzMmdKj0kHtePDJrPtGEvM/c/23QT7rr3y6vhg+UA8TjqN6MHKZ2uextm8+UGL
*/
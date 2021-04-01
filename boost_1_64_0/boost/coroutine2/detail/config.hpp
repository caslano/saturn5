
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_CONFIG_H
#define BOOST_COROUTINES2_DETAIL_CONFIG_H

#include <boost/config.hpp>
#include <boost/context/detail/config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_COROUTINES2_DECL
# undef BOOST_COROUTINES2_DECL
#endif

#if (defined(BOOST_ALL_DYN_LINK) || defined(BOOST_COROUTINES2_DYN_LINK) ) && ! defined(BOOST_COROUTINES2_STATIC_LINK)
# if defined(BOOST_COROUTINES2_SOURCE)
#  define BOOST_COROUTINES2_DECL BOOST_SYMBOL_EXPORT
# else
#  define BOOST_COROUTINES2_DECL BOOST_SYMBOL_IMPORT
# endif
#endif

#if ! defined(BOOST_COROUTINES2_DECL)
# define BOOST_COROUTINES2_DECL
#endif

#endif // BOOST_COROUTINES2_DETAIL_CONFIG_H

/* config.hpp
yUHFRS6z6D2Zw2sp7OMG3YkLUGyzj7Vqci7nsssSC53GBRQ5MNrkiA6DOraivVpYurJZRK9/4OzZGbEcvziizNYnCG/hYBZ/18UukE34BnuUssFQUEPkcd2GKfYmmWvLPG76UseOi1frFEX06c1mSTxynTKWr9/bHqSQxb1cXz+fbob/iE4FEKdmEjMq0PnMkWGggGxgfIgIZKyjAA4SRHJOOn0nVyzfRTcLKSdpO+wUVgAoHZTbhElWTTk3V7Y+2XCHB63QgYpFOp9tqzuOIskZ2sLLcBkJi3WJB8vwmj6or/y2Z1mgHv91nACq0wkOP4BbF5UaXO7TOxghkH2t2aODSRT0aEIt1rMbcwEGDXuLGklE7RqIebIHVwE/L/CBnNnA9N7SCuVbngEroe6pwicA+5iJMkyJHZlmXM1HCd51JUtc0X4Mk4uy4QIKvtEqPRHKGDw7e9sWv7Q7xRRsXPfdZwe304hFTCezkBJSCmMTOeuKbGDaCWtD3iS2xDq0jY2CZNfWOJhh6hmY8Xkh2gq1gnAlFt0yI/STDBVzOKZE34ees+SHQTIBKA==
*/
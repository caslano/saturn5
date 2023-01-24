//-----------------------------------------------------------------------------
// boost detail/templated_streams.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_TEMPLATED_STREAMS_HPP
#define BOOST_DETAIL_TEMPLATED_STREAMS_HPP

#include "boost/config.hpp"

///////////////////////////////////////////////////////////////////////////////
// (detail) BOOST_TEMPLATED_STREAM_* macros
//
// Provides workaround platforms without stream class templates.
//

#if !defined(BOOST_NO_STD_LOCALE)

#define BOOST_TEMPLATED_STREAM_TEMPLATE(E,T) \
    template < typename E , typename T >

#define BOOST_TEMPLATED_STREAM_TEMPLATE_ALLOC(E,T,A) \
    template < typename E , typename T , typename A >

#define BOOST_TEMPLATED_STREAM_ARGS(E,T) \
    typename E , typename T 

#define BOOST_TEMPLATED_STREAM_ARGS_ALLOC(E,T,A) \
    typename E , typename T , typename A 

#define BOOST_TEMPLATED_STREAM_COMMA        ,

#define BOOST_TEMPLATED_STREAM_ELEM(E)      E
#define BOOST_TEMPLATED_STREAM_TRAITS(T)    T
#define BOOST_TEMPLATED_STREAM_ALLOC(A)     A

#define BOOST_TEMPLATED_STREAM(X,E,T) \
    BOOST_JOIN(std::basic_,X)< E , T >

#define BOOST_TEMPLATED_STREAM_WITH_ALLOC(X,E,T,A) \
    BOOST_JOIN(std::basic_,X)< E , T , A >

#else // defined(BOOST_NO_STD_LOCALE)

#define BOOST_TEMPLATED_STREAM_TEMPLATE(E,T) /**/

#define BOOST_TEMPLATED_STREAM_TEMPLATE_ALLOC(E,T,A) /**/

#define BOOST_TEMPLATED_STREAM_ARGS(E,T) /**/

#define BOOST_TEMPLATED_STREAM_ARGS_ALLOC(E,T,A) /**/

#define BOOST_TEMPLATED_STREAM_COMMA        /**/

#define BOOST_TEMPLATED_STREAM_ELEM(E)      char
#define BOOST_TEMPLATED_STREAM_TRAITS(T)    std::char_traits<char>
#define BOOST_TEMPLATED_STREAM_ALLOC(A)     std::allocator<char>

#define BOOST_TEMPLATED_STREAM(X,E,T) \
    std::X

#define BOOST_TEMPLATED_STREAM_WITH_ALLOC(X,E,T,A) \
    std::X

#endif // BOOST_NO_STD_LOCALE

#endif // BOOST_DETAIL_TEMPLATED_STREAMS_HPP

/* templated_streams.hpp
/1ZGIwQfb8SLEcI5R8rECJmk8JJwgz7MErzEbhCoyHnpgpdanhO359WPLQGjIAE7/WUHNuEl0IerT+97RBWSg+8nyvknlGNcfW4oiL4uF0gz6+aRWKVAA3U8l+odNWYsWjLMp+wMxPc7afEp8mWucSwXLCOcIDuGEjQPit2M02PmlmtSpOVQECxIxAmsObQsNEEPj0hGa7QKrSf4ASL8Q/M5/OEPLXCLAdsqh6xuzIfGOmgakD89OCNd23HNpThLgSZL6Jr+qEWKItck6uHHmGH76VXP8n9t9AFDE4vbg23R41JcSXz34lSN2qkA1W2hthl50uyE1QyVJGMZEeBiIxc4GawHHS7ZicjeQFygCa02wm3uuAOnx+4XOmfFnULnJLF8wkkbMK01UuhkJNDQIwcq6PekRcgjYVZElZRsF+WTRb2jCYWHVYX6un2b2SWsZiVmQ9pLyCpNaDycQyObUaGOmhpYwZfVmh1aipoa+GWJLSV3RVyzSuFncE6iA1epJohldnsjyZaaAd5u9NECAWQQko3jJ02cME6sBkpbK+RecFtB/eOdyVBuMuc3RsyHA3PtOS6YK7sRBKARv3KZRwuVkYQMTjsiJ+iMkXl6OPeI+Ug3mryYcITm975hqqNksoXHHLWndD7iHFyVm3uUgkjZph52tf6jm4itP0GlFpvRDh8IhiZaXw9t4vCHZTmt2tiU4nGOVOWaYi0S
*/
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
bZUup0z60L1MGENlE79EWndp3OYdD2dB01xVnTg5CtI47EJ3qWL3LMWWM6VBVTT1kxGJ5I4DcVHCgehFyc06T7M8OE97f6P0JBjSk7t1iIsa/+NbLSbRrDZBZqGb5ggbcp0NpLczZDIolMKq+pM6jJYJbK7lTHxYuYQvt3WKaM7HSIU8YRyHzyOP+MoGaqqvGKAXiUUv35KGmEU0GX4pFQnkpZgf+sT3zbz7X6AuW0sw2quZI7S6s3b1sJkMEmU4wIKLdxsN3f1KK9RzdTx9yIjYAPrUjtLnm1n3eD59BQxd4Ox9oCeiOIoAzSI/U6nnLRhNhXIbN1TcPZ3Z21grGOfUZi99bxype1Ogw1hgRUKWp3e6UuTYMuU7pGGn4k/koBv0Wwet7NA0TkCjglWuOMHfK5WwLF+0RGrMqiKlKQ9pXsdk+D/qc49ttrJcyKqU2Z8opp1xFASTpk5i7WADclJddKrDsFE7I0qc9lmNjfMkqcjwhexTC+tcm0J9AvoUtgFH19QiOw/TAz/RcoVN2BXwqXt6aQb7Jubswm876HdQeWofxzXBHe2isg==
*/
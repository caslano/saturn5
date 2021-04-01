/*=============================================================================
    BOOST_PP_VARIADICS version of BOOST_PP_IS_SEQ inspired from 
    boost/mpl/aux_/preprocessor/is_seq.hpp, original copyrights goes to :

    Copyright Paul Mensonides 2003
    Copyright Aleksey Gurtovoy 2003-2004

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_PREPROCESSOR_IS_SEQ_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_PREPROCESSOR_IS_SEQ_HPP

#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/config/config.hpp>

#if BOOST_PP_VARIADICS

#define BOOST_FUSION_PP_IS_SEQ(seq) BOOST_PP_CAT(BOOST_FUSION_PP_IS_SEQ_,       \
    BOOST_FUSION_PP_IS_SEQ_0 seq BOOST_PP_RPAREN())

#define BOOST_FUSION_PP_IS_SEQ_0(...)                                           \
    BOOST_FUSION_PP_IS_SEQ_1(__VA_ARGS__

#define BOOST_FUSION_PP_IS_SEQ_ALWAYS_0(...)                                    \
    0

#define BOOST_FUSION_PP_IS_SEQ_BOOST_FUSION_PP_IS_SEQ_0                         \
    BOOST_FUSION_PP_IS_SEQ_ALWAYS_0(

#define BOOST_FUSION_PP_IS_SEQ_BOOST_FUSION_PP_IS_SEQ_1(...)                    \
    1

#endif // BOOST_PP_VARIADICS

#endif

/* is_seq.hpp
H2WPWHscKcjwbhNkNpXzCRaAHrVxzo1RQ+HTuuYwEmDe7iaW7WGYkhhZoi/fitrBy0uveh8vUr7J0kJlMyOe0uIVUJr3MTixBlItHQqbH4xKYWsm4OyKIKEIcs1zWMkDKwraSzYJFjW4+iUMBHayygEmSrC0jSf9Tg0kLw2OAPvqSsfBRhNLg4TclWc67x0sbPSi1ugLl8HYgqyfrRNCB0vwQmp7MXpinCUDp3kmBbmzW5CGK08MKEBdFnBW4S/tsh2p9lzVtnIaHZWYDcYxv96gLRToHiRE5M6PKrbTB2dBrhsPR3fPEll0oLu1ch6TCKAyhzXN+YXQ68LA+DiNGMdNQr812kyiykbYXjVNu4uROa6FuWqRK5ZD2fEFZzDzpgzOgWPsGecp400G7jCwMsIGQQXkFgJA09hLsUa/f28bVR9oMKqcx1psrcF9JjAM6TwOyyZMt8CEY8lgLuv7Dj5gWyOnR51GYmQe0XIuN1EBdb6NcasJ/VRGb07KdnFWllEAn8bFthKjr1bM1DOGn7k6AsXnn5FdlWFblfo/5o9RfKfZzKDK0MU7+Q==
*/
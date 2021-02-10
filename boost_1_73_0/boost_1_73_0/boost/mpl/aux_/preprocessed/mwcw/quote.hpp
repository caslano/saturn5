
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/quote.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template< typename T, bool has_type_ >
struct quote_impl
    : T
{
};

template< typename T >
struct quote_impl< T,false >
{
    typedef T type;
};

template<
      template< typename P1 > class F
    , typename Tag = void_
    >
struct quote1
{
    template< typename U1 > struct apply

        : quote_impl<
              F<U1>
            , aux::has_type< F<U1> >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2 > class F
    , typename Tag = void_
    >
struct quote2
{
    template< typename U1, typename U2 > struct apply

        : quote_impl<
              F< U1,U2 >
            , aux::has_type< F< U1,U2 > >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename Tag = void_
    >
struct quote3
{
    template< typename U1, typename U2, typename U3 > struct apply

        : quote_impl<
              F< U1,U2,U3 >
            , aux::has_type< F< U1,U2,U3 > >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename Tag = void_
    >
struct quote4
{
    template<
          typename U1, typename U2, typename U3, typename U4
        >
    struct apply

        : quote_impl<
              F< U1,U2,U3,U4 >
            , aux::has_type< F< U1,U2,U3,U4 > >::value
            >

    {
    };
};

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5
        >
      class F
    , typename Tag = void_
    >
struct quote5
{
    template<
          typename U1, typename U2, typename U3, typename U4
        , typename U5
        >
    struct apply

        : quote_impl<
              F< U1,U2,U3,U4,U5 >
            , aux::has_type< F< U1,U2,U3,U4,U5 > >::value
            >

    {
    };
};

}}


/* quote.hpp
L2RhdGEvdGVzdDUzOFVUBQABtkgkYE2SQWvjMBCF74L+h9kuvbWrdNtCCcJsCS5bKBtjO4U9FcUaN6KyJkhysv73O3GC05OlN2++mWdbJYyp0REzoaxviR+fOOwpmJiJ57oQz08vr6syF13vkhVKnqtKHhvEd6gw7DDcRGtQqIBbN3A5jmLTmUyUefH6F4qnqoK723tYu15vYKAe2tnMfWPSF6+SJwBzF86iTyduM14mcCbatJ1aM3b/WdY5pI1OsEfoI/IZ4WF2D4nIQUuBBRvhkFaog5YJZ9dsYMrxCsrrDsfgMAa+sT5haHWDYGjvHWlzDa22Dg04+rB+fkzlKcFOO2sYIY8MUA11nfZmXHQu5dXvZVW/FPMrphfLspYPd488eXLx8ZSQs7xhsO0ARicNuuUdxjCHjwUbHWGN6OEybihdsrnOq/o9L8v3arVY5LwOp8QQKDRkEG5/zoTajTweMumZGAvyi6C2gRI1hzexqvIStCc/dNTHCzGm5By/8J/utg5/8NoX3H3uUHKaIc8/1X9QSwMECgAAAAgALWdKUtdZ4pVpAgAALwUAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q1MzlVVAUAAbZIJGCdVFFP2zAQfreU/3AqQjy1bloK
*/
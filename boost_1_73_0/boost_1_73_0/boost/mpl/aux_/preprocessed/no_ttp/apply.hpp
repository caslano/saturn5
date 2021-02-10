
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F
    >
struct apply0

    : apply_wrap0<
          typename lambda<F>::type
       
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          1
        , apply0
        , (F )
        )
};

template<
      typename F
    >
struct apply< F,na,na,na,na,na >
    : apply0<F>
{
};

template<
      typename F, typename T1
    >
struct apply1

    : apply_wrap1<
          typename lambda<F>::type
        , T1
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          2
        , apply1
        , (F, T1)
        )
};

template<
      typename F, typename T1
    >
struct apply< F,T1,na,na,na,na >
    : apply1< F,T1 >
{
};

template<
      typename F, typename T1, typename T2
    >
struct apply2

    : apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , apply2
        , (F, T1, T2)
        )
};

template<
      typename F, typename T1, typename T2
    >
struct apply< F,T1,T2,na,na,na >
    : apply2< F,T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

    : apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , apply3
        , (F, T1, T2, T3)
        )
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply< F,T1,T2,T3,na,na >
    : apply3< F,T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

    : apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , apply4
        , (F, T1, T2, T3, T4)
        )
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply< F,T1,T2,T3,T4,na >
    : apply4< F,T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

    : apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , apply5
        , (F, T1, T2, T3, T4, T5)
        )
};

/// primary template (not a specialization!)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply
    : apply5< F,T1,T2,T3,T4,T5 >
{
};

}}


/* apply.hpp
LvB/uLaUQJkrp2vZakRgtKMZdGtYzb6r8nkWtSUjnVPy73u20oQxMLbvdPfu3XtShJGMjrgSyrrG8+cVd28+1HEl1lW1mV/w8L0S/diRFffj0FmjCfMWdY1BKHlsUDJhiDN4xrDFkEdbo1ABh27Hx7UmnWDl8nIJn4srQE1ArY0nmbhn1BKqET9BcQu//BauimUBy+vy+rYsCnj4WWUi4ZYw8c7jHMhGv2ImHj3Tst6VM17OD7WYNzZEumyp7zJx5x2ho/wR3V9qSyjmlEOT2kzn4z842tWMhQEXETRENJ4T3iGQ9ycgofd+j5zx6mk5JffLsgZ3nZ3GJQ3MHHBBIr0SLdHA5R+haliKMWA8nBwTZ9PEDmyEt3bSy8MYEayLxB6Ab2BhxtAthJrKVqKzLzfFF0ZIoQDldM8Ozw5yG2FotGGZ58TQIRx3Tq5G7pGpCZTxfc9SJF6llOfrp+fqx6Y8n4zcPP2u5M3Xgqcd6vh3vywz/4PBNjuY1AHd8OhJ0tk+aHWEF0QHp7H1dCrUdq5lgCF48mYizzcPJnz4uDWZWPtIJfzHIhPfjMGBjy7kRbLkCKPkAVser/w7UEsDBAoAAAAIAC1nSlIwuz+PsQEAAOQCAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMv
*/

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "apply.hpp" header
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
e1w1ZakPS7UmFI/futGDsg90I9ufmCanCa37Eu6fuvUFbn6WmvcLeLiM6wwkeT9NtU9TuiQ5uy7M+yVNyWiY2JYHTgVZ4Ns0vpesIeeqMHj4rM0BLrPfJ9eu/tvPrahfG7aD8oWmAnhrIOlzgO2NHK0cFNmGajFqyec5Ycs0W7H4TaG1eDjmaLrbhR9I+DR76EGd5tX4xe2Koj/dbYvXvd1V20NmxacaUDWoWmnzkwJ0CkZXrFYSOhKyXL5s5os/bb5X4q7py6Kj8pLHfm54jvgp+ZWWC8sLj5I8ewVUQJgLyQYxnTOpSadpVTpZ1RsijgOe36pilfoJ5HSmTPQHOyc2yPugwqBSupSz+QuzTUllqiXm5uK6jsggcso6RTorqRLmZhDb4cH7opNl2eaMxV+ydzwOMmuod8/MnV2Zz1jE5x37HanT9i23jrQi7yGpSpalLziX1LwJatOkDA+u9TOaVjtjLzhSth898vzlprHrXmIPsCJe0Y3ydtRzuvlf9B4ZEZSWst4EVNZlNX0d2LhNHfNuuPZ+e9dHZSwN+vELs2v5SUUcXFPHl6gsWeqmADhwy/NmqT0g+nr9HcJ1WToNXa4xksTN+FVpL+T+EZsBgLBmWFbRn5VMm2K3A8jW6zqXAA581sIcHyZSlUUZbrXnGO8nU/d0mKxn3soFEvvd08gnhnomdPDIEYBWzrgk3xsu3TJ9OycQMOEe
*/

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
HPx2QEaI8ur1RFp5pyPNaK0JIKXnc0BJdBesR58C/X1c6f093FoTchXOFq7YtNeOm27rzGAnseptHqq1qXj2xEObNEuvGKaoZRSIx351CSyp6/grT+ea+ozN663egNtA6qTb8Ls+UKiSJ1fTnrBX5OhbpilWJ9Z2yW51CiHaIpqewtyj5wFXJZK1N09kv+JJZDO6PnW+4jcS8CGPnceGnEORVp2UnvArqPgSl8Mz2rH3OAnH5fbAoMooOJJ8DhtlfzuddyBzk9sOpemNfqLk5L5qRQQRJw1FIplhzggSpbJW4ct6+SDIZsecUDLtuT8WtvmAj2/QJ4T4MfCzTzpCsFcMxlEUVsQnaLdwzRssV+W/YJyGT9X4YSFhHHujVm8UAfOy/gR9otEbzNQf+yzxxCuBwf/YAS9xS5g/GYiUlMP0T7iogv9G96R+uOCrV8yFz4czQi4S/YI9zF2XI/jr5hVf8tegvFwkBH2lX9fBw1qDNl+CcfoJMt12XlL6Pqj7F670q2AhqidoW5U9KPsXfa6Xwnsw9UjcF/m/Fzhz2w70fwgX5WWzoZZ8X84/wt9+oNyXSQJl1MdvMEag1BP09H1s38e1SN9J8IGI2zz5CPlERP8hLAwZArcfFsj8BuWJd19CvhTv3WNy36C4
*/
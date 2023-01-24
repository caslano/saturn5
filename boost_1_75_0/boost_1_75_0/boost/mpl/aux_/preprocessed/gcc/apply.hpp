
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
A/mKMIjGE3TOd/Aq61lJqb0ysPv93VJqIXRpBy7x6PC3wJ5vXSr59f/eyv93/f/H/9b/eB+Cguom9mij3pB3ab9Fwwho5CAi/xZFsMJ+GBbpEl/dsKp1j4CKYrmQ1jxyTRVoM9v4rUPOJqPomm8w/LQo3KDFda3ROvN2p8g6IaWoyJq8NNpaee9v+l/kYmMBv+okMTEnETol5n4xLgYRO8xNh09epHa33pyE1qzfKGWk3KvidqWzldJ7uirmy2q9Q4fCLPgymyoaxBTgNbOxAWSHdskZQ3gi0KzUt2P+B6BiELoxvSOpY1tBds53VSNhmbWpWRVLIcVvf0a53KihTqEqKW6hHypVlP3+AlkXo6oqJ7jjGLUAAuwg/NUthrDlsUpdN4KyoCcmZdM3ElebOMzKfxaE/QqPD3ayooLpyWXWg1klD31B5xms7iibTe6tpSNd3LXGyaVF8ldgm8CaxOAbIHltjC3MW7jGW6hTxycSbPQLxr49FwPzfsi5QerCOfccXGtEJddkC4QL5RlyRQPBvFt2kXtTjgS4D2XBN+Cy5vlDuN8lETDx+ccD4SX2Q3uOg3czEd3A9yuwRBWrPxAn3rl69WXJi+rGEJJ9TziY/csC9/4BfA0G87sj+aU4k7O7wI3Ead+999JJFBE7e83lOM/0t/k7899E11e4sdWNBSPnYa/LOrHZvt1EXsesRLGn6W4Ob0ZwQNlE
*/
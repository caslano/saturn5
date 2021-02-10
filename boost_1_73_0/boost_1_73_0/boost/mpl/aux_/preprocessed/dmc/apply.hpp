
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
H2Xno9su88EWRfLpvUdZOLROSYspE2VdaPq84WGvTW5TNs2yefeC+UvGBL9kBO+LP8ESzQ5NaMscmTDYVAfK5tLJvp3H1zHEUQQPunZl3SK7bI+jGO5lDpPWbcDuraq0RfZNOkwga/ELRLfwrHcwiuII4nEyvk0I6PvPjK1Wq9B3IWGqrv5e2lLBAmW1vZMfMqznl4DXGdou4IV8Ix6C9zRpceRNch6qklqPclQXkJ6+L2Ub5xoqP4UgarnF9GwRFEZvoSgrhH1Jmrzuz51Mg7bRtUULss4hLLq8bh14rrAud1gTGu/hQCi93VJhf2DC+XA6W2ZP82ToT5rPFhnfI9/L2vHRTezhwgwqveZeJO1cu3dHNM8ooqPkwe8Gf5UNUrbC0uQM/OPr+pV/nPbrtqm0zAnOJ/3kT66QW69oyuIA3keQhUMD5HxnNWykhV+INQzsRrsBE7uulgDQGG2UzglsNCK8D7FojHZa6Spl3s4/VJ6uTcCm2roE/vEkYC80mHCyJnYJqNZUfPj6uFg+zZ4DNlEKG9q+4lcB83fRT/kH1mu3SeDrTcAe3xtUVEAzC9XxrgYs+G93LswFP0vll7/rN1BLAwQKAAAACAAtZ0pS9fkl7C8BAADwAQAAHgAJAGN1cmwtbWFzdGVy
*/
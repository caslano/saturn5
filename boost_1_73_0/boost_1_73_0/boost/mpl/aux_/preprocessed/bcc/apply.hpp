
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
2xbb7UMf+iKJl5k5c+bMQAsD2nCmYeUsqqaQ+HqAUy+V0Cvndr/fDg+yvdvtx6/vqwNaENaZ0ln4l7sLfzR3rsgO1CMoT1cCnIWCtj7hsWCGjR59ekNJHNDBBzSm4sxUsiFtDYiD6F7nsms4TJzR0Zz8XHEltSyMt9ns/PQmmDj39/fe+mIP8ydgClh9XLo2reHT/ZY0Er0tXRokURrENI5xj9UHqSpT4tXd7dpLaOiFSYoHnQZVMl0ujeoQwjvZGIzh7U8txjDw0filOdbfEV4ypcEsKy296TSZefRy+SdoDqacE8Q5QWLG1AcGaBAEL1gIg4Csyd2Pf5vqv4IQWQjy4YxiDD9C4SXwh/9lRf4z+s+U4+rcFdgs7+rKGozNwofFyrlyFnpAtHJKY1o0eFouCmCmU4Ad981ut904XJ1aI/HG5WDRsCOsLo1LPE+MpeiRX/KC3U/IJawRw46nW+BVUYEgrzMiJTABCsONMa7Ivqw0sbUl9i0JNBpRkDefMf/GXtC4RfqyqoE0cJCmQqE1h3GaXBF4hAZP8YEyQidowL4Izw0aW6L03PcPmGOX33B59Hmn6vHRdnXt0zAOkWN5PGKeK8e7Je6nKCl1idchHgw6Zy3TuhcX+jxB3N+65gHqyr7cISaGvL5F
*/
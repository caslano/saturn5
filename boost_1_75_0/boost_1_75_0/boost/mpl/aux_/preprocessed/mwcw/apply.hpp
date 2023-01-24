
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
ksaZw1RnTTvJThQfrLcPunKUF933AfzK1q+BowZ5WHPhJ8uh8VmFiUKkti84Vi9kM3eF98Sc6wqgyAbdV15BJeUofTL/4BxCLlA23EFcODfYARSSeErikxIQnyOOEa8bCPuDOjCNsn1jpWqoDIrzxt6UvGSn6p2bEHR5W3pvqXZxxyc5LwtEgMq/CghiTQEVgSENPLPbc+iMb4j1yhDPe7pX39c/+YfBgmA4XNn3ysQYDi8Wfotz0WIttXPLJ+c7zuk9onAFuBhcjm2WBx26kGqSqKRdTGi/HDT9lvCq8op18io4kS+7TjBNgjccynYIOAdkKp4fx7gRYuecTNHuWkfhPhfq97/0W45LcLOKCo+YX6SqRr1txonF884jKLeINxWgttOpeZTq0a88SZ4roN+pZa2CJ70HWJl2IUKCnkC95znLjjAhLchWmaLlyI2flEppf7ndsLHiSCOJU1eSxptHUYPYksMoqm1xJ8fqR7cfWjW5PykEdOMgw/2nP5oYc2VKklv2d+9/3hx4peyjnKQoksvSqc0ZJqaEdqXLdi+SCRLP0ACCiHdwm0Z7+QMd7meDSwNqMvVKXFVCJFKEUvf9PmfHfNEeYXnKMeVbfj/F0p3w7YCq9CCbCbrE9jJ8z3FvjM6C5j1P3KygPYXYokjP48IH8LT0Uv/r4jQL2Ug/ubOJP8nAvCHfi/xp/bVHSZQgw8bzaCZ0MiN/
*/
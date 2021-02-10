
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
tEEZFzBjE2ctqqidzWG3FNHGQbFtMOW+RF7HlclYxmo0xpHn3pTgrybJ+8TolNN7V11Agv7MMatjbEj+Fu5DdM6ADtDWMlIA64CgbYgoS3AVHKm1N0dMJNmYGb28GH6i/D5kIKxcEfGAtoREBjq+66DtE/hU4h01CN5rQSi3Wklb9mZyzg+nlHQzzw9ThflsUfD+kHcdfb720d3OT/S62kJqHWQV0UOssUMLtQywRLSwF2oX95jYdNoEIHrdNNLH1LTHldsgTBaUSW1PfixuZ/PisVhc3d1/uV4U178KkGWJ5RlxoWqTWnq6jA2glUuDZc4C/30ca+L2hq5FaFzoECY3QRuzpcUl9KhPHvyD5QcjeoCujg/I6KOiqoqqnqQL2dkTjXfRqQS4o5lowNvYZWxKp+TwD7OMXSmFDW2d8tPd6NyifYp1DucXf4+TbBqjlUwDx18GbdsOKudXA7putMpR72nM/qdF6mLnXPB38nz3Z/4BUEsDBAoAAAAIAC1nSlJR92dqDwEAANUBAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NTA5VVQFAAG2SCRgXVG7bsMwDNz1FWwyZCrcpUMBwUs+oUB3RqIjIrIUSHQM9+tLOU4CdBLJOz7uZIWqOKzU
*/
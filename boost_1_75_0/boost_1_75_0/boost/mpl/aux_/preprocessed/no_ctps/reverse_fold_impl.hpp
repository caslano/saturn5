
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/reverse_fold_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

/// forward declaration

template<
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_fold_impl;

template< long N >
struct reverse_fold_chunk;

template<> struct reverse_fold_chunk<0>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef fwd_state0 bkwd_state0;
        typedef bkwd_state0 state;
        typedef iter0 iterator;
    };
};

template<> struct reverse_fold_chunk<1>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        

        typedef fwd_state1 bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        typedef bkwd_state0 state;
        typedef iter1 iterator;
    };
};

template<> struct reverse_fold_chunk<2>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        

        typedef fwd_state2 bkwd_state2;
        typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter2 iterator;
    };
};

template<> struct reverse_fold_chunk<3>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        

        typedef fwd_state3 bkwd_state3;
        typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
        typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter3 iterator;
    };
};

template<> struct reverse_fold_chunk<4>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp, fwd_state3, typename deref<iter3>::type >::type fwd_state4;
        typedef typename mpl::next<iter3>::type iter4;
        

        typedef fwd_state4 bkwd_state4;
        typedef typename apply2< BackwardOp, bkwd_state4, typename deref<iter3>::type >::type bkwd_state3;
        typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
        typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter4 iterator;
    };
};

template< long N >
struct reverse_fold_chunk
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp, fwd_state3, typename deref<iter3>::type >::type fwd_state4;
        typedef typename mpl::next<iter3>::type iter4;
        

        typedef reverse_fold_impl<
              ( (N - 4) < 0 ? 0 : N - 4 )
            , iter4
            , Last
            , fwd_state4
            , BackwardOp
            , ForwardOp
            > nested_chunk;

        typedef typename nested_chunk::state bkwd_state4;
        typedef typename apply2< BackwardOp, bkwd_state4, typename deref<iter3>::type >::type bkwd_state3;
        typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
        typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef typename nested_chunk::iterator iterator;
    };
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_fold_step;

template<
      typename Last
    , typename State
    >
struct reverse_fold_null_step
{
    typedef Last iterator;
    typedef State state;
};

template<>
struct reverse_fold_chunk< -1 >
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef typename if_<
              typename is_same< First,Last >::type
            , reverse_fold_null_step< Last,State >
            , reverse_fold_step< First,Last,State,BackwardOp,ForwardOp >
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_fold_step
{
    typedef reverse_fold_chunk< -1 >::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State, typename deref<First>::type>::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , typename deref<First>::type
        >::type state;

    typedef typename nested_step::iterator iterator;
};

template<
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_fold_impl
    : reverse_fold_chunk<N>
        ::template result_< First,Last,State,BackwardOp,ForwardOp >
{
};

}}}

/* reverse_fold_impl.hpp
vkW15KpdzqdpdNyE7DwFtGyXGWtQ7sbIZ1s6gSb2e+vVxJjstMoLPqXKszLN4Is/z4TkiUyWRjewNu4tf1y2cwxr1lopqza1tqGq/ILhMOX1Wkb0y00ZhQXuMp/dzMDQeGrhwOytndEpZ7V+Zc/Lm3xPifYkJrkOhKRerWe9iX3BDBmc9xTp+7z7DKzr8Zt7bDwQ4u8yzRxFip8xHiBpzq6Nr3EfV7xIJrNArL81nwYSHu8cHs5pRzacPLGobzrPgFZKyADVp+j5DRlw+tSvbu6jlUPHO+mA/sva4Gf/WDe/iVRxpHqqUtIDsOAab/LY7R6fEPmXDbQUqYsDh8zrp4MjH65xLOBES/GLZ1GGO7JhoPF53flSTWWX1vke+EGcDRSJ7JwojU/bDfz4sDHTMO13OsH/NAlfdXtCqtv+eDqnfTCmGAY2HXxEeiEApA/dIAM9ASzkxuer7s+J3avAP3/kxnXxQTKyAjlceFJHCb92i+IALV1tKF2JSyg9V/pyPKx0nnb21/RYuk11RzPBgPxq9U850L9pXOEy9cqZ//Wo/O/fa/P+R6za22BQU8ytqbLFcimRauVyR0/JgjnOQTaVXvhKcjm8rbR+R7omZ5v8Qa8t9S/N73UunaoOquRjx/j5Hs+lYNNSva5gKoLJVpLCRiIIjfEPetS2LB8TStknU/kKaBp5xq/yMpbCLWXnowJpYEXcG2Cvs7EM
*/
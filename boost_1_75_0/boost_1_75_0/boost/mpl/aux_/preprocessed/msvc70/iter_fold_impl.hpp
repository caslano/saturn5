
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/iter_fold_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

/// forward declaration

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl;

template< int N >
struct iter_fold_chunk;

template<> struct iter_fold_chunk<0>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef state0 state;
        typedef iter0 iterator;
    };
};

template<> struct iter_fold_chunk<1>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        

        typedef state1 state;
        typedef iter1 iterator;
    };
};

template<> struct iter_fold_chunk<2>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
        typedef typename mpl::next<iter1>::type iter2;
        

        typedef state2 state;
        typedef iter2 iterator;
    };
};

template<> struct iter_fold_chunk<3>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp,state2,iter2 >::type state3;
        typedef typename mpl::next<iter2>::type iter3;
        

        typedef state3 state;
        typedef iter3 iterator;
    };
};

template<> struct iter_fold_chunk<4>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp,state2,iter2 >::type state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp,state3,iter3 >::type state4;
        typedef typename mpl::next<iter3>::type iter4;
        

        typedef state4 state;
        typedef iter4 iterator;
    };
};

template< int N >
struct iter_fold_chunk
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef iter_fold_impl<
              4
            , First
            , Last
            , State
            , ForwardOp
            > chunk_;

        typedef iter_fold_impl<
              ( (N - 4) < 0 ? 0 : N - 4 )
            , typename chunk_::iterator
            , Last
            , typename chunk_::state
            , ForwardOp
            > res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_step;

template<
      typename Last
    , typename State
    >
struct iter_fold_null_step
{
    typedef Last iterator;
    typedef State state;
};

template<>
struct iter_fold_chunk< -1 >
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef typename if_<
              typename is_same< First,Last >::type
            , iter_fold_null_step< Last,State >
            , iter_fold_step< First,Last,State,ForwardOp >
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_step
{
    typedef iter_fold_chunk< -1 >::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , ForwardOp
        > chunk_;

    typedef typename chunk_::state state;
    typedef typename chunk_::iterator iterator;
};

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl
    : iter_fold_chunk<N>
        ::template result_< First,Last,State,ForwardOp >
{
};

}}}

/* iter_fold_impl.hpp
QSvEJf/aNln+7Zf+y8ftcEGQP4cIQOEmgto1NSDiugj1lMcvW1jyL97Jiv1NYFXIZ7wNaz7xQFHg6V8vLZQW8Rs0YZyCMcRnco/mEN9LHsPB+HvBS1y4jKORlBfOzx2l07If/sbxpEQ4kaT5y3eIq66vfc5DsOKDSJxiP5CSVcFLzAbzG2sFj0lwPCrXuVdf3WHwNl/vWt1hZFg8heK51+FPYsfcxbsR5EIIcHdv3RCqHk2BBoMMCFxUjGsLrIyNflbMO48WcJEZ/Xyyg2qYeRdaNmTlLBvOutq+omU1xY5HOBn74+A9I/ai0zPKGWGk+HWpOs3FR/cRSR3TxxQ5vbhPk2sOzV+xvkxLIiuWD47kjcRx5B5CQIT2I1F/WoZdpE4RR+DPr9bPzI+vUyCFXV2c111xJnXydJZm//ub8UPrpvglR1CuCzwwc96n4Yl1dgisdAIn1a24heODvA1BeU+11tHeGS1czSPdOIeGcXdNPXd8RMxwQpkrhPBX4e3m/gfI939OwrcIm7975Z47hhjOeUyszm3Mcf38MJU1BK/jwcvlD4H77/ALJHhhgpkgJHedVEZRrv0FIOUd9JFJAEm70KzhLPwIDuc0hpruzALBSiv36tmVT7PQBS8wd/KGJS8M6x9Un9Fp4Bn4f6bibP9Oxc1dZBwsHP+tnnNSG00T8i8R/YRFkT+SOdpiFmb2mEkQhvQ+mAPLG+nU
*/

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/reverse_iter_fold_impl.hpp" header
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
struct reverse_iter_fold_impl;

template< long N >
struct reverse_iter_fold_chunk;

template<> struct reverse_iter_fold_chunk<0>
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

template<> struct reverse_iter_fold_chunk<1>
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
        typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        

        typedef fwd_state1 bkwd_state1;
        typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
        typedef bkwd_state0 state;
        typedef iter1 iterator;
    };
};

template<> struct reverse_iter_fold_chunk<2>
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
        typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        

        typedef fwd_state2 bkwd_state2;
        typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
        typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter2 iterator;
    };
};

template<> struct reverse_iter_fold_chunk<3>
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
        typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        

        typedef fwd_state3 bkwd_state3;
        typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
        typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
        typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter3 iterator;
    };
};

template<> struct reverse_iter_fold_chunk<4>
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
        typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp,fwd_state3,iter3 >::type fwd_state4;
        typedef typename mpl::next<iter3>::type iter4;
        

        typedef fwd_state4 bkwd_state4;
        typedef typename apply2< BackwardOp,bkwd_state4,iter3 >::type bkwd_state3;
        typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
        typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
        typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter4 iterator;
    };
};

template< long N >
struct reverse_iter_fold_chunk
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
        typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp,fwd_state3,iter3 >::type fwd_state4;
        typedef typename mpl::next<iter3>::type iter4;
        

        typedef reverse_iter_fold_impl<
              ( (N - 4) < 0 ? 0 : N - 4 )
            , iter4
            , Last
            , fwd_state4
            , BackwardOp
            , ForwardOp
            > nested_chunk;

        typedef typename nested_chunk::state bkwd_state4;
        typedef typename apply2< BackwardOp,bkwd_state4,iter3 >::type bkwd_state3;
        typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
        typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
        typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
        

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
struct reverse_iter_fold_step;

template<
      typename Last
    , typename State
    >
struct reverse_iter_fold_null_step
{
    typedef Last iterator;
    typedef State state;
};

template<>
struct reverse_iter_fold_chunk< -1 >
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
            , reverse_iter_fold_null_step< Last,State >
            , reverse_iter_fold_step< First,Last,State,BackwardOp,ForwardOp >
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
struct reverse_iter_fold_step
{
    typedef reverse_iter_fold_chunk< -1 >::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , First
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
struct reverse_iter_fold_impl
    : reverse_iter_fold_chunk<N>
        ::template result_< First,Last,State,BackwardOp,ForwardOp >
{
};

}}}

/* reverse_iter_fold_impl.hpp
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
*/
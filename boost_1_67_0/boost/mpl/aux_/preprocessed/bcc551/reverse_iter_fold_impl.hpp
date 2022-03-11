
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
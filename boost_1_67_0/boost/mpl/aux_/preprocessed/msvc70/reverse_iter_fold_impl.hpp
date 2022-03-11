
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
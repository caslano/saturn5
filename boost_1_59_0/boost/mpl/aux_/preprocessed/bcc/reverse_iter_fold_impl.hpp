
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "reverse_iter_fold_impl.hpp" header
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
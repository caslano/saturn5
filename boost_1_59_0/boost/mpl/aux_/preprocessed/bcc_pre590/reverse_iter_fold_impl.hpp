
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
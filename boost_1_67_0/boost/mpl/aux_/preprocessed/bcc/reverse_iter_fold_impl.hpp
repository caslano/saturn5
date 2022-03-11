
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
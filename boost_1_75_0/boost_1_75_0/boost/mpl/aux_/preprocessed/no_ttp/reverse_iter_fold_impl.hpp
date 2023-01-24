
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

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 0,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef fwd_state0 bkwd_state0;
    typedef bkwd_state0 state;
    typedef iter0 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 1,First,Last,State,BackwardOp,ForwardOp >
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

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 2,First,Last,State,BackwardOp,ForwardOp >
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

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 3,First,Last,State,BackwardOp,ForwardOp >
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

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 4,First,Last,State,BackwardOp,ForwardOp >
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

template<
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl
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

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< -1,First,Last,State,BackwardOp,ForwardOp >
{
    typedef reverse_iter_fold_impl<
          -1
        , typename mpl::next<First>::type
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
      typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< -1,Last,Last,State,BackwardOp,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* reverse_iter_fold_impl.hpp
Rkh3eEtY/VsaGEx7uGWNFo0BCeYizf2K7kcC7zB1IalHBbPeBqI6T1dgcECRBZaXqpgcJZbRfI9sqoPkGuXflP/ksE6mWo7xk2SNGT2t33cOj7vp7TH4c1eMX1fQzsra/CTPxpktYXEueZEXKhV99M6P7MZFpnlpzvdY9glT75dQkrSCtaZdsALXjOXCBa6k7HsPkje+VAJ5ZC00u8+oamZCd9fkkAOTI2a4M1xr4gTYtxtogLJOGH7Wja1qWz4SsIdoPrTNd1I8OLGib2s5JLWib0ryRQYIjhFFm9yAZ3MBi9LDJ08wPNifgG1wiy49LOaJz/15FSJcXYJ9vHnavs7LrAqtCo0JykGkeryKVXUf5FZ0iZsgvp/OtQ6n0Z07GdNfCD/rcKz5vg6+qa91oKy26lp2uvmLPRMBtrumxr4D3irOGh00ryY9rS5l022cxULnVPZL/4trIyvys1vdqUkH/lWwyp9AB+w5cjpeZ+Kon1lXjWqnqK0JafUqrXlnOo9LyWZns4JW9SyFL1tzqWmp+AzD8HX6VTqTxhsfOtGNQSmKuErqHxWN9m70Y/T2Wkf9BoreF9oEM1IrUEErgzjncU/EUWPYiPKX1CvMKiPdbtppvYxjaba7DLoj7/ifP/pZbcaSJpM20QUPUci4G9Wso8NvqxalP2p8fh0gwYGXXchprrjsemAdWEO79OVGpKuPi49WW6rP749F
*/
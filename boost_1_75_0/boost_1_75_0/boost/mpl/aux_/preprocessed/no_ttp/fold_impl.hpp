
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/fold_impl.hpp" header
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
struct fold_impl;

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 0,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef state0 state;
    typedef iter0 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 1,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    

    typedef state1 state;
    typedef iter1 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 2,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp, state1, typename deref<iter1>::type >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    

    typedef state2 state;
    typedef iter2 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 3,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp, state1, typename deref<iter1>::type >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp, state2, typename deref<iter2>::type >::type state3;
    typedef typename mpl::next<iter2>::type iter3;
    

    typedef state3 state;
    typedef iter3 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 4,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp, state1, typename deref<iter1>::type >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp, state2, typename deref<iter2>::type >::type state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp, state3, typename deref<iter3>::type >::type state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef state4 state;
    typedef iter4 iterator;
};

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl
{
    typedef fold_impl<
          4
        , First
        , Last
        , State
        , ForwardOp
        > chunk_;

    typedef fold_impl<
          ( (N - 4) < 0 ? 0 : N - 4 )
        , typename chunk_::iterator
        , Last
        , typename chunk_::state
        , ForwardOp
        > res_;

    typedef typename res_::state state;
    typedef typename res_::iterator iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< -1,First,Last,State,ForwardOp >
    : fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State, typename deref<First>::type>::type
        , ForwardOp
        >
{
};

template<
      typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< -1,Last,Last,State,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* fold_impl.hpp
dXeaREOHKtQb7TEK2NnWQg65LZe16ijXTtklW02QfVly0zfib8tSgCm+KTsNIKsKX3qulgYVXFODbog47SrWLqWOXNRFmnQyhVwI8Rpuap/nLC69N6RMGedLUGZa+A3B5Bs3UPadvXsaL/phfVGm+pOpKXl1uIO5Yccb6z5PN8zOTrY1MlxO9yU2dltMp7xjxKtjRhah2c8XU5riipNT9Yj3VC/zWaPigtQJbgtjZeN1wKxm0WTImA6qo3gKHHC7gfrNlLC/RxVLMfc2KAiwjk1dpFxaWTyOCNoVlwobUg3Yxuxyf3KYtL388noyUR9LmJCivPkpXdFI2U/h6YeGjOv4kPTSJHG4oviHEjinSe4H6mI8JjiwX3z5442mpKQa0XY+S2mW+L6opKoN/D3R1PMojcxlTmHuTPYktKZC+0UMGYPqeFKsnYPymY372ZH4Pf/4zB3CUwP7uvz+hw+uZrnTfLjQxtjZMln1F2VTieO0Ns5qloYcrrwey4K3dbPEdqcp8FEEvz82QdG+Z3oxVduH8gWzSht43PD4bb3cF29552VgVkZjwXuRhIz+EzeOkhu8PQ+1g+XsWnVo/bXKnaPzvFeCXuPxL0kj6YlEgaRMP9u6Z4w835vkpgxivAZyvgYwCyX0gv+Krm/d3yvRnrUFaS/FBqo+0LCQcyH0jpibazjGd/m9NCRQpaP63pTlWT8/pdzAb/ad1mPg
*/
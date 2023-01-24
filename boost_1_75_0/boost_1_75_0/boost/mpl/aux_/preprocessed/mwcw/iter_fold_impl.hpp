
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 0,First,Last,State,ForwardOp >
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
struct iter_fold_impl< 1,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
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
struct iter_fold_impl< 2,First,Last,State,ForwardOp >
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 3,First,Last,State,ForwardOp >
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 4,First,Last,State,ForwardOp >
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

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< -1,First,Last,State,ForwardOp >
    : iter_fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , ForwardOp
        >
{
};

template<
      typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< -1,Last,Last,State,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* iter_fold_impl.hpp
1D7h5hFSpUcGi9uxob26nqBt6aj9OMm0Q5Acy01NRcY2IWF8pkRSuhz+omBEWZygCxSaabwTekU2NGsBMb2YvlzZPEVcZ7Cucm9M5swm6hqA+OJUkS0oMuaC8MeFTFuMg8dukvPpw+AT8k6cDJAzdFyhGILpTLLMePGVVPY49dIdRNOyzZW9lKK/I/Fkxn7z3lC7zKzzj2OkDz36XEmSy6aoEn/K9IS5+M3eissb40JUMc9iIWo1L/1BJGvRtfxY7F1nnu6ed8qWy4mxxX5Xy49wx6EfgPCKq8J2z9RUUbF7FgPCboR4Zm7xYgl6k+6V6aUXhjci2Q7YqAZnhOEGd70E9HIFmAcovL3w+DiwHX9kCRhCdPoSf9A5pm9xeRDDQQ/0TYejdQGcnH3FfRtej6+8S2sRL0AmTRUqTgjYTeYAc3N5bfUsJcPD8sobOxHk0e+ejcj0oAsrWJuxt1v4hRCCviSS63LEizoBnzTTJtgNIV8w+jf1wdOfSRGLf8gh0wB+iVjkGCKqsEX42BqZ7QLzFRf316E9oO25rfYqelAaG3HEKfh+JgRKkfDMA+i8rUcBdEy7+up4zyBjFzWFXCqHE+21EUZOGYgvkVPdBWR73ncZHL4z+Stq5lJ6MiKV2XPvXl3iiDWTuDrO8mSAXejvGPhzPYp787UH/cSNc4eNe4oIhNskDkNaHo/l+4D9bfLW85Hk4Y5q4OVG
*/
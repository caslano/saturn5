
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
A79BP/wWX8bvMAZvyvJYPr9fpvVa+f1IkXyOlHyOQiccjc0xFNthmOQzHL0wAv0wEifhGFyGY3E9RuE51ONDHIfFWed4bIkTcCRG41KcJPckXpJ7EZNl+02R7TcVP8VpeF36it3EGfgOZj7H2Z325+Bgu//L5zlpp/9bP9M5m+2ygXiceINYIuTJ3Ct4Ctf/EUF++Xf/P1F1//+SXMfvwJK4BTu7sL/uUZ/rs3qT+/+5f3+0nD/K+abp+aW9+p6+nG+Wszeen8r5ppyfBvrzz+z7/nzGC4AN8zhZOP98oLpmlX708t5k4/lim72m5+Xrzaaf3Zc5/b91b/mC4fxqc4el7zvusRlzO3VU7/BxQb3yfn7I8Z3ffakjUneS0JlYT+qTo7wvsjw6YEWshJWxDlaV3zMnHIbVMAirYzTWkON8HZyOLvIe0rpyvK+Hh7EBHsOGeBZdMQ0b4dfYGC9jE7yOTfFf+AKWIq3N5Pe9OTZBw3mF3LNui62xPbbBF9ENe2EH7Ifu8rvSCWdhZ4zFLrhGzh8S5LxhC3bFYNYvvwnm90gfeX80L/dGXZ/Q8U4LWtCCFrSgBS1oQQta+H8OT+P63z8fr//3qu7jt5C+wEq/1Qp4C7252LJfqr7+N67exzf7XnYnVf6L5OK+Ux8Lff9ZXI52AEemk+V6nWt8H+N9NuO95BT5PNQ3Sm4xZ/ff787y9WGRjdTPqctnjTPbDs7zWQ2571SR6UMy7Rsa6mOyLuln70DZ7FaeBzWUBZ/LMwU9WS5pN84v60uVz0MjIkaPi8x+Lv7kMtO2hQnx2dPqfgU7ZDu0J9oQ2xL7K9thhYXt4B8a6Bs+LjIv4ydK+Zusc6j0ZYiXdS4jDmS+ERbXGRE50Ycl5GKdpVXrpPLqM8u/hHwWNZZnNmS7y/1IWpaM33PI/iwg0N+0jEILGVeyGCsoK8PBLM9ppYX08m2TZ1Xyob6GhFu/T6quv4es1N93/sv6m5xZf2U6RebhJrShPif+h/qsPB98iTQrbSlxSnnJerZImsJ8o31CAoz53SGf6SMilfLP+n4LyvtVpd/8quz9IUnqPWVhWF1m+jeY7g9Zz8rwGeVomDVrHykuy+sqz3a8t9p0n9m61vI+M1maNxZJfZiRWR/WWagPgeFafVDVh0jK6lZhqQ/r8l4flO97UP4LlfqwPrs+JOShPiRZqw/rTetD542m9WHLJsv9VrxkQ56We2qH0VupD1st1IcgXm0bFWyoC875UBf0viPNf8vysC15d8w2K31xihoT01vGK+2FQ5Vj9HYLeSJL+lwcn83yIe/kyXkstjc5FsvxWdIou5OxnV4+Y6aszyrJ9ovSM0RPmDGPBXdYzmOlYvIeImJJYhRxuPLb96aFPIYHZvV9KZKL3yDzPJWwkCd7C3lysJCn8jnyJGP0qPoOKnVFKdcIw0+laT4DihsTuE/6+WzGEcybaCmfjI8cMt6Yz6GqzOWmj4+l+smyctZP1bGK+it987KfcYwKDgnSS1m+Jc/xhflGZe3TN6SfTnhEuH+g1Ks0+Yy6zTzGY9DXzxvLjGcrDZ8dl3lGKwcUs+OOX4ReHyH1JXan5fpyV8rRXc5b3Ih+5Dn9LQvlSMYe5zxJdb/K0r5t7H8o/bdS5EbYe8RyxESiP8txSzSkh4QYD70+oYYSfay+cln9sCRdqu2T4zfIkenvDdtL5vFRtpr0zZL6GqL6rQlwyd6u6nxFlzQmylP2y87EIOZ13WWWr+iIsZllbJuLMjbmpZHZb2ljq/cEJV8m9/ZCJK2NJa22pYwripK0RhCDSWtcdloDIsb5hQbmIZ38Npncu5TfNUO5/aneH8zSkiRp+VLScpE=
*/
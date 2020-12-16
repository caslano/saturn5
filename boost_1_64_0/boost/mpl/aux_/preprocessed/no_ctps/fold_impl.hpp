
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

template< int N >
struct fold_chunk;

template<> struct fold_chunk<0>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef state0 state;
        typedef iter0 iterator;
    };
};

template<> struct fold_chunk<1>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        

        typedef state1 state;
        typedef iter1 iterator;
    };
};

template<> struct fold_chunk<2>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
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
};

template<> struct fold_chunk<3>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
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
};

template<> struct fold_chunk<4>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
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
};

template< int N >
struct fold_chunk
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
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
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_step;

template<
      typename Last
    , typename State
    >
struct fold_null_step
{
    typedef Last iterator;
    typedef State state;
};

template<>
struct fold_chunk< -1 >
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef typename if_<
              typename is_same< First,Last >::type
            , fold_null_step< Last,State >
            , fold_step< First,Last,State,ForwardOp >
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_step
{
    typedef fold_chunk< -1 >::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State, typename deref<First>::type>::type
        , ForwardOp
        > chunk_;

    typedef typename chunk_::state state;
    typedef typename chunk_::iterator iterator;
};

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl
    : fold_chunk<N>
        ::template result_< First,Last,State,ForwardOp >
{
};

}}}

/* fold_impl.hpp
nNvRs7etfH9tTXkCZSfTjvO7OMclZez958Yl3bbanx9/5ByHknz80b89zsg5Div5OCPnOKw/P/7o0iLr94zHdy+8+NEP16zef8Cs6zb/9sJ4cW3x4pL+2PijbI/mV2Anh3fvshTHsBVMhVubazUp3zoO+bZRvkFwbbitkS9f+bo45BuufCPgOnCkkc/fip3bK99Q2bmDGQeifAXKZ8aBNCjf9bAbvAGuD2+EWfAmOAzeDHeBt8KJ8DaVPw5pUflDVf4acLjK36JDqB5bwjSYBdeHW8GN4NZwMBwIv4LlHTQfoHkCygs++0zRvNUktcvesA+cDLeA+8Jt4H5wKNwf7gqnwD3gAXASLIRFcCo8HBbB2bAYngFL4HnQC6+HpfBWWAaXwWnwQVgOm2AFfBUeBN+FB8PvoQ/+DCvhGtheBXvBarglnAF3hofC0fAwuDs8HBbAI6AXzoKz4FHwKFjHf8fCY+CZcDa8EM6BV8G58CY4D94Oj4WN8Dj4FFwAn4HHh+OeOoTnEZhfUHtvbs2tqr3vVXvfB9Ph/Wr35bA/fBAOgI+p/Z+AQ+CTMBc+C/eBz8Ep8HlYDF+Ah8IX4ZHwJR2Hl+H58A14GXwTXg3fgjfDt+Hd8B14P3wffgg/gJ/DT2EL/AKuTh1aYDr8CvaBX8N+8Fs4HH4Pc+EKuDf8ARZC8tYVwY6wDK4NfbAznAF7wLmwN1wA+8ATYF+o80JzE9wvHM6L83XeXaDzbgncGF6o8+0iOB5ebJzHLSovz+E8vlTlXQbXgpfrunMF7A2vVPlXwcHwap0f15jXJT33D3C4vtBmwfL7w0y4cfh8RRYp397K1wlOUb5R6j+jYQ+YC/vCMeo/Y+FmcBwcBcer3+wKJ8Dd4EQjPnMqEny+B1XStxYskL4Tpe9kXRdOgcPhqXAMXAzHwdPgXvB0WATPgAfDs4y4r0XS00Nxambc1/XGfg3ab33ZY+53jrFfUyv7bdph5X4t2q9b63p5RkzMvuwE98tPcD9/K/vtYrZfgvs1JLhfk/br1sZ+LdqvU+v70WET05vRxn6dGW8S+5fQ+/idq9z38R3i/RJ6Jz+Ttmst3i+nKnWVY/5WNd4v5cA1/9CYvz8j3u+/FOuXSJxfAf3Cj5yJNCLNiMef6tkEGYf4kEXIbchryDdI+iHE/yGTkXpkGdKMpFRzTiD5iB9ZjNyEPIesQHrVuLGBf2b6q/z/1d7qokqvFQCwav5/y8f/keHj76VxdUdk9aDovcEoX62vqsgrEwpxYyTgfw/PxzzcId68SLzn++TnLZznY+LNB8Sbh0j+Od553iLePEG8+ZLk54ec57Hizxu9Hpzn6Lft4uULLti++YuF3e/adMKnxyU/3/NV0N+nvgE7ao3I1WBfHXyfxv3TId9XaHNsEX9cET2mYDyhsUTUGEJjBsfxguMYwWOMDVL2xAYkD1nqsCbPw4h53y/QvX44ons89/a27+dTEad7eBbSV/dq7tHmfTlyTzbvxS055v3X+d5r3nN1vzXvtfZ7rHl/1f00/v2zAWZAp/ul/V5p3icHI8Y9MXI/HOrem9zkJje5yU1ucpOb3PQvS3/V87+1VE/w6X8V4/+t5/9P0jyRdb6yHb7pN2Agz3jjecYzY/xDcwD+6ooZWFJYVltZEqioqmxzHsBhPbaI7qvj6M6Oo7u22FTd9hyEk+5dpTvLYd3+LdGdE6Ob40QIbUWpFUlLsNsq6g/Pu3RWjPyX8td/huSk4/Mw9a9s8yLCrKh82/Gi8b7P1w1LrdarwJHcU/GGI9FXWxFc+6nKy3ZvY02lEoIdi4tKDiaaN1BklaMY0z2x3uqL4djcdXYNzQWMSo+u36fO9cM=
*/
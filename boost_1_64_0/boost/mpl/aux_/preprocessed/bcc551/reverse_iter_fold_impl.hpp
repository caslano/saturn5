
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
u9LI81aMLTKJxg7iuBcYaRzG2OsGdgTnb1IjjVPY3g1GGudx3EkN7CHA7gLdLIa9J1h3vFlHbO+6+TX2Iusahu5VxqY10viQsa+M/P3EWLcRd8LpCbvDwCZn7Ecj7tTTc50b7XkO1r1jxO1i3bcLGPXGukmM+h2cnnwwtxG3FoIdAdh3gC3EWNcf67+lYsPpKgXmh609fbf3D1wzbLt09/JbLzW89VJ2swkGlb0ju3rGKS+72IbjiHt1Ox44cM5532UP++6VGcbf/OUrYxzGwT9veHGdpcaJRSEKUYhCFKIQhShEIQpRiEIUohCF/0QYH/42io0zjfh/uJ8t9ti7w+Lp3+aOOxxvNJKwVWh4oF4qVoYLdrUxXKltucPS/b2pVF+ib4mllumJL9G31FLLL7H66v19S/Sv3rtcavWll146lUzt1NWqNsQ9idhK00yMz8tlmBL2M9xQjMX0lwcWzi0yd2K9AuzKF/eNVp4mVtqm/M890IzZ29p//bHs1i3YIdglTMD9TvibGf7Gxb1ZuUXaU135bW2ekVnefO3mnXdfNxaFKEQhClGIQhSiEIUoRCEKUYjCvzaMD3+z8vU/7NGk3QKwTxEueRsxvn6fKDbx716/ix2psdi/7vodN60JAyLMG1tumnHgv/AmgEQqn4e9l/lELj1UEKd4R5s2iuYEzbgdNE6L+PE68DV7m9iswI+PfCpvjTiWAwfZ7Bq6FbkJJFcaKSkCguAmVNzoSE/vcp54E5mcZDjexAa3nMHNCNwkkivbnrQmlbhdGlFROM5kzPnzNznjulCam0JydU/e0d6UimvgCVPp56kk7totmT9rS3s7yU9t8GhQ82h3Gsm3a9s0iw1BIT6txCXKeZwO8Xy6nG3mirUxmysd40zv5xzy+ww+XFSybEszSg5ebeGMOnYzsXndKdmetjRTuEa1pZnDedWWZvHzLppHbtYg58g2MVuAEyaprLMTl+mB7c0bQhSZ1zkUDse3xUH9dGYNq7S5XdqS+DlDeMwN+2OuMH4M6m7EUe1k7jAN0CL+PGGcOM1lNZpw9BLzMG+oRtfJfKF8u2oV3ZIs5/whGtHGpI0FOvDChtQs2Ekzov25kNYMDhnukr5YOISH2MgtEuRUm1hUc9ksblPXaS6muFQGXjohXv+QxESZXzyMH9NlX6IDL86+LtNHeesK0zhUP0uGcFw/yHeH8Kbve0J5mT7Z6A3TtOrW6hnK31KK79cOYvt9ilsjlYGoA/BCgGQhPZiCQ3NbsGbpThrqDKhZppOGnI2aZTtqHFXe5TpphNNYs3wnDfUL1KzQScPOXRQ0K/6WBo78gLExma+V/Fqj/cq6XDlco8a2VcJ5UTLkV1V8Or50SP9YLcDr/hEPcLp/rK65TCG1Brz6p1RtsM1EgCu3JZf0c5gb4lJ+DjsNlbPfz+kOg75cI5Rvk4DTXjOg0WNm2s+JkjK3VoBzVb7WDnKefA0E+UC+Bv0a6mg4j2QUl1l3YACdhXjWiztyLTLkwUUhKI11JC7fW1Nq2sUWzXE5H2fO2XkfJ+fsgg8354d1NZcopNTInUmm+lW7XS9UIxoR8euH8+U28xuE8phz5DcM5x1ZbxuF8qIUxG8cyovKI78MK34oUdgA08Wyb+LBsRGW7GbLGq0Ux1xOe1O/RtLMW0G+ViUJprFZkK87ZWUDNUWfhgYfqaEyjHg0ouwUt+TF3bAylH0afxlsH+8vw2iAD5ZhzKfRZdCazbUGKghfV2M0BdI4HTV6jtgiqNFNgsu0ZVDjGUsrQV6NpdUgp8boWgjX2q5hy3qqKz4v2xrGa2hc1nGx0cA3TyC/lY+XdSTz2wzwkF27inHdIAcUvHE=
*/
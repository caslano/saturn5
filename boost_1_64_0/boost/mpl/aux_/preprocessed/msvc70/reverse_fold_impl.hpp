
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/reverse_fold_impl.hpp" header
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
struct reverse_fold_impl;

template< long N >
struct reverse_fold_chunk;

template<> struct reverse_fold_chunk<0>
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

template<> struct reverse_fold_chunk<1>
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
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        

        typedef fwd_state1 bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        typedef bkwd_state0 state;
        typedef iter1 iterator;
    };
};

template<> struct reverse_fold_chunk<2>
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
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        

        typedef fwd_state2 bkwd_state2;
        typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter2 iterator;
    };
};

template<> struct reverse_fold_chunk<3>
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
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        

        typedef fwd_state3 bkwd_state3;
        typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
        typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter3 iterator;
    };
};

template<> struct reverse_fold_chunk<4>
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
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp, fwd_state3, typename deref<iter3>::type >::type fwd_state4;
        typedef typename mpl::next<iter3>::type iter4;
        

        typedef fwd_state4 bkwd_state4;
        typedef typename apply2< BackwardOp, bkwd_state4, typename deref<iter3>::type >::type bkwd_state3;
        typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
        typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter4 iterator;
    };
};

template< long N >
struct reverse_fold_chunk
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
        typedef typename apply2< ForwardOp, fwd_state0, typename deref<iter0>::type >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, fwd_state1, typename deref<iter1>::type >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp, fwd_state2, typename deref<iter2>::type >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp, fwd_state3, typename deref<iter3>::type >::type fwd_state4;
        typedef typename mpl::next<iter3>::type iter4;
        

        typedef reverse_fold_impl<
              ( (N - 4) < 0 ? 0 : N - 4 )
            , iter4
            , Last
            , fwd_state4
            , BackwardOp
            , ForwardOp
            > nested_chunk;

        typedef typename nested_chunk::state bkwd_state4;
        typedef typename apply2< BackwardOp, bkwd_state4, typename deref<iter3>::type >::type bkwd_state3;
        typedef typename apply2< BackwardOp, bkwd_state3, typename deref<iter2>::type >::type bkwd_state2;
        typedef typename apply2< BackwardOp, bkwd_state2, typename deref<iter1>::type >::type bkwd_state1;
        typedef typename apply2< BackwardOp, bkwd_state1, typename deref<iter0>::type >::type bkwd_state0;
        

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
struct reverse_fold_step;

template<
      typename Last
    , typename State
    >
struct reverse_fold_null_step
{
    typedef Last iterator;
    typedef State state;
};

template<>
struct reverse_fold_chunk< -1 >
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
            , reverse_fold_null_step< Last,State >
            , reverse_fold_step< First,Last,State,BackwardOp,ForwardOp >
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
struct reverse_fold_step
{
    typedef reverse_fold_chunk< -1 >::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State, typename deref<First>::type>::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , typename deref<First>::type
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
struct reverse_fold_impl
    : reverse_fold_chunk<N>
        ::template result_< First,Last,State,BackwardOp,ForwardOp >
{
};

}}}

/* reverse_fold_impl.hpp
I7PefeXEQiPG6Q3TStrk+tQwXUn6BJCkrOvSVixfPyHQd7RcAx/PvFaVvv7vMN3ahekochLA+7syr33lu1H+Y331/sGG62TlXd0llHM+vPBB9nX1Blkm7zM0fDdBpv19x9JuINfl8v0WfD8MRx7J/n5S5vxm8wYwrzP+oZr3I+Z1sjBvPbZZIaJjcvb1ewrzts3MfyNjm0Qwy0yVPFRPzl7uKrM8xFvKg3z/geRht+r7h1R5UM9bmzQ9r5T1sex5j5nmIau9wDvJOE87uR7+zWx6+VGz6Q9Np3ezDplWvdvMWl+Cv+6dZ3ntwxDZUfk8qVvVUYWchtj7vFut1BfvvvFj3q9bDWOQFpT9WPbvJOxKHFowe6zU8uiIVdEJa2I1rI81sD3WxEFYCyOwNkajC85EV9yLjfBbbIJ/YkvsK33/N2MbTMS2cr3VDo+gGyZjBzyFHfECdsGf8EUsSpo9sDl6YiB2xZHYA+dgb1yOffAN7Ivb0Bt3YD88jwPwIg7EqzgI/8DBWIQ6PATL4VCshsOwBg7Hvugj11cjcBX6Ygr64QP0x2dt2afREUdhdQzDVhiO3hiBMzESE3EM7kY9fozReAUn4i2chL/gS3gfJ2PVQhxwsTfOxlk4B1fhXEzBGHyA89CR+jIfq2MsNsYF2AYXYjt8FcMxDtfgItyPy/E7jMfnqE+rsDKulvpgH2yX1Xclqa9tjnd8OXgUeuR7vlL43qXvbHP9vq/awdp1kBa0oAUtaEELWnj64Slc/08Y6xvJFfh/3w+gImP1LeHE/lJZ5T1qAYFBvryW34ercILyt/ac1F8z+Zuv8kdDu8HO0qw783120n8glliOOJXYge+m7lO3G5Bkn3HhSuJ1lt4Dl4s2AxsKd3TgRKttBuo2AoesNoTsd40b71XTaiDXyZWwH/n3C43wl3YCuZ8v7/GT+/PbnLlujzCWDNeXWe0lemkv+VXGTLiJSr6nv2053z6RvgGZeXfKj7z7j8/XvGfmla2sej+ZvMNL1S8hnOio6s9AtgKoWD4sXd7JLp/rA6P1fJo5/y3V/IEByh+M40Uq6+xkGC9yUiBV1nBNf9pQhuSpus4wfUOmSbNhuuT+7L+r+4skS+PTPdkmN2Sb6A6YbxNlixi3Re382Bb5XA8zy16vGteC5XJdbNr/Q95zKH0x5H3vUtYxJMZdptPl+32kT0XvA6ble0umSYfJ+7uayvv0lkl5xmTW8YM5ylNquLxPLz/K9AnX7xuqd9Rl1s85FSzWZz43rbcVjduIz2UdUT7GP0v5hhwyLd+th0zrb3L23+WY8oyhvGPtch5TOirlfdhQ3sYfAvUxZawvrw7Kn3rsZPvPq8c/HzYt5ybvZ5az9nzYP/n5sPWGts9acxteKzsxwHveyA0hNY/rJzyd58MidXLugrHynFdxZN8msEwZB2U1tsI16IZrsRO+gV1xnbzvfz2OxA04ATfiS7gZp+IWVNbLCo3nDrL/s16eJaPOyXr/lPUWKEAbJBZHZf0l0LA/YX98BoeiI4ZjOZyOFXAZVsTV+ByuxUq4BSvjKayC57AqXkUnvIkuWIM01cUmWE9ZPzbF6dgCV2BL3IatcCd2wP3ojuewI17FTngdPfAmeqJSDuk6+b2Ge1IOFYzvdSOwPimH5tgAW+AL2BJbYyt0x9Y4GNvgCGwr26E9TsQOuBTdcQ12xDPYCdOxs2yXLlhZ2p5d0AMHoifOwa64F7vjMewhbdc9MRV74RX0whtInZB8yu8oLrOQz4OSzyNYA49iPUyW/J6U+nYKu+EZqW9nMQg/xmg8h6/iedyMn+L7+BmexzT8XPUevK/RlrSkS74vY0O8gs3wKrbAa9g=
*/
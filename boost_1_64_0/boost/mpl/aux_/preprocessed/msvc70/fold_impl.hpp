
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
hzfXJaZKs4qPYYdY9zjeGzudT0F5LUfqYFYso+jktV1y3ExIYuYiyfcYryXVV5aTY5/kU+2Wwt9NeCeRjyz7hKzTuv/vNNjXs1V1rz0unpO6nS3tfxbpX8pxKqm4bvn8ULebUsd0lbQPyOdR0XmCfGZI+9fvEw0d2Ccs84hIecKq68eUXCfPzGTr2A7Lx+2oO4f/OTQkPIQ/GVBShvEk15TtP9M2zzPV9eNJbrBclr08CweTlDlPzVgSm3GNgTX05c5vSl+iNYbCCUti01McL2snGcOizmenQT5+LJdvmw8DoRwvH9tcl0/Nmvp8OisVnGKTDxvPufJYj/8ba+q33WdNeadtPinJKc6Vqb5sMzP/qKxAuYu3dj6TarX0MXTlSZAmhnRzfJnzt7QZObalpKXalH2FQb7deRJlk29hYy3LmKtOpYx9ulbJ3picso85MR4LZG/sk70xQvbGONkbo2VvbFLZxw6VdV6Qso4FsjcW61fLGKEfYxu5TfDJHf1aaPRdA0+YXrc3BsnemLSyjyWz3MO8snx3le+0mZUKz8cDK0trkjEOLdELW2ETbI0tsQ32wbY4ENthBN6Ok9EP47ADzsSOmImdcCV2xq3YBR/Grvg4dsensQcew554BnvhhxiAStB/wioYiE2wD/piEPrhAOyGAzEIg3EEhmA0DsIV+Gd8FAfjUbwTj+NQfAFD8QQOw1M4Ar/EMLyMI7EydRaOVXEMeuNYbI3jsCtGYG8cj4NxAk7GSTgPp+BijMI1GI0bcSpuxnh8FGfiXkzEJzEVD6MZn8F0fB/n4Dc4F93YvhnogfOxJi7ChrgY2+MS7IWZ/BeMS/FOXIFhuBLDcRWOx9U4EdfIGI2NleS7tHzHpj2xrXk/Ko8hlWhPOBy9cAT64EhsieEYgKOwH47FwTgOYzAC43ECzsaJuAQn4f04BR/GKNyF0fgKTsU3MQY/xzj8GqfjzxiP7sSYgDVxJjbBRAzBWTgUkzAGkzEeUzEN03AhpuM2nIs5OA+fx/n4Pi7As7gYv8AleBUz0a0y9Y234DJsiMvRH1diKK7C4Xg3jsG1OA7vwSm4EWfgJpyF96JlPzfJ92v5W9kuVTCQpDwClPwxENtgH/TDvhiM/XAQBsn6skgFsr4PZH11cIus74IcNy6hD17GlvgNBmABDsDvcQz+gFPwR8zAa7ger+MjeAOP4K+YiybiOAmV8WX0wLewCp7GqhIny8r3Y9YhcXrjIYnzqMT5HHrhcWyKL2AHfBFD8AQOw1cwCl/HafgGJuGbuATfxo2YJ3G/gzn4Lj6Pp/EEnsHX8H38ED/AfDyL5/FjvIafyH6VYpLvwZgp5aiBsVKO9VKODVgfN2In3IQ9cTP2xS04FbfiDNyGs/EBnI87cKFqvoTVpHzJ903JtzYulHyz5Hfhj2FzfFzye0K275M4CJ/CcMzGdNyPq/EAZuFBfBoP4bN4GJ/Dp/E4PiPxXDPJd035DppJ8ilsZzyok0rEg7WwBdbDIeiFU7E+zsBGOA8b4xJsgqvQBx/EZrgTm+NB9MU3sQW+hy2xAFvhj9gaydPUBtvhbeiH7bAr3o7dsSNGYCechf64DDvjauyC67ErbsBuuAV7YuHv9uX7oHxPzNT8bn+7HF/vR298ADviDuyGD2IgPoQD8a84Fv+Gk3AnxuKjOBMfx1m4C2UMnnx/s+zvPGzH4M1Qz8Mgy3mXslyuan3VNPM1RKvnx3BwOVOKY8v5pkh8pSwX5OByUaUs5+XOcksrZnyh7dhC43GFNUcYjScscSyhavxgxYwdVI0b1IwZVI8XtB0rGDrSZnygjA20HRf4Kkk7HlA/FtB2HKDvex6MBTQaB2g=
*/
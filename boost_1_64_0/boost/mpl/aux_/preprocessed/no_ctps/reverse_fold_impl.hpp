
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
1Yfxj/ER5mV3mq/L+cyX5Dt7ZV6sfN7F5wqNlHsLyaZlDvDZrxbLcLPBst7tlvsNE8zv3tvLfxupz8cocN1p8u49ecddQk2WVW4gSDtPy7W09wP2rqX/ff2mC9tPXP/az/41sP61pf1r12rRyvwfPn7w7YXpu19p+L5Dz9nLorqbryGDHpB9VfZhV5K7ci2Hlv7GtbAW1kMXfBTroh/Ww+5YH/ujKw7BBhiMDXEcPoLT8VFcgW64GhvjS+iOJ7AJXsGmeBObYSVi8cAq2BzdsAU2Q0/sikbsgS1xAHphFLbCGGyN47ENpmBbTMN2OAO9cRb64FPYHldjB9yJvngYO+IR7Ixvoh++g13wInbFD9EfHVHvnTQL5JpJdb3EtZJcI6neN6O9HjLIddBmzbVOJslD3baBpH1PDNcu1uuWdZprEbkO0V6DWK89kkhyvaH3Phe5ntC/dkiSa4SjJdcFJVPJVDKVTCVTyVQylUwl0192/W9+AXdxXP9b3ld/2fS++h7dgkL8e3bvGTiY1ZruDTR3Nlj70W6XaygPrIzuONbI85uJlneDD+jfs19gSHiCl7l7pNwfcESZ7D6j1vafdJS+y+Gq/tnWfpeq/tnq5/235bm8um+nPLeX5/TWZ/Ih8gzeWrZUue8RJn2ER5HiKJtxsm3ZYiInmQtXgPey361sFEiJo0hlqyZlk37T1Ldtf+dA6U+fIGUZS0pQtpOmLKb8vMITCvKOeZ2yWO/XHFHFbinPSuZFJSbHq8cVIF7rtnHRKZ9sKymf/W21UgZAqCb7oRMmUT6/KXrlY4tJ+er8yeXTjieRVCavvLma+0l35N8t+8QtTflz5HOSMkPVR1tdJ8o9piC2dQbf68P8a0r5Vf2IlXgnaO4v3X7A3v2Wwvcl1n+W/+ffjyrsfSf9+1f27qcVvs3Kv2s8QH/TfbDgnqf9QzccvxIVUK3FPxcmjbV330z6BhvkfI0e8r5l5Vg8Y2CS+1qVsZHl2bvqHQ6+mnc4BKEHhmALTEFPnIdGXIKtcAW2xu3YBg9hW3wDvfEY+uAp7IBfoi9+jx3xV+yETnKfqhp2wUexK7qjv/W91XLOxjCd91aPk/LFSfni8WFMRE9MwlaYjP0wFUfgBByFE1X57JJ8EnTyqSr5VJN8ash6a6EPumBHrI2BWAejsR6OxfqSz1GDnNewmmwv1mXYK/n0kXz6ST79pTwDsT0ORj8MxO44FMM07++fgsNxNo7E+Rgs228UbsbR+BqG4HkMxVwMkzjD8TZGyP3NKNle0dhDxjeMOelwzzEOaadBmww+42GS6dm/btsNuff4X9Zeo7jfhW1qn/EXtc0o7Luvi9IOQ9sGYy77zGZSJun6yZJ7riVTyVQy/WdPf8X1f3xkakxxXP8r1/hG1fh/RrnGj5Jrx3DSRv5I8Us1XVsl0TY8hPxpNx6WkJZ07/HoLM/417AOro2s13apRv5WYIbl+beX5J8l+dfAylgVn2PZ7GTb/BOTJt/zmlWdd0RKqvnaWz6nJI+xXFMRC5/NsdwzPkcpbDBWFg+yvl0xtvGlJseZ4nO5a3yO5vb/cSyr+nxZ8zlTPlej/cQ+83836tOvlbdB5j2fN6+dZd5v46zz2ljmfZk3r7Vl3oa8eS0t8xbnzTNa5sVY53lZ8x2cN8+ar1/evLaWeWXz5rUySF+QE7GWed6mz1Otn9vq7jOOmrHVnFTjqCW1zLsGL12Gz155Y3VFN5bref1ta7qGvkDGl7mOVgpxTYlD1YfDPJ6YuccF+4H1+w7m8XMMAWPzvn9L5/sk67EVJ+MG/iT79k08zPeNCfn2nZCU1GTT/lOlgPu3up6oGJsx6KrIvAlhcWk=
*/
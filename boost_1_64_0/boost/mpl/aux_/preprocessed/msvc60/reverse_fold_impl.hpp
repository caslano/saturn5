
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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
bQd9LfPkp9xjdecRqCkH0paRymbO+ybRln3qyzC059/QGvGlcv6ZuJ7zD1+tOn8KiSjbsp2+W88DD6xx3sdKmur3ghIfTk392ZZnFtfnqv/9f0n7feD2+ds+44FBFdvqbQwmbmtdtVv0bHzn7OCK455vC6rY7ipHSXOXx/R8zOXs4MrHPfdv5HzM95i1f9yY75saOR3znUrNf86Y77brvnpj5200c9f+MW001zR23kby6No/to2kLa+vODnf+9juzFoXY77Hz0/15JxnNK+Y1/FNKrZdvF+Jxzrnx7zasfVPNXE+nr3/ums/nr3t3BKaVszPB5TvVxfHvJox/ZMDtGP6f1rX9Zj+ZU7i068Fz5ou4uNpO2D99/6b0q5THYelzaTPW4lDQ8JmpZzBVRx4xvIkHyQOTp/N/V3Eybd5xXS5iXTJdhEnTz97M5r/eWPbO2/X6qod6R/ffvWPbqfqvH3mtWu/6rz9sOt2rWct6x97a/qX+xKbnP91Y+6wD9o8ycPBS7WU5fnnbmm1OWb/9atuOFGlwXd7DrtqV+x5O9gBPZXl1zWvsnVkSnStm59YeLAs4Ouwa9cO9rfau0ZUkXf/UicgnNCefw9jgTJ19qEeOnbFQAzDJtgTB2MvHIm9cQL2xWnYD6OwPy7EAZiJ4bgdB+ODOAz/hsPxNI7Aszgaf8ax6ENcxmF1HI8tcQIG40TshxE4BCfhdJyMt+EUXICRmIlTcRlOw814M27FW/FpnIHvYBS+h9F4DmPxR4zDKqTRLGyIs7ENJmAwzkHpZ1vqFsh4pbp+ttN8OS9Mx+ZoRtt2ub+xXaJslyTbJaO085N37TIWra6dX29p79EP22J/7IMDcCCGYywOxtk4BDNxKN6JI3AjjsQtOAp342h8BsfgGzgW38TxeAon4sc4Gb/EKXgBp+JFzPWVd+3yDl6J9wb+nSMPhXHSPsaIHXA2hqIJe+EcHIhzcTgm4jhMwimYjLdiCiZgKi7ANMzEdHwAzbgDF+IezMDncRH+HTPxFN6Bn+ASaV+9GoNwDY7CtRiHd2MC3oNmXI+LMBtX4QbcgPdiLubg43gfvoX34yl8AMtxM36LW/FH3I7XkVY7sD7mYlvchSPxQRyPD6ERH8Y5uAcTcR+uxP24Fg/gffg4Pob5+AQW4BE8hOfwKfwOn8ZaXIiFGIyHsSMewX74HE7Bv+Et+DzOwxdwAR7Hdf9m707goqjiAI6vAkqmhjcKKqKQBykiCqYZKJaWIiIaFgZyqBQKcpgWFRoqGhqVlZUVlZWWFZUWppWVlpUV3XZTaacVmZWVHb+B/+7O7M4su2p2zXz693WXmffevBmG3Tn+D3dgBT6Dq3EnrsPn8H58Hjfii/g4voRv4Mv4NdbgfnwfD+IHGODN3xbsj7U4Ej/COPwYz8RPcDzuwUm4F8/HzzAP9+E8/A6vx/24AQ/gTvwBX8Qf8VX8CV/Hg/gm/oL78Vf8CQ/hIfwDvZR7TprynC02wSHYFIehFyaiN56FzXAGNsdL0RcX43G4HFvgzXg83o4tcT22wvuxNW7CE3ArtsUX0R8/wi74KwZgE/4+BWJz7IqtsQe2w2AcgD0xEkMwHkNxMp6Iudgb52FfLMZ+WIon4SrsjzdiON6KA/EujMD1OAgfwEh8AYfgexiFH2M07sGh+DMOwz9wODbh+DEC2+Cp6I8x2BVHYRTG4UQcjdPwNMzG07EIx+BCHIuX4RkoY/nLfR/cB6Izln8J83XChdgNl2IIlmEYLscIvBwTsBzPwiswDSvwIrwSF+EqXI7XYAVei/fgdfgg3oDb8UZ8CW/C7/AW/AUr8Q+8HY+n0WuxC96BQXgn9sa7sD+uw7E=
*/
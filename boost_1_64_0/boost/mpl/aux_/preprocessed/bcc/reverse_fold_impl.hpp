
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "reverse_fold_impl.hpp" header
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
vZO9s72LvaudsXezs3a33WPn7Lzda/fZ/XbB3t2eZRftAXvQLtlD9h522fbsij1sz7bn2HPtefZ8e097L3tvex97X3s/e3/7APtA+yD7YPsQ+1D7MPtw+wj7SPso+2j7GPtY+zj7ePsE+0T7JPtk+xT7VPs0+3T7DPtM+yz7bPsc+1z7PPt8+wL7Qvsi+2L7EvtS+zL7cvsK+0r7Kvtq+xr7Wvs6+3r7BvtG+yb7ZvsW+1b7Nvt2+w77Tvsu+277Hvte+z77fvsB+0H7Ifth+xH7Ufsx+3H7CftJ+yn7afsZ+1n7Oft5+wX7Rfsl+2X7FftV+zX7dfsN+037Lftt+x37Xfs9+337A/tD+yP7Y/sT+1P7M/tz+wv7S/sr+2v7G/tb+zv7e/sH+0f7J/tn+xf7V/s3+3f7D/tP+y/7b/sf+18c9S7kLOws4izqaI7uGI7pWI7tOA5xqMMc11nMWdxZwlnSWcpZ2lnGWdZZzlneWcFZ0VnJWdlZxVnVWc3Bm/3OGs6azlrO2s46zrrOes76zgbOhs5GzsbOJs4Ip95pcEY6o5zRzhhnU2ess5mzubOFs6WzlbO1s42zrdPojHOanGanxRnvTHAmOq3Ods4kZ7IzxWlz2p2pzvZOh9PpdDnTnOnODs4MZ6azo7OTs7Ozi7Ork3F2c7JOt9Pj5Jy80+v0Of1OwdndmeUUnQFn0Ck5Q84eTtnxnIoz7Mx25jhznXnOfGdPZy9nb2cfZ19nP2d/5wDnQOcg52DnEOdQ5zDncOcI50jnKOdo5xjnWOc453jnBOdE5yTnZOcU51TnNOd05wznTOcs52znHOdc5zznfOcC50LnIudi5xLnUucy53LnCudK5yrnauca51rnOud65wbnRucm52bnFudW5zbnducO507nLudu5x7nXuc+537nAedB5yHnYecR51HnMedx5wnnSecp52nnGedZ5znneecF50XnJedl5xXnVec153XnDedN5y3nbecd513nPed95wPnQ+cj52PnE+dT5zPnc+cL50vnK+dr5xvnW+c753vnB+dH5yfnZ+cX51fnN+d35w/nT+cv52/nH+dfHPQvRBYmi5BFiUZ0YhCTWMQmDiGEEkZcshhZnCxBliRLkaXJMmRZshxZnqxAViQrkZXJKmRVshr5D1mdrEHWJGuRtck6ZF2yHlmfbEA2JBuRjckmZASpJw1kJBlFRpMxZFMylmxGNidbkC3JVmRrsg3ZljSScaSJNJMWMp5MIBNJK9mOTCKTyRTSRtrJVLI96SCdpItMI9PJDmQGmUl2JDuRnckuZFeSIbuRLOkmPSRH8qSX9JF+UiC7k1mkSAbIICmRIbIHKROPVMgwmU3mkLlkHplP9iR7kb3JPmRfsh/ZnxxADiQHkYPJIeRQchg5nBxBjiRHkaPJMeRYchw5npxATiQnkZPJKeRUcho5nZxBziRnkbPJOeRcch45n1xALiQXkYvJJeRSchm5nFxBriRXkavJNeRach25ntxAbiQ3kZvJLeRWchu5ndxB7iR3kbvJPeRech+5nzxAHiQPkYfJI+RR8hh5nDxBniRPkafJM+RZ8hx5nrxAXiQvkZfJK+RV8hp5nbxB3iRvkbfJO+Rd8h55n3xAPiQfkY/JJ+RT8hn5nHxBviRfka/JN+Rb8h35nvxAfiQ/kZ/JL+RX8hv5nfxB/iR/kb/JP+RfPOZZiC5MF6GLUo3q1KAmtahNHUoopYy6dDG6OF2CLkmXokvTZeiydDm6PF2BrkhXoivTVeiqdDX6H7o6XYOuSdeia9N16Lp0Pbo+3YBuSDeiG9NN6AhaTxvoSDqKjqZj6KZ0LN2Mbk63oFvSrejWdBs=
*/
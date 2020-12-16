
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
kVJm5aDNJM3n81BT/nJfQu4bJMRGmMsr371DilVil+/WVI0ZlxSWHBYfEplAO3abZdwpr3LtNCVR1i91JG1vbL4bxHeVneMb+a5sP9ZP2RJD4hMjIpXvm/qgfC/febuBwaZ+02WcPwep3zL4GnUTOsGmfiMi6d8TWYB7Qtr6NZ0/pL0S67LWbZr5M7dkJO68sd6Yrdo3NGPT5aj6J1WTezaqtk9299ck6mpBOXN9ZU+w3V/V96+oG5tzl0N5g2nqLef27qR1ygWo7bk1NiE2tdjO6+0l79uSt6dsm2aybYzRNnnTqs26fQqw/5et2inG0p6s6NvLcl94HDdTpT+U3I80zzNox1icoL9t1PviOvlhekfq+iRps1LX423KC9GRCQW4/2rvWB9IbsrKVH3gZD8zSDnsxziggsE0bZEYN0qMu5JsYjQd3kR5z3v5RYlR7v3aHAe37vL7G1zRYJouScznSdtY19FUdcymgVcLMIan/f2FFcj+Yjv+rZNqnM7U8JS8MXJJfOY7+mXM1ZQxR/a5lDhlB9PfVta6kN897fYLqmQwTUlSF3GkHeSZlaauCxmUs0DHk259UFZNfRgKXx+37NeHzrEk9aFT9lt4oJT9e8z69z4Lf2878EFlvlOW44KoR/7R6eah1vtqxPeMsX8vOcBRme/7k3vjwB+nzd/ZfYRLTvnFM6lYF2X+1TkRS7fWurnveo3wf2TOfaOp/Xvn+ve8C39PurD9E3eYyjV329oPPj9lNM4+NXhS7JKtOfQTNM1Prb3wn7MHrhnxRNNh66u0rnCt8Pfy9e+RF74/pv49e3v32u3fU59gunc+rJm/6+V9uzq8/sPY44ejB6bY6+9ZfP0fTW1UDXI9hVHSf9YB+5CUKUju6Q7HmjgC6+BIbIrB6IOjsD+OxnAMxRt43SDXS3Idpay/Nv99VdbvLetvj3WxAzZCX2yOHbEtdsJO2BkHoh8Ox8cwFLtiHHbDNAzARdgdV2APfBp74fPYG1/BPngI++IJ7IdfYn/MxQF4CwfijzgIDTKOpyMGYlUcIuVNKiXXX3I9RnnJi3MJKtNHUt4rUp9/x/H4Cc7CbJyH/8DN+Cm+iNfwIH6Ox/ALPI1f4Xn8Gn/Ab/A2fosVZTxEZ7yBtfEmuuEtbI0/oh/+hOPwZ4zHX3Ay/opz8A6m42/4FP6Om/APfBEp8Kx9WApPY2n8AMvgx1gWc7Ec/ozl0SDjI5bDilgHHdGIldELnfAxfBB7Y1UcgjVwJNbEaKyFKeiC0/EhnIe1MQPr4jNYD5/HBvgyNsQD+CgeQTfMxMb4PrrjFWyGX6AH5qInVuD4NGI1bIku6IWPYGtsjm2wHXpjF/TBvuiHx7ALfoJd8TPshjkYgDexJ/6OvWScu4HoiIFYFYfJ+IVsc7l2Y1vKcaYcpzkGJhm3sDIGoxuOxjYYgh0wFHthGA7AcAzBMRiJETgHI3ERRuOrGIOncCxexXH4OcbhLxiPpYknEStjErbB8dgLUzAEU3E6puFsnIhbcRIewimyX03F73AG3sSZUv5dBrm2Qgcpf3Xlb0gp/0o57p5GZ3wG6+Ia9MS12BfXYSA+h1NwI87C53EZbsaduAX34DbMxJcxC3fht7gbb+Kr+BPuwT9wLyrXgvusz+7kmkeuhYjb5tldU4m7OTbAFtgYPbEZtkQv9EIfbIVdsDV2xzYoz1rl+oZlpX7Uz1oPSj6vY008JPXzN2yER9CIb2BPPIr98RiOwOMYgSdwPL6Fk/AkLsVTuAoz8WV8G/fiO3gAT0v9ncFzeBbLEmcWlsf30QkvoDt+gM3wIsp4o3I9wzqlHtXjjT71gGx/dMbVWBefwRa4BvvgWhw=
*/
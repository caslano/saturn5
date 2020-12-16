
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
6uzruakerZGe2Gfy9zjid6/+Pa74vZT+PZ743Qdtivtwjyw31tFK7VqtWLXLS7SKY6tgXjwI5GNebxuytoG01XwhfveCbW47S/1J26uw7V6Ml7faNWtE1nmfxrbRYzJh2CK/EG12QjEaTLj01KHpFfzpTcvpLaNsQx+BvI8DeV/Wk3enZqlmz///+2OYU1sG3LGl2+jBeCE41+vyXK+9ofbWTGfE9UIiZVlox/jN8Vfk+IuGxQ/PO84dK/N4Bu3gs93ZF4CJOFV31Kr+1ev/aWMTzTgO6K+F3weBgfGgDwlsPMYOHNLYBIw9vrjGJmLscwObhLHzkhqbjrGulTU2A2MNA5sTMJG57Dgamx+wteF3cjyNLcS6D2IaWwSw40A3k4EtB9j7gM1iYKuxvTfG1dgGnJdbjPJuwrqrjbgO665bSWNbArYM2HrE0G0L2JaAfW9gO3LcHYzy7gzY9aC7z9DtCthHgC1kYHtx3A+MuAcBtvR43rIdA9jugC1sYCdz/u4ysLMBux10fQZ2DuflYQM7N8TehWL8HB/8Z9TR1YBtCNishu66kHRvDEnjnhD/3cs+mNvAHuZ03+d0c7EJZhTtOLnCcL1h11yYnUo2/a9bWWKk7VTKS/R09XR1jy6xtdvb3bOs4rZdbpklXFifwvhStkfaY8yDzX5ts2xvPczx1ksMF+qwAB4ezMP/9vR19XR39S4tmBGnNrxm3W1tsNwyw9vCX6nSldoArjW62E5X1zD8w+lyboZLze0arfpwuVKpFp1aVwnSHfmnyzJcBxLWYEVYfHc1yiOQxrjjUBpLpP+xVOb+B21Jtzi1UqVdtv9R02wz9tmk7INO1tnu79B/NKuk1rJkdiiVyecHxI1McT08kM6sDWgyn7XWT2eW6jUUhTVzcNWTN5BM1kpuCFey6YQF9xrSmZTBDaUT8IvgPFy3rDw8L+TIzJLKUxnWqZix2Ofc5rQbf9ePwxVnZHjYro2JK+Aleqye4Xl1Lv5gun8mOSBFCusvNfcS25T7upfvnnuJNVzxr374227uJWr1Sn2sbjgiv2FeuRL/a4nFmQX38KxB+B9VZqDFPcBkOp6B/7USuYK4F7NuLoVuTg3BlV+8IDy8biadgIsLIVL/O5gsz71EFv6SeLNKcPw/GzlzL1GC5vBHh494YWCwPyEbyJ+IqGPMm1hheKhZH2sWq3P3OxXbnXthcOciw+s7tXJ9G3Hd/bUs89pOyx2G+6b9G+STaw/3dS3T1SMNDber8/6+MbLQ061iQX66u3qW7l5mqa7u4Xap2frrRvqWWl4YoWbwt81AcWAuGn/GCaDcYq2wMPwtAn+L8vp/PfDJ4vDfv5vONk4NC12A/rcB+HrW2HiQprj6mx/+FoC/BeFvCfijOexp+L/JJ4E14GSwlmPseZ7bzxnS2IuAFUC3YUxjr/H89/k4GnuTdcuxbtHfmneq7nC7UXFqW8KU84U/r32BvM4INyO2hnweBvYmYKwPsPMBSxtYAbBXAHvTwA5lXcXATmSdbWDnsG4uA7uGsZUM7BbGeg3sNsCmmxzWj+No7FHWbWboXmJsPQObalrKy/IGNtO0pBsysFkYGzOwOTjuFwY2OC356gYjL5sydp2ha7C9+Rnr/Y36kuPssC3u5VTqpdB6WzNQb2dBGq+BX/rFvSbGzgdspilisZ5JNXYRY19OpLFLGJtxfI1dNi2tZacaR2PXchofGmncC1h24lhsYwN7iO39soDGHue4GUP3PGPbG9jLjH1jYK8zFjPy8hWncft4GhsXbpAVRbpG3PGno7hPG9ikEhtXY7MwdqiRxlKAHQP2zjLirsS6toGNTUd5edfwqcO6R4w06qw=
*/
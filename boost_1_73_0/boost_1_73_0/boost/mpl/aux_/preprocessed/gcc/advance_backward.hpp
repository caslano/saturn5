
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_backward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_backward;
template<>
struct advance_backward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_backward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_backward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_backward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_backward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef typename prior<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_backward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_backward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_backward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_backward.hpp
NZEK0G239HJ9037nQx0LmFXVokwnPj5UoNVY0mrohhM4wZLClkIe25pAB1q7vTTUhk0BLx4bMjWFiIbROHeOX5vI2Fcx7qJ1PhLAM/FpxE9iAIOuZXaSjB65MZLaSdCYbUqt5Ow5A6QV7AEEu13uhdIAqdWBQuJ271rq+MDNpkBalmR4E0iElOWzTIyxjklMAQ3zOkrpN0bdmRUdTOn9OMdAltotYTeK9J3bJ3FHMqCGCdTWr1amqwvIvzHtnSo1mc3L6mkxnaSFi/lrpa4vbzDP+4bLi1uB/huT54F50vSeBA8emiVTEJ8Ie1ewMRE/iDo8jo3nY9CDObJiHTx7610Bwh0TVo+sri6uMpj5yFP8TymDN9Gf330K+BTtJjg1eX94LZ/mLxncWUtrSZ+pswwyITlCaPWHq8Yf9gNQSwMECgAAAAgALWdKUoFwi7miAQAArgIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzMDdVVAUAAbZIJGBlUsFq4zAQvQ/4H4aWXMq6srvLZjHCUNLSpNuug+32rjrj2sSRjKS05O8ryU1yWDCyRvNm3psncUvGNsJQDryXrXK/LR0+ld6YHJZ1va7Cig/3NXB2TnE2oeESLrEi/UE6Nv2GgGsah4MD
*/
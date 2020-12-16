
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
lv7oh9FEQ7xw0uC02W2fE2LQMTo+DEAdBoAJo4tRG5/Z9XT+/YgLjUogDqbz88vL+8n5pXxou5CTBwLpazfLwy5U8GbTeBzWGHlbKe4uG+qhhnqowYSKep8zKXU3MDcgarol+cewyAv1O47RBBlf9iRohHqfgYw3LtHvWCwVpD+Sdkf1fRyKjg10HG5slJM88Rt1Ls72VhpUwzjA0airsHaKAZhVHM004a9D6JYPYWp6sy218ml+PBBKKBdt1iqcNN5LxGFdZqDiEpuaxuUmykbsIMCfpz/Mxz/fTdK3rS1CbXTOULzty74afwnPFqPmGcQqYxWhJ+jAoLFGTfsvFyJD5BpkRZC0dAraJQuyOn9O1apd10nGkNxSZE8RQVK/dg4qt/bYQrxjNyiUMnJi3rwgE5TPtDSLINVm1ERCdl4SQumkU5+roZIboX79YK8fatcP7voy/p7f62JZrfDpXV4DDDui2aCHJm8zjFK68I6+rCxKUVE4lTsBcicvMHP8GI4+Bsg7JduWigq2VqT9LZZ3xrbJqtghRv9SKdmKOI1vTKjzDQq1plGxqtTpNRnldfHFkCqirp/NmOYeQ7dOLXPeyjhXZfjsYkB+3P253ipiS1SVpr4VQHqTFypBJTuQUdecZodRMJaya4O8GUB6LYrJJuP7bnOzeAcpCVVV7N1aBfLEIGaNVTCHPiveqLFpJmP7rDFSqmS21IQePKu7TivsJXzrTZVvwqny7bjXszGnRrfonqus8m07dWzgHWWfggrf/FPTNQsapzvQw7DQTLfh4KqqQHb1hNQ1kVT0p50PF0vraQ+9aWeTaLFPe/BpN88vPrWmbOHJ/UOKPK+M1LSr20RioWmEnCZRX+bwmBfXnPnsNOG4k5ZJ5gtf/3Br+viotyX4bTa/ukitteyslFlMTjpP9qfSpzWKWUIAq3Qu1vNn993udPHs6y/lrHtthdP72fg67xlp5TT2AsyvAxsWm0mN8ld4drtYQApqh2KmxkxPILfhdIWnHITT8pi2nARL2ZSHMgHinBX8dl/EpgatoYs0mI00kIs0oXbo4xiLCL/p/VJrrlErdHc6IiBD09eItOgcYZjVMp1v/mVZoqhkylFMTKrMgoz7HAGsbI+DvJY2W9IcIxkKBJKAoGm7Y4iehrgq1rM6ukMtNDAXNEt+Zx3Euul8xdquYKhFJVSjEmpRCf8XlVCLSlBRQSuTfoqcRqBLWLjxNFSLLqiig2iUXb3BnEPZAC5VQcpNqZVozL5v58Ms5Wx/wtmvP44n13e3t9c8m1806UtzZDJUSFlGCykm9+kLyZiEEVdCtLczMu6pxrdWke3PHu49ABYiv1pkofMHhoGZo2a8gIeYQl7w/NBRCK6sjMFwFUH0XUoRBWFE66E5U6KNH4C/ijxRLECNV9HFADv4NiNZXo2KnoaaOgVy4EMZDci46zHlZHFYla8QqJaV5A60jWqdzpEop0CUPTzFPQoSlhyOdT4DRkfnATK2zHqINpVsy0ri4w3qoiez3FV9SqGryOGWlRhv4rQNRY9vhagKOUVKAmIvop1FQjGuki/F1UmJxnP78ChkExaaiVIM2rG0Q6tEZniLd3E/G0l33cD0hK7TZDb0K2E49CuPb+5iSLNBTDcZt4CsKdL+klUVHnEusMY5ReZZhAz7wCsaRXlFmcKGVWWMOFFj3PBKl+hPlz4gwjUFukS7S8NPI/jQQPv6eTT7MU1mtFA7xJ0aezCvsL5XpMVGX5pGSCBvQcIJz81HUtRtCjR3C4ZtTCiloRbKJ3rXCZByRW2K1oajyboxnC2MUWwWIT0xjWILL0ahXzNrnndqU1Cl1xjejvPmIbcmt1PyBtY=
*/
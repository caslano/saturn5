
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
XOt/0COoulGPEUI86N+vDGaVrf9eAbEMPeHjzUYZ2NP65yPWbUkYGBXa88Nkq6KaW+vKpQ8+2FcuIcNOZVZWn60GfjxnKzjZTxEcj2FVIRD1ZKNozkoYNStkh90j5iLC/9SOt30o+BxYtMCIldVHw1hITekIXyMCYIKzx/UWrC3a9vFDQS70vSOMpLiR9yyzccH2I270Miy9gNwsWJpOvkjNleNeMK5Zc2cUEXJMJY7BTWN8MkCa1xhP1ZN9nlvo8Dmm0AjV/CkjO5pVZCLnMve8FDPEhe+IqJpftA1dEQmqt2YN6TdBmSWaL4YEPra8/TwDvtAXeAHMtEPe2TjlBcUEY6/qfw8n4c4E/65xSlftO598BojosQAuCd3L6EH6ZC0GQdT7HO7YYe7fmA+f5kckySZS3bqjWXX8ylfHcobsOhiWxGuUTt5c/Qb0i29vAxHlpGC97+xfhwYT65xLZnDCwNK62rfvy0BZ9r+NnB7EvlVircGrdr9kZoHEkKzZ+xOukKeBJ8rYnuA2tAJ9eihuYIpZbmjHkPGC6W5vXjYLElppOSk+bIa+RA==
*/

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "advance_forward.hpp" header
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
m+x1U3WZg/ElvLFpRLwgCjjSv9GvEFfrFtA9oORmQox9NqRdTCuw7hTuCZKHtQBll4agqIfV+LrsUkwZT18jylY41dgSkvinzUxUPR66Nl3vXeqZunYbrtr3l5dSCLEpvdA5kal5RIOwh4Q2rRwjVnp298/kTAUaPDseBI2PKBcQv/oqWyFtm8kHeDc8lHMR+MKqFNBPKSp0i3tnPyFonpwQUyAPFS2IyJNUeTJnRZ2EwqTrtK8jpJnxozdvHCb3za41ZFY32GGJSHXv1XVsEOAA0hDeiBGvoI/dxu6Kb9Zn2v6ZTZecvJ6NsK+VFGHB5CZAskzKLnGCcXqujE7Qfy09IJxJfiEG7e01F7sQ5iXaARBd6tbiWCagbstamkEx71mVp7K3MDzsrstI1yH3GkLtCyzM0MHiNXNu1EV2lugBc8ryC12UWDpl3+X+XXP2oeLI8KRRxw91QB2EqlEwI64x0WcFWzwYH5CSoFerxdtzoXl41XGW8tNj4fsZqUdHT9bP+x29eEV9TgM98UA1oGObuRmxnJskKhjDUtWHPI0zKAdywXHOxaLdFA==
*/
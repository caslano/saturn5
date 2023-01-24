
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
FIfO55LTVeqDDT1C6i1xN/YshPT7S1kMEnYfSNDgfu9T8GHXo1pIDusnfC7NxFhI1V8lam2VfN3yRTXjWVUTmUayLhwax11Ekr4zFbtnqJ02lPBsqdH0+XTiuzGdpHh3c3NHHle2XDrLp+HerD60WKzJ4fJpJb0F02z9JbzdhYSuGKTb3jzFM03qW/4LGAx1Y7Q1csVc+4kGShW8MkCDyIRR9P456IiAID40m0+nmsFUoMFY2QJvxgFbIr6qrY1M2oEOa1nWeLF0mcZASpm04bfDTB45O7ORlN0dsIpwQkT9pC2ldNqwV3gDT7gXm8Gpsu8U2VVKesK4XVo8JNuSdUvxC8Hxt0yaHUf8cnOj10t/YbewqognmskVeNFDrD/7WqnIEXuraY8Hk8lRjMOa3K+7dz5Rfyy5Vs6RrT1HtIORZAD7niA3rbHGP4hsDFuN5flDZ8aXM1f6TErX7uCbFwtArDuNZU/uv8I0vucyFs2mVqbQxl5eM2qvWzz92VeBTWritU6C5TcTrC5xNhhkc7muPjxujRNFXvvbkQja01RnuGtxdaTWlHFs1YzpLIUk+pFSX1k/U52G7WztsCTelP11Eacpzsm8ucbIQAg65pyODVbU/vzlGN38ROSSyS/89hblltmOT1nIPLPIgQAS3w8F69Hd1mIaz1J7hb26LHPwBED0C2YRVZTJm02b88uj1PpbL1e6vZ564W1D
*/
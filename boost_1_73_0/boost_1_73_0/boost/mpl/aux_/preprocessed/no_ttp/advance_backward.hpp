
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
koSeIzLJvdTc6rjk8g4YgttxSiqt94b+H/ZAS1kDV3CqmDYADgqBC6XNPJAl3OaHpr4liaWlpObrh6dn0+8ggUSwHabX/wm1PGEDumICZqNfq8n7JJuMpitbWy0nv8dw4rqCfSM3DSoFOavrNcu3Rok6KUhyudsxUTivMaU3b6Z5sohv7JTF/COjxoMZtKF879xcOsznecPdIfqJDS9bsBkBK3VnDLsTABVTsEYU4KtKap8kx45rJEpeI1gvn/3LDD8li9FyOX69gx9Tp7djOq+wcEDxvyZsalutiYsWvd6Ef1BLAwQKAAAACAAtZ0pSVxF4910CAACoBgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDU3OVVUBQABtkgkYO1VUW+bMBB+t5T/cKKq+lICtCFtGYmUtVNbrV3Rkq17deASrBCMbNMs/35nyEI1aZuiPuxlL2Cb77777jvbxAa1SbnGMYtFuZD0WuF2I1Wmx+xuNkuaByRP01k7uhFLigBem5zFXoeNvTb8iB3BFNULKleLDFmssCq29D3jhreUXtAPIPB9uJalEWWNPdZGRPAoUiW1XBj3/n7qhX2/x264wQimdXkK/jlMKgVnvh9CMIjCi2gQwu3jrMe+uYncoMLMfb+N
*/
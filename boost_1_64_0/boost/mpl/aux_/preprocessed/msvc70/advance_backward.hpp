
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
dIAsDbGMYGvtnAll3Ix4ooa8tyTpXOmSCVBDCSv/D03vWRWRDK1RRyou1eA5Qfx1frrf8aVpVz68vD7bnnvKZWMWBilvLTs8U0rMw5XU7gndCAYZ++jSuv5VeGANBYZCDpny2LALkocQng1BAb6niNYC6O0+e4CFEAzf94JlcqADDsJwagwEvu2vFGmujKw5CIfTYK6h3oTZHqV/vuH06m95tgB8+h++2rKBZZaiUTFRjvoVnNB/nByVv0vNqT6jRNiuykXcvb8fNMFUpv3RqJRz3ZLz/fEIxjTl6j7IVoytcjYO6zC3rJ+OIf7gCDmsUHrb2ftbVHnnpO5zheasWgHrIT88J8sH5DrtXti3qOi8ujjiQHAw7h2ls3RFhni8B/WMOf4BfkqwwfpueFtylcCZLt0UlvGpk0QfxS71IIysjqZEMUrhI5hrT4u7+mmPjSDL7FUnWBh022hGuBzpavqWruvwpFmFjjEgpmCY5CBLFVBW2TWBds83ACO07xQ4CVf2gkluJN3GCGmP45ufyrGExe+5i1OxJ8Ml3/jNBC/Fu4e3tzKwfJk7/w==
*/
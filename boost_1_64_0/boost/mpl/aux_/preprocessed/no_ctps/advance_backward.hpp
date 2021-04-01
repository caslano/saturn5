
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
jbdMYhQPp+h/28SP14mnssJZ3oaGQtEtwIsB/S56aEqKBxwq6hZhGEOEl/1RZ4JKHFpt34afbRDaC6CQYRVyvy//8sxMIY+4emzJxluwP4NEINkqXTrJLjHIIgvwZpy8tgwlIwYiJ500vjJN/V+2qLF5v7vDIOx/aFqCB1ggfGDvJLHWxmVbF2hwXZ0qR9aP7LAOjvdlrjG3rzZQ5qZD5apOBPVzBo9UMxBLcr/cPrwIeB62NWvXOSaXdzskXzbSdau8EwNJ1GpsELHx4ryg5Q0PtxRGr+tVm2vOzyarryuuwILhcKLy3ArY5ymFgs1g+w1YYRFfjCC14mnhQ8W93aVNIVFdXG1tUMXsVEiWxE87cJJmWKiP8JrQ5N0mTLTHxePeYmiWOnUKlOy/8kxK9noeW/ZzcKTwwLwKeBUFZQaoEKrQkMsBL4I9pZ9bkN1y8axMyKvIWoS/7+jTI5YKMd41z69W2Lk5BX1TynNkNc04QwrkDOe05z03C8GScNu232u9boEdzMFWS0pv5XJU0qvrVhe35AvUlIMhR+oDeBROTKpG4pNIRagCrg==
*/
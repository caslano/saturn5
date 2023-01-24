
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
ON0T6l8i81wsCIr5l8hk/f9VL75/Vb3Y/7E4y+GHjme39RM3yhhVKHW8P4LZ+07BbTZuNlM/igneTXxFxT9qJ0wDl5LIJ3mveniX3QfRGn18gsHx483pGdqWWmXEVfWAYm35isYVkQeVDq1iuxZ1xjq9yuYPvL8MilcSLR8E7tadnpaXzOPmy43o7w547jxOhfZz/E67IDx3j4+ULB23fpRrcA425mN8qS3lZvEfKyOyEmF2CNjJ3UnjVlVbxzqbiwxP6M6m69oHPkxiY27GKD+Q8EVpav8oRfzrFq0R5D52U75adF20tcLHtqtAweqa30+/v+Ai04R+ePr4lZc2rMQJ2aeXQS3R4OqYcr+8wgImU94+PvE4fQaHmef2wxO+JygLlY7IS4bLfgeqqo44hhP8zFdTTKGW/ONQlgKWGWo+ksNBme0XHICd7Ijm39D20yPc2tr0xbw5nGHzvTFOp/QeI5ypVkz3MjOTtjMGhPOEkWJyfu9TGphCGuh2lSdy7Ac8wwkQIDANOUIegqBkMWbTdh+2B/b+3sE7kzjWuEqe3AyWSnny8idd9fQGncB6dM70Vvn3wJrxBBWswFM7W4TLEPGdCS2FF5KzKxD0peHld9FVjkHrs8rqzhVsvLrHmm/VOf8Rjs7WBr/Sc2apJWnFaaX0fvWXqaj3ochrop7eHn7TLlX7Ldw8lKVP3gCMOuI/z0MRHfCPHJZj
*/
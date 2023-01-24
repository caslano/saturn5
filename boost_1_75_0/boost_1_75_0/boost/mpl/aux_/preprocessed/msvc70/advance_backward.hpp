
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
h1VF18sFfU+ufTKl3fPF3xKVEzlcP0J6dW/hckhoNllMBHaNH8sGBx4Wj2+cJRqiXJJHh2RfwWF/ZloG6R3M5cjLcgj9LrOiuH+aeSET+nQfUPmUb3bM4JFZagvEYe9AMAdLUJqAlWb5hGHzxAwBtjckKKUqPEBaRzkHqrlL7YXw7nCJ/LVCeEvzJOTm6P78xyT+nARluzkkmvIo4MJDwjxA7ueF+BKgbT9kH2AIyD2dXxQEVh9CwnhaK2kh2pwSbG8QW3dXlYxSvKyjQg4xBIOpg0x77pZRtesG3JrT2gJU/iDFLYUXAMkqJeN4A0vHAvDgS4KBErva2Fyl/uYhO1H7GvkNm+fC1QWJdF3Y4JkvOQyIU18w1dW7PWwbNgUTxM/lLnPpettrcjEx6okJqo0cxWJd9a9KlpnnUGfE6dB7bDgcST146QIvHGOmZzbztL+nH34o5QN4YcYdJAL/KnAvu9Eofj/7BoPfj+3aETcTJsAwdPPIYFsn9S0LDiMlSqv9o7BkWavYoFXVKv3vWE9mrVSjc9vOp54XKBc28CQ7JrpXNiqQ6wb1BIvQ4azvyV8K735yW3+qfA862DKdMe6lDIsfmhx68Y2w7OUI3jnf6V8BsSt2PshqFMl3IkW9RrOyLL7AniEbi/QhL8di2nWtf91vHV16H2CF/sb1M47dG2H/cz7P8p9cL8gvLPi3+N93z0k9dYYyMRCj
*/
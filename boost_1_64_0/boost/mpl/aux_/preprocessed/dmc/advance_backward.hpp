
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
jFmiEAte6IlbGsEKI6Zb1eS4PAtmLCCwqeH8vL5rS4XpXqTrWY5IVOiFHPlgq4NvSnz4PthT+FpYxXgXIcqEPq2jtffZJmcp+ql+vEGksX7pZHnUL6Wrqg/IOim465TwHzzQqEHEAndNnLsIATtQDiGAhtDNCmnQhzSbhR/xm0dIEUcKCWPzUn4zfkQiI+KNTcR1RZdng/Omuc72RQYTq8UuFEYMpOTHCJhBnYWJVAg7iOOf+fLc6jc54zGXmKi3XusUkJptW3/VGdhsG6feVUYKCvh004k/f+tD0FGMCyQfkt1f9VBlNcj/6vGfGEcefg+LJvpohwl++kQXpdmj3MFKhdqUil2b3U8wtlD+EZg+mQOAt2O48opOs18l3TYCpfFXXEEOWQNR3BFe0VabMrRuVW18c529PeY0XJmHfV/1yq3YnQImEoPmaHnOTOej0nF2AAZicbLoeslj2uq60sRGptT3QE3GPyFnb8qz2wD7QQNSxmCYKH1xQuR0hTnrmT5nC+zapdihAIQwMJ9ptS3xjrAXc1LhW/fwsBrUDgi2qu6chrHLn1/JFA==
*/
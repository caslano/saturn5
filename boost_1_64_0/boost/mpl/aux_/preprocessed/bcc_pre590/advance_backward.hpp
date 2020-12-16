
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "advance_backward.hpp" header
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
r5FP0v23iEn5/D1iUj7/iJiUzz8jJuXzr4Dp8vl3wHT5/Cdgunyei5iUzwab+kyXz/MCFpbP80O+Vs5O2dCy8Yki2+m5t5FofAIQvBuLXiSXtE1EK6JL12/qtCmzPUXf+JxZfaRv5uu5iQrFf3Or13BGkzxUiW+R4lSIXMe2THIUMsLYqpdnLvOt07zTtuPbSW5yAXybJDc5Ar5txPHwAd8uySWN2/fkksYXJj2Sxh2SXNL4oiSXNO6Y5JLGF0ccjRl8pySXNO7ck0sad0l6JI27JrmkcbcklzS+JMU5jVSHXyo878yhxFEb293T0Wxwzct8Zm7G+ss93dwE+h5OX1U1//Xtg7i9ItQrM62pdbNm7zOHr9vT8nqWc8xY30vplJ3QX6l0jjHrrwr0ufC/WumUCuiv8fR6ZvXXBro9u+x1oU6RZfb6kFGEmb0hZBxpYnun2Fy+7o0ho8gz2ydirQnLZoWMHqzM+gKm+xGzA8bRZLZvwPR7Y07AKCrIy/0U0/r+Sl9LkWB9LnTaVK3ZnbJj3QdAVxPEx9fRIk3mb1IcfV7miOOBms+cYH7xtabtWXUHWdaoZ1UVl4O1zplB+pu1zhlB+iFap8Ty++dQq0/X990AWr9oc2yezFMadTOgD4jOWYIwBkWv9cFbslq71lfZdx/3bpyv9f32dfoCpeu2t1Dpuo0NKV23pcOUTklHHBeJ7tK+WGkmjlQ+S5RGfSjOGGLDjmXVuik8LFShcl+aZpXpRpPiNeJ4YyabrhcngZF+OHTeXlfa8ajW3TOcrylrpsp9TOuqHS5zuq5znAfLwbicWTtCaeZYMtJWQEOXkrSVSps9l31HKs32W46y2gmrGu2pmVYL89SPJn3FWGl4sDRIO/gtK/cvKHl7dR7Tw2PHVI5N8+IrD8WnUvD5QyPl4gcrfuu/xdOKXOF8qhb6gtJwabR/MR0AVJaxz/GYue/mtZiZ2zOrh4zG25hlEZP5CxMB41zh/v5kyLBHd8c8jIbVevFVad+a6lTXzZtsRB6ZV3hcxGTPu9Uh429XFL+piOUufno9+3Tsk/ih/JvaU142b2y05J3p1EpxfJubiRmSwGeOHV/whUv6B9B+2vZvN6OR9Vzran+2jtZ5t1Q3PtPVTK3dWmN1mXVIYZ3g6UZVZ22sdYw+yZC2zmn0YYfCPlE0zABl/SSn8+xPd16y02VdydsKbWiw1F+Jz/M8WZg+0JPY2y3Th6bi/u+wLAjvnU6Pzzl9l2M4BBT14d1Ol0/y9Dkc/D2aU4jgSPN7iQ+Pze4ztQTaKdBMFNx85PeRNtJfr5syygdWtRq1TNe796c46t2pCabXH37A4/Or042pdTrsD6Y4wv5QgumwP+zxpe3RanOSI878IyluAndrj5NcvqV/zOMqdMT94z5H6Mw+ETO3j9MnDaP1lGa9Y3zOGvYqT3vcu+C0NHfvgk8XfPFSPqAOz4DPFNqSQdcnOB1/c1Nj7bNWU99QP2e1MbMCLqeNe8n7eehoanSPM1ibY+/xBfyt7/FFaPoeZ0IL7/El6PoeZ7E20Id7fNn+rZ4ZZztNnhlfcRoCQ15/1ej8TB5YOlweG+03GYmDl3lssDevDAxzGF9PeqQufiPJpS6ek+TyLD2XOO2FcMTQ8Oy+DaCfJzoG0Fk/X+nd6ZnKeKNF+jcDfWKG8/BbTpd+wAW+VtF7dXxb2CQvGxzP2hW+7kKf5Rlv+kLsOz5Dr5Lj8F3HaKU8xfd7vubScZGvu3Rc7HTZY/4S0kpj5YH+kRIvMC6XDl9mVkjw69Wtw+3tMyXFnkt7e9x8/Ms8T3lkUf+A99z4Qczdc+OHMXPPjctDNlQpXiV1Wglk190mPRg=
*/
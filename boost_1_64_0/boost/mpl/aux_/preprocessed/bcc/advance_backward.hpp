
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
w1JniGUi5ahLOH1Fde3BK5aH1EKmHYeQyTRTjnp67SKrvcKL0jRZmifQ0ODf/d8ubaMSp6y7Zv/5QZrGex8+bGHwsDHqdQ+tBEgH7TfhssqwiWLBpb74PLxhU1RZQQ9McANoWoy9XETR5QiuWLJAd3iF+kxIMkEHjPYy4MwFbxViZ6LWxl0e3PvGUbHU1ZW1L4/WqVyXHxAIwIJB0At+O8I6tNB1Rwtgw08knsPfaMEfOm1x5mBXkIUysOhPFWnZ1K7Xsg0rz9dNIKr1ukBrRySoznH3TsmqAtTH6EYk85bkI/xE0JFBheaHeYHHwZuXo0l0dhuvdISUT248H2p8/4qwcpPZzPb6qhKGix4FasyzPFfret1w/tbcuOl2bynMhnaMoFASLpp6cgTTFS7X7m518VZR+rPZaQLRkTM3TRVKzS7jnQrhGJ2XWKqCA71wNGnbX/WXty772FCxyuwCaD/YorE2wq1sThF9M9Dg7vck3dELpP3IR1scdPWKET0+c5bGQpC5hRI6MNnBPpWMt05BupHPSvYCdFMAcBRX4QPQ9H2/mbikZQJJZw==
*/
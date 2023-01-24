
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
DGBvyUtV5cWRypFrf9XLpV5Gf3D29PrsbByFcTUF9JkWCJqs/m7ubpoDicViWmLzGEc7wrsLmw323H7YMVd6Wtd0rm0z3qwW+Xa5cu/YvebsV/R9DQkLhv44rzb3OQOrCXD552VHvI9maiVDS13fU+67VuozFzC6yo1XkxaNklaBgPOlK1ZAt/4V72tzxSyYK9L37TXBDn63ys6z2j0i3LsYvZgdlbDq1nLQAY7Yex7fQuBkU11HylGxzh6r5aHDEVimhC6EzOVi8gs7NK96g2IJL/AaeLDG32hFzK1wunT3LOIhGiCpyi8Gy+MAujxv4dRlwCE0iIKbRcT2iuVPivpfFDR/HdPezuM/d039xB5V1g+YTi9+BxXY/kMYPCoPI1IA2t7QpwITglJOgGLrN0NMK/3Zh/0caX2t/XqD/Z9eJG9kDyUOMffFyfOdhl9anscVTx9SXtqH1YByJ4apWepKtn3EHdb4ELHzUoRGRNApcGn/QBkB/HtitznFPKYc+0//f480xxfuL/+CX85/F2sTGzoZyd1NfV9NHlLIH5ou9d/mjy3IxrseSe6YGdzR43PO72g651b5w9Nyd60dcM3m65vOX+yGhcXundlG9UZdD7MKiabRbtJQXKeM6j0lkmToe/keZIq532/eAABd+VxcD1cBLTt+KpHiFrInM1s5XCf5Ap4z+Z0tz73XbK/DcqBOSLZ6CrY4ag/o
*/
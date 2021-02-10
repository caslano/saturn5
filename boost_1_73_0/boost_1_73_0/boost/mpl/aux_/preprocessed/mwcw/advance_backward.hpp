
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
fzeV2FXmioGG5Hx8rI2TW6fq4nhx2cCCnyAhRaLruv7xvNsfXFzVPyoOr7q9gV6Yr+3w67JGMMi/WJYMF6CqCoKhRAJy0lAPEAcCY2MpHIqYy0OtcZ/bqtKSEZblsfa10/2j1bm5uLzAQ+m81WsXX0+ue53+efdqcNPpnnw7u748eTJ0fbltsN/unbYGrXwo97pRlzcn3e63i/bL0dPLfj6kPPNltTEP7+oARbEA/HOVjIRKrZgGIfu3DlVtlhY2r1kYa8Rizc5Ff4DzP1goWXSDvN2EY357i0mK1qst87mBZa5Xe83C2rZaq9MhoW0S2tkGjRUoEp6S8C4J773FE4lfI/H9bfj9dr9PYhtVEtzALHfarcvrKxqNTqJhkXVn2HThOdrnz5/z49jYs6oNl0b3tKt276zb+07vmE6O4a9R1PELWxY0H7PwqolBo5g0ikXrkFaL6dAotChMj0ah2TV9EsWia9wy3n6Op6i3aOqtHVBsGsXZWYwWnQLLI+Vi1Ui5WP5ajOaeYrTpe4xt7CxGmz5+bDoLNp0FmxaATbNv0wKwaQHYtAAcWgCO8cb7F8WYQ1e/Q/Pu0Lw7u1e/Q/Pv0NXv0NXvPFa/tWf1u3T1uy8fsf5s9bbd7M861/1z+kmFFohrbcjttWy4
*/
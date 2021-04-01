
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
w6OhczikHuMOmlqLMTtMbAT/ncJXBmMwWn1gF9QrnhDK3SG22WcIMkwT3ThNmHnJJTTfLbLY8UunCPgaVckukM1QwnQ1h8QNUOiyFSijOr3epCA1+34R0+PgEGYNeQU3eKOdFPnj8cGI4W8xLY7WM/Xw+yaOYEFCqgNQHsoefqrF2f1vIcFteKCKprURMYM6xS+xJ/1RsNYo1OjGqxiqV7ZWaf4I4wC7RrbGQeIhnVzWpYkN8gLwtlBJ01wutFcze/+47Oz9NqZMLwhdvOobuSU52nwnPubQ0ZMvZimDXshOBhiMcF2mO7gf1DGf5tdA/QuaSvyCvSiJnHFTpEv/cK3rqupDaeTVj7MfRzVtL6fQJKO9+5F5imc10+lyH/+2AN4K3b2LDB4Nmpmmc7e9TOzIvaEVez5EWls16L/N1lC0Dkxc8Q6epe0X7G1/azEXweSPfYo3g5viLa20yagjqHDIXVyc7GzCWEF6haOb194MoQ+/kG91CWUGvVg0gmdMZvN0gfonclailOT8IbB2dfQUTlfN3Pgi1910727bxUX1qhZz4F49pFAYIg==
*/

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
ryC8chDU3QlFn76HIgoUd/9/+v8zrk/80tdJ79QGr0vpHPo2EN3Hkl2wxHSIlqywtiaHh88kR24bjdRLz7bbzZoJfaytIovzQVLxAy7PLQm+n/W8t0QmEJXEJPAqg8a4DqxRyFxiBk/RQ4E8Q02h+3gXsCukAXdp4J4KsDKUEZ5/w/JzZ2BoC9pClggV7pWVpKBq38+EC8B7rOiUFtIHBSEH/lN4rsjZkWLmQbCnepr0SqhDIBpd9kvdlGUQxcOY+FSHA9W5ZP41eF+jjCIP/IbwUNI5r7kxbXamys/A+9RUd1hK9/C6nJTy8poYXW/ml47ezc2HXRCH4wmR9JiLXk/XSEg/opb5EdztA88talduz2HBDaRIBHimUNZjyX1nSwFqrawSqnRNgW0pK2qMIxpvybrr7DLCg4pJz8rYOXwDbMD+dHSu9oRlDh01lx9//7Bd37wfsJUQWNP2i+DFd7vkqep5XZenCRB89tu29XOlDz6FxEqoDDMn83+Gzc0Fau6/uqCPg8HdhVPbwuuuhWbAT46KRsuF1yXvfEytKkM240k6m/A8jmZiFud8gtPxdISjFNN0ipPhlDbHYjyZxTiLIjGK0yzO8jQP0+EsnsSYPhlCpxn067xG0S8R+4UMSVwP4nBCe1RMcP5B
*/
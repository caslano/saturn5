
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
dAC7XCVAPzEteh+eoNBBf2Ez18jTPyEW1nBbQMRBA349k5lavLYNNhZx7HlsSLRV5w8W6f4zljO5VhDSirfvZQuyKUXVPg6RgK1YvEXWW1uVQwsUUWckq81i41uorJ3Sqi9tAriKyVyGMg83YCr7dmeT/yB8wRQ2EhoPmtRKrWJkyRoDuwe5FLS8OVmlWnfVOX9mrAPP18T31O4tMeY3hCqxB3FOmkJS4kXVo3XTJesvHYQQDxl+0slxIipmu+IDW9a/tpfcFgBiP8biEwL6MD8zPtJ+TUZaBEm+WLOE7Ygz1pB8GuMo2+NL67nvBEuvGW0iPgNGbmascDm+JzNj4Va5dQHA2w4g/MuI6otFzw57qyy15H6+ZGLtyvNjtunfmkjZO/xU3ZqZa45atcpkRU+zmlC7byZkULvw6JM+vD0HJqRO4QTTSqt+3G7/gT5SqtByyshQoDA7WSxVVOpUD2j+HILlQCO0Yb7t36bL3DiZ9wz3DzAsrZNB4fEv8qPhSdSofPAQoryffs/wpsTp4Ane7N+WE1XjX8TnpzAMpi0PHxP70zr3hoxWZQ==
*/
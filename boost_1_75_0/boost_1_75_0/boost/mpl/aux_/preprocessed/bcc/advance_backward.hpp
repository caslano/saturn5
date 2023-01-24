
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
F6UZWkRIFUXCFKpoZTJYRD4tdXJIo2Rio0qVphzrSW8QiiY083pPldlkWJNgT768pk5sJ2pCaaexBMwbRHEviLDBKCiiGocI6YGpNT2aMHEBUC1kI6sWttgAuXLacEICGVikaFpALAQKPBvPUl2u6ajXnvkETtqmgpm2jERVfwtDp4GStQHFugpYTAaqUpQIY36ie6NJZQJ06AIuGtSo3cJWFQW3oaaVULtH9+aoeTPTI5IN9RrXJCmuVTRiRZdXJFrFNKOIGGZ6EtRKxUpqNjOGJihBKks7DUZlziI93neN1UOvA1Dh0chr1QKK0cgOx9S6VC2R/Fp8vbt8svDiXIs2EGLwzNGeg924QmBTbm9gbJdli2sa6PftrgahfwNyaWCphQDIMjTwsHqGKhUghn2BilparSMjmulYNcbtCSWnlgEkHnLW0tMMkVLeUgn1koHYngaWttppTqyZqoB3B/wpv6BliFaFuNcD4tscqHIgwobU+CaplzU5WchD8VRRj6Ae8aehz0geAwpckTI21BZQymCjcTMydKzXU9afCzTSsAl4YQsN54k9V1U1ekRrzMnaPiSW0UYQXq3yfMWlFS5oSlcLVWZ+aKLSEtO4x3rdVjoZm3kf9T4WaxEvoHMzORjt1/VQFaP8aGQy4pRG9iKFXZ9fKGN9k/BU05liNzPUgEIVbb3Qk3JoZvYUOcxSvEYjwdY0sK9puppe
*/

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
Lgz99lbFMZj2EVfYB99Hstts976c/hQh1fy6N5nLIdXHgKYu6/lPqQylESAqfHuHn/CP3g2uesMlvlrCS2zGYQVhoV624ZRL8c8dXFs6xIQ2s+kFEcA12gtFhkVaCPNwG64xOqmsfYmJMzsjyv4sNiYJ/K5bIlwk8uTtVuN7j/tGYPCvkcrlXMNnTyisnRsusixidnSkhLOf4S/g0AMfZ7dKzEEf24gZPxmvla8qtSUP25WHiKlik+C6LPSEUDvjY24LIETWgXdedwn250u6KyXBo1ODbSrhb7KCVTTITZGG9+yombjg7RyD/W514QNLy8gQKP5r5Cm5gQHHd04kNivO9EAd1SavcO83cSzmKGIsMtd7gPmnlcSMKPVXrmevpMee93NKtxNw6mk5UDBVlHzcSxjiBsJ+lAy3Im637mgjhgo5eGrw2zH3UhTSg/VKRl3opuPMWC8ItHClgx2I+9dMwa9hIaQUXvOaemZLnCqdBTHtJ7g9RHbLifX7FjLZVMope5/5hCYjtSN4jIPpLb5usvwI0iRr82V3Kk7tP6XuAqbWQ2mRQ8ArTg9JXJf1o0pGvyQ3AMQKsab4pFy0YyxB1ctxRR1kIsewqXQEbPZuW/8T3dAplmULj1MW3YDHTCSvVdjZ+9YxspadtdTkP4T67dvJeNNiWrrwVnMmhztEHzXNDCZHWirijYh9BZSWWvMB8TgbyrRNqcwd
*/
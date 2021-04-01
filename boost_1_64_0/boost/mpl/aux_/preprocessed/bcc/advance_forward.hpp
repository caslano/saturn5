
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "advance_forward.hpp" header
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
aBPlp45UxQkpeyPrh/wlcNHexYsfZw1zf7fd8c5AkDwYDyaImQaD4zzJdTzpyz5tQBsPNhMcMBlRGTEqAfUqWAvuWCWEJjIgzjEvJNnGgpzydfZrkUrQVz8B4qmu94qAyLLgCM7oY/P1sTYBRDEnUM5JR2mw4bAXy5H1q096Gy4m9rfi8bUvAKgYtW024v3CGosnLCEZqsOjFV6tCCITcmjR68lC5dZ+niH/y/wFBq5dMdPCK7vCia1iFy4eOfpCbZVyVF6RBysYLy4YPUTLeTXxzlnO8+e0V7aMDF5TZw6T/iZy+Fyz9lw8NAg04ybjpLTYQdFI1uN3h9fwRhKhu0KwWxf3CKoSDCHE44k/1IG45QOXYnnR3y1zAcyiAmyK5ZWLJrSg/KPQczLWM0mBGgyOkQOq3H81nwqm3uSbSm4BvVjk9kMHkOmR3L3f3IsV8qv0WuuHK/weGI/YQYJCIkPbMazwd2ojKian3RVI6UPUbIZN9MAJWLY0wTnawyV2GXv16Bt9A1mPUxEuiI92fv7X/6A0ltOu8lGhCm7HPnCmFtCJfRD748rEXA==
*/
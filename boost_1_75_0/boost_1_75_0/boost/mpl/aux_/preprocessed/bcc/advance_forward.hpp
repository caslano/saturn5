
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
VgpZpodlXqa3RI8+kNe4qzI9QiM/JsGU2gaoZE/6JUN9W+wa4xYMC7YzNJXoiamQ1UpeXZkCKet4PBlWC3mqOgomQFfz85ohR7tSU7FZ2DGHNOiKBMsG5c7Zgwpw7xS0o0vP60QU6sYsTt7FME8bYkrgMMakNdnzn48gLhat0OSB8BpS6gIpxG0s6ek70FsEaRuvbXNkFDgT44Gc4pYL2ZyfSF8gVEQ6N8poVsnNiE6YSU1L46BXAMjpkOQcVOohRjWaP4/sGKqPcLNlihS5OrU7GQdALRwmaGukXQqvOwJp5B8KCwDn0MKGApaulprTDoAVyRuuwmpnRt7NZIUhBaaU2niC37j8pCm+DMIywpkK2sh7IkpmV0ukhcD0OaV2xTyeDu0t00T1jcwMolcbPHeafs+DopyNJvxK76mc1vPKemOkHYRB2S/lYz3yddfnqDKFt23iSCVQ9nZaUcFUrlZmCgGt1rYTDionTWztSvjxDoJ3kbYc0oN5FBgi5xd6rPkiRzEJy/QFrPj4cS5bpokhVwhyJ6kVSqdAcx6velWM2vZEfQS0OxAVxD6hW67Gk7w8QsMui3uNiRLJNipa96rDRakc5wX/EA6nVEO1GEBSTqpF33gIPZcM2KQhORon+ZQhXE9t3T4OaajY2jzgtTpvnVuQ0Kzndmzd3tHhAj1Rbetwi7BOinlMAo+1u5jIcRFtrUCk4VpAwwde
*/
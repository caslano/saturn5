
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

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
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

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
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

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
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

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
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

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
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
0YfEC2DcD8dt1RBy1Ii1RuHoRqmPVF654sURhyu7FM44K4MPt8gn1PeVWbHySee2euKhjVFnLu56AYlPnGw/kfMauNAvD7tIj0uELdgRaHVIKkcelw/I7cR97PTDr7Nna/JEqbGOHetsOTMqOCOO4fhYqYwUZfLSX2S8iCI9Nma9an3ixosd+VqrxzqdEYctaEluuXBTf0uXxn3gLkT3UtbkQ4BgeENrHEG1/VHEKxXE710lwWzmGWtDS1U+mRCHnKc3qIIOBIRu8IUhV1DJ1PB07IOpCOQ+FQ8Piru3R0pKdLs5TIoovHwm73frI0KXQOhfX+rGXFpBHIfFzmjlhL8K0rT/0i1xdmWBeX+HKkhQ8RLKC/l9xfBGyEJdqyNaBf5ipEt/X7Uh9yhP8VvlAUF0CU+Im+wQ1OGzQnAGFYaXGzHaAXmE6ppUag5LFEsEbMdL8/sfBnDm0GPy4pk5JAAXXkh2uEmtEWMyYxPVg260KPLdnihn5zveAjJHoxLvirYvBWokG0l6k9s8sCrbldfAdqePlFodhVOnSWqhHY3+1HFw6k4Y0O8nGw==
*/

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
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
*/
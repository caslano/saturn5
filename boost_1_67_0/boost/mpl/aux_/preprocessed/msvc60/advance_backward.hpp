
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
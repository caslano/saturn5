
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

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
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

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
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

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
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

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
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

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
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
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
*/
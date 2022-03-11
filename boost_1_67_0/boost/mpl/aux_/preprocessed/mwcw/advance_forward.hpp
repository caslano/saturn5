
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
+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
*/
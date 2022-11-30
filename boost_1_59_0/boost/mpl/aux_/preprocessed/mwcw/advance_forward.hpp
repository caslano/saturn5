
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
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
*/
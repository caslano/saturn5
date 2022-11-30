
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
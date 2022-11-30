
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
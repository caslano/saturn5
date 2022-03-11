
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
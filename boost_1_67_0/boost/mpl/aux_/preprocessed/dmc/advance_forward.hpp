
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
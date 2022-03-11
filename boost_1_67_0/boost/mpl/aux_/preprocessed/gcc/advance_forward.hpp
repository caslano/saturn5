
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
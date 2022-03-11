
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

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
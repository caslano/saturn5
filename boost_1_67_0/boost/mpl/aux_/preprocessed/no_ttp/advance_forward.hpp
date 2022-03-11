
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
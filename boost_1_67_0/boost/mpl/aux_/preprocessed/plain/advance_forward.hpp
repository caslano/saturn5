
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
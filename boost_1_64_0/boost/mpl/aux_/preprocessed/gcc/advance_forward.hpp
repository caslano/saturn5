
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
qFOw2hC837OA7VDFwQ0sSG7sxQlZ1y2NyLwtnygsjNILw7wGEoxdT7WQK/UEZTh5ikUzYogAZizBG3jWUxBDQ6bgOroNxpABtais1+YAjRhRQ4aisdz6Hz+H+EjY54H9ibsZe3yYmoDkCftYbs0+dmmDM5znvS8Ll29diaKTNmPqOQfEjGJQJInh1CFV85cbBsd08Kj72jkNDOzHs0vZt2JqvjE9zXXHYouz+fqcfPMGM+xh+65lfo+EUfrxNgsHVPch5oWg7Sv+EE13lHxPiAPZxEUE2ROi/2XUmQSFCqpNxcFiSmyJYWRRk2vhgN123L9NoqJLp/MVKRuSAfCwSvQmkb/WvRBEUr/iaoGtqSM5U6c2ZlyhSptXgZ681KA/qnYgQs1bGbejcvPRc3ygVN6hGsmZbzI/xGMCGxCvN6LItalHCgfgNVnSIqRMot9wHh0WenpWpfKi1JgBEYQglmGEdXixLj4jYSw2lc6u6xJyCg4AtviqboenSYUjCPv74euklOIoiV4WfckVXLoJ+loNnguGN632MLWoISKeLwdOXFQJDpGOzPCMKA==
*/
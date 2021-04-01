
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_backward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_backward;
template<>
struct advance_backward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_backward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_backward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_backward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_backward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef typename prior<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_backward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_backward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_backward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_backward.hpp
Mbk+OnO00FiACXUMmoU0gQsmu1dUNpE8uIvhrfsNieBAWEm2WTgRz1rApGhKMLQnbNs1mJqZ6nkywPk7as3qSBXjHK/khUOTojm35oqTvcb6n+ln55+t6d0S800TIXHIedbhMZtdqO2HQLGJSFjByulPnBiHi7jaD5mEXfQXKk+Lpp+qFyRItaxZZvedqyuUHdspjjyDBt/D90Vg+q4mWm+s+udM1VChEH/4LJpA1QQxk55wp+Fz3lrrT8hRb5PfVkVlxKvIsDX50Fp4wE6BdWPGpuO3CfLpxZCl7AX8nf3eSoYqJAmFZ97ROTulv/Htz2g/uYdjlthYLFDCQbJF3oU7n4MgYKsneZIb0LDvOM8UHrum5INsVDomUhxsOrPFgZJOgiLtALTMIRwKmr+dsaZKYiK1EJpUj+ZH1r0eEVHH9QIuBUcq66kqaesKrtC4+QlAr+Tr26T10zi8rwp61NXWqBt4aCX7GPL0BIxyc6WUQ77gcfdG22HqHUoY47a8HCxDfroL0WaKhZUYIEb4nMIGY3q/ll8GYs/4CHvZ5H1BB4LOYsGXSdH+gA==
*/
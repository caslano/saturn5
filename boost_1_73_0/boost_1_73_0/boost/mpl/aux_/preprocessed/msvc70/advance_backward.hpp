
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
dGVyL3Rlc3RzL2RhdGEvdGVzdDM5N1VUBQABtkgkYO3cXXOqOBgH8PvM+B0yPXNmzumsgihWXeoMClVaxCqgbS+2gxABi8BCfP30G6Gt2z17vXvzXPgSkif5BcLtX6Ikp66Tkx6SwniVsJ83ctwnmZf30MiyHosvPFQt5CabNCN5TjwkcZdBElfWfUPfsEmyHcmqeegRJGUkjY7sOtZJ7NMAJyscJ7RKYjfxiIfdJKYkpjjMcb0l1gW8D5yi5WfEoSTDNHBi7JGVs40o3jnRlrAp2HQDe6a/juWn18VMs9RXU3tR8Y96q9Fu/kSS51AHL9l+Ws3bqyPJr3rIvJvZ9qB90NeqP17Le03t6Mo0VZ+fZtEk7BtLoZlriiZqqrjzQvk4VmSetQ+TtS2wz0lTPWMu8w+2MD8ibzM/sqK+O7xbO0N7NzabJ309PmiDQH1Z3KfPi6Y/48W5zh/SZTxvPph9uhRmq5dGmroFYrwdr5+344XqI1sNpvppuh0fm6Juqf5y0Xl7ahin5aB91Nc+Gyj7VqMfLSPDsgbtvb5+2xrC9H1cP3I3+zPgOJnyD2i+uTsSK/GnC2P98tTndXu+fRY6b85CjNl2laUg8i8LkdfnM9Ed2i1tNIvIaLpzRjO6VHL/WQgCNzYiT6nf
*/
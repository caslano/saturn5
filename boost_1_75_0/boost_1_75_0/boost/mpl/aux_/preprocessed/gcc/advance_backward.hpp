
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
7a/Q1Fa8yZiqf0OmR9QwJB8juHUyfGYBT+tue7cE/lF7u/DWUQlEembAcCl6036Vek1VGL698AVPP8qDldZ20+E7RpDavla2Hdqhcw5rvsQRBpn7hiybTbRsBuQLpuw22WDUFsYVIBbwquJ6IHl8XPygoJ49UvGHJrIf7iIcJ6W7kAWxeivCkRHj7sttUT450pbia2UO5gJR9KxvSb5E1YdKpB5x9nm6qnJ9F+4Qc3Z+r3n7zIyVYZJdJQ6qXpq6qLNdFL/XfB+D87spy/KKwqXmEN4F8+YIhEWJCMZvKvOufuH5xUfjtDEOxHTwANxreaoo2soAvUZSulsKXz7CZKsPvV160k+z9IEeddRln/dVEHqAyMSFMRVG8mcn8NMtCZjqkWZjoyHOcDU66fbuq2LuZpjPwpnV22geqdVlgvqyTwuY60pBdmXapwUMx4R5BQse8Sg2ker7s8HReM3pl8UXzTHETHIJGkKe82p+2fmlTYsqP7m/EdndrbZ7VKlDZBEdWUQVAt4mPFA7Wh9DdXvhQE5A9gXcQPHgv1T1B2mRYl9R2rUoITfQI6R0tw6dbSavKL9aSOav4KyraKna3qoRETVLr79yBqYYlzl/LdQ5YcsusPf4mV7Xpw+aNf/lwpbOntLF5YbTGDWQGnI70DKA65VggNwji0T/UX3lUd58YIwk5UIjjAmsZLzUWy3T+wOhQ/yzEHTWB0/G
*/
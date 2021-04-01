
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
QPmafbAR/CaUlfxTbD7eXi4jt4v6nZxUdLwSjVpMgCRwEdA03T5nfCLAQrqtiKCflSPkLXgUA1lUbukRyNnpXwCkQMnw+6y7dBkwwBlN4SbaXL0bXxMqfQ2O4nZNSpx5ftFUQ1HGeBj/WsyBNh6XIWQobJdxRloA5l+kE6wrqLt/EqLPW0Mo3+/J+xHvdTpxi19IyDeUa56587qzy0InYDXoI83X10GUujao7ke+K3bGq0mm9WDmGBqZXgJmPj4iAH3cfFET/2XC0Odzmm3CYGy+IEZ5Es+iBQbDG3KEYRXk/b0KZsebrBvuDN5B5D1cWHX3ww4SglCbeW8YrEd8BpWwCSQTYCXO4UcWxv4cX9ezfd0JYSIq2JMQx2l+d0HxyFbkBHImLZj2lqbLG2HcdcIw0wm5w0XXE9nQQTqpmmwRYjG2Ij7aeci8HGAyFBLklbvQPslDg70RCOs522TXCldUcQ8uGGHocAovgpKZA/9k5FjHwD9WUeXys3tH3zCNRRSCi4fJVBFw+G2sl/P6Qt0fPpiG31c+dXMcxlCQTZYYfhPl972sJIUsMQ==
*/
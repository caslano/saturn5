
// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "quote.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template< typename T, bool has_type_ >
struct quote_impl

{
    typedef typename T::type type;
};

template< typename T >
struct quote_impl< T,false >
{
    typedef T type;
};

template<
      template< typename P1 > class F
    , typename Tag = void_
    >
struct quote1
{
    template< typename U1 > struct apply

    {
        typedef typename quote_impl<
              F<U1>
            , aux::has_type< F<U1> >::value
            >::type type;
    };
};

template<
      template< typename P1, typename P2 > class F
    , typename Tag = void_
    >
struct quote2
{
    template< typename U1, typename U2 > struct apply

    {
        typedef typename quote_impl<
              F< U1,U2 >
            , aux::has_type< F< U1,U2 > >::value
            >::type type;
    };
};

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename Tag = void_
    >
struct quote3
{
    template< typename U1, typename U2, typename U3 > struct apply

    {
        typedef typename quote_impl<
              F< U1,U2,U3 >
            , aux::has_type< F< U1,U2,U3 > >::value
            >::type type;
    };
};

template<
      template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename Tag = void_
    >
struct quote4
{
    template<
          typename U1, typename U2, typename U3, typename U4
        >
    struct apply

    {
        typedef typename quote_impl<
              F< U1,U2,U3,U4 >
            , aux::has_type< F< U1,U2,U3,U4 > >::value
            >::type type;
    };
};

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5
        >
      class F
    , typename Tag = void_
    >
struct quote5
{
    template<
          typename U1, typename U2, typename U3, typename U4
        , typename U5
        >
    struct apply

    {
        typedef typename quote_impl<
              F< U1,U2,U3,U4,U5 >
            , aux::has_type< F< U1,U2,U3,U4,U5 > >::value
            >::type type;
    };
};

}}


/* quote.hpp
K2EuPn6k49E1P4lrjj0P+XtcHIO4Mb9vSEXkuvD8LGL4ytc2XJF+G2PjBJ2zwZa2zej3fc7ItwMAAAAAAAAAAAAAAAAAAAAAAIBvQaUpfxbaS2htfVjxf1XqEjp4cfPbk5jYXb66Vs2e7nf7h83fhG7LUrr4+UbdDKX3tLpk3Gn1lYanLhUD/wFQSwMECgAAAAgALWdKUu1C0xyAAwAAdgUAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMjBVVAUAAbZIJGBlVG1vqkgU/j6J/2HSmyZ7m1UQpassNUGgQguoCFj9sBtepoAisDBa8NfvgLZu95IAc+ac57yfw2NUYt8t0QTwcfqekd8e1R9ZEZQToFjWov3AmWwBPzvkBSpLFACeugnx1AX3A/yAK1ScUNEt4wABvkB5UhN+4GIXesTE4/Dprkbl3QSsnk3bFkeVtpNDfSd8qPJYk5a5vHkzk3k8NTxmWKqSyqoyewpiodYlgSZ0Nd/ZDHnPqhwYjkC/2oxTg+Dg1AQ09WfPO3dmn/TV8Kzt9EoVI3m7fsk362Fo0qyj0VXupc7wdTXFHmO+bwd57rdO6Ed9tznqazkEthwttfPyqNdDVrPk0FuP928D4+yJo1rbhURQCK3BNPESw7LE
*/
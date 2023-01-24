
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
PhZjmmaGtglKTZhMwSxOxb7eEtHW8Gyo57pbG5MrzrjNuPFmz2i0/sXgp+RsUjwyZiTlJlVe72zr5LGaAJOyaP+NkPOv4j514SH2NYTiOVqHaUjHR+6lpIoJV6fw5SMHLk3l/d8jMkbzyiHjE+OUi5hV3oXyf/gIBm5A9UU+EmAV5tdhp+V+TqrxUrorNYHvW11VU02osG6j8jRPAdzskKxGIkK6wv0yqz/5FSpRL2piJVVUdyC8uAHFBsr8nmanay3evJQ3ihvGW/WEpWrLxs2/Ui3hfNon10/8AZDitCui0DzTwQZn1muVf6uBpG4frboTNrl/aOi4Y1z0aPo51kRKEU18m1I/23qxTD5Y6/3X8+ofzAUuWJC0+9EvXYHJzX4T1x6qWQ9YIz3pXSnKiRoq2a14f4Ge5TfeJnBckPrBtOMtHj8zdKCc/Z4swW+wf+vncYqT1Gd26FOUpymVUxZm83X5WDnFHRAwyiPxY7WyBKxhUVxkGxJkofg+rdfscjrjolRDOERu34qasw8vCJVz4GlZnt3NsqZ/uCNkweLCqbt13hZ87V9OxP5a7RnZVqf7EDWLKIkud0S2RqclMXjH8AddA+P07afUUacsYYIknStAwfx0EktsnOdWVb/y7Qc0jORo9JY30GRzdRFVFyLlgs0Bi+/KIbIgiN+gRN1s4eaJ2sjocaEcFC9zXbUPz83TydhlClcNKnRd
*/
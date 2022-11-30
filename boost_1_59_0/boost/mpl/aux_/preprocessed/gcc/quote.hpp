
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/quote.hpp" header
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

        : quote_impl<
              F<U1>
            , aux::has_type< F<U1> >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2 > class F
    , typename Tag = void_
    >
struct quote2
{
    template< typename U1, typename U2 > struct apply

        : quote_impl<
              F< U1,U2 >
            , aux::has_type< F< U1,U2 > >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename Tag = void_
    >
struct quote3
{
    template< typename U1, typename U2, typename U3 > struct apply

        : quote_impl<
              F< U1,U2,U3 >
            , aux::has_type< F< U1,U2,U3 > >::value
            >

    {
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

        : quote_impl<
              F< U1,U2,U3,U4 >
            , aux::has_type< F< U1,U2,U3,U4 > >::value
            >

    {
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

        : quote_impl<
              F< U1,U2,U3,U4,U5 >
            , aux::has_type< F< U1,U2,U3,U4,U5 > >::value
            >

    {
    };
};

}}


/* quote.hpp
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
*/
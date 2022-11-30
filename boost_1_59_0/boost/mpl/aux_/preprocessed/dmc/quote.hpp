
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
    : T
{
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
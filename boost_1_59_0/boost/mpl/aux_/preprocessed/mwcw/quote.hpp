
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
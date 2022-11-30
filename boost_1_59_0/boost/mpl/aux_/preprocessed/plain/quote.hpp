
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
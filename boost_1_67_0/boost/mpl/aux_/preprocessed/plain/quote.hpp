
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
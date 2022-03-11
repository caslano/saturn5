
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
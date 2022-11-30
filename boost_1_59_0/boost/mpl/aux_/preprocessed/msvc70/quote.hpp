
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/quote.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {
template< bool > struct quote_impl
{
    template< typename T > struct result_
        : T
    {
    };
};

template<> struct quote_impl<false>
{
    template< typename T > struct result_
    {
        typedef T type;
    };
};

template<
      template< typename P1 > class F
    , typename Tag = void_
    >
struct quote1
{
    template< typename U1 > struct apply

        : quote_impl< aux::has_type< F<U1> >::value >
            ::template result_< F<U1> >

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

        : quote_impl< aux::has_type< F< U1,U2 > >::value >
            ::template result_< F< U1,U2 > >

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

        : quote_impl< aux::has_type< F< U1,U2,U3 > >::value >
            ::template result_< F< U1,U2,U3 > >

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

        : quote_impl< aux::has_type< F< U1,U2,U3,U4 > >::value >
            ::template result_< F< U1,U2,U3,U4 > >

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

        : quote_impl< aux::has_type< F< U1,U2,U3,U4,U5 > >::value >
            ::template result_< F< U1,U2,U3,U4,U5 > >

    {
    };
};

}}


/* quote.hpp
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
*/
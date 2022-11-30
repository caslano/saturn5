
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
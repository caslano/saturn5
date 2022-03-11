
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
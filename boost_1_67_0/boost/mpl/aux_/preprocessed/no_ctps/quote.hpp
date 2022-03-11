
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
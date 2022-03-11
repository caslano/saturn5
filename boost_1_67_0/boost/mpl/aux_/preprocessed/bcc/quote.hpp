
// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "quote.hpp" header
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

    {
        typedef typename quote_impl<
              F<U1>
            , aux::has_type< F<U1> >::value
            >::type type;
    };
};

template<
      template< typename P1, typename P2 > class F
    , typename Tag = void_
    >
struct quote2
{
    template< typename U1, typename U2 > struct apply

    {
        typedef typename quote_impl<
              F< U1,U2 >
            , aux::has_type< F< U1,U2 > >::value
            >::type type;
    };
};

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename Tag = void_
    >
struct quote3
{
    template< typename U1, typename U2, typename U3 > struct apply

    {
        typedef typename quote_impl<
              F< U1,U2,U3 >
            , aux::has_type< F< U1,U2,U3 > >::value
            >::type type;
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

    {
        typedef typename quote_impl<
              F< U1,U2,U3,U4 >
            , aux::has_type< F< U1,U2,U3,U4 > >::value
            >::type type;
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

    {
        typedef typename quote_impl<
              F< U1,U2,U3,U4,U5 >
            , aux::has_type< F< U1,U2,U3,U4,U5 > >::value
            >::type type;
    };
};

}}


/* quote.hpp
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
*/
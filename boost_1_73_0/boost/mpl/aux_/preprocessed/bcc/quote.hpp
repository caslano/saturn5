
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
57wLKIwPWcipbw+3QN5EPDSrsMeW58S09LA02e90tg+W97yprXQdZoUyGN7BmbcOVPZDeumkb2fcrjzp10of3fdi0g+XfrRxnyoj0fdbhHxG66KYaTab5lSJlcnoNCsLmCaSfqS0G8RQw68+lpunFSFPA3PfqZlvHqVKZj8rXGVfiH0XRqif86VvE9KPmxPSh/dg5Nad+dNPk/4ECe2n0WVYHJYhb30USd9O2ikisgzN50rP
*/
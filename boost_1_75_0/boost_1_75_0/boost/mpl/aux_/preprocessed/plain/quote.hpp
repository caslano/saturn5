
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
hF+nL5ZMoGbFGrKX06QstyI94xsG3vi2jWqfQawV7L52MBOeTujECK6F465EUl1imuEkBasB6XImJIgOwp5abi5H3jRorZzgC1FyRjMQAL/l8p+ikf/9HUANjyZSrrLAFpzLuy3viuKZSNaOstkYOydW1Uj5CRxisCx899dDLYSqyJxLoo8rmJKX4YXlr6JZ93CqwpZZVDhZF0rHhQ9eB4Am/2ZT6v3zO8Nf1eO751yGRcpRrY8NNOH+VL7zh5ISz5KPdo+Cp3zGeHXM8ao10To3QzQHYBbirUttU6rLRZK0mJ60qB5vijsjou+GWnUQaQ2Fi84oTP/CndompuyVoh3GmqiSR02Qp8KAaUpUH5X65QoBk9FTY9RitrkryN+/R9VlCcIcNxpr5zq2ppSl2DCkt5xWLlv0qMshWJYmB7g6whzrRnzOZFZinl+wbrH905jZhK2X1ZydVRRbiWVVI2osTXH3l4P4+l8Vi56qBTxKE5Vk3MULFfxN0o2OVYSf5kJWZM+UMj5f3nlZU51dVVY1/JycqbED/HkwRyBM0q8zrmWHsHi7TfXGEYDzojUEgMLT2Cu2dRV2AMksce23eB5MeIKJPWxKJndRnt2JnAKX4XP5L0/594dVPUmnaRzfA6z6NQ/tvaQMHi5rgl9AsW6+rMkAREWCkvpDQKdbye6+5DN6JAIRXhNdL3TvRnRmrN7eFX0rlJ4SDDjU
*/
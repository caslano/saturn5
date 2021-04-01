
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
b3oDvYfNPhHlF9q3VN8jE1ONTYR41R8kkMfgjE5aq2qwcBKcjEloAlQQV/4C7Zv4EJxKGkBM744CtpHrqiRjlK3UlHFEIiHwcKZUxU08L6aX+oTQFRNAWvHjnlyEIUZq0/fh7IlbZFKXiZA0nKyJ89F4tuacw/JousH7+fSR4vucZY8Qa8S/KpLKDYNen8bSzuq66mFY4xnuo0eRRDChHSXd1FyRlkquDUVJmjnUGdQ6UrYXbI4j1bCXKv5D69P0nfB4ynXhNepMevl/rpIma/RaLTql66nwJWRolamcS2Lgy4D7XA0E7Z2LrGY/XoqsI2sNfcJg4xqgAqeCquK9tpGUKpnWuqSvt3viLJ8NZ7sV7r/t0m36tJkfl2lOenl3zDPmdtkz9Pdv6Mbbm9SXRObhlYdKWr3OUVwMlw8k2U9dkEYkCd5srjhxkTyas58iebX3l/MGPWwxWtKQhE86gN/fhvDjmJ0R3kfI3zv3SQgEtX1Aderwy3Rw/XsxEPkakfMDnIxv0iPCIrDG29zCCghaHD3bgVFyq4VnUL3m/ZmhTdfzqDijUMlb3Q==
*/
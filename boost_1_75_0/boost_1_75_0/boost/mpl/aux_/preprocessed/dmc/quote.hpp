
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
MO8356OXPgYGtqxRCFj+tu9rct+9GNZr0Phd+1EzLBp2033eQAy5c492Lu+4daZ5oSg0hNojZLxNbx+K9wq5LAnfg7/uQfpImEygHSf/LHPdSnwVhfxPdR39fy1z5f/7rG5pbevuYen2r2uCf4DmUh4sL0deYmAQDvurL/ocCvUnTkkfIvJx4V1TeCb4RWle9HE6Im9OnCMqpOi85vk6o6ZIlq3WyXO5HEqthWh8ZiPXtVqnrWWtp8Itp61ax5O6jfWHxgBDx6WTJ++ZDr6UxCHaM4qHu5OXwKCnXH/jviOBI2/Q1B1IKehldXwyWAJxnnii+KlJWjNRg4F7QlPiuHAbDLJq0vZ8fDqhSdtGJG7Y0HQcDdh3uJPY4TfFbiDkJ+eH58fml38iy1RQCz755Nin0pdjyyUNj+qWDKAeM1/kcGEh5FUqDvCfbkrYVOP8ugzQmH7oCNTAE0EzjumjJGVcSa/qDLAroG2B/5H8KOjSSEI6bKH0Q4JRNrxQDBAb5D8j5/OIYE1cZUjyvLh+2DmcbxmSNJmbQ59I5aN0LUjE9H4W0jRe1Nd6qHT1ESwPyzxJ0IcOA0kcX1bqtvawXp307iKdbwg9VBFefEGEGO8s3wlIEY9Xcp9MeHghxemAhT1k/Hf258Ml9sfNPYETg9MsrSf3qzc1Vw6M2zuoD2rcJtQ+8tx9qUhswT/mqju4PthjMUphlBJ2SgoJ
*/
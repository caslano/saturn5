
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
tTIqhsf/6kCXN4FhySjBxQhltFDome3wScdtVuOoqvhQkM6sJwsCWEN0LkcP/RtzDQoDRzbljBzQvHa2fMj6sl+CvxNt2TOahdPs+bHDXRqEwTTwE5z2eqhGDphzQQxqgs7F9WKsTlnorO3bwkqVM3JP+tgz/I1/ta+zdhal2+h3oCRVlq5QcFItRkTUE1+GViUIEXtbazRvsij4l3k3IFR+Qr8ygIT2hsHuaTV+EmsDwbWwa43QfH0fkHWK4GiQhVKf1KVw+b/F/hUwseIB1zxFtALOUVgf1dHI4+FRNl9oZicAKkGUeh5YyAOJR5Rzol/YtgNG+NDgAVvSiGxcaZM6cfxfCc5kTR25cnKpGRZp+Pgbg5faipN00GWtw6u53Kr415UBd92MspqQ6/1pJvw5yU6dwpgsx4S1qBXDZJW3SgGSFQ8dXkOGxo6z6zveHKI8ENtaaXZZ8lkhN7dLjDJGBQMyZbwTdeNg+hBNLpewX7JbZc2rNG2RfQ81iJTQhHQJM1BWf6DvQgxD0wiLFJptfpOKFRhK5+yU9IR5T9MimHSq5WslWbltZw==
*/
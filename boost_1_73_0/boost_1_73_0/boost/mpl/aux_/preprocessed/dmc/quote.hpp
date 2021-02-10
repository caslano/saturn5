
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
6sE1Q0ELGNlmt/TrO5jdbKVICDzMmzfvjSdxaJ2SFlOW1F2p6bPFca9NYVO2zPN15t/wcJfPh8/S1grk4CqW8BM04XM1O2fnkKHZoQltXSBLDPbNSIBCOjlT8vhjDJdRBKuvYPdWNdoi+yIdCsgH/ADRNTzpHSHiCOIrcXUtCPvwPWczr4BJc2h9wEu5RXarO4edC/Oxxyn9x/HKtQ27H7puDCuUhYARLT2MlM5KEn5Q5iXfNvVEMEtWPiBIidINBslfln2jilOczO1TVjnXW0odY0g62eJhdtPYYF+7CgbKg+wK6KW108wIyGckJEq3LeVSFm4hHGCyJHyBJxecL5arLH9ci4VnXa+ec/4piqnrWyUdD6K9nQ2auhxhcgqydETlKvRzg0pa+IXYwZmttDtjyc5jiaI32mmlm5RNsqcOcLyugC21dQLeCwnYDe2CNvVf6WrdicOCvLb35jXvY3W5GQP2QmbCm9+kT4AaTMMXm7vn7HH1RNVKYU+/L/hFwALycVJxWJkfdUflDsqhaeCYBa+6VlNPKIa2hwoN/vzvdt9s8dOK/wNQSwMECgAAAAgALWdKUkXMPoB/AQAA4AIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzMDEwVVQFAAG2
*/
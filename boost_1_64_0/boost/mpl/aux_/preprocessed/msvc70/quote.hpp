
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
jqPHyloF5ycsLW4V+fiykXx/Bk0Q1k20v8toLAb9p92ZYpnt2EaVNLeO/62fs+23i+qydmp7p0vucP1xL9mPjhHO6ZkTtyWWtJI4ohDnD9rYysvBykI0UaMaT9knIPqwSYjMSK3ZucPT4mlfyKXITq10BS3aA0qcjE2WgY4dSNlWDlp+VzoE3Xkghscquz+bA34PvVj1gzESivZD4AhjVC8FLQyolzM3rsJ/PGFr8E2dH98e0rcz5huPBRHEWExiS9kocpE2yUsAp4MqUq5CJadk4UJzWE+Z0WTlSBnPGcEmfv+V0B++IJ7xRxUv/OGkICwuBwuzGrGN7kJrQGh3QHj6Y1taIYxKj4Qg1asz+KPa7oO2DPorvG/GKBGAScbDs63jJ3NGg++Byw4byCwwqi76Z9Ad6Wd6PblVeMHUD1LmEiE4CoJ0aUfhjhq+y9lCeSTIapDIr2QjnWZcVwklaEYd+lG90tKdAt43xBP8olTe+JGJCBZtpSoGqECPU1eystmYTgoPy08yZ1/CL6ZDs3DEq/uaJEa5WuvBNE0y0tg4XYkpftkjTT22gQ==
*/
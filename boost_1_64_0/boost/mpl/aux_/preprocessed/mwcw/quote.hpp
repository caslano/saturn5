
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
RFKgdXsNt74t2PtBKh36varfsZuRtg589ax7U5xjOoyBWbAPnApPhdPgMJit+OF8WAAL4CXwYng9LFR8qws+oXjm9+BM+A/FNXfE9mw4GM6B+fASWAQvhUvg5XANvAK+AovhJ3Ae/BpeCb+DV8Hv4XyLDsp16Lep7tFWPaNgrup5req5EMYqzrkDXAxPVpxzCrwBDlW881mwBJ6reOcLFO+cBm+CmYp79r5nYp7ihmXfXC/1ocbYP4ZRWocUC/8KE2AlPA5+4lC8dyP9vtTvTspjfNsdZ+7eftbY+y/wWPgr7Km4/5MV7z/GApwIG8M8eAicCZvCubAZvAoeBhfAKHgfbAHXwd8rLvkIxetHww9hS1gJYxS33xruhrHwUHyMg1GwLWwJ42EbeBTsADvALrATTISdYW/YBfaD3eBQ2B2eCU+AY2EPOAH2hPNhL8X9nwjvhCfBJ2FfuAH2g6/C/vAteDJ8Fw6An8JT4bdwIPwBngF/hsOhta5lBIyDI2FHeCZMgqNgHzgangTHwCEwFY6EY+HZcBwcp7jpSxUnfZXipBcpTvoGeIF3nYB+24J49SNzncB09aNc2Brmw3awAHrfxy79OOmbcz1TpT9N/S/b0EuVXqyNXrr0psAYmGHoOaXX3EavUHpFsBl0Sa8CKZbes7ovmetxN6h/Pyd75bAHfAH2hy/CQrgRLoGb4Br4EnwFvgw/g5vhTviK5pJe1RzSa7A9fB32g2/Ac+CbcAGsgLfCrbAUvg0fgNvgI/BduBa+B5+G21WvyUjZtb73ocPgeNXrUdWrTPV6XHNnT8B+cC0cCZ+E4+BT8N/snQl4XFMUx6fVyqCllNqCIGipStsgrS20qK4ppUU1SZO0QZbRpm1oaVAEQVRRBEVRFLGnFEHtW3xqL2KvpQRFUcvvTf5vcmcybzLZpv149/vO98t7M+e8e++8eZl7zr3njodVMBsuCawD0287uIuuY85fn6F+L9b1TtfnfYaeNzNlJw09n+ys1eewh+XngVaZLf2zVd9ztc5iDtwVnqfn1vnwBI/2O4Kl8AJ4IZwHL4I3wDJ4J7wEVsFL4VvwMvgRLIdfwcthJ+owF3aFV8AecJ7WI14J94JXwWQ4Hw6B18CJ8FpYAK+DZ8AKeC68Hs6FN8D58EZ4K1wAb4c3wUp4C1wCF8LH4W1al3g7/Awugt/CO+DP8C64Bi4OfD76rQh3DPP5jNbnczTcFB4Dt4BjdD8cC0s6NqwvqP0zjg8o0p5D625v9bbaUz1k7n/EfdQT6IsIe6kb+6hDxGEOf9R7p68v+6a3Zs/0FPpsHFKMzEeqkBWI5y/myCNDkFykFFmEvPCXG09yi1vc4ha3uMUtbvk/lvaf/59enDUxKz3bmgHQyvn//v3/t2PcVj8HoN6wEiNa8f387viMFMdI7NA4BnbS3ozhG+L72TlTi9Mx0aR/34wdVMtuJ/lCOsLnqFO3M/12ZdOuVvSxA4fciZo3YMRCFBuZ5lF+Ys2jN3P3X6M41pXIM9hNmxVcN2u1Qn2W++hjWaH1U67J4PpNV/2M3NJ2LGYCfU8FUHHjI//F+Ejnsdb5t+8as/ibxy6I37XuiafKt+wQIc9f+DyRbRsfSUL4vjv6L5Pkp+kr/2W/QF42fZ/1PUcvKC/bYdIbBLvBwdAHh8BZ8ChYCofCK+AwOB8Ol59sBPxLfiLr+XF0Q747fVdpl+pr5rvbT/66/WF3OAD2hgOVV+wAWG7sq30wLLby1PwVF3Uui1A/k296nGcOEuJvahNfk+lnUk6KNvM3Rco3sYD2OPmeHpxu+p6cc0ssQ5RPok18UOSJaJUfqq18UOR8aJUfqtPfcZ4EJPVv178=
*/
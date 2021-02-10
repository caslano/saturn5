
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
c3Rlci90ZXN0cy9kYXRhL3Rlc3Q0OTJVVAUAAbZIJGDVVGFP2zAQ/W4p/+EUhJAQmZPQsdXKKiHGKBvQqgS+p8mliUjtKnaBCPHfd07aUAn2ddqkqPHZ955f3j01MqhNmmgcsaiUuaLXAzZPqs70iI3jeNr+wPQuZhF/O4l418z22B7cYv2ItafLDFlU46pqqCFLTNIx8OBTAKHvw+QX+54YFBCv8Qj8IdyoRzoIfAgGYjAU1HJxHbOOToBV5um24HnygOwqoY1rlZV5idmGJTiGn2tp6YklFIG/ZTmPk4UANwz88LOXpV+84+HgJBwMv7rsNE1xZbxZIheoBcwbuomdKWlQGu8K5cIUAk7sjsTUlEoKSCulse+JmxVafc+GF2ZZsR9rKRuvwIRUNajpYczLlfLIp86HiG98aQ07q0pL0xmWtgW1dJ86YoUxKwJsS4hksqTxxE8KFpWazzGD7Uw0GAVm5+BudqUJwTsIRKlaLhOZjdiBZRWc748nt/HlVOxbiulkFvMXJfGIOF75AXgxHLxUasHzstZmMAyPbKExVTKj6pU6xuDGNBipBNCOS0L7O6K8rBDs1d/cXRJ3xNqlBUDaeagJaNs3qGAH1l9HuG79ETCwpm69a129x7rMG7CGQ5IbrMEU2KYI
*/
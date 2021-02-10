
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
rn4z32++3ZTQky49ZiJtzN7y4wnHwbrKZ2JdFNvpBl9vCyHl4BpCaQ8kUnVSpWouFO9gh+4ZnfRNhSJ12Lcj/65KKsFYXaN+WsUj+njurC7eX8CH83PIv4EfvG6tR/HlYMwoayyrBFjKl7ixhtCQLMYeEyD8Taqmrv0Mui6dR1ptdrm8ulp+kh8BQDBPcAxcRwIGu2mb0GIG09OCBX7CzURN1LP8ZQmpKTucIUEf3YndYWioBt+XGj00hoVqVkKqbdeVpsqEHCBe/DlW/QxVf3+YGIJFotRine+KzTZZhN7b/K5Qy0uQFlr7qDjX5SVjvLbi1yMpT/CArtmPMIVZ7gkdUI0Qdg/q0sMvRAOxry3FIn2etGFAqrgrdLbCVRyS4+jfDDCkMNVwce8sWW3bTPDuQwB92bVIrK2nBP6bJhL3HKK8fmTqBPTBtWrxcHu32+TfI3GtNfb8+UydRSJip5NBql6R1elA/gNQSwMECgAAAAgALWdKUrKcxXzxAQAAJQQAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q1NzBVVAUAAbZIJGCllF1vmzAUhu8t8R8sVb2ZQiGJuirUQ8pCtKGtAQWiaDebqDGrVcCZ7bTqv98xBqIu0qppSCAf/Pqc53wA
*/
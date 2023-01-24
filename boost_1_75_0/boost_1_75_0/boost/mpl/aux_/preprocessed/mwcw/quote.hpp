
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
JubdEHpa866bME9+TKIiisWFyL3dADjpjshoHq+/AMsO0Mz7yTcwMpT+F4o980i4D0yJQm3dXWiaJ3oq1WWROG48rGjWbSpJQCpdF8LXzkmqcMdMW547CHcz/PIefOYc7+R66Xy+cXqN5bK9vkxiv03usL1CtnG1S6C58abCeVO5OVP7lIG0SmzbtqVjFJsIRT3K3LiQs25MITxS/+ThGeX85Rs89BmXYo+lurS7UjvDcbv2YqLgsRNP7Ewp9ycevXf4g2ViYvc9t4m+YQUEu101sYw6zQriNYZN/LM506ANVtxpxpLzZ4Mt8jgsIX+F6fntctejqPn99++w+p+T8pKgF+fbu4ubeEoVAYF7KfQvhnmGgUiV95W/NBbjdrFrhz+sjqRHxcM9vrWVZlJ8MwqB0WgxJF1ocLk7/Sam+CKXm5eHU6EVrkiS7o3Hm/k5wyWjRL/xh8RkB6tLhVacE53uRLD2DhcpiQLTLoSbS2vTOEDry4qvowC6OdJaoH59KRcuqZBZAkMWl8ali9NQxOH+NM3szwhcJaKuIybXj+dJO7bYyWfHseM2dvW132qxaH8Ft58llne5LDlrqa1zTK5cSrTT8xTemU9ecGlWT3fFqupogVwTA17+7LnwrCJivwGTZ7H3ZAd9VPj6xe4+OeuOYPbXVmZfZT72Y3xpuBRaVoUVzbpY74jRmT3+9Qc/PMmThudAryzFbE0V
*/
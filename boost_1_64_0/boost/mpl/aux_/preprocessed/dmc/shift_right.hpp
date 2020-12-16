
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
KnbEJOyEydgF12FX3IDdcR964QfYA49iTzlfEhxk7Es8KuV0xEgp55aybG98ExvhdmyFb6MPZuAw3IHhuBOfxF24Ht/Fzbgb0/E9PISZ0s6nOMh4lnhJ8n8IEy3PmyX/feiC+6UcB7A3HsQRmIVj8TDOxw8wFY/gSvwQ9+MxPI3H8WM8gefxJKr9M86UBxsa9M9sZLlyuAndcLOkIy8Zk1IZq9L+/afBcr0yBGvjUGyBw7AH+uMADMCpOAqjcDSuxDG4FQPxQxwr1yWP4Gkcj2fwMbyJE1H6jWRMSa7FDPqN1jlSLlyPbpiGrfB1bI8bsRNuRi98A/thOg7FLTgG38T5uA3l/kHGiKQuBvcP38l5fBvbYD564g/Snvwo5/EdlOt2Gd+RazGD6/YO7IeHsDN6YRc5LrwwCHtgCPpgLPbHhThAjhNfXIUDcR0Owk04GN/DoXL8DMMj6I//wEC8iWPxB3wE72IQdqRsIeiFk7EPTkN/nI6jcQbOxEicgzNxPsbgcxiLW3A2foBz8AQ+gefwSfwKF6ByHZ2E1XApdsdncAwux0fx7xiJqZiAz+EyfEGu617E13AVbsI1eAhfxqO4Tskf1+NpTMNcJI1ct8k4jTJ+o+11W52K7Hesjy7oiu7YEn2wFU7E1jgF2+BM9MDXsD2+hR1wH3bEw9hJnht0xmvYBW9jdyzAXlifMvRGT+yLfbEfeqM3TsD+GIIDMBR9cSYOwjgcjPPQD5fgEHwZh2Ea+uP7OBwPYgDm4Ci8iOPxe3wU7+BELMRJKO2hjPvId41Be5gs7chT6Ixr0PS+LPrhWpyI6zAU0zAcN2AabsQ3cDNuwXR8D7fgAdyOufg2yveYjNtIm2vwPdZBrqc8sQl2RE/shD2xM/phFwzC7hiBXhiNPXA29sJU7C33x30wHfviduyHO9Eb30Uf3Iv9Ud1uMg7iWYPttlvaufekncvEprgH2+Be7Ib7sDfux0F4AEfhQZyAh3E2fogv4zHchifwIzwp7R99rzKuImWW9krZT/FyHnwk32s56KyUGd3xY+yEF1HJ9zNMwMuYhNdxDd7At/EmnsBbmIPf4Sd4Gz/D7zEP8/ErvCvt1c/4TyxEpZC/YFW8h22Qe25T+1UWB2M5nIDlMRgrSL9BNXwKHXEZVpf+goekv6AmbsdauBed8QjWxg/RDU9hI7yG7tI/0Bh/wmb4kPI8DWtjC2yILbEltkZPbIPdsS32Rg85LtxZR0BTOZ+kPWrsQDlkP6yX+5U0dMbXsCluQA/chANwM/pjOk7GrTgX38TFuA1T8S1cjdvxVdwh11s78TPchYX4Lv6Ku7GGcv2ODTETW+AebIvvoyceRB/MwkH4IUbiMVyEx3E9/gNfwxOYiScxC7PxFJ7C03gaczEH5bqb8R/lusfgujtU7hfDsS5OwUY4FdtgBHbFadgbp2NfnIFDMBIDMAofw2hMxhh8FR/HdzEWL2Ac3sB4zMc5+BPORWV7PYF18Umsj4kozxtlfEeOQYPnjf+S9qos9W6C5bAVVkAfrIh+WAnDsDJOwSo4E6uhacxuTMGH8TV0wk1YAw9hTbneroUnsDaeQxf8HOviDayH36ErKvd7blgBG2JVbIRq/6mMo7jd4P5spOyfUeiGY7A5BmJ/HIsR+AjOx3H4NI7HFHwU1+ME3IyPYTpOxK04CeU6V8ZjNH7P/yd5P+YuOuM9bIW/Yy/8F/bBMlW5HsGy+BiWx9lYAZ/Ayvg0VsF1WBU3YHXcig/hW/gwSn+hjLlIG2DQX+jMcnWwNjZFF2yDdbAj1kUvrIf9sD4OQlccjg0wEBtKeRvjZGyC07A5PoVtMBXb4hrsJOXujG/iKLw=
*/
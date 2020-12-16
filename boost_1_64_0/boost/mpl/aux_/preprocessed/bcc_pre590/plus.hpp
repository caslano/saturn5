
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "plus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct plus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< plus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< plus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct plus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct plus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct plus
    : plus< plus< plus< plus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , plus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct plus< N1,N2,N3,N4,na >

    : plus< plus< plus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct plus< N1,N2,N3,na,na >

    : plus< plus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct plus< N1,N2,na,na,na >
    : plus_impl<
          typename plus_tag<N1>::type
        , typename plus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, plus)

}}

namespace boost { namespace mpl {
template<>
struct plus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  + BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* plus.hpp
9g2AL8F0+DL0wUXwDPgqvAK+Bq+Cb5l2hIvhU/BtU9/wHbgMvgvND88SmAzfh13gB3BP+CHMhR/BfFhj5MFP4PnwU/gw/AzOg1+YcsDlcCH8Cr4Dv4Yfw1r4CfxWz+HyBL3X6X3PPIeDzFy+xh4/yO/oR/kdrdBefj/L/+gX7en3q9Zl/Qa9cDUsg2vgZfB3WAX/VH/gSbD6g1ZwBWwNV8O20OzltwHcEraDA+GGMB9uBI+D7eHlcBP4OEyCT8LN4auwA3wLdoRLYCf4PuwMf4HJcDsTaxD2gFvCXrAb7Ae3hofAVHgo7G7kw+3gKXB7eC3cEV4Hd4a3wl3gHLgrfAH2hAvhbkYf2MfoAXeHX8C+8FvYD/4M+8M1cA/4BxwAN6JdBsJkuBfsBgfBneHesA8cDAfDfeAwuB/MgmnwMDgkuMejeUeMKi4h73ZRxRusa+w8xfPr8U2rqGL6xTIf3dz+XnFfr+b19cqqjsf1c4vrN6M67uP1T/DxSvsGPUlTSZWkKtKSb+Jz7fEjfsSP+BE/4kf8iB/xI378W48WWv/va871/xsx8b1gjPG7PiA9I33MkFHeseOGZo1JTw8uA2jYJyBlrDkvY8jB6W67BFj+/w/YYgCWu/j/f9HBQ3zzgO0sVKAxwTXpX1BvO1vWIXyfwNqECD7/rvJiiznoGRs5Ft8oF1//w41/grtc3NOblmvff+A82Sn219rzofBI8p9t5R/WILkF+bmTVLaUKOrySKRM1ef2cCoN5csN2qZNPZV5grbsVM73Fcv+HLRtW/4M1EU2+t5j5vSMfrCDbN7vI3SiD28EnWsqK4tkPrdfKpu27Oi/Gxn5QXt0fd7GvmDiudxef75s8W90JG/5q9vXgSyTf8Fqj1V3Kz1W3aV92EjdeYc1+Kv3X8f6W15ff6qHpSH1oDpWnVrnLDJ+KXz2W6e41vN06qGGst1v9goIlCXoW3BaoO7UXvJTKPBZ1xVwzVLSeNM+HzrrMLU150nPOskzDg9Ov4DgfZndJvz5Ptrc9x+51m3Ma0+ox7BnvLpNhHib7s9CTOtPhjfyjPdpG/6MH2OeQfeyRr0Gpd7noZPi79XoPl1KGk/+863880q8xgXLl1Oc7zXdf3lZTqGv3G+VrV0U/lindgzf7/Is6recNiEbh0/WhL/YOxc4qaY4jm829NRW2wPFSt5FUirP7YWUWj2IYnbb3Wq1j7EP8l6EvBchhEUI0XpvSKtCKBYh7/UOi0UIeXzPzG9m7p25szOz1RJzP05fd/bM+f/Pueeee+ec//9/3JzbbbI83+nM/5tMRovQfhnY646x2VNusC3FCtVxgup4LOk39Kp6x29jFtyOGyW+STR1M/Xw3re0boLdRmmIGnimrv2FpElcm5oPPXrnZ7qy8mPp19Z7vZXOJ2UU0V52uWsl9yq11+WkLOSW1fjlomvkPuCTa8YBviG55lxyLdfO3dT7GftDettFn/E9PvLacm39kXfc6N/Rrm+rFl6hXfSc6gyNvmkf+fTNzsvIyfXomxSlvtl5ufXqy4W16bvW8llGseKi6DPKIpvGt8BnZPPWq0T1ekk2axcFna+21Nucd/84yMbtY+d2Wad2eVHX8Tldx6qPfe2SQ6+MZi/LQLvwjbDtskZjudpFbaXxvKComCHd8d6t0/fyMoqm6Xt6Lni/Z2ljvuctn7Jsda1o6VX4NPWBEjjZ1PUTX13zMoozp0bdB/RcD322WvQoDHpmeSWQxzIeFZVMCqqz/Auld5mC9FSbayRONeP7Zza9XUW8QedmR467tA3PFJAw9nPzfa89Ym/v/3cfMbK/53w7/3k/z/kW/vP9PedfIdt73tdz/pr/vE8=
*/
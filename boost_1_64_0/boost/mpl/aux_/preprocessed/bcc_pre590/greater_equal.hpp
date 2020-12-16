
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal

    : greater_equal_impl<
          typename greater_equal_tag<N1>::type
        , typename greater_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater_equal.hpp
gXhOFG3YYx+obkDlahhQPXsM2AJsHFB9e2yA61lwpOzHgheBGJtNvzoxoPOok8ASmXeDkueTA9r+Tg1Qr4kAPAe4je28s+g1tvPl3D+5Gmxg/HWpPKvox+tm7kvdAvaTfsB9sNXcl7o9QeW5I0HlWZug8twJzhI9mKDj07oE7Q/3JGh53Zug5XVfgu4HrwdflX4C7pJ+kqDz4gfAz6WfJGj/fUj2ecBNYBvRp2BX6TdgsvQPcJD0D3CU9I8E7Q9bwULpHwk6DjyXoHp3W4L2j+dBeW73YoLO+14C10q/SNB+8jIoumFHgvaXVxO0v/wpQfc73gA/kXl6gu5n7Aabgn8BT5b2L+seaf9gL2n/4FBp/wmqx8ukHEWfg5Ol/SeoPv8InC76PEH7y2cil7R/8HHR5yIP+CXXTyh7nsME2e5qgzlsd2nU6xkhfW6UCYrenxDSep8Y0uc0WSFth5NCWs85XE/lcj2Vx3V+QUjH/Skhe92ZeEv0deeLbPcvsd3/MaDrtpfZ3ncEdJ7xCtuv6PBSxvcJxynRx4cY37XcR1sV0P3/mwLav28Be0h7BUdIOw1ov14D5kt75T7aWnCJtFPwWmmf4L3SPsGt0j4Duk5bH9DxZiP4D9E1Ad3HfBBsLO0RbCftEewHbgYHi/4G82S8l/4pehxcJO0UvE3aaUDb2VPgXeDTkq60U/BNaacB3UfbBvJ5Ec80mnKIeF50RkDX4WfKvh6Iubup3zb8PeYtPFeIMZr6QMbvFdQHHVie5wS4D8Z9yfO4L5nMfcnu3JfswX3JnuB8sA/3H/sFdL+kf4B+DiU/4CBwNzg0oP4Oh3F/ciT3J0cFdDy8EPwKHA1+A17Mch8b0HnieLA+ZE4P6D5yRkD1QCbYE5zE/crJ4HQwB5wJ5rIepgR0HTw1oOvgQvBhsAh8DCwBXwIvEXnAGaCF8roUDIEzAzoOXgb+Drw8oONhKdgKnAN2BOeCA8B54BjwCnAsOB+cAC4GC8ClAe3vy0A+t+DZP/zW47lFM45rJ4OnyD5LUMePU2V+ALYAe8k+S1D7bcug7jO14jzlDLBU2knQTq+c6c33SO8yjhOzE7SfzeHzi7ncZ5+XoPPeK7iPNT9B28UCPp9YmKD7IYtAPrfkGTyznx/x3PIA95O+BUPgd879If6ut8f+UB+/ytkXbCjt0K/z1v5+fV58vl/3nwbw+e5Av5bXYO57DfHbzwfq8KxYN4/nA8OZzkimM4rpXODX8knxqx690K/7lKP9+nzlIr9d3uMY/1yP8k5l/BO4r5Ll1/E4GxQZJoFy72Q/9bJfnwflgTPAfL+OvwV+h58/npepy3HC6b/vfKefP97XsJr7hlQRX5rjvgLed3g195XGGN/qCPm879saw33rEMp438+sh3rgzbyvF/tZP56z6A8eJ+UQ1ONsA8D+0o64Lh4ETpD2BOaKnguqXhwGLpZ2w3XBCM4fR4Hbpd2A70m7AQ9IuwEPSnsBf5B2IfPwkFWlX8QO2FwbgVCEsBJhM8JuhIMIXXF/41L4CEAYgJCFMA9hLcI2hDIEa7b6Xkycjfvl3whFCCsR1iPAz6Knb4dts93+HXbLd4Tmc2xfD13nqL+HFDAHYR5Che+HdXPC/T8g4Nr+Qcano8sPxAFcrzMXPhYQhiAcwN/H4XoW/l2CMHMw4gFrdaUfSPqL2IhrOxG2DVa/kHvnuv1H1JqHfCMkIWQgzEPohOtrwa0IZQjh/iXK59k+JhpfgTwiWOJnEmxOnxM5Vxi/E2bTrgOurQN3IASH4r5zcd9Q/F1+N199Uw7A9wbz1TdFh/lu/xQj8H09aHVTPxU583EdQf1V4G/4dyv6tdwxH/c=
*/
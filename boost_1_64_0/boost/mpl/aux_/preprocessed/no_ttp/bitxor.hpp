
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitxor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitxor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitxor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitxor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitxor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_
    : bitxor_< bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitxor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitxor_< N1,N2,N3,N4,na >

    : bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitxor_< N1,N2,N3,na,na >

    : bitxor_< bitxor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitxor_< N1,N2,na,na,na >
    : bitxor_impl<
          typename bitxor_tag<N1>::type
        , typename bitxor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitxor_)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct bitxor_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 ^ n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::bitxor_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* bitxor.hpp
/em1Mjgq/ekvSRlcxAdYZv/sEu8ne6REl64McnJKVwaG/hLafWXr/XZEF3u9XJysysXZqlzyJQ/UPj8FVmVw3lAGVveppZ+VVZlYl52k9aJ1/hvKM318YiqwPb2eZKbHxpgW5KOUy98fN5SLob/FdOkr/4WMIXMaK7NM7pM2ysXck5HDLC02ne1b9LYo5XMrKfNLV1Yl9rcI198fZ6j/dz1mjM+vTLV6PiXL6vjRxuK3ynNjH66MCakW5T1VxkI/Qb0OqEAamJ44j3011AM2Zdpx8t9UJp/OtXwWpdI8y2dV6s6XaYs+DPd+795234b/3D39/1QfCdv3+kvqO3HvfT9s9y358/owvGfqw7Bw1shvP56cutB+eFWP3rNeKi65j4fpXm05aeek/SviH9349w20U5R7BLfQEctJXwR7bIwV0A8rYi+sjMPxfhyLVTAeq+I0rIYrsDquxZr4MtbC41gbP8Q6+Ck+hGfRCYuwLt5CZ+l70Ag7oAsGoyuGYjNMx+Y4FVthNrbGBdgGl2FbXI0d8AV0w93ojofRA09iRzyNnvgleuM17IS30AfrkJe+6I6d0Ru7oh92wzD0x0jsgXHYE+dgL5yLvXED9sF92BcPYAC+g/3xMgbiFRyA5Si3IGyAA7ERDsfuOAJ74CgMwDAMwTEYgWMxGsPV3zDLqW0ubbHUhwF2yr0AOVFLfZiNjjgH6+M8bIfzMQCfwoG4CCNxCcbjUpyAyzAHl+NCXInr8GncgmvxIK7D8/g8/hM34i+4CWvKPcc6+Dd0xhexNW5FN9yGnfBl7IW5GIjbcRTuwAR8BSfjTpyBu3Am7sHncC++gK/hXnwd38d9+Au+gdfxTXyAvHoLW+Pb6I6HcAgexlF4BDPwHZyCx/BRPI6L8V18Bk/gGnwPd+D7+Dp+gEcwD7/CD/ECfoy/4CdYh/L7FBviKfTFz7Abfo698QyOwLMYjl9gJH6JkzEfs/Ec5uB5fB6/wU34HW7F73EP/oAH8RIexcv4PhbgabyCF/AqXsSfkH/Tl0muKeRao0g55pTyRuXTUeqdJzqiN9ZHX3TBLtgc/dATu2Jn7IY9sAeOwV6YiL0xC/vgE9gXV2A/3IQBuBX7Yy4OwHcxCPNwIObjIBk7bDBWwmB0wCHohkPRC4dhBIZgLA7HbByBc3AkrsVQqW+j8ACOxmM4Bi/iWPwRw7EC+RSJlTAKG2EMumIcBmI8pmECZmAiTsdxuAzH4wpMwd2YinsxDd/CTHwXJ+GnOBlPYxbGYNHuyqbxvwL2VC773bzsd/M/7XfzjYP5vZtQWPa7dtmn7FP2KfuUfco+ZZ+yT9mn7FP2KfuUfco+/1Wff8f4f4w0kfFnjf83w9FOe6a9rfzOqEyUJ1SXMWtyUyzucyZETooN5/ZmNNvJzIhVknP3d62XNF5NoLz79qj8tl5JxgAsj1WUdzhbxj0hJTkjPmVCbNoUec5biTwxNWmKXSnHljuUXroxgdQx1WoZ7qumR0cmRcp6jlb3ym3dWy2wGhvwkkxPdbe77d6r3OdmWtLC0+tyr1e7fz6ZO8lgMTZNoixzQ5aZEJk+Hizuq0/1sBp7kPhN/RAmWt5bXahOW/VLCC5vzsQHpV7UJrRhmfwMY9lYVYlSvAv8TuP2SD5ajKt3Uh6UT5b78OOwJemwy7R1H540SJ1wvEud6DX5j9cJ6RehP5Mv9aG54Zn8WtI3wtdVXS/dtJ7LXcadKTQ+ty9lr6QlMjrafL9dptX6UmB9T56y7TFJnvWXsh4v0xtl+rLV3+tMVv9u+e5uNxnH7gn+WBVnoQP1q0aWqQzi4yiAgaYhOks3BtzsKaXLe+M4EjVQ6rGW78bjykk=
*/
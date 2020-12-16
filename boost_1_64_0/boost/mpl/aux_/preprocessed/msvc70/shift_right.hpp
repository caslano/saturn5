
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct shift_right_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct shift_right_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_right_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right
    : aux::msvc_eti_base< typename apply_wrap2<
          shift_right_impl<
              typename shift_right_tag<N1>::type
            , typename shift_right_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, typename Shift, T n, Shift s >
struct shift_right_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n >> s));
    typedef integral_c< T,value > type;
};

}

template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply
        : aux::shift_right_wknd<
              typename N::value_type
            , typename S::value_type
            , N::value
            , S::value
            >::type

    {
    };
};

}}

/* shift_right.hpp
jS9jG1yIbfFtbIcnsD2eRje8ju5YhHV3QmfsjB3wReyOHtgbu+Iw7IZB2B0jsCdGYy9MQC/cg71xP/bBj9EbM7A/llDe1Yd1cKBsn8HYCn3QDX1lO/nhKvTHdRiAtzEQC1J+QdgHR+JADMYtOAq34Wg8gqH4OYZL//cbOmnLlDbOJKxIvEQk8GyfcTt8jU0wHXviZQzCKzgV72AC3sUpLOwXXIv3cDLpvI+r8VdU6su/cBX+hhn4O5amfjzAYPwDD+FD5Npc9yc2RR3pnlcI8CssiMr7HGyUz9EW07EQNiM/hTEWnXCvciwIzf07/NqE5l+fa2+WFUyMIe4gphEfEGuH2em6EyOJccS9xDTir8Ty4Xa6FuFan2staEELWtCCFrTw9IPtk+//75+f7/8/oRr/P62A3IfHcvgbcZ3Sv6mruj8Lq1f1Q37cd089iXcBJJBWfz//rP4NG1xk7BmT/iFRIQHjAg39ehy7kS/5njLdx2x6lmpa3R+zqdwPHS3lNAw3MQ/FabWcjKOjSB+Rv7CsLL6nS1U+6v4hm1Xld960/Iz9qsi3vY2xTeh69+z+B+cs9J9e2N20r+uJ7pb7S3cnrUq4SixH/FTqYGqPHGWbo790+b+wXHPUQemLslVVhjcs1MGGPU3r3Os9Ldc5Lxnv8Gfpa/YDUalzGT2tlovUuUePj/UkysNaPXtg1sf8VwtlsrGX5X7QsfKcRE3DfkdEpW44eanLgK63+n/OMWrbI45REV6m9WO92fQVs2n73qb1p4uU3S07ecZEyi7OcMxC5jctu3/+cWv7I45bcdSj43bG/rvxff7zccu9j+lxa1Ify3WzSFG5xyvHrSQ5biX0NS/ff86xa8cjjl23+5rWPW9vy3XPXvrOX5JjV5ocuxK9zcvmf+P45d/vf/OdQc4vKp+HHYvtf3V3f48LTT88OuzDrTMfr+9dgk7OK6VsklA9psXvMuaH0mZZGW3QGQthSyyMblgEe2Ix9MLiGIolcByWxKloL23bDrgFHfF9rIgX8TnMwMr4G1aRNt9UnZzXwWhJZzlisqRznaRzK1bGbeiMO7Alvolu+Bb2xF3ohbsxEvfgRNyLM3E/LsEDuEk1ts1BPIuH8Tq+h7fxfSyppAvL4wdYEY9gMzyKffFDHIbH5HtxOjmnwqtyvHqGOFvyNVjy5Sv58pN8BUi+AiVfI9ETQzAQR2M4huIEjMK5qMeVOA5343jJTzR+ihMlXfE6OafBnyVd9sRYSVdVGUOkOpbBGlgRa2JDfB6bYW1sjy7og/UwGOvjGGyI89EVt2IjPIiN8RPVO6JewB+wmaQvkWg832CdUh/KEDcQdTLWWjl0kXpbV+ptfWyirFfqryv2w0Y4DJviaGyGYdgcX8EWuBhb4kpsg9vRDY+jO17CLngPX0SlPnhiOeyade9CfuvlHMD83sVp2d7nZXt/Ktv7AjbBi7LdP8dB+AX64lcYgelSrpdxkdzrWIFXcT1+i+/gDTyJ3+FXeBMz8JaM1fQDlsEfsQH+hO6Ygd3xZ+yJt3EU3sE5cg8lDu9l1W/57cUzFur3VMnvy5LfOZLfGMnvPGyDsTgQF+JwfBX9cRGG4mIch8vxZYzH15E4/V1ciUm4Krt+y+8eZW+hfreV+u0m9buD1O+OWAc7Y2N8Efugp6SvKw7D7hiEPWS79MJX0As3Y288gH2knntjGvbDmLy8iyzc7r96H1kw348lvkO8RCwSYadzJY4gxkRo93G0oAUtaEELWtCCFrSghX+zdydwUVRxAMdRLDQ1SVFA8EZRQEMOxRNQvPFAUVFRQBYQ5RIWRMUrzUzxSPMoLbGs7LAoraw0sazUrDStrKwoLc0=
*/

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct less_equal_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal
    : aux::msvc_eti_base< typename apply_wrap2<
          less_equal_impl<
              typename less_equal_tag<N1>::type
            , typename less_equal_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less_equal.hpp
066vv5C+/i2UMtXnr0KFChX/uTi1+X9cWqLpf0nk71oPwF/P/3+zy/9j5bs6HDtgb9ysZ325OVcYNmlkjPbMMWlxcwwnPfe/gdu5/zJooPjsJF1bu+sCZKXMd5hL7wruMzcu05ofaI/JsuVVcnuq7hzJD4zadrIMMdIysi3JP+W8Ai9dwzYl/Hsr39PXY7MveE3W8wBkTr/5phzBet8D3OEu3CL3teYfsk3uy7qwNvnl5ts/66IzLT/jtPyR03K103LPLxyXx8jy+e3Ny9fYLfOc1v1VLP01vrK/PPFZrb/mK9v+Sk2PSzTtNNlfE2g7ohZzNTZu032f6XkNmZnkOrL/tA4F2ZzsQ6TEX2k0WPZR6dHjx9d62vokdrC8l8dlxZuXtx41t3emwWha3nLUMUfcLsvWazGy/Jze/L7R2uPFr8zt8aa01+uy/ILevDx4r3n5JVm+S5a3y3L/fbbH27dnlbTNbm7sgDtwMUld+T5be87LTDEapEG19pxch/a87uuTt6d9W9A2Lttuu1Nbldq1lRfLJbKs/S3EmJ5J2lz2CV0sLtvUZ7+5TeZIm66Q5Velzc792rz8uiwnsyxtaM2rIzzcXbNBXQPjz14D41Rf0yLqDG39jTvCr/b7MfXRt9dOiPReVMrrqg7W1sc98+mHZ4Uf7tNy9OhR3yx5vfTUXyulUsuXdPKdI99FpfzjHP69R/64zm3AXKfYETtjJ+yO/rgUA3AVBmIR9sPncAD+gqHYlG0OQn88H4NwHA7G8TgSJ+FMjMTLcQrm4lS8HadhIUbh0zgd38QLsRwvwmq8BA/hTNTy6DnYG9Ow0lRPinyG+crr7ca/9ajFFTK36wLsirnYGxdiEF6NobgIh+BivACXYCxehym4FNPwZlyEt+BDuBLX4634Nt6O5XiPzAlbiF54P3bEB3AsrsGpuBZz8CFchA/jtbgOi/ER3IbrsRQ34C58FHfjY7gHi/EL3IjV+AT+jiXYinZ5Ej3xKaw0/cyQz2b5zC4196XxWWSOZ6TdnpP22oL9sRQj8XWMxjfwMnwXjXgMr8LfMB9/x3vxOD6AHuy3EmyEL2AT/AGbolaZZngOnoF6bI7j8Eychi1wFrbEGDwLr8DWOB/bYC62xUXoiSuxPa7FDrgDvXF7g9pdA2XXBTVfB+V0XQOl6gKeGxuNO/FaKGOX81qW1/81UYpucH9dlMRxp+baKEXjTn59lK3hjXXlFN1g1R+kQsV/IU5P/h8zLyWtfvL/Bm1t5/mPbCDjW5SGlJaU97Xj/z+15T+GuYY0o67m6/9b8ptsSsrErEvBIeefNzkuM26OznGMWtbZxi9t4yrjJScbjEPIgw/a1SkjPTVVJ3VK1dU2HzuzTb70D8yjeLFcIMvJkzPT56Yk0kKSk7E+zUtyJZYLWX6XdpmTZTTlQl6fmX+DbPLUmZb9ZflDyZViZPlJuX2e0/1XON1/q9P935Hlj+X2I7K8ytOxrUqlrZrL/mtGOUDj3vK5ra2yEjINhrSa9595u2eZtpsr/Qw3y3tihWx3tXm7mYa4RN5cWnPV7pyQY9Z2t40Bv6U3j/GewzEiRlw+WHsNyVxlISbDkJnEUJD5tT/7ufSVSFt4lFvaQuWh/+Y8dO6Z2vr1F82PPtDkprULi9qV73ho5XbGrvtp66NvmLm8548bW83y+u3o2NuD7zs9eWioTj778CyZB6URSp+naW6MhhiNbMY6rnkxVmIB5aA8frzkJ9ofXZ483k/yk4EYiKE4EsMwBc/HbByKKzEC1+IwfANH4Ic4Fj/B8bgPJ8g1PCKxHU7GUJyKg3Ga1C9QJ58N2FxeX0PUS/1myeubLa8vRh4XS1ktj7s=
*/
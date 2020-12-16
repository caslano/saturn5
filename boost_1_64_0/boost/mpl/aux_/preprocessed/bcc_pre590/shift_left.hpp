
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
zbANh+tgl+asXTdP3Kjx5eP+MA23pWmIHU1W88SNYkvzX/aHmd48MSq7mo3tExO3rdkw25rLuG7zSStItaSkFvi8kNJIblIZqYL0HqlpS/z6SENIbtJs0iOkVaQ6UqtWiQk9SCNIuaSZpHmk5aQ1reL2O//Hoykpf9Ov/7P17bQSrwfAhvkA+GL7JXnX+M32j0OGDnENH3qca9yYgYcP9S/Qc5g1+sWW2H5jHdboP+SkYpFnjia0sBhj+01wiEFXHSa2X3k4mTHG9ut+ZPjYfn0c1utrzJxYONkxxPbzr7tsETr3+Qky6pChuc9QOVHI8LXpRzHMgdrj/tnn4j6jnJSnfXNxG6bTBOfYZtJB8Ye0oHKJ+tuZpFfIV/eUdDglvA7pNtHh45q1kz6Bvf6lk9aGMmBHS+wbbV7t32d8njWujeKMmfU3blN/vDJT1+xpJcGxyVz4vdjqW940qJ+rr6U9rZhDXreXUYOOHDp4rD+oU+S4Q9a4RklbhsZ0uhV90p1llOTFEF/pZoe9eedsGRpH6TbzQ8JRHkGdIo4XdpkTgmKI9WsbPqZTl61CdfnCzK0760LwsNj1sK7BEjvMJn+Og/w7TAxMR/lmVTL6PaBvdt6L1ya/1dbO8bxqnt648bx88i7b2jmGVsLiTRtDy9f3ZmjtvbNseZLhLyhR9qRiaNUzriaHH8MsY0Zs8bK0Z74tfmGdfOAYV0wuxbnSmGEe+P41e8VCJJPJUxsYZxhGGjfOVXwt4/+5llHlWcs4esofF/+RNHPE8d0+Of6vPstWN95aRsWi6NYUyhdFt6ZQvSjymgL5eA+Lbm4v5enIc2zpCXp/gZcEz63Kd60THAC7yoctVWsXY7R2kQ1T4alawzhNaxhnwsHWOEXSp4Xm6K36dNrCEp9L+dpGyFeqfB0i5CuPMl9VlPlqLPqlNQkf9yhhscpzzqc1Io3/sLPDGtERmtsepTn9NNhLaz39tNZzotZ6TobHwNPhsfACrflcAY+Hd8IJ8DGtAb0ET4TroAuuhxmwleJitYWZMBlmwZqm3rnWuYo5ZPYDLWsdjzn0b5hj/Sf9Ff/Lc6z/xPxq3H9xw+dYn2Jc+pTUbBvmVknjSaWkeaRq0lpSlzasE5GySDNI89rE50vjR/yIH/EjfsSP+BE/4kf8iB+b19FI/v/ZLMlssP//dqx5f2nWr0eaNZnMwlxXYXZGUUF+kdb6lyQl+H0XS7XufrJ84PJIqzvwz5P22IBDR447Cq+QsSyjjB04aIRZQonoF11f/L3vkJ5t8YmrRd9sXCITLHt+8DUTk88sh2ySOHzOaxax7/0R65z/PxXPz3ntI/Y1lFjXRP5taxw/e9Y4fuvtvu7tr5u9eNAF5Q/OaD3wucZZ4xifoHsLnKy4eM3gCJ8duyUuXhfYCw7QmsZg2BtOgPvJXr4PzIN94Wyuy8RfmZNKTowq5p2Z35yZnBjTfHJ8Lrlhc8n/1Dzy5jaHvLHmj6ONezc3OTHi3HF83njD5o2rkuNzwPEjfsSP+BE/Ns+jkX7/82M9a4N//+8q2/95g4zN++DRI1xDho0Z60obNWzk2DEWw3+T7xt+d6/25Bs2Zsw44uxb8ioaoGc+4Tvy9Rpi8nnnElyTczOmFHljAP7UCVmevwW+640glFEyPSEQb7DKKY/CCe5AnhaUs0Z5bDoojuCzljiCax18FH7hJH2+Z94iuNLGXDhqu/VTOoTGL8sNE0ew6j4neTRyFHbyPt+EpwaFj4W3wsE3YZ3ZB925nhiMR5ZriweSGNqOv3FS7i0/6GLF1o5Nk0Pb8ZHEMPEYHeXF1o7JQ8K3Y3LT0Hb8nXpWOcqNvh0V14T9k0Lb8UY=
*/

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less

    : less_impl<
          typename less_tag<N1>::type
        , typename less_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) >
    {
    };
};

}}

/* less.hpp
y7exN0P2Zur+FMIEWATT4Nm6XsUWe02t2LtW9q6Tvetl7wbZu0n2bob+fWX0t2mI7Fn3lTlRMffJsjtFz88pei5Pg/vDaXAwPB0uCDGGW/ds14/jaj+NkOO5TWN7bHFMd6dfuwfsp5GQHRPRPTVaYrydu5dGtPbR6MhYb0funxH7MvtW0LJpFbRFtGW0jbS/aIkNMa7RtGkNJiZsxIgRI0aMGDFixIgRI0aMhCNRz/+X5Mx1R2Dtv3jXTr2eJhD5yfbbkgOaW1hUXuwuK/NkuFze2oBjLPMCBioXv4NyTj1pj3tyzS21AX4Doc4LOFh5t0Wy3U+2E2gPM676ZtszikrzQrLpy7lZ6+x30npwnJO3z4PU5x/qM159xtHupc/c5j6LSosqwu7Pek4Lt1GMW/YTaQ9gf0Gz/Tnu/LyKgnac0246p75oYSLPOn9hDm162ZzSiijl9MKt1++s3J19LvG/W68fbk5vmTent+nHR0eWx068ZfsD5266eOQ7WZ2b00t26btE3zGxQes6DVdOIQX2hCOg9PQ9wWfJRi9Revsqp9HfopcrvXgbvT7S6wvjIE16+gzD/jZ6e0kvASbCvWGuJbcxvyHmf5ffiHRuw+Q1TF5jEZ+jpbTXaZ+Y3IURI0aMGOkCEvX5/yU5s4tmnlNQHoEYgMfPP84yB2CZ/NbbYF94FXwKP79+nd/PP8ZbLzylaGbpsV7P3OvD5urc256jb+PPykfnpNjOz+LPNh/zr+2+LKj+uk6vZ2PIuu71rfygd+tYH9e2vZbCZZ65r/C49ZyH3vuA3puv9+IzN79f84h78caXLe9fojW1tb6/df1vjjX39QJvHojuuR5f4O0W3XrN/2cSfo5iBQH9ZaEzEv7TrKM9AHR+GpunJnhnjedp1QgfGfT6gqDXfwS9Lnw78HWT/3Vg7XiF6ukH0OQ/uZ5N4l/v2jwHGURLtiCW8Qx2db9075vr7isq3f768t6wP88pB7QOg/aEZAGF4H0N6lWYnc2J9YXj4fP0kRw89qkF5UUzKo+1xpey2vkcW/ex5Jm1xGQCn+Glwc9wwDMVuM78Obomds/ZPG5KNed5Hv9/nfe8tCdE8HOm56ZO73lB933vDXoddN+Le9jf98YNttcuoz1xskjf90N9MTfVxW/UHg8b4Ev0Efue6vf1tZlTxKjDmH8SjXHvYtm/giF576mba5/LOSRx7Mz3dE8t807yC7z7DvjvaaPe87Luadr7/tf++N+yToz/dbWa/q4W/4v2ev/hxgW/8cYF7+xzTWFywfBtk+5589Ne/wxZ3LlxwQXd9NtDv0kG0Ybw3xWK35+o2uLJcD84BR4Ms1S7fBIcC6fCmfBkOAdmw5vhqfBB1SQ/BqfBp1WT/D48A34Oc+F38Ez4G5wO/4YFsAdjmQF3hYWwDyyCA+FZ8CB4NpwMS2ARLIVnwzI4G7rhVXAWvAGWw1vhbPgqPAd+COfCr2Al/AmeC/+E58EErs18mAjPh/3hBXAQvBBmwAX8MwleBE+AF8NceAlcCBfCKng5vApW+eOe+tuvvw2DguKeYxX3PBbuC4+TXiMtWXr8Pfbq7en5bpZete7f1bAfvEb3sQYmqSb9cNWkp8Mb4XjVpGerJv0MuAguhLfAy+Ct8HZ4G7wTLob3w9vhK/AO+Aa8E66Dtbqvd8PfNRdjF8a7BMbD++D+8H44GD4Ax8MHoT9+vcH5+kzQ9Zmo6zNJeqnd9PdJf7fQ8+ok6fneQzX0fWAf2FfXJQ6OgHvCUYo7T1S8eTLcB85Q/PsCOEDXZ6Cux37wPs2xqIMHwefgYPghTIKNcAj8ER6sdf0PgdvDZLgjHAr3hMNgKhwO02AKPB4=
*/
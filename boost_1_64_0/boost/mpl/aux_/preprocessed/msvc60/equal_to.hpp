
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct equal_to_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to
    : aux::msvc_eti_base< typename apply_wrap2<
          equal_to_impl<
              typename equal_to_tag<N1>::type
            , typename equal_to_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value ==
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* equal_to.hpp
eO0lXgfJl4/ky1fy5YeW9axpZD0vluW1kOW1lOW1kuVdIsvzlvVsLevZBqXuWq5bKCNZvrO6a2/sjX7YFztjP3VdpCwnQKO8npDl7JH4T9risSM5L+eBEm8QtsRQVd1BhcTrLvHUdQe+sp/7YScMwC7Y0ZIuEfdL/CfkOOmppCv3JiZI/BjsjldhH7waR2EsjsPJOAnjMBHjMRWn4FycirdiAlbgdXgnXo9VOB2fwhn4Kibhh3gD1mAyfoUp+HdMxe8wDX/GdPQhzxnYBTMxDGdiOM7GGMzBVMzFdDTicpyD27AAt2Mx3osl+Eecj4/izepnBuQ6ppvG9tor2+sZKe9nJd4qg1xf4EaJ1wZLJd5JiXcaQ/EMhuO3OAK/w4n4PU7BH6S8/4mz8Bwa8Ucp959wOf6M66TO6A70QEvdcrXkJ0vyo65bfk/yc1y2/0fYCz/Bflgj+fpU9oPPJH+1kq/PMRVP4Ez8yloOcr2AKzTK4XlJ94Cke1DSfVXSfU3SPSTpvi7pviHpHpZ0j0i5vCnlUY234DtYhkfVz1bI78PWGtszUPLTBS/BrupnKyReoEM8x7rTTlilftZB4vloxBsk57NQbI+DrduLIPHmaGyvy+V4HY5+OAK74UgciJEYiaNxAkZhHI7F6/EKzMJxmIvR6mdW5JmiNhr57Sv57Yfe2F/1PRAk8RZofA/cJ/l9AAfggzgYH8Yb8RGch3/ALSTQWH8KIZ5ehl04iuk51IOWE3YSGtSNXmOuH41GZ3Wk5U30u9Afowhn+Ttlsmt9MJycbK5XjSAkEkqkjnU7VuEudOyboVb6Z/CkrjUBg9HST0NsvPO+GnY59NdQg/UErX4bRknfDUlYRHDWh8MuplUTkvj7LJZgwFTnfcHtkDrfEwTvBFsfD/0TyA8GRjFdo5+H2ASWhylYRjD3+YAJtjrjPQnkk2Dp/+FEgn0fEAnYWD8QPtNsfUHEoKU/iArcQzhKUPcN4X2d+33KlSufE6oJJwnO+owISrT1G5FIWCx11/sd6q+PJtr6kTjP3wHXN+xPIpxpxzAJTXXd0rfEHqwm1PN3DMdJFmExYQfhIKGWYPCizpoQQ8giLCZUEvYTagmeF3kZgggxhCxCGWEH4eBFer22PuiDPujD/9rwq9T/0+rnQtT/K/X7x1T9/2XJNexEua87gVCivIt4nar+Li+zgL7elboKbtC7fm/X8X50EUHqpOzqdzKT56bmFGda6y3mkn56mvl+dIQpH1wHBNu/4zdW6p4jL+JaBIejkm+jOd9KiSmFXpSdJ02v5L5wBjZWV5eywVJXdyHXw3x/+d0ejBeVmMaPMa7EKbjc/Hmd3H+21OfUWz4fbB6vkc/zZ5vHz1o+D7O9O96SrzmyjOOWeULN49tlnNv/pjh7VHGM8p7rHFa+zvQuTfaBOygLWdYJiWtkYWwH67yBHua6rSLVvCdlXpZhN28M86YyrV41b61luTKvrb/EC/fO3AvV57r2PXb372m7255H+x67s3vI7t/Dd7cfRe178s7vvaeY7oGfa568/9Irjc/siE946p9Ry3Y7v5eufU/e2T1253Ul5nuWci6Tc9yhRtrbXIo9cRAG4wTsZbkX4yHnFjnnsBzTsVrq0bC90GXYD4dhfxyNYRiNl+PVGI7pOASzMAKNOBzn4ghcgCNxJY7CTRiJD+Bo3INj8ABG4Z9wLB7BcXgco/FznIBeyjGIrXAi9sWrcBBejZMxFhNwEhbhNTgfJ+NWjMO7MR5fwCl4AKfiZ5iAJ/BabMH2nYatMRGD8Xq8DG/Aq/BGnIzJmIMpOAdTsQLTcCOm4wOYgQ9hJr6FM/EvOAs/xCz8GrPxLOagL9s=
*/
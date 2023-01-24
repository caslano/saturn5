
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/plus.hpp" header
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
F/lC5RTWODKjNxwTSV8qlGiWNa11K19roJQSVh85ia5mOGpK6RJwEZXoLyLCBGaXCq2Myr9fFaGcjVatWf0EPeeEEAxX+eV0WjeoPFI+qqm/AgWwFsp3rGB4VfRGlgnr/XF+HKuJIXYh36cVrU0j1yy/bJmKU7ib/mR5dslvmH1oZ4k5yfQJoZ2ZYV0bfWF7+mpO63CBZpHSalun6kDdBD/dFUKq3N/jROwqlaL9UHtYpZX1mA7q+D5MRBHDE42wXZOxDUUzXC37Vupk17Gm0q5zlskBHm+SPissyCw/YDrJnT2PVC9a/PEEPtBtxU2yr6oA5q0vXhwt2XSIHhrhX8t0XI3+heyBc0cs+uYPmeQHSRbO2FORU+z5tgfxLpbNzBDYwq8sfd1kFkXNvM9xrG/l3JRSgin0fuBa8JrkZBeseX7C5S09IJD2o6/YPliOf+FQ7Bif9hvNieFgfC433oobIVdXb+Zto9YHjN8N730BLK9YAJq73C4XLyRKDwV6vFK5Whx+/9EAjjRlLS7E9xqY/F3hrC/DPul6uUegmnIHvRo8N/Rn00fPtDnV34bRVG0rw8N2BekpCPp7Mav1jyWWFa7acZ799CMHp79nemh749jy+JFwPkfdccHPYA3JJO8gf5w/og5tXwscX+phOOduwDBBUYU6U3+mR1l8kDOccmNJwTRB1jZ3I5+KkGHlBXxfSnNUcG4CpA//
*/
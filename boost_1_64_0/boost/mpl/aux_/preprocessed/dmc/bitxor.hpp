
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
template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  ^ BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitxor.hpp
oz2+82Qs/x2yf5eQrm2g3NTb2yFZObrjc1if63HC9PXXbj9+Xrh1L19H6qg6HjTnv/VSCH8/S7mrYVNl+6nKrfyesY1F7eI33Jdf8T26DcQnmX+rGPyGk/1Y8xtNfrcZ/BY7Ya+vpv4ZJM32Ve2/jsfMAfUxLPtRuXyP7R6bPSfVZF32lLRnWvK85DT57LS6/eT7h+T76fEm2/cbqMbxc/hpahm3kH2kkfl3NPvHl/YY6lLVGMpsG9uycYGW82TzI/Zlt6vHW5aY7lxzfrHSbNp1rGUd/nx571H7OvY7rKPMeB2a/Xt+kPQblP17nVIuZf8+Zt9P0lIz5sTSoO6MD+nuuVv2C9VxYLzdT1u3W3x2jm1bao5h7XkrrY5+rpDryLfcsT7myxGPQywnFbePW6N62fdB4+P0nGMdVPu7XBXN23URNUipYxnvvuk3lNegvkbbMELGy0+TOqeQWinH+jfaOluq6v7zhZ/cuP46zkNgYgVtKU97pQ7H7XU4rTlW9WPoxYVI/Jpcb67ENuSVd1xbB/uNhPvn2p/c3BcdrwshbuyfynZs10C2rbRBF+o/nS8X8P47hzbgGqecQ7hWWpb1Y7kY0jiW6fat/Vg+pbqeSVtpzu+hMrZ+ibTXFuyg7Off2tvLlJWbkezBMau7JzFou1PaZ2bGx6x+f5UYf+ex28ax9s5j541j0p3H1BvH/juPYTceE8DZGAWex9QbjxXgeYy8cYy/52MIeBo7z/HK50381l//+hVHmo5cNmd47u6YZ5zG/ns8hoNx7L/zsR1y65nbs/eNpmeGPL1oYOGciPUxqXddvFh+Z2M+sMvRN0Oekcuz85jqlvmDukjf3pul7+mtGIJ/x4a4GJvhEmwnsZqRuFRidu/E8bhcYmdXYILEbmbg3RLLmo8L8V68De/H5bgSH8BVuBbX4NNYgM9JbP8Wie1/VWL7d0ts//sS2/8p/hOV8/F6DMSnJDbyaWyCG7E1Poud8DkciEU4Dp/HGNyEsfgizsGXMB2LpS/sUhLPxiXWzNKOV+IiOVnNkHaMx2BMwFBMkpjQZOwtMb6pmII3Yqq0x2x8COdgAaZjEWbgLszEwzhXytPDR56HYwcpjx+2lfJcz3K+GCMxqlNkO061xejIM255DrHeoa9qfdVyA2S5ui6Wi1Otb5dDn73a6r591vW5WK7QzeVKVcsNdyjfXlX5yt1czueQ1KPS5UiyXC0Xy0W4ub7oQ+6Vz+TmcvluLlekKl8+yVmfzDLb+pwvF02qkOXmyX6pHrPjRekz/hKaY6WxDW7FQbgNR+B2zMIdKLH38tyGc4esVx1731LW2waDsS02xo44ADthJHbF8dgNY7E73oQ98A7sicuxN+ZjH8m/wkeeseAoOY8q58kjkv8+yf9DbIIfS70O4hD8BKPwkOT/KU7Ez3AGfo7J+IXEunyND0jMzEMSM/OExMzslpiZzyRW5rzEytRQYrwwBCvwavwRr8VTMsbHzxJj8QtG4K/YXWJmBknMzDA8K/XmnCrPVfhdJ/VWYqD85PrhK+e9KyUG/io53wVJrGCwXBdCJFahrsQo1MNVcv54DMPwCWyIb2MjOb9fjRXYGH/Ba/AchuN5bI4NKEsLDMfrsBm2lPN9K4mFb4PXYzuMw/Zynu+AORiBN2EnvA87S6xPF1yDXbEQu9muB/KcBXYYXA/6S7sMlOtAJPbDITgWh0osxzCchSPxLhwlsZVj5boYLdfFcXJdHI+bcQKW4EQpz3zyr5Dy+PtZyhMl46PwYkwGGZsCQzAOG8px2w4TMBoTMRuT8EGJlX5UYqPXSWz0c5glMXnZeAjn4QlcgOdwIfpSmJvQH5diIC7DMLw=
*/
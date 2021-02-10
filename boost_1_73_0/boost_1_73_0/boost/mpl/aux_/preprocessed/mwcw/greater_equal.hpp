
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater_equal.hpp" header
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
RuFA7GId4ZUNwc0KDB7I1cpPwzJHxzQvv45db+SYFNnEJcU62PYEo+VBXal7JlS8zFHUBX+phTrZjtyYYSHIwfUskrrO+LbEUoi1kloGheipO5xgv9/XirvCRZ7ntJoPaqw/H4A01NjQcWc15v10hujVWHEN1Nj36Yie3DzH4eYpuHm+lX4DUEsDBAoAAAAIAC1nSlKhnVeoxwEAAOQCAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NTIyVVQFAAG2SCRgVVJdb9owFH23lP9wlaovVTMnKXTDMpE2VpWtdDCa7XUyyQ2xCDaKDRX79XO+QHuJc5zjc4/PCbdobCYMJoRLVWi37PD8ruvcJGSepqv2Ac9PKZn9Wi+Wq/TParlOCadXGqfdSXJDbuAN6xPWgZE5El7joTo7Qi6sAKWzErPd1D+j8TtxGn2IIA5DWL545KuwyCA94j2EE/ihT+5LFEI0YqMJc5zn19QjnTyDxnZgWkALsUOPLITbedW5LCTmvU70AN+PqpngdGIWhRedp1RsGfhxFMbjIM8+Bg+T0WM8mnzyPfI5y/Bgg7VQWzQMNmc3zCMzrSwqGyxQbW3J4NEjHimxqrQLoLlgE0R/4TaJWSUbfpdE1gJH6TwnpLT24A4M
*/
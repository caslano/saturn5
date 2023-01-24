
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
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

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

template< typename Tag > struct less_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< Tag,na >
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

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
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
Mpr3tnMMp03WhCYXXGt8vlOc6SrLPw9zRJFSU+aWFb/pgJqJjQq2hkzchnom0wuxPPC8Y134ubcRq1ti4hNQzStF9WeRzYS6X0kRTCcWTm2rRwD4pdjfm9Oeyk2fx0a+7qLd9IJdGd8rTsxALY7vsx2juGhTxUBOJfrJHc2Kap5etT/Eq2bq0TmEh7q0q/6gNwcLIgk3zmVImKadC4SjUPdnQelfFGpMK+dySCsU/P4gLl9x1OSRnt9nd8PoR2G/wO+Byv6PjgRCz7U3jmT/QY89SA5oIX8r+vQ9SBlEwZ++dTsuFH578j0e1J6/yx3ff85MEknNTPIQkKv98Uqgsn3HunSn/k4sf+XnLmtbfIXX8a0DML6fToxAvGi3RdGz2+vLsP17uRbAzM0DaeT+kHyH5Y2W6tNyg4FQ0M+lSqdYRaajzIm1py33fWm/z7GkhySUsFj7WMwhnSE6i8oGTaryweLX/sAM4w9U3sK1GHVa8+SUti0zGvjmQjzpDZMuZIRktQq8Xj/fD+UN4QsY7dwjKM6Grnjth9moyxHkoLPnuWMubyMPCSuQA4oGX1riu1vvbzd4IOb+udKHLK0DJCFC9KJe2lwa0gnxG/jDE46UmQgNoFk1x4X60hiLqzx79GhWnoFLRy9FWBBIWoSoiXte1iLAWUTtECmNH4yITd8kcuPyrPEOy9VKMcF/8K0182diB1BXCvLoPlsb
*/
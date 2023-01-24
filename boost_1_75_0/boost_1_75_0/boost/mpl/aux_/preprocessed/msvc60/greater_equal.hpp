
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct greater_equal_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct greater_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_equal_impl< integral_c_tag,na >
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
    : aux::msvc_eti_base< typename apply_wrap2<
          greater_equal_impl<
              typename greater_equal_tag<N1>::type
            , typename greater_equal_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

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

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater_equal.hpp
8Q38aXUni+GLvD29Mcl7J2zbu9rxFtFn6nH2ZNJzdaaViqWJ2aPtUNwZzVMqVmwDHw5506nQus1SvCr10QIjiYVuXmp5V0uPOZtg28FxwWfCMcIxvvtLy54PHWS82SWu1We+zltAnqdRVmCILnSuIOq0xuyXJ+9i2rLQU6Jtlm70I3D8EqqwsYUCE7iXfPrB1A/YoFx3oBfXJ5LmQbx498WNjIS/cIgS/WES/t4ngccSqI8BDIUz1hQa2gZQrbYJdvP22iXaFqcWs7Owm9L+KIEhmlG+3MeT+FLO4QZxtzqBFdNgn/LLmGCJlPsNnveggbzIS5NwrMx0cQAKYEFnVvSLoDfs9oSzl9Ytz4ApKDd45mQeZtfcAvB5frmumhXeVQ7ajjnXe0/gEyqyTa7L+lWEdmdEOw86PDo/u96g2FCiTmvQhvFGXpMP3Of1QSKb6MBKb4Tt/0HMEc5Rfhi7F7YtbUTr7leHsoHejl3/tRjoCu+E7PTuJKQmxDnkIuT1HTacAVwNleWYSgo2vPe7NbiLEKw/Bzu0n/7wh3edcJshwiE9IUEhZP3B/ZIhCA69koNAHilZuJ4QEbGPf3w3+CEOW1K7L4gv/HE/BDdE9h3tO9R++n5Lh0n7lHggO1SXmZRTZkpzuKOZ3462yZ7TgdBe0MvBYjJmBXRuR+PQSRnHfaTvXer6XZTSm8b+Zhx1hIyT1HXvhlbFUP5K
*/

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitand.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitand_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitand_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitand_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitand_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitand_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitand_
    : bitand_< bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitand_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitand_< N1,N2,N3,N4,na >

    : bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitand_< N1,N2,N3,na,na >

    : bitand_< bitand_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitand_< N1,N2,na,na,na >
    : bitand_impl<
          typename bitand_tag<N1>::type
        , typename bitand_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitand_)

}}

namespace boost { namespace mpl {
template<>
struct bitand_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  & BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitand.hpp
v9Rd47gpokXLvscfs95DPAq3pwW7NQpfpT1obTVEPl1G7hrVwqjqTUdFYNm4l0QqHYy7bFFArFuwTdaac/7fDL9LxigcP7tjvYZ99x+G30CTAJRbsXx2ZVQJHmkkeBHcKnj76J4IeeC+EjuivgMsuU6snbTVC8AtzZOet04/PznymWPD9bybPaq3oBmXgg5jtHC4pvoHOMLfludfltqMHnw3HqQD4N71czdSj3CqBDhWwssBDJL2QHlRul7qu+SjQmgWyjudm6vhI8iWBCQegaMeQIxOe85sHhqfMQwCKojz4fajx3Dtos9QcCkc6e/deRR4iV3/9wOf5b+3AfzrA5/7P7rz7Gz1h35wxxbJRjzl0Z2MPXkVmMnXS4a7F8nOzKN4Ut/KEdF/LWIeSfgMSFDZT4x1P+sQ1kg6OeSsmxPiZRkJv0GiTHujrveBhozRPjMvfO+tPTkd0mqB7M8CpIyS70AeublhqdP5mBrujueLmNK9oTrpzDcrA50t1A3cDQ0N3M/3Fxxwk4UHwMPJRziq4DETQa93mZNuwkIIumT5u764uwf1sqS1rCfzp2B5sY/TVhuLv1xZ8/lrPJnFScUFe9UD0QPN342hab+vTGL4MNhaFnFi47zql+7XPUcaph7zE1s8bHot5Fpf5w/Lryj0x6JTbtefD7hmYCFn9lOD58LX6nOxplu9JhdbH9bk8zDw/vi88r4zNpEg
*/
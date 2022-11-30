
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

namespace aux {
template< typename T, T n1, T n2 >
struct bitand_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 & n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct bitand_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::bitand_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* bitand.hpp
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
*/
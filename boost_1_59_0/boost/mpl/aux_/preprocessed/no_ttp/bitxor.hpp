
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

namespace aux {
template< typename T, T n1, T n2 >
struct bitxor_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 ^ n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::bitxor_wknd<
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

/* bitxor.hpp
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
*/
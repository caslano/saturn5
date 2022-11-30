
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct bitand_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct bitand_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitand_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitand_tag
    : tag< T,na >
{
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitand_2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitand_

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , bitand_2< N1,N2 >
        , bitand_<
              bitand_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitand_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitand_2
    : aux::msvc_eti_base< typename apply_wrap2<
          bitand_impl<
              typename bitand_tag<N1>::type
            , typename bitand_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitand_2, (N1, N2))

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
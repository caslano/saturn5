
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
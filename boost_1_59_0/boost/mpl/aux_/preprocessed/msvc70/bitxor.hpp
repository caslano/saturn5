
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct bitxor_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct bitxor_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitxor_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
    : tag< T,na >
{
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitxor_2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , bitxor_2< N1,N2 >
        , bitxor_<
              bitxor_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitxor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitxor_2
    : aux::msvc_eti_base< typename apply_wrap2<
          bitxor_impl<
              typename bitxor_tag<N1>::type
            , typename bitxor_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitxor_2, (N1, N2))

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
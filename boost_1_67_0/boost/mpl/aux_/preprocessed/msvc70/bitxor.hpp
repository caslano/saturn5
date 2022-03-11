
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
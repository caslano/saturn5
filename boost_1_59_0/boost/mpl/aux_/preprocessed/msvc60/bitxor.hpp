
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
{
    typedef typename T::tag type;
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

    : if_<

          is_na<N3>
        , bitxor_2< N1,N2 >
        , bitxor_<
              bitxor_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

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
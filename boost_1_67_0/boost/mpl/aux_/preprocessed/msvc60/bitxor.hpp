
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
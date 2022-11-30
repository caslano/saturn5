
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
{
    typedef typename T::tag type;
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

    : if_<

          is_na<N3>
        , bitand_2< N1,N2 >
        , bitand_<
              bitand_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

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

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
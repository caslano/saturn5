
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "plus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct plus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< plus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< plus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct plus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct plus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct plus
    : plus< plus< plus< plus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , plus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct plus< N1,N2,N3,N4,na >

    : plus< plus< plus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct plus< N1,N2,N3,na,na >

    : plus< plus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct plus< N1,N2,na,na,na >
    : plus_impl<
          typename plus_tag<N1>::type
        , typename plus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, plus)

}}

namespace boost { namespace mpl {
template<>
struct plus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  + BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* plus.hpp
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
*/
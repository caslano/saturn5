
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/plus.hpp" header
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

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
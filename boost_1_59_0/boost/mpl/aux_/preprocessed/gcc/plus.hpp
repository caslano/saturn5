
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

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
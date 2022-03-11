
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
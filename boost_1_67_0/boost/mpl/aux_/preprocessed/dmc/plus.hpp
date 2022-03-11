
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
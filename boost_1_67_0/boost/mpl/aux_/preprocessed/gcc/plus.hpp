
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
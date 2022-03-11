
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
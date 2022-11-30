
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
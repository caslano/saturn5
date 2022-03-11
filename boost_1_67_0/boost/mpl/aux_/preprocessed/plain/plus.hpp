
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

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "plus.hpp" header
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
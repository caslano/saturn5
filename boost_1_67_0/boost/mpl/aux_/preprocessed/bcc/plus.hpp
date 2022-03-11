
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
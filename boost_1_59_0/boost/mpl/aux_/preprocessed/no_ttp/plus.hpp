
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

namespace aux {
template< typename T, T n1, T n2 >
struct plus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 + n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct plus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::plus_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* plus.hpp
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
*/
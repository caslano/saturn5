
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/times.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct times_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< times_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< times_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct times_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct times_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times
    : times< times< times< times< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , times
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct times< N1,N2,N3,N4,na >

    : times< times< times< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct times< N1,N2,N3,na,na >

    : times< times< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct times< N1,N2,na,na,na >
    : times_impl<
          typename times_tag<N1>::type
        , typename times_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {
template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  * BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* times.hpp
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
*/
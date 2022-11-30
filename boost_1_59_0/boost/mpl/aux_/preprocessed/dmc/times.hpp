
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

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
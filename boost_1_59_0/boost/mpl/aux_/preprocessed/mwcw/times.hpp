
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
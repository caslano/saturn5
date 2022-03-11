
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

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
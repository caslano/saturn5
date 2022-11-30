
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
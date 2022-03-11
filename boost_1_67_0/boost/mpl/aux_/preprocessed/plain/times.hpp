
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
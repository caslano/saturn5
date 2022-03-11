
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "times.hpp" header
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

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

namespace aux {
template< typename T, T n1, T n2 >
struct times_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 * n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::times_wknd<
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

/* times.hpp
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
*/
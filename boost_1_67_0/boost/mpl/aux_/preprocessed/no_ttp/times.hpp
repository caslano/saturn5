
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
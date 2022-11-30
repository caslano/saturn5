
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/divides.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct divides_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< divides_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< divides_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct divides_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct divides_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides
    : divides< divides< divides< divides< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct divides< N1,N2,N3,N4,na >

    : divides< divides< divides< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct divides< N1,N2,N3,na,na >

    : divides< divides< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct divides< N1,N2,na,na,na >
    : divides_impl<
          typename divides_tag<N1>::type
        , typename divides_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, divides)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct divides_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 / n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct divides_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::divides_wknd<
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

/* divides.hpp
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
*/
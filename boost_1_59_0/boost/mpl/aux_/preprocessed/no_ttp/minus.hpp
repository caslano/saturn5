
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/minus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct minus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< minus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< minus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct minus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct minus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct minus
    : minus< minus< minus< minus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , minus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct minus< N1,N2,N3,N4,na >

    : minus< minus< minus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct minus< N1,N2,N3,na,na >

    : minus< minus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct minus< N1,N2,na,na,na >
    : minus_impl<
          typename minus_tag<N1>::type
        , typename minus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct minus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 - n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::minus_wknd<
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

/* minus.hpp
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
*/
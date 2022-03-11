
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
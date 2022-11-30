
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct modulus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus

    : modulus_impl<
          typename modulus_tag<N1>::type
        , typename modulus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct modulus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 % n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::modulus_wknd<
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

/* modulus.hpp
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
*/
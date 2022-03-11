
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
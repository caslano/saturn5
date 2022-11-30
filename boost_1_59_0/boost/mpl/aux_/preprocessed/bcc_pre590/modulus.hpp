
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "modulus.hpp" header
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
template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  % BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* modulus.hpp
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
*/
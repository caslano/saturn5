
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
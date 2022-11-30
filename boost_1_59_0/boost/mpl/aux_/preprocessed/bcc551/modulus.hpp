
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
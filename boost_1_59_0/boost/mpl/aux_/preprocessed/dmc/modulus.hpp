
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
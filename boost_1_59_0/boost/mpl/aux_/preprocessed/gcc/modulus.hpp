
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
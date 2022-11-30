
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

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
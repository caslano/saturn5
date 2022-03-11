
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
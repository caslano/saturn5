
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

template<> struct modulus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct modulus_impl< integral_c_tag,na >
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
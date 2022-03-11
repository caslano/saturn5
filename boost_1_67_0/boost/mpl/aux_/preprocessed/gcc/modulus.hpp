
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
+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
*/
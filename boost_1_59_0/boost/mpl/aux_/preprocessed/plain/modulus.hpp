
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
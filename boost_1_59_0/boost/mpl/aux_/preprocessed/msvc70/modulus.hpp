
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct modulus_impl
    : if_c<
          ( tag1_ > tag2_ )
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
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus
    : aux::msvc_eti_base< typename apply_wrap2<
          modulus_impl<
              typename modulus_tag<N1>::type
            , typename modulus_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct modulus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 % n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::modulus_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* modulus.hpp
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
*/
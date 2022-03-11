
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
{
    typedef typename T::tag type;
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
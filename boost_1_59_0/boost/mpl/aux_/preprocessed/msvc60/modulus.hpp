
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
+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
*/
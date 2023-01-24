
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
/S0cLngAbQba5h++2b7VgfUIms1wn4Vb8reqXy3WUbpeOT8oQat6lj9k6exN8D4G1im8jWKzpcGdI5QaX3cR/4HgPQxmSPT/s1xO/1/L5f8O1pVdHC1dzF1d/8Mcpzb6D3Mc/aPY+0TWNQG8y/fjkiae2N8YSBZsNLWJkCTI12idh8n1i901uia2u96v92tzksXrOprrpVAxbnK2WG+P2PxlNB4H9WDD2pTa3lmFiDuB6zul/7q1SXadx/noM3eCb4vOd7IKcJGf4YkfcGbLO4/Xcmbq9fqy183hOvywrBaKfRw+rSZyYxFTwUKdQItXGKIs3gvImbaoubysG1TH3UGwzWwD25DkRYJzZ9/hB8f0U+6pOBF4cbXrLU9jpY0BLEIaDSPgBYV5Jt9S9D7/pjEJRXloC5EZfOeyYZsPHaOmm5B4a2ps52yrhcrN2r9qv5qffDumea94/hvpKVhM7Fkj1kRY0iySKGVAWoo6yVBhI1PQks4UM4ieI8sBLcBOzvPBZrdzL1WdBGdC2lTPtFexlA5A3J3KANb9ytzC8aKEbMEQuAHp6m/bhDius32MfLnZ8tsA+KBwlQe9+c1mxr9e9P+YEQDH4SNyz8i/NT8B990KKeGLb2k1Vf5YEEXwKiSdA15c4qNTpPUXGPiNJ6JUCJ4Tdem6nAxoP1aED/f19z0W46jPiAQGxvsFBLhq7lnyGmaobsM7eoP+
*/
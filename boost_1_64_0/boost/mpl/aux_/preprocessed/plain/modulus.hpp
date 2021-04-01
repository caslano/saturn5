
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
byDpjM+2jBv7twk6mCt+7AG8m7Bx9eHqyNnw5UXOnJHuF8WiODwcqxvEoqf3XTdPG0SaaLbgWEmQ39h97WoOO39lZ1oD+v6I/nXoJ6LRXUh7PHx7ZlhoEULJMpxczQ8/VT1lTHfMAJ5RMVLZYbqMMs6kpDtffpRJe+EJfnbJ/elrgDk/GNFdEpEHLvT2//+8sHslN3duxKMaj+NAGsDzZpT2S3ZpQv0wfXRfbWo+dEs1WRKnALfMcNvJOS3j3qD0bsOwMeht5us1jB9NHDys67zrtAJ39/O4KnTBEn/gXnP6ZQBM4vwBOHcMLPRR/8ZnFyTTspOoaQZKIvD84SaI28Bx1nhgVFmebvc6WJTfC+4/0EQUBFoQ0rzT/kHyipYjVSQZsnCbdoMEz6PXZgRLjmrtyY5WYFP3aej+Nak4dGCS1mBUoYy7I0kt8s5EdW4tZxYHGLi/+Ybj1z6nVwYh7aUTR5YI6o5uBLg/AcvOeMYu41P8las+oG59EZPZKomVtBlMvXkyqnKVc6f0Yl4NL8yqEkoNsv4wT4ftRCT+nopfxKrHKJCc4tZxzg==
*/
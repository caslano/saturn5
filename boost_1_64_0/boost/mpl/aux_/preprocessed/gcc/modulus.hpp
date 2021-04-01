
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
RpnQB5UrYfuV9p2T/fTDTfewAt0E0xYr/GbFseDUwoWWvPOH7/MH5bkakGjy9vD5kgpJkAprW5EzJMLumAGFI55RjPNtcSc0e5xP3jZrJ3DrJy/cALrjVzDF1AUytolECJMtmTKGBzS1QLKumBvGkDoSAICMROKG8+jXYLmNzEaxcGlzBsGizKpDqXSPVrrWu+cIFWfKd9F9NOut6Z/SCekxRr5UYBurezENGHLrfBO8wGSzYkfvjD7ZEgL9M/FhSOLIIiLkeglNRJGPhmXuEOem94/XuVzYvWzAVyzZY9IV9SB6NSDmm7ZSwhMnd70ilc9mawRYQKYg+ttvbgzVwp55/bLF3kLivli1qU4DklfU7UySPJZ3szdVQ7H6MRiKcqncl87OTsfbvezGCfQX6dqstS8bZF5ef0PPKFaZ7nNoJVeDf4WhnvRPBPJ42rAbwFP56+Ue71U1fW3m40VKyzpbtFGOMczI/yoK//1n4/cbhVJl7hqbW/WeIzCblMAgUs/xmhQjsQamAbHFGg3Kdzm8ZddtH5kqaDGGYXJm1xtt0PMNLgHFQ8ScAw==
*/
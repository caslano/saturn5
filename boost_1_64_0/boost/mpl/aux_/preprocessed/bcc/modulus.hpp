
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "modulus.hpp" header
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
0HakehirhgAXHqXbeWw1oLrQhqZfJgMV/RfPhoQ7/ufHxs644N/1oNKa3qvYLttEIBCWJEAYItCykuus6svPEl/7oJ6SQ7QBgr6E3EfYK1+tN4GuXW0uWajh50A7oDqqoKByGCxkFj2qKuR7En7HZYnNKvR2y1aFY5cvF5W5qKXF6bB7LEgT279Hf267ExHVz4JVMIXMdKfofIj8MzXjkJQmOtFxwoUCIQJvgUA437KVKVFbAsAl15ESdGEUkbuV05xth1YoPMqjgj8OUTjzH1PRVjXmhCg5CC2KYifWe5rqJnpvJXCg6v5ha3egza//4n/NanExzbYS0Ck/I/BmJttfC7fjCfXL6/QtKEdHTfv74Z/quBhv8Ppu8WtW1nMpqqjVNybaFUFXWZ/RFVesY36c0bm2GV6mRtNVnenmY2EcetG/6fhKT1Vk5OK4Jtk0Ws4jx8kXRaRr3OPocPOo+MbqzAij/vFHOpGncVjwOKnR3nd8PZOkBlyD43MPonjBFUG0vGS3U8bkDAhTRwkPJnuS6RnQ5QjlW5IDO6waOJeFPolURWh+vuXGow==
*/
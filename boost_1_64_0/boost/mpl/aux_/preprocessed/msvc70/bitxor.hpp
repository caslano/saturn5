
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitxor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct bitxor_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< bitxor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitxor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitxor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitxor_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitxor_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
    : tag< T,na >
{
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitxor_2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , bitxor_2< N1,N2 >
        , bitxor_<
              bitxor_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitxor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitxor_2
    : aux::msvc_eti_base< typename apply_wrap2<
          bitxor_impl<
              typename bitxor_tag<N1>::type
            , typename bitxor_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitxor_2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitxor_)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct bitxor_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 ^ n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::bitxor_wknd<
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

/* bitxor.hpp
Pj6KC3APLsT9uAifw8X4Fi7B9zCT/z7C5fg9rsDruBLd2J/uwga4Cn1wNd6Oa7AT3o3dcD32xXtwMG7EUbgJJ+FmjMZ7MR63YBrehytxK67DbbgJ78c9+ADuxx14FB/Et/AhPI0P46eYhV/gI3gRd+IP+Cj+ho9jdfaRXVgPd2ND3IPNcS/egU9gID6JA/EpDMH9GIoHcBQexsn4NE7HI7gAj2ImPotZeAwfxedwLz6P+/E4vom5+Dm+gF/ji3gJT2Bljq8nsTG+hM3xFWyBr2IvfA374Os4CN/AEXgKx+I7mIjvohlP4xo8gxvxPXwM38cn8QM8gJ/ge/gP/Arz8SJ+ilfwM/wJP0cPjkNfYA38EjviBeyPX+Ew/BpH4EUch5cwBi/jDCzATPwOt+IVfAK/x3141Xrf90py/i3n5cq+d5tyHEKTjMFqiD9jS7yBfvgL9sDfMAgryRibyhiNbjgD3XEZeuAqrI1b8FZ8Cj3xENbBU1gX38H6+DE2wK+wIf6AzbEesfmiD7bAbtgKe2Nb3IC34/N4B76NfvgT+mMbytkZO2IX9Meu2AV7YwIG4EwMwjXYH9finXgfhuJuHIb7cDjK3Ntyvk2ZSO00c29Tf7KcnCdj9VKWS3FwfRtlOe9SlssuZbnQMvahuOYRc80j5kh/yP9sX8hhD9MZ0g1S66eZh5cUT1pN2vW0q6/D9XA9XA/Xw/VwPVwP18P1cD1u9uOm9P/T41gR8/81Y76ZF1rQn9ZD6QdSukXpCoyclp4Uk2Zm1ZZ/p4vVFNRT/e+FswiwgGX8wCTV+IEwuZYzkORG6k/qy5f/qMLxAyHh4ZGW37jLmojFXOq9Ea39RvGV7PUb2esvsdfvYq8/o+L6Fcr6G2vj/ht7/VX2+6W69lFe/8ct9To87VU96OueVftse35iM3v9TPb7zyzX60yy3WR7+vJHFQwkmeS3eG44C5thEnbAZAzEVOyPZmxI/q++xBi9lzwcvpajuo5jcw2H6zdy7cbmuo1cq3HsOo1JdX3GfSR5k0JJOw2uw7xKUl9/Ga265iLXW7jWUvL1lSiS0XUVP5KPXD8JHa26bmL3mont9RL9tRKbayRyfcT22oj2uoj+moj9ayDZ6Bvh2DUP9fWObiTVtY2i6xrVXnZds3A9XA/Xw/VwPVwP18P1cD3+ux835fs/c/ZWxPd/5ft7ZF1T4bhp+Y5tWSepFqkHaZoyznaO7byhwaP6h6UmzIlOixvKLMCOz8+q/Q3A9cbKHOnRpY6Ht84FOJIoU2YyQ6fJdq7yajKvf1u57tBG4s7Wxx0ZNmbA0JDxplKvO5QUc4ap9DH86vh22YkvXx9fSnRq9Cyz6ebEJ9ud38vq45vBE8+5tvGFDAwbGkaATJsYl2p2Psb4tmWPsZq7vm0msp4gfYxFTbMscwdr5zL9hXqMi2GGagfiLK197nLX1K/EvlEXuzTPcmz/X8qw/QdJfKM99PHN5kmuJr7hIaNHDewfFhI5MCR8dOSokJFjmLs6xPlYk8vQDqzzUBYYxGrmSYEm1rChA0f1LEc9rvQpe2zrquhjq88T3wyb2Mp9DLrby/HYrPtPcFX9/pNObGGa2MIr6NhemeupqeU4tlvjvlBVU6cSd5ZB3OlTExNilLDLsd0rN3G8bq379+pqxjHmaWOsgM8fZ+Jrd4s+vrnKk3k28RX+6mNgeGh56q96o7LH96pBfPN44m8UX3jIyPLEt64Mx8cBEt+K6vp9ZwHxRc3Tzafu9LmR5XdjFXhu1Ne67Wto6lZiz9bH7tT5kSXucp5/nLITY74+RqfOkcoTo7UNpNXUx7iIJ57zdTE6fZ5kidPJ8yRrnP619G11Ces=
*/
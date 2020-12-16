
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
66yXUdvfstphpp3WdhSKPexUu6edYQ+0s+2DUSt028VHz7OPsQvsCWCtM0Ba0/ELL7Ur7KtRMW6Sb/sss5WaQeK/5sf4V90g8aAqOJdZHS4jY9WA+rUB1WuLpOHSE1moWyaq1ljUrGJUrFmoV4tQrZajVjWhUrWSgdhGvQwSLqeoaWom/VKlX+bTL4vYR+XqXDy0JfD1lWqj+pcyYX/5fVM+65+HOzEWxTWLuZmDfj+SPmH6ru/7xUFJUB7MCirp6ehyosiN5Ip90eBQ30R3IxVKnmmQ0iznvH00+AK5uhK1VG2Uk5UtcrayWCtBe5+lVWrVXScO1srXALdonXTOFPla6Fp9nSSGOiWRmyqZ3A65C65frpxr5noL2C8pXrbnexPZ/VUo7WvRCxQ8CpfUUikYqha+3BbbGcuUN+K4+DoT45NADOXxRWTf1uFXpPioi8IQUBNFRyxn/bdEuda2QeKvparprHGFuog1riPXsk7dQIfqpDuladnaCM3X8rRMepGp+3oLV75F72ROpclX+wqNifSZMsEDIAHhEQ3UeiHXXoK+Xc4eVzoHyTs7ar2v3jSSFqQHGZxqZvXRX0uDMp5B9JWFFqZqG9prBxy7E59zB256cVhC3y7dndVV+CdLZr+wAfyicmZhxe53jUbvYiuU1ShiPabFS+Nlu9/uHr2T+ZtvjKv1l/t1/srdesNEnPeir67vW1+AyOQUejbK0wjUODU0d58onxQmr1dJzxLtxpdVijCTkp0lulalucSso85bUOwUK4NzRsl9nyV6fZk+1muHPaaRVTNj+czxUvByUvOM/m4pakk1O6GRrEkHqno6iTalJkvZSY9LMyVTzs9eSSdZK0nh5ImmJpBOC4hsi9VJ1afJu+5U28RrLIBNsXKSwVsib15oIGnWLK5xp7zTLsPJFJ3EdfLhtdNg27Pkm4w1chK6Ht91HapFm9Mp56FT3Uw3yx3hul1nokvgN7PceW5VUlESLWktKmer2yZvzla8dPkWmem5XtKhKBE1qMpbJO80q6fTryPN1cp6bOFOFfmGXk5shOT3SO6xNtOET1TFFslbX+tBPGtjLfL9yZ0xRb6tlI3b6cfHJveB7IG58UqwwxJ583+jcPOW5Dl/OeGfzgShN0hXyAdBsD/kTYLVID92hihQbeCo5C5Ol5PbI/EQ2CeyQ2axP+bJl0GW4yCsE61jC4xAkVR3NnskV05ZT5S9XE5yeBH9kkSquAX4BOIQ4A2IK4AfIB0I/V+U/4pElSj9aPxRMp2uuUMyn1lKk2QG0vEGk+qJG+kndKZykEelWk3fXA7+aKSuW6WqU7VMLUsbCfbMpbIL8QtL4CizQKDzyLEtgRfVybspm3HDO+W0VKqcQTd1l7zFWFER0A/QsSr1ajyC2q/1tC3SGdKNbHqaabjSIYqNEqkA+IKoDXVGo2ABejj9mzRvW7T3RYeDG5ewxyqiE9zgSiXJkBST/f1dvuRW8he+x1WvNnztvcstrESVvkyuvIErb+ba2+XaFa49g6tXQVJjjUkg8dJvdLd0N4Ndns0uL4HHlLoV7ly3kh1e7bbIzv7WtyToN3/uXRJpst/oMV3dpUpO/jfIyfyWoOOrvSM9xkVrLJA+SAdk1laBW5ehoDWKy4S/JM4SnhLTa4TkpgZLv8hEDcjG3VV5FrnC3pJa22Alg/X8a+9NXhtbJ29L/uprrjukpnZ92zA7ntP1Drbc73SnmX40eevorai4VFGH1FEqM2AEdZTbVUmshdRRjaxGfbA2WCersYPVYC2k2/phHlU0SSYCa8FK1Ei2u0mQR7v4bLsmuSqzL1+ctBKZffOSnpm4ZY2CPrZ0nZEaLHtQoY4=
*/
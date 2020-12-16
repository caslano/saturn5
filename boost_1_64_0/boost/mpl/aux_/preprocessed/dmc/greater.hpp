
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value > BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater.hpp
1xjGSbldEu/dDY+Ge2AEfAdGw3dhJ/ieJ+6LSX1RUl8I7GiwlmoknKaOF8t+EQb7fSj7fQTDYZV6/vpm8/6doD4Pm8379yxVO0qlXIxBOyZLO6bI8U9Vz2eX/drVUn+ZTZ4vwRYp1wLeI+XyJL49S/q5AMZAJzwZzoG94Fw4AhbBFHgRHA8vgdPgPLgIXgoXw8tgCbwc3gTnw5VwAbwfXgHXw4XwMbgIlsOr1DqfJ+T4ar0+5RkPtq6lHxZjqVJus5Q7Ds6TchulHzbD1vAJaIdPwTPgVpgMt8OZ8BlYCHfAIvgcXAKfh8vhC3AtfBFugC/DTfAVVbt5FpN2mx/fQMyxRdsPoTBWyr0u10eFtP8N2Aa+qTruUtn/WYPjLpH9rpfzfSNMhythAVwFL4O3wyvgnXAVLIWr4V1wDVwNy+Ddcpz3wq3wfrgdrlHfd57y6A7wrz3uqBDKwWqbPGPIswftdvXTp1Kus7S7C2wJu0E7jIWnwu4wCfaAKbAnnAztcDrsDefAPnAB7AeXwf5yfAPkOAbCLXCQHEcc3AUHwy/hEPg7PB02pZ3xsC1MgHaYCBPhUDgBDoMz4HB4KUyGC2AKzFDllShfzJxqrDbNxT7+venVIZ48E3tiQlw6jG9hLfkmass1gS7j0OSbqI9cEyOSQxok38R/JddE+Y5/R76Jg801sWdH/eabOBg9Sn3knPin8k0cbrkmuir3NiwbK8ZWYGVYJbYPi7mG9YuxZCwPW4iVYluwSqwaa7oEHQyWis1bYulfrM3arM3a/k9bKHbeIY7/F+TMVsL/BxX7byvx+xWdPHH68cPGpbvSRDNe7coNsFCZo2rw7xLQ9+gHYjpryrA7Y7SiA+ir+TetFuBnVV6BVQZagKvwb9sk8TtVA4LVA1wZrc8rEHakcbyzdKPeXzCaAFtn87wCDgNNwGLa1t7gGIPRBfSW+vcY6AKupv54bf1BaQNeC9fHxpMMtAHX4CdD6ydofQC+dLqNjSEmug2tr6Bi0w7NOdL6axqqP0dLOLYSrb+A49Puem8M1ceplirfr03a+CV1+63X3V/XBhG7dF+DHQ3y9C+nnirfdsh1GMz5WxZEe9z9sqqRPnZ4A/WEPeaOoQXfL1xHRnFDTT/ENNb7vUn5rnj81r0fuN8Y+dfEuirFfxzWTMbelFhXWc39pyA3/zxiXf7njNd3rMsdW1SOQWmEzSdmGHeU/vt4M2Udj2nyuydMmDB+ZOLECcO8U6/9xwwbcr6xcXzFPK5mHIc7fOJnxvGewz+u1iZK+XzDjlYr3m0WcdKCa1avTV7YJtQsrlZ/8TPPvLtN5nGoU9Xj0BvN4zgDPeUwqa+Fn/ria/GbpJ7HV0u5RG85fk/N2xevzpOsa59xfWVSrp2fclW6ckbHK78HsLWf+uJ15fT1pdnkPgvjpFwTmGwwf7Ml7Apbw26wMzwZ9oSnwD6wOxwIe6ja4VDFRVO18yyZ96yd71h8LWNJmNn4+07+rQpbd6p23N0OQ5+ofQ7kiHJrHqQ1DzK4ced/6zzIqmsDnwu5Z7P/+ZC1zYW0XRdi64glYdlYMbYKK8cqsWosbCnjvVgylr00pMH0/44500gXpQwBHJz+3z0GUNnR846eOjFx9LBJNa/wrjGAuEg0/rp/l9d4eY//XaXpzzB4j/9O0U0/IO9P3kqU18OAn6lHGOQGfF989ZNn6F7Y9/hK1fkKLv+S4osO9ui+xonuy0jfXyS+neK71NC3vV58DxHfEfJOPEb6eDT2I77jHzT0nc7CVZkzA3h/cevmG3HyHI4ZqOR9tL0zVGsxhrrK8DpHGXmP+MGlra/5O0qOhWtV02+LQ0zGXfRtz3UG0GY=
*/
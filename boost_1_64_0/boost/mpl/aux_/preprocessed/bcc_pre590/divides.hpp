
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "divides.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct divides_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< divides_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< divides_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct divides_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct divides_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides
    : divides< divides< divides< divides< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct divides< N1,N2,N3,N4,na >

    : divides< divides< divides< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct divides< N1,N2,N3,na,na >

    : divides< divides< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct divides< N1,N2,na,na,na >
    : divides_impl<
          typename divides_tag<N1>::type
        , typename divides_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, divides)

}}

namespace boost { namespace mpl {
template<>
struct divides_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  / BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* divides.hpp
LMmyCjGXfRVd13v64yhsFcI+0LuSMJJTKslNkltIniH5iKR7FblJ0hdz20uqiFdFvCphR7i2Ss5vX1NFfqkS89w/qqJnqztGBpBUkcwhWVpNXJK3SbaT9JpMOMk4kjTJEpI1JBsmi3nwWyeTG8fTvToXnu5LSKaTLCZZRbKeZPPxYl589yliXny/KRR+kikk80mWkzw5RZ8jv2GKmCO/na69p5LbJNNI5pEsJVlDsp5k89R2e0P7r/3X/mv/tf/af+2/9l/773/z99/+/q+rSSf+E+v/96G57xf2pDkfk71vfdo4tNjb8y/qTZX3zmNlfDHh3Y7X8GZet0+E/QjPenPL5wd4Y6IWBybXiQPl9wEnMsXnAE8kE1ng3oTxzoxzGEUAo4lYRMG7mTifWS3wS8iPm1Jd6NuTgbqmWDQWr09meM8BvL87Pw+H+Tx1oc9jfXOmJmpjvRiLObHejInj/gGyXy7tSeCC4F2ew03x7PRUDGG5nPDOEo9JXLrdjfFcJh6tiWeidZk0nl1Kz65PUzjZv8A4GgR+BeGjZvp4PDndx7F+YzbF4yB/DivmwQ/BGoEBJFfRoP2WU9nWwwmVba6pi2OOXOeW5shhjcAV9Dwdch6s2/Dm+9eLJQCkk2sAapobOG3UeXsb4Z9hsDsdRfILcm/UDPZPUUVFVGaeVszb8/eg8OKTMzQfW66vKREZGWsWfP9SyfB5vcBrpDzn+/dY+HckIqQC/i335xlK/7KhjD2NoxFaM99QfcdyvOM4vOMY8Q7yUPCOXNJ6S+ve4eeDvl0EcGsH8Y6b6XogBbxcvKM2kYxxBm+N33tGuvR4oontQU3xJkopJW/sR5PB4kaar8C7y0j2IsknuYbefUqS380FpCYWE0mO94d44Bx6P9V7R3Me25PeEryXhBwI1ulc24vvKa6EX46GX3pjjnwvxHVPfx6u7pfGmkyW/dOa+PDmjr6aFPax63vp7+uFeelvoPy96qW3V/6U91HtIg5Pr/cK8Q/vuxJWDg+luBfH3Mty6K3nmc3uynU4XlzFGuNeOeH1Tn27kn9IDvXKUEqud9qKcozHg/VOfcC5uZcI+zR5r+W5/pibfUsnCjuu9V7Ep5WwZ5sbI61YN7ZrpDu72ZihZ5EHjxT/H1BSOmhYBLo8qRvq615tDnSDfd2zUjfI190ldQN93flSN8DX7R/oBgbv/X5moAvee7nUBe/dW+rYvV1J1yHQjeD7D9L+/XC+fzG4H8b39wf3Q61yt6tS71EDyfd5yOcJ4L2wB08a997+ZLx2Tlk3J+rNbLAOT81rW5Avsk1pLl/+GromciOVy3KeqEyLdLq9l14XLEWeuBbl72qSO4izJKvmiTl81Ezryp5eFtT8tx3vOh9l7xySO716J6e/Kxmf3aq2T40Htf6OYS76pA6ifhtF11XEy5ulvydDRTzdnJrFxQlh6+18ZQdHPRfe9oq2H+0b6sLs3LTVvvGx7VzmtTRE50HUBfTSSD8Kz3XEGz9L1gUfod6Y7gUAum2oX8TTyAfgUfUS1BdRuHMP6ovLjfv7cH8f7t/F/QPIO6P9NSmoFGNIz1NIHiLOk7PD41n05tpep6rliJxQ+jWIbxlelJVMECdq/Kv5cTE8MErkfco/og0eNUf6PxanIpWa2+p872pvvfPvua3rKPLjTnR91CtjeI/fIY2loplEQ5LfNa7V7W2XHmedRu5w8yrXjb5H/oglGsj3St9LtjNBPfQI+YPezfdryc2He8l65jGjntlA94959+TL2lw96x5G/GaEu6x70s+bNZnp/v5jz5DuV/QsB3ZGfK7f1i0hj31EmWch3X8zl8IBv60j/hOeX3C/HvcZpd0=
*/
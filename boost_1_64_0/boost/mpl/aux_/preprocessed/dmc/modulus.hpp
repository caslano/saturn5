
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
nCvnawG8DWbC7XAh3AcXwUfhYvg4zIINcAn8PlwKX4XZ8E24HL4DVwRjgEvfCPSKf/oY4OPFvyvgADgBjodXwivhJDgHToY5cAqsgFMD+tHXIvp/ILExRrX66d++JfXmSRgPvwMHwu/CIfAQvBR+D06G34cZ8CmYCRvhUvg0zJFYxjfC52ARfB7eBF+AH4dHYBV8Ed4MfwA/DX8IPwt/BHfDl+Be2AQfhi/DI/Cn8CV4DL4Mfwbfhq/AGPL0K5gEX4ep8NfwEtgMZ8I34Cr4G5gLT8Ab4ZtwPXwL3g3fht+Ev4MN8F14GJ6Cz8PfB2PESz8KLFCcv51Svg/C0fCzMB1+Dk6Eu+Ey+BC8AX5eyu8LOv31YfTXiv57RP820X+v6N8u+u8T/XWi/1N6/4ut9e8V/V8T/ftE/9dF/8Oi/xHRv1/0f0P070PqRX9PqX99tXyLfqfod8ExsBhOgGvhNFgi9asUroE3wbVwHayAZXAjrIC3QjfcBT1Sf7zwO/A2+JzEwH4d3i715Q54AdwSnOci78MgVdFepWvp4HjYA14h/k+AyXCiTk+66JmuavdETy4cCq+Do+ANcCpcrRtfVS16ZinGV00S+1NhCpwm+qbLdTsDIo6Zoq8WaRZ994m+PnCz6Jst+hbAfjATJsGFcl9ZBEfAxXAszILT4RKYC5fCdXCZ3Fey4VZ4DayFy+E9cEUwf/IOCOco8hcv/iRK/pIkfwPgSDhQ7m/Joq/KIe9l4MuirxcsC5knNkz0DJdyHyH5uQQuhCOlfo2ClfBSuBmOlvbqMmmnxsAvwLFiPw1pEvv9tfQ8+8i9j41y1B3XIscNCHucvHfAuHaOS18X3m5jF46vi46ti46t+18eW9eZcXXugzGO3cgR5DSS8h3idCNlyA6kETmBxH6XGNxICVKHHECOI90OEV8byUWqkX1IE3LmUHScXnSLbtEtukW36Bbdolt0i27RLbpFt//f7aMZ/1/YZfP/U9vi//F90Dy2+LxU/rm+bWzJnOVZ2tCSdCdDS/CZ6eredsdHBb77L+VHoafMMA5sl8kmxGasyqY2+Gelu4iR6p2y2es8tc00lU0Gr3WFzX2K2H3nYzNdZdNburY831fpcbU/9izEZnCco4fOaDd69OOovdq+/LK1pjFxMebyuADf8sy+Ee9g1bLF8+ba9ut+LOCXwV6twt6F2HMr7JV6vZUuT+TloC/7swp73bFXrbAXrGIRlD15NNl0d1PbrFPYpIp1yuZssXlSMSehBzb3KGwGq5iTEWk2xlUqyjd4PnNljkA/sRuH9MRuY6jdDsTJUJ3P18TeULGXhvTCXnOIPRrJ8R1pM7SyrZLfveAf+e1bbxy/mneB2ofYG8w+dKQNsePDSYUPffAhw+yDXEfakPzIfWgvTkqZzG9YhvRGFiOx+OFW+CHnv91xlGYf1HFSrhIfzogPG8QHDzIqmToR6kOFJ6L5Tf7rDAbGl8byR3SbxjnqffGJ4lvEl43iS/Vqoy+VbqfHVdz+uMyQa15lO9gGnOpubnfitHvbmjbb0oZ3+D7eV8rAMN+sh9luX+ymW9ll7HgFqwhheG4k14VmuyrE9gmx3V1sXyC2M6xsM3CzNL9saeX6ApcngrZPZbta5jF45FyXI/HYzlbYpv6HZNt+PaTeGdqDy6U9CNQFfjMnx+hbmoyxzxDfpotvzWrfDMViZ6xzqG99db616lL6F2w39oh/g+W8pSLvJlNnWuebll5RRHE5g5eLr8Br/1wFrxXx6c9aDGm32JdxrrG9zGNrz2I/D/syzlVfRAystT+u9n30eNcZ7VUr7J2Xwn61Pa2psm0vo795HG+33uZxvN2wt0dtTxs=
*/
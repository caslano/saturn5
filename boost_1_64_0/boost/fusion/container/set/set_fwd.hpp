/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_SET_FORWARD_11062014_1720
#define FUSION_SET_FORWARD_11062014_1720

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR) \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_SET)
#   undef BOOST_FUSION_HAS_VARIADIC_SET
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_SET)
#   define BOOST_FUSION_HAS_VARIADIC_SET
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_SET)
# include <boost/fusion/container/set/detail/cpp03/set_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    struct set_tag;
    struct set_iterator_tag;

    template <typename ...T>
    struct set;
}}

#endif
#endif


/* set_fwd.hpp
P9XyoSZO/dPJrmvZOvdT9XFES3+B/hJHKOmksmz1cWh/s64rDvv2NVGZjy6OUzVKPkPqI+Io1MdxTb9jZvvtufr9dnX9iZfn/vlIHM1kuRTp43D7t600xw6OGC5KDEtJDeUcflXb4JbGGNhVK8XzU1xuT02e9Rf8kbqNN33W31cS0+ek6kxbaIxJ3ZW79m19A/1z35iffWZKfPVP2eM7Jfvc4ep7fbzhslRWS7wrSXVaUa9TxnjVXUC3nuVjFq++b7o9Po+P7fF93Fo/dv1qeY6eMpanNxbhp+Qp+Nh1fCYDn1/1WQNKH6c+xWofJ+kbr4tfnj2gf25InuG5IaFXfEZ9zixt32k5RsrmMJ+j7JwZmZK/C2qeRe7yWRCxzvnO1DzXXqbNYchq9lMM231PeZbfKjnGWi7HWD6faduTAaizklNKs5yvcvynW9fOSNmDKlA2huN91KnYXrbcVCEjX6unPuwxxF5l2VX/Ur/s4k1+i4JNlo2/SVuHmrR1hP55f7p+bMV1Zdx6OZ5+CGlTOkSa1Et/+Fqq9TLuK9P1Uv87W4q6OdaPD/XbCz6XOuu/l2bPOdQ9iyBJns83VNalgY7j9TNXqPd1bUds9dWtUxXl+XcHZD/mddlPtZrEoO6uXmO5pd1f1ca3S+J7ReLbKftZ1rMl41N3t0rRJ1PKLbGOx5rsb8Xr4jPez0O+uJL7h73k+X6ZsmynybKNt/fnytTcKcWSvbb2tO33fV2yf+PO8rbxPehX9siYNyvWWPzbsy22v9fCb/3gPu6P2W7e7879/pPm/R5d9/cz70/oul+feX9F9/tPmvfzdL//pHn/QNf9J837Mbrfv9Tdfozm/RJd988079/ouv/qqum2eiX9PuiBBp1+efquw5Eb23/j47qfqvRP4bqBWT8o/ZhQs7ErzsEQnIt9cJ46Vo9cD8DtJv3QLLb+doCBWB7HYAUch5XRilVwNXrgGrwJn8Pq2rFx5TpBK5P+S+WJpypWwJZYUeIrLCfn6eX8vTJdkH2MYNtruPSfGYFtMBKH4EiMwlGYhNGYjaNxIY7BTRiDu3AsHsVxeALH4+cYZ5F2wkrST6kuJqIvJmEgJmMIpmA0TsHxOA2n4HTMxTRchum4BjPwYczEl9CKezAb38Yc/Bhz8Ru8DX/GGfg7zkKv8ixnbI5zMQbn4SRciBm4CG/HO3AFLsb1eCfuwyV4CJfix7gcf8MV+AeuRGVM+7uxOa7GQXgvDsP7MQrXqO0l1xtwosl6tVb6na3D1rgeO+LDGICPYH98FEfgYzgKN2EsPo7S/1euKbDMTPr/dpJyAtALA7EZdsEw7IaDsbuUE4wLsAcWYE/cgH3wWbwFi7AffoXhWJ5y+6MnDsCmOBA7YAT2wME4Boeo7SPXHPBBk/bZIXG/gL74osS5E4fjSzgRX8ZM3IX34Ct4L76K6pijUk4tk+/dRhnLeRPWxMdR7ad4hem2ynTbZLrtzuk4t+96ujdluv0y3QF1OtJx1/0bP5XpirEGfqYd0/0K052Q6d6T6d7Xbo+uMN0lme4Xme5XtG935Vw35phsd5VnQ/hgVQzFahiON2EmVke1vidc939tKP0KG2E9vFkdg1/OM8v553zDGPzeyvcUm2BjbIotsRm2QR8MwebYH1vgCGyJo9AX52MbXIJ+uBzb4Spsr8Yh55TxE5M4PGXMudrYFetgL6yLEVgP47A+TscGmIkNcT02wkfRB1/E5ngcW+BJbIn2fspyvhgfNumnPFjGDh2C3XEo9sRhOBKHYy6OwFk4Eh/EKJTlzXle17+z/5T+3hewJf6AbfAi9sAfNf3tI2U+W3X97fVjrk7F9piKQThN4p6OozA=
*/
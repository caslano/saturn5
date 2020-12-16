# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_VARIADIC_SIZE_HPP
# define BOOST_PREPROCESSOR_VARIADIC_SIZE_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_VARIADIC_SIZE */
#
# if BOOST_PP_VARIADICS
#    if BOOST_PP_VARIADICS_MSVC
#        define BOOST_PP_VARIADIC_SIZE(...) BOOST_PP_CAT(BOOST_PP_VARIADIC_SIZE_I(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,),)
#    else
#        define BOOST_PP_VARIADIC_SIZE(...) BOOST_PP_VARIADIC_SIZE_I(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,)
#    endif
#    define BOOST_PP_VARIADIC_SIZE_I(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63, size, ...) size
# endif
#
# endif

/* size.hpp
nIfLcAGuwBW4EldhQ/rbhI1wMzbBL7Ap7sHmxnpiC8zBVpiLxuvpOrY31hPD8C52wCqu1ut118QkbILJ2BIHYxsMxB5YDvviXPobgvNwGM7HUTiU6WNxGGbicJyEKfgmpuIcTMeNOAq/wgw8ih3xIkbg99gF8zEaXTigxaAbdkUf7IZVsDvWwx74tOSNJG+PvbAT9sF47Id98Dl8AWcplhNn4wxMtDD+OABX4Yu4DsfiXhyHB/AlvIQT0MddqYlYAadgFZxqLA++hU3wbWyFM7A9zsEonIuxOB8TcAGOwkX4Ii7G12X6RFyCb0j5m1L+Ni7D+bgcP8eVuBdX4de4Di/gx6g8+I4AXfEzLIGbsSR+joG4BSvjVqyKO7Am7sRI3IVdcQ8OwyzMwH34Eu7HyXjAWC48iB/gIdyC2bgDDxvLh8fxGJ7AK3gS/4yn8S6ewd/xLAZ4clzE2ngeG+ARDMEcjMQ8TMKLmIKXcTReweV4FTfiNdyK1/Ew3sCT+COew9tYyovjH5bF+xiEv2Bd/BWb4ANsjQ+xHT7CJFROzB+d8AV0xgnogm+hK86S8uXogSvREz9BL9yP3ngEffCE5Ockv4Al8B6WxN+xFFbw5riIERiI0VgOe6LR73NYHpMlH42VcDI+gWuxKq7HapiF1fEA1sKjWBtPYR3Mx7r4C9bD37ABuvhwfMQnMRifxqbYCpthNDbH/tgS0/EZfBl74RRsZIwXNsaZ2Brn4rO4WOp9jG1xK4ZgNobiaWyHf8b2eBfD0KOEUuFYGjtgOeyItTESg7ETtsTOGIZRGIldsDvGGeOI3XAEdsdXMAbfwz64APviMuyHq/A53IzPG+OK/fEYJuC3mIhXcQDewoHGuGISKl+O0+iDg9AfB2NFHIJVcCg2wGHYGIdjW0zBCByBz+NITMJUDHNVxZ2vbDtXOaW99RzlAKMOz5cQm4hs4jLxgAjgTaY+EUb0I4zzmTNwBrGK2E2cIW4QLuEWVYkIJsKIXkQaMYXw6/2PndecS3A+83/9XOZC5zH/35+//M+eu/zfPm/ZdL7yv3eu8t8/R7mo85P/6XOT/9nzkgudk/wvnY/8+Fxk9Q+fh/zPnIP8nz7/eImcg5xnOg95Ccer7cSJ8Mfn/z5+PH48fjx+PH48fjx+PH48fjx+/L8+XIhB/7Xz/5NHjeo/NMl6BYB//xoA98sVvgaALit8DQDKCl0DQMqclPncVnu5szKfx2rvw0XqK1OZa0FdU5mb7VoB9jJ3XcYZvaYyD10WHUNr5u1BWdHnyr5gOlfWxVnux0w4yb+vdi7P345vOSnjq93UxKT+Msy2c1cs9vMeijxHULflP3/buYfyo4uiz7WU+oXP87OfP7tcT39enyMbWV7/ptf2+/wsPc2XZfey/UZ4ni5LUfUpbUFU5veCbsr6G7p01n2U/L7tTb+iz2n1+Jvfq7mW+vkt+29mAs3nuNrHQpd72H43I+tc6NzNDOk834l+xZ+Z4ve2Hm8Zan32ZuFzN23r/Gddt70qpyoXNf7SV+FzNIsce3td2++l05KT0+1jH/6OMX20peActz/NMPIAZf/9tz5Hz/Zb+BG6v7lOBcvOGiePzVC28+s+0P2Vt+jc1l+g7RzA3rr9WqdC56Pp6TeYnqinf2iaPnL0CGOdZHm76ukbnfLVe3+zzOw/8npOtY1luq4/Vrny5UgR54PZzruwz0+f82U736GObt/V6Vn1V/bOBDCq4gzAs7sJCUkISYAAAZKIiHgh9+HJKYRbwiVYQyAJBEIISbiUKiIooCBVWhUvvKgCVYrgUVFAQVERwaLiUcUbjwpaD7z7vX//fW923a3Q1p4sTL6df/7531w=
*/
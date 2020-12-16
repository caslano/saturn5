# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_SHIFTED_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_SHIFTED_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/debug/error.hpp>
# include <boost/preprocessor/detail/auto_rec.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_ENUM_SHIFTED */
#
# if 0
#    define BOOST_PP_ENUM_SHIFTED(count, macro, data)
# endif
#
# define BOOST_PP_ENUM_SHIFTED BOOST_PP_CAT(BOOST_PP_ENUM_SHIFTED_, BOOST_PP_AUTO_REC(BOOST_PP_REPEAT_P, 4))
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_SHIFTED_1(c, m, d) BOOST_PP_REPEAT_1(BOOST_PP_DEC(c), BOOST_PP_ENUM_SHIFTED_M_1, (m, d))
#    define BOOST_PP_ENUM_SHIFTED_2(c, m, d) BOOST_PP_REPEAT_2(BOOST_PP_DEC(c), BOOST_PP_ENUM_SHIFTED_M_2, (m, d))
#    define BOOST_PP_ENUM_SHIFTED_3(c, m, d) BOOST_PP_REPEAT_3(BOOST_PP_DEC(c), BOOST_PP_ENUM_SHIFTED_M_3, (m, d))
# else
#    define BOOST_PP_ENUM_SHIFTED_1(c, m, d) BOOST_PP_ENUM_SHIFTED_1_I(c, m, d)
#    define BOOST_PP_ENUM_SHIFTED_2(c, m, d) BOOST_PP_ENUM_SHIFTED_1_2(c, m, d)
#    define BOOST_PP_ENUM_SHIFTED_3(c, m, d) BOOST_PP_ENUM_SHIFTED_1_3(c, m, d)
#    define BOOST_PP_ENUM_SHIFTED_1_I(c, m, d) BOOST_PP_REPEAT_1(BOOST_PP_DEC(c), BOOST_PP_ENUM_SHIFTED_M_1, (m, d))
#    define BOOST_PP_ENUM_SHIFTED_2_I(c, m, d) BOOST_PP_REPEAT_2(BOOST_PP_DEC(c), BOOST_PP_ENUM_SHIFTED_M_2, (m, d))
#    define BOOST_PP_ENUM_SHIFTED_3_I(c, m, d) BOOST_PP_REPEAT_3(BOOST_PP_DEC(c), BOOST_PP_ENUM_SHIFTED_M_3, (m, d))
# endif
#
# define BOOST_PP_ENUM_SHIFTED_4(c, m, d) BOOST_PP_ERROR(0x0003)
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ENUM_SHIFTED_M_1(z, n, md) BOOST_PP_ENUM_SHIFTED_M_1_IM(z, n, BOOST_PP_TUPLE_REM_2 md)
#    define BOOST_PP_ENUM_SHIFTED_M_2(z, n, md) BOOST_PP_ENUM_SHIFTED_M_2_IM(z, n, BOOST_PP_TUPLE_REM_2 md)
#    define BOOST_PP_ENUM_SHIFTED_M_3(z, n, md) BOOST_PP_ENUM_SHIFTED_M_3_IM(z, n, BOOST_PP_TUPLE_REM_2 md)
#    define BOOST_PP_ENUM_SHIFTED_M_1_IM(z, n, im) BOOST_PP_ENUM_SHIFTED_M_1_I(z, n, im)
#    define BOOST_PP_ENUM_SHIFTED_M_2_IM(z, n, im) BOOST_PP_ENUM_SHIFTED_M_2_I(z, n, im)
#    define BOOST_PP_ENUM_SHIFTED_M_3_IM(z, n, im) BOOST_PP_ENUM_SHIFTED_M_3_I(z, n, im)
# else
#    define BOOST_PP_ENUM_SHIFTED_M_1(z, n, md) BOOST_PP_ENUM_SHIFTED_M_1_I(z, n, BOOST_PP_TUPLE_ELEM(2, 0, md), BOOST_PP_TUPLE_ELEM(2, 1, md))
#    define BOOST_PP_ENUM_SHIFTED_M_2(z, n, md) BOOST_PP_ENUM_SHIFTED_M_2_I(z, n, BOOST_PP_TUPLE_ELEM(2, 0, md), BOOST_PP_TUPLE_ELEM(2, 1, md))
#    define BOOST_PP_ENUM_SHIFTED_M_3(z, n, md) BOOST_PP_ENUM_SHIFTED_M_3_I(z, n, BOOST_PP_TUPLE_ELEM(2, 0, md), BOOST_PP_TUPLE_ELEM(2, 1, md))
# endif
#
# define BOOST_PP_ENUM_SHIFTED_M_1_I(z, n, m, d) BOOST_PP_COMMA_IF(n) m(z, BOOST_PP_INC(n), d)
# define BOOST_PP_ENUM_SHIFTED_M_2_I(z, n, m, d) BOOST_PP_COMMA_IF(n) m(z, BOOST_PP_INC(n), d)
# define BOOST_PP_ENUM_SHIFTED_M_3_I(z, n, m, d) BOOST_PP_COMMA_IF(n) m(z, BOOST_PP_INC(n), d)
#
# endif

/* enum_shifted.hpp
sW2lFVGGnYz1OydqTv3eTg7mrEyeBpPNwqorkptOJYvd+h30pd4sni5Qbd7M1DHiYGMYQnP9tD6ReL2VEnE7EWEWndWCdDjZ7Abp1jEWDmRmQsE7J9bMy0yyXSd+BGPZzih2sh90lpHbeNr0Te6KD0xsyk23kgZWamur66shwwUIxhHDjXllRcPMKm1s8/ZXkdSWs6nWLS2YM7vBFs0pkcxYVKtNTyVloq7SdVwk+4Pxx5S2mbI+P1ZcpPA1NNrwFKVk1uIq40co54SM9iOSvXJA3bGtytVer1Pya52crTSkeU9XpxE/IxUKKa+lUQpY8ZwgJ2QWrV52hFNR2H08OZFQ9rTUTtUotSE/ddrZTP52qVXBDmubLq8JJXYndCCRXRR3BjLiQ/vccmOL+nrQv4l7YxfKDFEkX9x/3sVpfEtkYnX9fVKX+TV2k9YLSFVKYf8VFVMJkWcDmkjl23sSU7nGP3cSc3Nhteoa2NScQM52kDIdjFoGtmO22DK30t/UVH+yyXjJSeJld0e2n8RUdkp2nMRcdk229DeXbdjqHW5H5dz6ujmoosmEd/WTmble04N8d38z6qKxLvd9T+usQGL1bFAwtyeztieC2UEz02dmdcpNz3hp8/PVvUMyrG/ZdZD3hPOp7qnrTHo+ldCwj8TKaKCXsraQM/OXvx1g9W6qO0f6l3DfhlW2sFuqnhxht4zWXjGn3qbPj6xrTNBa/lXWBfPcg1XHR4zEnPFttpKnnCuNbIGpnNtYbQsBu1MLI7l2MVk9zh/Q1I6T5/nyYyroBb293bLw/WQcJz3HmF9XWR0sQu72PN3QXZor9cbM3nkJFphRhb8qU5Oy81UrC2z9zMxOl+lNQ9fokWK407vGhRjzUh1uRlHWtumqmriZWPSoPtndqudY9VpQi5lPEamxiZFqEElDRU11ZcUV3g361bFZmHYDmNkx5MsGMKFOXmxNr4tM/RIULcCA/vUsaGUYN3dAs1wZjba6ZmCzGxb1lKl2Z+aX83R3+XaRWvXO5l5g1ztX9ZMzwWWMbotMdM1lQ9YY+R7mwkoxQ4NNcqs3SRnU9Urpss529ZlEAleKVO1ISZb1tnKnfn3ki1WINieVbkqTaYvDPczvNi22Xxv5jl37CNak/5rqtVur9FHCVX+ziaDKSNBo03vjFGbicplx+ZXGb8+/X8xjXTamXWJ7QNM/BzWGjelBX2MY/i4Tj+dncwtbzALAGs+b1GaWQr0xlvXYevCKpNyXmgBwV3mUBlb6vGikYsVPRXb7R4Fz3f6XJ7X0opOOJDkAwzOXbBCiOmdvlyvhspr9W8vbuyaIGmu+8cjebg1WN5s0DufEXxD5ac0Ib7K3hJX0cN1nsYyxd6el6lHP2zrS2ftaLFd7vcQv5HdBul98/WTm6tbERBb27U9e1U/OTiQvI6G83RtjOXZvCWWkeosLyYpYbns4LWaONDZTf2Gkrt3Us4TDGMMHSyzddFlMO3yePWMXSO727lAdvtJzeruwFqluLzPrBa+NVtf0pNPCAeZseHmh/3k0dcS0YybPTGn/arCzTmSVwZ42kf3UlF6xa7Xnfq1Pkeywcz/e9/YV709qT95mL+/X5n5oYDN2ptK6JmZ+x1vXyc4V8QPmqM38GLl3g+wyejTc4YVL4Q6viqhk+B2flScxYeLiWvYBRasrOndeUMC/wbLGTfCydrXSpCF8NPF0u8ij82irRZ4qx90mbn4D1bsNb4dN6b7X9Cj0oQ/MGkWm3h981qE2C6CUDBsD80Nf5pZbqY1IIr4lsOvL3M0puyKeJadloxX184y8IpOpd2cOhHetwQWe715wk3udTl2Ykuo7YtiDEK0k+KWBX4c=
*/
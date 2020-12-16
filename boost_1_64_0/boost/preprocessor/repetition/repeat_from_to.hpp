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
# ifndef BOOST_PREPROCESSOR_REPETITION_REPEAT_FROM_TO_HPP
# define BOOST_PREPROCESSOR_REPETITION_REPEAT_FROM_TO_HPP
#
# include <boost/preprocessor/arithmetic/add.hpp>
# include <boost/preprocessor/arithmetic/sub.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/debug/error.hpp>
# include <boost/preprocessor/detail/auto_rec.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_REPEAT_FROM_TO */
#
# if 0
#    define BOOST_PP_REPEAT_FROM_TO(first, last, macro, data)
# endif
#
# define BOOST_PP_REPEAT_FROM_TO BOOST_PP_CAT(BOOST_PP_REPEAT_FROM_TO_, BOOST_PP_AUTO_REC(BOOST_PP_REPEAT_P, 4))
#
# define BOOST_PP_REPEAT_FROM_TO_1(f, l, m, dt) BOOST_PP_REPEAT_FROM_TO_D_1(BOOST_PP_AUTO_REC(BOOST_PP_WHILE_P, 256), f, l, m, dt)
# define BOOST_PP_REPEAT_FROM_TO_2(f, l, m, dt) BOOST_PP_REPEAT_FROM_TO_D_2(BOOST_PP_AUTO_REC(BOOST_PP_WHILE_P, 256), f, l, m, dt)
# define BOOST_PP_REPEAT_FROM_TO_3(f, l, m, dt) BOOST_PP_REPEAT_FROM_TO_D_3(BOOST_PP_AUTO_REC(BOOST_PP_WHILE_P, 256), f, l, m, dt)
# define BOOST_PP_REPEAT_FROM_TO_4(f, l, m, dt) BOOST_PP_ERROR(0x0003)
#
# define BOOST_PP_REPEAT_FROM_TO_1ST BOOST_PP_REPEAT_FROM_TO_1
# define BOOST_PP_REPEAT_FROM_TO_2ND BOOST_PP_REPEAT_FROM_TO_2
# define BOOST_PP_REPEAT_FROM_TO_3RD BOOST_PP_REPEAT_FROM_TO_3
#
# /* BOOST_PP_REPEAT_FROM_TO_D */
#
# if 0
#    define BOOST_PP_REPEAT_FROM_TO_D(d, first, last, macro, data)
# endif
#
# define BOOST_PP_REPEAT_FROM_TO_D BOOST_PP_CAT(BOOST_PP_REPEAT_FROM_TO_D_, BOOST_PP_AUTO_REC(BOOST_PP_REPEAT_P, 4))
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_REPEAT_FROM_TO_D_1(d, f, l, m, dt) BOOST_PP_REPEAT_1(BOOST_PP_SUB_D(d, l, f), BOOST_PP_REPEAT_FROM_TO_M_1, (d, f, m, dt))
#    define BOOST_PP_REPEAT_FROM_TO_D_2(d, f, l, m, dt) BOOST_PP_REPEAT_2(BOOST_PP_SUB_D(d, l, f), BOOST_PP_REPEAT_FROM_TO_M_2, (d, f, m, dt))
#    define BOOST_PP_REPEAT_FROM_TO_D_3(d, f, l, m, dt) BOOST_PP_REPEAT_3(BOOST_PP_SUB_D(d, l, f), BOOST_PP_REPEAT_FROM_TO_M_3, (d, f, m, dt))
# else
#    define BOOST_PP_REPEAT_FROM_TO_D_1(d, f, l, m, dt) BOOST_PP_REPEAT_FROM_TO_D_1_I(d, f, l, m, dt)
#    define BOOST_PP_REPEAT_FROM_TO_D_2(d, f, l, m, dt) BOOST_PP_REPEAT_FROM_TO_D_2_I(d, f, l, m, dt)
#    define BOOST_PP_REPEAT_FROM_TO_D_3(d, f, l, m, dt) BOOST_PP_REPEAT_FROM_TO_D_3_I(d, f, l, m, dt)
#    define BOOST_PP_REPEAT_FROM_TO_D_1_I(d, f, l, m, dt) BOOST_PP_REPEAT_1(BOOST_PP_SUB_D(d, l, f), BOOST_PP_REPEAT_FROM_TO_M_1, (d, f, m, dt))
#    define BOOST_PP_REPEAT_FROM_TO_D_2_I(d, f, l, m, dt) BOOST_PP_REPEAT_2(BOOST_PP_SUB_D(d, l, f), BOOST_PP_REPEAT_FROM_TO_M_2, (d, f, m, dt))
#    define BOOST_PP_REPEAT_FROM_TO_D_3_I(d, f, l, m, dt) BOOST_PP_REPEAT_3(BOOST_PP_SUB_D(d, l, f), BOOST_PP_REPEAT_FROM_TO_M_3, (d, f, m, dt))
# endif
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_REPEAT_FROM_TO_M_1(z, n, dfmd) BOOST_PP_REPEAT_FROM_TO_M_1_IM(z, n, BOOST_PP_TUPLE_REM_4 dfmd)
#    define BOOST_PP_REPEAT_FROM_TO_M_2(z, n, dfmd) BOOST_PP_REPEAT_FROM_TO_M_2_IM(z, n, BOOST_PP_TUPLE_REM_4 dfmd)
#    define BOOST_PP_REPEAT_FROM_TO_M_3(z, n, dfmd) BOOST_PP_REPEAT_FROM_TO_M_3_IM(z, n, BOOST_PP_TUPLE_REM_4 dfmd)
#    define BOOST_PP_REPEAT_FROM_TO_M_1_IM(z, n, im) BOOST_PP_REPEAT_FROM_TO_M_1_I(z, n, im)
#    define BOOST_PP_REPEAT_FROM_TO_M_2_IM(z, n, im) BOOST_PP_REPEAT_FROM_TO_M_2_I(z, n, im)
#    define BOOST_PP_REPEAT_FROM_TO_M_3_IM(z, n, im) BOOST_PP_REPEAT_FROM_TO_M_3_I(z, n, im)
# else
#    define BOOST_PP_REPEAT_FROM_TO_M_1(z, n, dfmd) BOOST_PP_REPEAT_FROM_TO_M_1_I(z, n, BOOST_PP_TUPLE_ELEM(4, 0, dfmd), BOOST_PP_TUPLE_ELEM(4, 1, dfmd), BOOST_PP_TUPLE_ELEM(4, 2, dfmd), BOOST_PP_TUPLE_ELEM(4, 3, dfmd))
#    define BOOST_PP_REPEAT_FROM_TO_M_2(z, n, dfmd) BOOST_PP_REPEAT_FROM_TO_M_2_I(z, n, BOOST_PP_TUPLE_ELEM(4, 0, dfmd), BOOST_PP_TUPLE_ELEM(4, 1, dfmd), BOOST_PP_TUPLE_ELEM(4, 2, dfmd), BOOST_PP_TUPLE_ELEM(4, 3, dfmd))
#    define BOOST_PP_REPEAT_FROM_TO_M_3(z, n, dfmd) BOOST_PP_REPEAT_FROM_TO_M_3_I(z, n, BOOST_PP_TUPLE_ELEM(4, 0, dfmd), BOOST_PP_TUPLE_ELEM(4, 1, dfmd), BOOST_PP_TUPLE_ELEM(4, 2, dfmd), BOOST_PP_TUPLE_ELEM(4, 3, dfmd))
# endif
#
# define BOOST_PP_REPEAT_FROM_TO_M_1_I(z, n, d, f, m, dt) BOOST_PP_REPEAT_FROM_TO_M_1_II(z, BOOST_PP_ADD_D(d, n, f), m, dt)
# define BOOST_PP_REPEAT_FROM_TO_M_2_I(z, n, d, f, m, dt) BOOST_PP_REPEAT_FROM_TO_M_2_II(z, BOOST_PP_ADD_D(d, n, f), m, dt)
# define BOOST_PP_REPEAT_FROM_TO_M_3_I(z, n, d, f, m, dt) BOOST_PP_REPEAT_FROM_TO_M_3_II(z, BOOST_PP_ADD_D(d, n, f), m, dt)
#
# define BOOST_PP_REPEAT_FROM_TO_M_1_II(z, n, m, dt) m(z, n, dt)
# define BOOST_PP_REPEAT_FROM_TO_M_2_II(z, n, m, dt) m(z, n, dt)
# define BOOST_PP_REPEAT_FROM_TO_M_3_II(z, n, m, dt) m(z, n, dt)
#
# endif

/* repeat_from_to.hpp
7mLoX1+n+t0P1gSw8u9/4U/+274AgP+NH+wi8H4gv/60bgI28tf+0lgAf3OvR0F6B+C/Xv+++FT36yQQv8WXgvwtvhQU6HoAPgAMdP8XAD4B7gl0/zcAxrv8c/lRAfg+/hH6X8Q/UgOOIfx1/KU/l9eveEt/9icFcCNgyH8Rj4kfuAbaX8Rbov3lDwSKT/Tgj0T0W7wekP8R1uhD+QC/+P7X8Q9OAA6Kz3UDvJ/st3g95H8RrwcoT+A32//af/AM4KB4Xvfxjc4BDopvRAZcD/+3eEMEv8UbIvxzvKG/8j/fBDDwvDz467Dcn3/0l6L8C3+pBMAOYf/6eTl65Iv3HLhH6L+I/yU8+ufnRRrAcH8R/wILwKOAYfwWfwrzt/hTWL/Fn8L+c/ypB72M81v8Jbw/r7M9+OOS/EV8JGBdFBgv/D+e0f+KPrjvn3D/Qf8E+Br88sEBUpCvA+Q9x3zcjwNw6EcfBtxfvgoP9evd7K9x8sn4r/mFDLlf6c09f9xjD/u41x3ucQ88/KNvAtqjDwL6L1+Dh/oPN/FrnI0FpPfPJxmQEj3uDUd62JP/K5UGOMLDHv9fqTPAER/3+AMpsNf7V3/DCHweSIG9+0D6uAcb9WHv/q+UGzgPpEBMyF/jZdBLGDgOdv89QPrgKwKkEH9xXvPxvP7j+TeP522A9GEvPJBC3ecXkN7nWyCQ/mWcAlYfcF4IcDAIEbBxjvrua0V+9xbwD0MbGepHcTF9irXaptqxb749xZ7PYSbiaLO6eapri1k7vjeZYwxtF5Bf7nSrcXqjp+4bMKchAwEJrI8D18k7j+pA9dOYhT0389RXqbQ7NCF1j+dLq0GICB0UpQSDGqVFIYpsR6emzonJYbGBWPBOkYHMuLBUY34yX+j/Mp8NghxsW2qC7+zrnJZkRz1DUgZ8RO71sbMrh00qqqg55huqEWzgLT/QyiuRl33eOAVbuU03Cqr6Xo9TbFSXWnlNg6nHtw4ZQ5DJXdhXmMnQGZBKoiEfd21oTgRi68YmN7//JKopIYLUCw5BhoH+mU0jVQAdRTuURW8ZQhFaKhQ7vPKFUN11yejJDVoHBBleJl2i9lT36I2MKz05o8yq4va+8mGR5fVzrB/PVap9GIFyf8z/jMf8L37M/7rH/G9/zP+hx/yffcz/TSCFva+vQArUR6AC/qqPSEAK1CMgluuv+kMFpEj35QSkD/NUQIpyXx+AFPWvyhFC574cvb3BZhPENgXEtFeh+4cKBHt9Hc6qc9LNfzwVocO7MlOXt7nZKQ3gRiAraJFwstLQ1zjZ/UjRG7HEwYtLuvssx3o7txHDi1j1i802uaPgNxYCCSqfu/6X7DDMGHyUzrsYAothl6aKzxSkIOSYWhRJK2OXRJiZItFufKJCUClGj24Yi1TVf1UEby+GPqEIzc8hYDhnW7wHrEPQuNPl20lMik/Kx7lbt08nBUhtzj1PlgeVlV0CrzbZUd4zxR9dfabpSJnq2A52UeE3eureNkjbpTAmhjic22MJyWRH2WgJfYUDz8KsU7P3bu67dDgXEoyA/Bqaz7bZ8fP08V30Cqudk9twh1gylt5iyUOgLl6GZvlXzNGVGbdyHMd1qLxBHD1cQ4FIV7xympVM68pdxaGbLocd1C7ACJ4zRJhnDjUJCZ3Fz/I44RsiCM1uWxoBLrEsB30E9UHBQGymvP7jBxXGnrD3RYiYyB7c2svM71E28BO5N47Iv/j7r/ykdSJjs2UcurtmLvOv+tBz3NBTiBr3DEIYRSQpbrPy5cBzg3nOHW6XlDo0FRHDIp9Sa7CCk/k5GUSPuhzjAqSIiEtSzs7oOt1ykyIV4ZYaLjN3L0koiLV0EeA=
*/
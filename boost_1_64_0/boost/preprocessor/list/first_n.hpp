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
# ifndef BOOST_PREPROCESSOR_LIST_FIRST_N_HPP
# define BOOST_PREPROCESSOR_LIST_FIRST_N_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/list/adt.hpp>
# include <boost/preprocessor/list/reverse.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_LIST_FIRST_N */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FIRST_N(count, list) BOOST_PP_LIST_REVERSE(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_WHILE(BOOST_PP_LIST_FIRST_N_P, BOOST_PP_LIST_FIRST_N_O, (count, list, BOOST_PP_NIL))))
# else
#    define BOOST_PP_LIST_FIRST_N(count, list) BOOST_PP_LIST_FIRST_N_I(count, list)
#    define BOOST_PP_LIST_FIRST_N_I(count, list) BOOST_PP_LIST_REVERSE(BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_WHILE(BOOST_PP_LIST_FIRST_N_P, BOOST_PP_LIST_FIRST_N_O, (count, list, BOOST_PP_NIL))))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FIRST_N_P(d, data) BOOST_PP_TUPLE_ELEM(3, 0, data)
# else
#    define BOOST_PP_LIST_FIRST_N_P(d, data) BOOST_PP_LIST_FIRST_N_P_I data
#    define BOOST_PP_LIST_FIRST_N_P_I(c, l, nl) c
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_LIST_FIRST_N_O(d, data) BOOST_PP_LIST_FIRST_N_O_D data
# else
#    define BOOST_PP_LIST_FIRST_N_O(d, data) BOOST_PP_LIST_FIRST_N_O_D(BOOST_PP_TUPLE_ELEM(3, 0, data), BOOST_PP_TUPLE_ELEM(3, 1, data), BOOST_PP_TUPLE_ELEM(3, 2, data))
# endif
#
# define BOOST_PP_LIST_FIRST_N_O_D(c, l, nl) (BOOST_PP_DEC(c), BOOST_PP_LIST_REST(l), (BOOST_PP_LIST_FIRST(l), nl))
#
# /* BOOST_PP_LIST_FIRST_N_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FIRST_N_D(d, count, list) BOOST_PP_LIST_REVERSE_D(d, BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_WHILE_ ## d(BOOST_PP_LIST_FIRST_N_P, BOOST_PP_LIST_FIRST_N_O, (count, list, BOOST_PP_NIL))))
# else
#    define BOOST_PP_LIST_FIRST_N_D(d, count, list) BOOST_PP_LIST_FIRST_N_D_I(d, count, list)
#    define BOOST_PP_LIST_FIRST_N_D_I(d, count, list) BOOST_PP_LIST_REVERSE_D(d, BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_WHILE_ ## d(BOOST_PP_LIST_FIRST_N_P, BOOST_PP_LIST_FIRST_N_O, (count, list, BOOST_PP_NIL))))
# endif
#
# endif

/* first_n.hpp
aTww5OXgPDA9gAc+mdoUHkiznT0ZiJV8cMxXHpQFsEH6VI0NYuuTB42YD5TVww1HCvzGhGlTz39MOBjaEA/ceHGjecDZLCgPLJ0VjAf2d7oAPGAJ1ff/XwrOA2WB+/9TmsID5baz5wNx9cwHZgXwQNoUjQfiznM+MKse2h+b7Ed795Tzp/1/0WAD33/HRtN+syko7Tc9F/T7j7kAtI8w69//C8FpPyvw+5/UFNpvtp09H0iVtL/dwrSPo/QUaFbIu6VFe9my7OTpvK+AvcU0CP2POG444mzi0if5yWSDTTpOko+TFsXSDQLj2oSZ4yM8uYh3KMlGAZEvrynaqcDCX/T4x2QBersmEffm671DvSDf9w61Msqo9bl839IqV4crFcjh3ZUtJi5H33GV7vuLadJBaDOpHZ4DciB9GnVuMCSSNDGjkuXNhSCDtDSjsbctkLNj8gPGuI8QQbZsYE3K4G+6ku2QNs5TSpfH8fac2Au7tqoxLOZEeVHB5CgJtznDxUdI9YaJgU8ygnNIQ/fMU9zLqau13bplcr/n7NmTMbMK+IrmgQsamEedaUdbagUV+pba3VV+W2p72jVuS809YBT5t8sPgbay5GeAjaw+Kg5q5P1NdO2H0vq3smQlsoq58pqt/IZskIf0v2xKE4h2/xMBRPsLESBYk6ammacNlF7E/akfr29HE173GapJYZV+eH0qunF41TAqsSkFDIuWD/CCgBQt3rLgomVhgGjJfrwpxwJx8phmUnOSH55P0DLZsSpeOzmudFKE+4eceND03iJmV2Nz2UN5knaWdObafe5PVZIdgr5Fc+hKGcgrrb7E4bGBZ1aakby2dBKZ+0rQ8pdaWtY5i2NLb4rEy5xoasIpmPo66ma5TTURVUqIv1CJ/FjcKJ1WWHUrVUs10bUqwMmAeBdyn5eWGfZCcloodOFW6bUvnUaGefguK/L9WSguL4CFPstjeyaShaIuPy8Wav23wULWB8rq558HLmJVEUOV6uvlOv/gjTp+Gn3gRY3kIR+TKSsgaCQGhqK7zFsxEg+SbzQEpCA12wcDXSaYKDfbA40Br6zW2adqH1lMIUaZXm4HgrsrJpTVrEWMN2neDyewPJevWOn3FW7X6B2n0ZsrDa0imtdNiDRIbnlas+52qRvZB4HAktxUmC8wfO21uJkhpiQrYwwY7jdguBIwMB8wJMyC/OcZgXqCMsa84IwRPj6AMV4b33TG+KO2QXF9RxRrPBoa8x9+4csWomfU+bPE+zO0vleekyUWBLBES1c9LCGx66724Yp37LSkBNWndB1U+Hf4pI6fh9NnvYzvlPb4tjT19aRK97rf3w/9cZAUFpSpOUkPz+a/aRoLUVM3+TJ6Whjipoylze9TAqUNZRNlToRqzU4rTGSVQ5aJummcj8WQ3N805M8yf/lTF1T+dAQvpqjyJ5qY0SQmTbug8oeuziv5fw4iNttVD5uVjwtgs+ucTWezZ040Qv4cbMVHbYbq4OClZ8mfla3On9muf1pjtoT99TObREA0Un2Z7bXHGiF/ooax/DlgfPsPopjqvXrc+cqfFMgfg+RlxecjfzL26zD8PFaH4b3H/OXPsgbkj2SMmuCMMW1sAGN0eazpjOE63qD82dSS2KLGYIurP/OTPx+1PH+W6DFd7/s5WSI/gCXcYxonf2KG+cqfUMifUCl/lgWVP6E81ZHyR/QfEyBU3isMFCq+85vCZXNGdDCeDIOIMVnkcX1SHZgnlR7Cqkt+VaBL4viTBj9Y3MPwbH5kp5L00nSiRkKYLHVT4cpbS5DUvzZ/jbSsJFcYj1MnBkfK9yFLLV3ptn9xuvjgSY2FV3P4oSdkmF/HkHGlgyA=
*/
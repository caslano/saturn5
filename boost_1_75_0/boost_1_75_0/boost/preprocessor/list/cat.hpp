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
# ifndef BOOST_PREPROCESSOR_LIST_CAT_HPP
# define BOOST_PREPROCESSOR_LIST_CAT_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/adt.hpp>
# include <boost/preprocessor/list/fold_left.hpp>
#
# /* BOOST_PP_LIST_CAT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_CAT(list) BOOST_PP_LIST_FOLD_LEFT(BOOST_PP_LIST_CAT_O, BOOST_PP_LIST_FIRST(list), BOOST_PP_LIST_REST(list))
# else
#    define BOOST_PP_LIST_CAT(list) BOOST_PP_LIST_CAT_I(list)
#    define BOOST_PP_LIST_CAT_I(list) BOOST_PP_LIST_FOLD_LEFT(BOOST_PP_LIST_CAT_O, BOOST_PP_LIST_FIRST(list), BOOST_PP_LIST_REST(list))
# endif
#
# define BOOST_PP_LIST_CAT_O(d, s, x) BOOST_PP_CAT(s, x)
#
# /* BOOST_PP_LIST_CAT_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_CAT_D(d, list) BOOST_PP_LIST_FOLD_LEFT_ ## d(BOOST_PP_LIST_CAT_O, BOOST_PP_LIST_FIRST(list), BOOST_PP_LIST_REST(list))
# else
#    define BOOST_PP_LIST_CAT_D(d, list) BOOST_PP_LIST_CAT_D_I(d, list)
#    define BOOST_PP_LIST_CAT_D_I(d, list) BOOST_PP_LIST_FOLD_LEFT_ ## d(BOOST_PP_LIST_CAT_O, BOOST_PP_LIST_FIRST(list), BOOST_PP_LIST_REST(list))
# endif
#
# endif

/* cat.hpp
YBKyIJZLDjduLe8maegfJP8ojbDgI+zYscJcCSzxYmRNxrl48ubPSd1msgLTlTiSqJ4EeEySqDBKjXOrT5YEMtu5VFPaE1gaL4b4EFB1vizuGpahlSVBifIwnaW9K6FdY6GdMmCNCV4GQDjjm3q7iU7xuf2Rfhoaho0xm5DlxhTWPdjRgSeedrkU32aQWL8pQN/cKJG+VD9meQc1xtLn3NMwJla7zYf4W8y8dEUVprOf52kHKtQuTzeuCbVY+YX2VC8qSzzJYafMsYtIB71Kt7+GCeP8OKZDeb2ioe37pd27DMR2UWTpo71mwYjAjcifzqs9oUu19jpNCC9p6J1e502wehXu5NtiFC6scJa6E+TJUb9BTb+3qkR/hMi39ZHMWXtqO62J9ikzJj3npe6tsrcW6UKtmik73WFYbnWS++WiavlUUq+fNqn/n18kkgzQybp+CpllXrmjn6XrsJqTznPXvG8KMKecvOMv186Dh0YOog+AmS1GG6YEda7T6Zr8LTuHjMaVj9O0XSdCeY/qI9NXHqEPc9I+w0SLDtKAJAiLUfg4r85K1/y1ULHnZeMO0/1NBP6gChyWHeBhakqvlvRb1MS112gbOCL8E2eFe/LdYYXbUtsvtZ/m3n5Ojko1PNpplTLd8l8J80QIhDv+RLriMS+lqoSIHo/RXgKSkOthu0o+7Uh8b5LsoZ8DThUa26k9d4wMU2eIVoQZ
*/
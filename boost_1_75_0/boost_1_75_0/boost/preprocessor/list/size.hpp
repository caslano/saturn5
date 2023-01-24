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
# ifndef BOOST_PREPROCESSOR_LIST_SIZE_HPP
# define BOOST_PREPROCESSOR_LIST_SIZE_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/list/adt.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_LIST_SIZE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_SIZE(list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_LIST_SIZE_P, BOOST_PP_LIST_SIZE_O, (0, list)))
# else
#    define BOOST_PP_LIST_SIZE(list) BOOST_PP_LIST_SIZE_I(list)
#    define BOOST_PP_LIST_SIZE_I(list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_LIST_SIZE_P, BOOST_PP_LIST_SIZE_O, (0, list)))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_SIZE_P(d, rl) BOOST_PP_LIST_IS_CONS(BOOST_PP_TUPLE_ELEM(2, 1, rl))
# else
#    define BOOST_PP_LIST_SIZE_P(d, rl) BOOST_PP_LIST_SIZE_P_I(BOOST_PP_TUPLE_REM_2 rl)
#    define BOOST_PP_LIST_SIZE_P_I(im) BOOST_PP_LIST_SIZE_P_II(im)
#    define BOOST_PP_LIST_SIZE_P_II(r, l) BOOST_PP_LIST_IS_CONS(l)
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_SIZE_O(d, rl) (BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(2, 0, rl)), BOOST_PP_LIST_REST(BOOST_PP_TUPLE_ELEM(2, 1, rl)))
# else
#    define BOOST_PP_LIST_SIZE_O(d, rl) BOOST_PP_LIST_SIZE_O_I(BOOST_PP_TUPLE_REM_2 rl)
#    define BOOST_PP_LIST_SIZE_O_I(im) BOOST_PP_LIST_SIZE_O_II(im)
#    define BOOST_PP_LIST_SIZE_O_II(r, l) (BOOST_PP_INC(r), BOOST_PP_LIST_REST(l))
# endif
#
# /* BOOST_PP_LIST_SIZE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_SIZE_D(d, list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_LIST_SIZE_P, BOOST_PP_LIST_SIZE_O, (0, list)))
# else
#    define BOOST_PP_LIST_SIZE_D(d, list) BOOST_PP_LIST_SIZE_D_I(d, list)
#    define BOOST_PP_LIST_SIZE_D_I(d, list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_LIST_SIZE_P, BOOST_PP_LIST_SIZE_O, (0, list)))
# endif
#
# endif

/* size.hpp
synUud9oCugm2sY9c13jJtqlGtbtQ75W6N8ceMtl1PAMO7enFDMqd1jktdNrk2291K1rj9v6ia0bRbZaCIiggNNcIrONnLWaLRbGJRXUoY0sdrcWPiYvl6eZRHRXGazEzyvGrwTpns8a5nd49m+yQnS+RwzjK3/bWLwCzedXbJQbpy0gITMffc4HBi0rKmw4xfx4d40KwOtUDiEkcua1eBPhPJk0BYiBVF2Pi1jv9EFbN04RxLq5Kg43KrPorHGB+LdBNfNYBAqAhMMO5GTY8eP6bl/JdVgQ36HR8RO9aPbLlQtHQH3S27LEfMZOkDChr+BN2EDczdYNYTp3QlwhMACxZLgBfusDcjr15vFn8K40q8JZLTwEpD4UUJ0i0wbQwo+CgtoOr426EdHTy9hXAPrM2jNPyqGpcCgw7KZvVuV5drxs4TgkKGgEigPg0WeBxkh36V2zwINKjr7tbln4h448FFyzMmeIw9GT/fJKATw3gc8UvyhYbntq7LXbPsAKyomgcP5faqdBm3sls3CKv7H9H9u7hNH/V+/1n9n+y99idWd7Ezfrf7I9hre+rIeoW1tNh8VaMoXcm/ZklPloOuu4K4ts4LfXj+emQkqH/EUjaQ1ldqd0NQYuXivtpKSaH9XnLWv442xs+rZm11nDWGhCWmeTP663/rmcFfyJIawdUbFA5dvESjhOMxQ4dXGmm24udxPAapT1MtPn
*/
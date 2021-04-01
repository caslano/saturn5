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
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_MUL_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_MUL_HPP
#
# include <boost/preprocessor/arithmetic/add.hpp>
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_MUL */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MUL(x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_WHILE(BOOST_PP_MUL_P, BOOST_PP_MUL_O, (0, x, y)))
# else
#    define BOOST_PP_MUL(x, y) BOOST_PP_MUL_I(x, y)
#    define BOOST_PP_MUL_I(x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_WHILE(BOOST_PP_MUL_P, BOOST_PP_MUL_O, (0, x, y)))
# endif
#
# define BOOST_PP_MUL_P(d, rxy) BOOST_PP_TUPLE_ELEM(3, 2, rxy)
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_MUL_O(d, rxy) BOOST_PP_MUL_O_IM(d, BOOST_PP_TUPLE_REM_3 rxy)
#    define BOOST_PP_MUL_O_IM(d, im) BOOST_PP_MUL_O_I(d, im)
# else
#    define BOOST_PP_MUL_O(d, rxy) BOOST_PP_MUL_O_I(d, BOOST_PP_TUPLE_ELEM(3, 0, rxy), BOOST_PP_TUPLE_ELEM(3, 1, rxy), BOOST_PP_TUPLE_ELEM(3, 2, rxy))
# endif
#
# define BOOST_PP_MUL_O_I(d, r, x, y) (BOOST_PP_ADD_D(d, r, x), x, BOOST_PP_DEC(y))
#
# /* BOOST_PP_MUL_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MUL_D(d, x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_MUL_P, BOOST_PP_MUL_O, (0, x, y)))
# else
#    define BOOST_PP_MUL_D(d, x, y) BOOST_PP_MUL_D_I(d, x, y)
#    define BOOST_PP_MUL_D_I(d, x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_MUL_P, BOOST_PP_MUL_O, (0, x, y)))
# endif
#
# endif

/* mul.hpp
OqlPnGnRN0Dwl8oEaCvchgPkCifaU4YNCo6LUSpNv35oKtsmYuBoq4STmbAeQpCICtQ61/7ZGzp2G7779oUtouk5hKJl4tCIpPyrhh4r66BKSlVpX6i0cVEelGlE5BZrJxygUz/J/pZGqGd4b/uQcYoVu3ORzz9GjpT32nhpDKWnoNhgltIVCX3JvWkS5LIfwtcMRIW/+nSc1bWg+nYCgmPEGOdHGWNUJC/7mAK2qD/XJiRwMa97ijz+HHpwcNNx9PlO80GQX1THzhOt/zOLh20yRq+hvo7j8mtuEPR8ypWrOjLkQm3xQMS/9KZspgrKKp47ej6flJEKTA8mzN1ER+u/xySXRCd6CQzzER0+ksNGq/c84k7nahuroEQGtq7EqllnX48QSUptglW1bruqtr/DQv6OdMVVJ6eBEAaHzjFPH8bFASHfuB0Z1bUC6smbBgvWXrhPVsDp5iMy1oyjMHSJ+bfpGebHqxLNDz1IgLqJodVnus0peyBBnr05CWCL6HKrLhCValM0HwE/d+iNPazP4zbD1l2U56Edgl25TnUDwvr+CS3qJcH7lA==
*/
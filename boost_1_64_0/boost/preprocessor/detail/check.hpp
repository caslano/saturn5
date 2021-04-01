# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_DETAIL_CHECK_HPP
# define BOOST_PREPROCESSOR_DETAIL_CHECK_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_CHECK */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_CHECK(x, type) BOOST_PP_CHECK_D(x, type)
# else
#    define BOOST_PP_CHECK(x, type) BOOST_PP_CHECK_OO((x, type))
#    define BOOST_PP_CHECK_OO(par) BOOST_PP_CHECK_D ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC() && ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#    define BOOST_PP_CHECK_D(x, type) BOOST_PP_CHECK_1(BOOST_PP_CAT(BOOST_PP_CHECK_RESULT_, type x))
#    define BOOST_PP_CHECK_1(chk) BOOST_PP_CHECK_2(chk)
#    define BOOST_PP_CHECK_2(res, _) res
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_CHECK_D(x, type) BOOST_PP_CHECK_1(type x)
#    define BOOST_PP_CHECK_1(chk) BOOST_PP_CHECK_2(chk)
#    define BOOST_PP_CHECK_2(chk) BOOST_PP_CHECK_3((BOOST_PP_CHECK_RESULT_ ## chk))
#    define BOOST_PP_CHECK_3(im) BOOST_PP_CHECK_5(BOOST_PP_CHECK_4 im)
#    define BOOST_PP_CHECK_4(res, _) res
#    define BOOST_PP_CHECK_5(res) res
# else /* DMC */
#    define BOOST_PP_CHECK_D(x, type) BOOST_PP_CHECK_OO((type x))
#    define BOOST_PP_CHECK_OO(par) BOOST_PP_CHECK_0 ## par
#    define BOOST_PP_CHECK_0(chk) BOOST_PP_CHECK_1(BOOST_PP_CAT(BOOST_PP_CHECK_RESULT_, chk))
#    define BOOST_PP_CHECK_1(chk) BOOST_PP_CHECK_2(chk)
#    define BOOST_PP_CHECK_2(res, _) res
# endif
#
# define BOOST_PP_CHECK_RESULT_1 1, BOOST_PP_NIL
#
# endif

/* check.hpp
7bEz8F8S6Qkb+1VR4QRsKWPlMMdPwDPuiciHWnrFF12BK50YJoh6r4uNqxmHoiCPFUfoUWo7Tfra3xN6TmODVHiAM4HuHQ9CgmYEZcPeYxcOWF26WYjbt/9M3M7fiPB/3vzdhLX66V+eOzVqIDcKfD2qKZ32xwBsUreMulpHE2yMTui4s/M3AfVE/Y3ppflKg+8MWaMWtXFl3i1rEb3ncHgtzKuz/ev8yKRC1cYRQWli5VzV3FAa5GBEpF9U3gWQmObinJccQTJy/IlW7yzBey5ri2oBtbd1pxGgCsl5xndDj1d4wcpy8WueYQmEKNOqoyYmHwSlwQySEO5we0miN8cns8CS1G0k5hUhDzGXtGprw5KXyo7TQ1oCRUORJh61MqMJqTIhDZISEQIn1imzA0brHuMNzonruZeGe9bewrCppMfagrH5isoKpnWzEa236/3qwAxyyRZ9/rMwsc0Yr61woEfHUSCuPjlhLfnGnQCh61PSpi/vV7FE1th0d9OnK4HFxytTNNZiARRw45OO4o1A5ZMtNtJFk9Qb9MUpU61x2/dTxQSQcWk1Eg==
*/
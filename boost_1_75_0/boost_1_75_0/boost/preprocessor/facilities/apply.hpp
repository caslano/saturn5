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
# ifndef BOOST_PREPROCESSOR_FACILITIES_APPLY_HPP
# define BOOST_PREPROCESSOR_FACILITIES_APPLY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/detail/is_unary.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_APPLY */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_APPLY(x) BOOST_PP_APPLY_I(x)
#    define BOOST_PP_APPLY_I(x) BOOST_PP_EXPR_IIF(BOOST_PP_IS_UNARY(x), BOOST_PP_TUPLE_REM_1 x)
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_BCC()
#    define BOOST_PP_APPLY(x) BOOST_PP_APPLY_I(x)
#    define BOOST_PP_APPLY_I(x) BOOST_PP_APPLY_ ## x
#    define BOOST_PP_APPLY_(x) x
#    define BOOST_PP_APPLY_BOOST_PP_NIL
# else
#    define BOOST_PP_APPLY(x) BOOST_PP_EXPR_IIF(BOOST_PP_IS_UNARY(x), BOOST_PP_TUPLE_REM_1 x)
# endif
#
# endif

/* apply.hpp
n3RQVdBxi4+11fecDoj54nLhB0HKGIUaWZc/bLvR6wYEDKCa724dshY6rgw7rcxYYrn91eyMxhpaIT+yKqaXYVZ6kTVcejFj3GJnJ8jOfnT+Z6zj7lG6vCYuC//2U43mBsTi4EcQD23MxSW2+OBIeOmememuD1LJp1mdeFEczGsdb4BinSn+oLc+vrBB254wMds7cbPj9GD+zwj5o6tBDkgjJlNMUNaQe9VUq9b4kGT6bSyDbDzfAAvrg1GYJ4W/2Ff6H7ttQxBAArvoxELvLBZTax/T31F/q+ljxKbnZZNq9QMIbeZtb9rYSM4xqlva7qKRwR8INQRDivRc0CwAIyOpt3e2nUC0GO52k93z1OzsoWoumDeyDD7atUseEHB4qNfYVPJ4J9Jh9Xcv490F5TwZmG2dbzqCQN9ehjdmIH+Yoh5p2digaG/gt+fHGD5H2FH2H/g+VX+bM7zo/d3Xh/b2CJvYG34jhld3JD5yugY+v35uHnPwzuqd1vhEL/cPuKn7kZDaFZl3z2syfet9dp2XTr+lkOz287BUly+3F1L3xe5bifmWQFIXqCHrxobYdzzrEad/Bzx273p//IFDO2JmRPgJB+nZ5QOf2ZeXkEy4Wu5ZXc05f5aarq5BVaV/9NDF9TVpmAwvaR4Nuatn09/fSN4dmZnNDQ2vtdOOfEYdvjMzTrJ/Lv/PxRkB8yH25h+7JhGTSuKKUv7l
*/
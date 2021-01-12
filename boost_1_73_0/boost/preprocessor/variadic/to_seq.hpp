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
# ifndef BOOST_PREPROCESSOR_VARIADIC_TO_SEQ_HPP
# define BOOST_PREPROCESSOR_VARIADIC_TO_SEQ_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/to_seq.hpp>
#
# /* BOOST_PP_VARIADIC_TO_SEQ */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_VARIADIC_TO_SEQ(...) BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__))
# endif
#
# endif

/* to_seq.hpp
u01QgY/2Vo73bbnyQrS/cvz5cuZ7U9Psv+6z//3vEU/g1tsPRCtCJDN/TJPqLFcB5noOvN3ZzKH55SGeehHIIGSyeAjWeAKMve9k+WTIQgHbN6NGv/bwdOWuXpw5IPmLRzQZRk64HhNZL4kGuaX1IvHo2RuD3jExD+4k214QzKpqNe0T2Lm72Cew/uIh2I83SqhI38E/NfscdXujXqfZbg2S7HM0GPbbjWGrj8feAqQq9RaT
*/
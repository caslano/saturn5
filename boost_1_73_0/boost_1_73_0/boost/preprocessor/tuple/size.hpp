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
# ifndef BOOST_PREPROCESSOR_TUPLE_SIZE_HPP
# define BOOST_PREPROCESSOR_TUPLE_SIZE_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/variadic/size.hpp>
#
# if BOOST_PP_VARIADICS
#    if BOOST_PP_VARIADICS_MSVC
#        define BOOST_PP_TUPLE_SIZE(tuple) BOOST_PP_CAT(BOOST_PP_VARIADIC_SIZE tuple,)
#    else
#        define BOOST_PP_TUPLE_SIZE(tuple) BOOST_PP_VARIADIC_SIZE tuple
#    endif
# endif
#
# endif

/* size.hpp
fbZF7V0S3KczoZl2UcI6M1rwZfe3+qTxYRseaNMsuZeQ3MIhOaOOtfZZGUy8cbTLDD4lNKQVGHwm7XJph//tJLSjv9SVaGzHFTYf2cH0vjYv0TnOriL+kaMGFeqV5UPwiWW88dxXQjLiMB1i5PgbshEkhs5bFRh728gy4vgF3eBnHa+JtUP7mDHjYu0wMVJOoIflU4FhXfz4jysnnYxxUXsMGddSGbkN1EslyYjDdIjKifW7kBHr1+tj9TB9VhE=
*/
# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
# define BOOST_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/variadic/size.hpp>
#
# /* BOOST_PP_OVERLOAD */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_OVERLOAD(prefix, ...) BOOST_PP_CAT(prefix, BOOST_PP_VARIADIC_SIZE(__VA_ARGS__))
# endif
#
# endif

/* overload.hpp
cy9odHRwMi1zZXJ2ZXJwdXNoLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS2tBtWX4OAABEJwAAKAAJAAAAAAABAAAAAAASLQgAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9odHRwMi11cGxvYWQuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIJr0ZmsAIAAB8GAAApAAkAAAAAAAEAAAAAAN87CABjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2h0dHAzLXByZXNlbnQuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJipFuEWgMAADkHAAAhAAkAAAAAAAEAAAAAAN8+CABjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2h0dHAzLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSbapnKeoDAAAUCQAALAAJAAAAAAABAAAAAACBQggAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9odHRwY3VzdG9taGVhZGVyLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSUePQJD0GAAB0DQAALgAJAAAAAAABAAAAAAC+RggAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9odHRwcHV0LXBvc3Rm
*/
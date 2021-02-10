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
# ifndef BOOST_PREPROCESSOR_ARRAY_POP_FRONT_HPP
# define BOOST_PREPROCESSOR_ARRAY_POP_FRONT_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/elem.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/repetition/enum.hpp>
# include <boost/preprocessor/repetition/deduce_z.hpp>
#
# /* BOOST_PP_ARRAY_POP_FRONT */
#
# define BOOST_PP_ARRAY_POP_FRONT(array) BOOST_PP_ARRAY_POP_FRONT_Z(BOOST_PP_DEDUCE_Z(), array)
#
# /* BOOST_PP_ARRAY_POP_FRONT_Z */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_POP_FRONT_Z(z, array) BOOST_PP_ARRAY_POP_FRONT_I(z, BOOST_PP_ARRAY_SIZE(array), array)
# else
#    define BOOST_PP_ARRAY_POP_FRONT_Z(z, array) BOOST_PP_ARRAY_POP_FRONT_Z_D(z, array)
#    define BOOST_PP_ARRAY_POP_FRONT_Z_D(z, array) BOOST_PP_ARRAY_POP_FRONT_I(z, BOOST_PP_ARRAY_SIZE(array), array)
# endif
#
# define BOOST_PP_ARRAY_POP_FRONT_I(z, size, array) (BOOST_PP_DEC(size), (BOOST_PP_ENUM_ ## z(BOOST_PP_DEC(size), BOOST_PP_ARRAY_POP_FRONT_M, array)))
# define BOOST_PP_ARRAY_POP_FRONT_M(z, n, data) BOOST_PP_ARRAY_ELEM(BOOST_PP_INC(n), data)
#
# endif

/* pop_front.hpp
bmUtb3B0cy9kaWdlc3QuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlL1SXoyywEAAEADAAAsAAkAAAAAAAEAAAAAAFhJBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9kaXNhYmxlLWVwcnQuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlL1IFviXAEAAEoCAAAsAAkAAAAAAAEAAAAAAHZLBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9kaXNhYmxlLWVwc3YuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLAq2v3pwAAAPEAAAAnAAkAAAAAAAEAAAAAACVNBQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9kaXNhYmxlLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSJ8/+pJMAAADDAAAAOAAJAAAAAAABAAAAAAAaTgUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvZGlzYWxsb3ctdXNlcm5hbWUtaW4tdXJsLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSv0pxT/AAAAB5AQAALQAJAAAAAAABAAAAAAAMTwUAY3VybC1tYXN0ZXIvZG9jcy9j
*/
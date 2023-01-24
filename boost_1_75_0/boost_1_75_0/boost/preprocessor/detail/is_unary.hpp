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
# ifndef BOOST_PREPROCESSOR_DETAIL_IS_UNARY_HPP
# define BOOST_PREPROCESSOR_DETAIL_IS_UNARY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/detail/check.hpp>
#
# /* BOOST_PP_IS_UNARY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IS_UNARY(x) BOOST_PP_CHECK(x, BOOST_PP_IS_UNARY_CHECK)
# else
#    define BOOST_PP_IS_UNARY(x) BOOST_PP_IS_UNARY_I(x)
#    define BOOST_PP_IS_UNARY_I(x) BOOST_PP_CHECK(x, BOOST_PP_IS_UNARY_CHECK)
# endif
#
# define BOOST_PP_IS_UNARY_CHECK(a) 1
# define BOOST_PP_CHECK_RESULT_BOOST_PP_IS_UNARY_CHECK 0, BOOST_PP_NIL
#
# endif

/* is_unary.hpp
lYIsIX0IhGYd5++BEBdAWr20tG8FBGCCAjCA4C1AD5UrteDAGt3m6NcAA8HdnaCgNts+yjv1Z25u0OSkEU5MmfKCoJWfFUkio4Vp8C2B0foVPLNyrO9rdJvwB1PT1atdvwo71CCdWuM6FSUlzUr3lEjFkkKdEgFOEnx74uvk6XjGmsWZ9S9/hpa8em4a2fOCrrI4QCj1ZzGNGCrEvOH36q4Ho6yKXWaThEQNi2aIjY1LwPBo4WyHvYVe6OynwOaaEh5O9Wo1fIdY+dN99/2Gt36mnxQtk2Xqlti1P3BYpehb6bA7HP9aFmNSfH5+0Zz88IdLgx8SrluzIz+EGBFb4b99l+0LC02r0PEinHZmiupJ0FD7hARF9QNGgDOmwnMzM9Z8ON6e2ZWVouuL1hVvcwWIFxaTc/mW9tiJHzLn+XJUzw/LMDBmhpjZYlGpPCkG2dk/towhb6hCxN55t1frZ1rOFoe7rO8cSUr/aXmuzfOla2AzL93Plm3le/gvHdksEYvH7U6ffqHVJbLW42A01aVFobRkmKCAAAnZ/TygOSUNmJwGXFq69/YhKys9KNcympz8NspeQbB9WTw9PGhHRMhnbl7l7t4760B8bZ9RLapuyKxaHh3FP/Red7w4wQAo2oH3x0IulCNv4cnp6Z4N5NXksvaO1Xxcyu6/Xc9enjHQ8BSfn/YQECq3TI22tpMy4Po5U9VLS0deC6Lo
*/
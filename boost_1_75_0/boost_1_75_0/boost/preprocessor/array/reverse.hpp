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
# ifndef BOOST_PREPROCESSOR_ARRAY_REVERSE_HPP
# define BOOST_PREPROCESSOR_ARRAY_REVERSE_HPP
#
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/reverse.hpp>
#
# /* BOOST_PP_ARRAY_REVERSE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_REVERSE(array) (BOOST_PP_ARRAY_SIZE(array), BOOST_PP_TUPLE_REVERSE(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array)))
# else
#    define BOOST_PP_ARRAY_REVERSE(array) BOOST_PP_ARRAY_REVERSE_I(array)
#    define BOOST_PP_ARRAY_REVERSE_I(array) (BOOST_PP_ARRAY_SIZE(array), BOOST_PP_TUPLE_REVERSE(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array)))
# endif
#
# endif

/* reverse.hpp
cuIBZ72XibapFlC7dUGJGCuem6fXaQtXEgEuhFZklkO5ooGMeEGreOmcgf3ffu5q1VNvOdgt8c996v84DXTm41E2CGspSJDofbC8k/ZDJCkJFbxnVJU+WjQyaO8+n2VUhPwhPeeaoGMxIQXIiQyVU7oVal/WDLg7vplcnm2J0lIsuCnHTzPDZ21kwn6xHEINI+KSDnkwTy8XVWI9Q6Hs1K7g4elmybBk3h3KdRCSjN8rqswcdXwlfoxikQH54EReuBJMnns9/3aI9YxAbr/J/PBznO9OwAV6N5Z717mbGuqv6qrXyrGbdfMnomGdjGwyOoknDVf29LvBTdHJYQlaR/PnbX2qJWMQg14qbhFz0oiP+preSQyhBzUMvxCf1vRV7+4JYKTUeOQPnnbDy39qK4wr4DFOCuu8uOKt8S8XZbeOVpt93rN1bcpn8SQi/0indks0NBMWlzWVhmTS5lDZJyOdf3Z2y1Znxe1JF+5hLk/ELAiyQ5eBLDJD6v5OK6x3KijVXGLgzKz0+Y9dxx+4nqaaUlLE6dt1pBWvjdJCPAY8Mw0lmzU8fh2MphonIhwYdvXmEyMblaqEgM3p5Pq7ijGGnc0K1X8j3W4eZGZY+cPM8nvZL+tLYQ37EI+JuR4Nl62NUUpw8Xudp4TYU3MG3Wq1I8+QniBQl1KO7kduQKT+DYo3Gz2RyDx1N5mPS8kRYwGgoH0mnPvyycgD
*/
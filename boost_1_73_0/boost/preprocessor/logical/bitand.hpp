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
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITAND_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITAND_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITAND */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BITAND(x, y) BOOST_PP_BITAND_I(x, y)
# else
#    define BOOST_PP_BITAND(x, y) BOOST_PP_BITAND_OO((x, y))
#    define BOOST_PP_BITAND_OO(par) BOOST_PP_BITAND_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_BITAND_I(x, y) BOOST_PP_BITAND_ ## x ## y
# else
#    define BOOST_PP_BITAND_I(x, y) BOOST_PP_BITAND_ID(BOOST_PP_BITAND_ ## x ## y)
#    define BOOST_PP_BITAND_ID(res) res
# endif
#
# define BOOST_PP_BITAND_00 0
# define BOOST_PP_BITAND_01 0
# define BOOST_PP_BITAND_10 0
# define BOOST_PP_BITAND_11 1
#
# endif

/* bitand.hpp
YaZmF+uNxZdahW1j34GELgXlxPSGlglOKroKHaqZnCP9tKyUw+POQA/JdqyiZ+UEt6aGKREavhI6HJT8RaxUvshN2Km8DeEhY2jL7S5UEX2o3eWSIiytvDaLXQkxlFmkCMXCWM0SOoZ1W0lfmC7yEX3j4r4GodSjCWYOx7D4xM0bNZ5P6mkgHh2OndQXFemknrA8kXmiCzh3u3mibW3EN3RytsTxIZpMhz8oEUO/SNJDi8LG
*/
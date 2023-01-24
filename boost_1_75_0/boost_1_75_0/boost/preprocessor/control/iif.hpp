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
# ifndef BOOST_PREPROCESSOR_CONTROL_IIF_HPP
# define BOOST_PREPROCESSOR_CONTROL_IIF_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_IIF(bit, t, f) BOOST_PP_IIF_I(bit, t, f)
# else
#    define BOOST_PP_IIF(bit, t, f) BOOST_PP_IIF_OO((bit, t, f))
#    define BOOST_PP_IIF_OO(par) BOOST_PP_IIF_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_IIF_I(bit, t, f) BOOST_PP_IIF_ ## bit(t, f)
# else
#    define BOOST_PP_IIF_I(bit, t, f) BOOST_PP_IIF_II(BOOST_PP_IIF_ ## bit(t, f))
#    define BOOST_PP_IIF_II(id) id
# endif
#
# define BOOST_PP_IIF_0(t, f) f
# define BOOST_PP_IIF_1(t, f) t
#
# endif

/* iif.hpp
X5j8wBWlem6DBO8FdihWQB/5zB8wj/+YiMUPQunHwhB6D/z3af2rJ3/jbLF0Uw2ZN96eX2i1VopzU7IsGJ5fa11sG90vrTj+SH0WSSHLPIKlVUxgXn0r44fvvOEkfx9+K/83JdNzlwWg8XlpzfaZC69XeMEjgdw/HvzrROSsA1Oy32ZRSqQexHg74yh+cU09i66Z2upvDhjuPRQ0+z1Ojndm3uoxI1AY2OBKAB4JzGRTSsEjCBDc/uEu/bylthKE9XyGe3GN5ZFEnWafUnRFMrrZ+9cjrvczqpir0grw5Ok2cOLLrfhY5eaXHn9fUxdO96/kHh3RM6+lqaH3N40cjumETx4mtq4c3KqN55zEii4O23kSK6fniA+MPYaEJ2HOt+WUS8x/vtra6kkcEcrQu15B3wUEsb7cPJ518d3l5MyO/KjkKFFbjgcKMjPlHd76iw3SSCCaHsj3Th/crkv24xYWFw8rOjdfZlr2JfRMweWjug5zlU3DpjQO/Q6eLpVBsJmVrmvc6+P9uAHTCAmes0xedNxTzuu1h9WL2OSCW3HdUqBVkN9wNzpYZKlyV9NU3HG7zSZmebtElaGAiJsqLYU2XBdmKs+kaQgQSSroX67Fvq2qjAWIQLYA7aAlrnnWREL0lIqsaLkowcvZH368O1kWCYzBwXrdRzpPF75FaDKkZIrJojycMkYgoR3uD1xZny06AcTZqi172S9j
*/
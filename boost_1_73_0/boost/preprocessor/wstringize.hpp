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
# ifndef BOOST_PREPROCESSOR_WSTRINGIZE_HPP
# define BOOST_PREPROCESSOR_WSTRINGIZE_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_WSTRINGIZE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_WSTRINGIZE(text) BOOST_PP_WSTRINGIZE_I(text)
# else
#    define BOOST_PP_WSTRINGIZE(text) BOOST_PP_WSTRINGIZE_OO((text))
#    define BOOST_PP_WSTRINGIZE_OO(par) BOOST_PP_WSTRINGIZE_I ## par
# endif
#
#if BOOST_PP_VARIADICS
# define BOOST_PP_WSTRINGIZE_I(...) BOOST_PP_WSTRINGIZE_II(#__VA_ARGS__)
#else
# define BOOST_PP_WSTRINGIZE_I(text) BOOST_PP_WSTRINGIZE_II(#text)
#endif
# define BOOST_PP_WSTRINGIZE_II(str) L ## str
#
# endif

/* wstringize.hpp
z5l6nRPnh2GuF6icjZ/QDWY/ud2R/zezLfkXGJax97xu7b3VDM+Qpw/DN6U3VFVXFBf6Cu2SX9lPkj/zYd7RudWS/32k245d32/t3WriP6p5XnYY5PfZNcNVzsG5DcSvizT3fcaS+SzS5T9PV5v7Te9S2XyG/TJvrrZrVssyRGbvPyN5792SOZn099Idf7Wk+qwp13w+P8F+mWmN8rIan7ewuqbErotfJ5QRqoczp5k35O8W
*/
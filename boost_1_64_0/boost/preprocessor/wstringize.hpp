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
dUO+tefOxXUTJ2pXHo1XEti4zHItmjIr5b1ur3avRDYS1YlZGqlfEeKi7METQdNr0Nvn8LfmsktSTWuNv3i3V/6cwGp/IewpHABXmsVXIDeF1yvocYq4SQQG15SUzQa039BqRntY//AkEC3hQ3MguKO5GaucLmOuydTewWPr+YaSjXzeRlbGk7QN5S7lyRkFXUKpYzl/elj7an+TB0S5hedbbCaHBo4DYhNTFpVJoNzvXxjsuyxAZo9oxMNvz6fMfDR9EmNf7cGp7Jwymh0vs/CCHZ7qTXmf9ypkgdHqmd8QltoGlYKw1fGOlz8nNiNVfftvp9ROkCLT45KMgzJ05oLkU5xTndMVJDKi2awQY9o8f4LqdtwzmUzFNjVg0NzB9c7u01oea9KKcp2Yj3voM6LTQS9FBG2Y+uMpZvH9HnqLvZgfQe5SDc8Ai8h2SNRdnjyNUVpvXamcTNvR3Ojnx2ctXUTzpmpohrZVajczPGQDILDCgPsNhNctIIIzkhhyr+IiqbBtYywe8fTyEdVt3kOlp6paNBqYNqDSnaaFnnPJ3nbKzBtqrAMC3w==
*/
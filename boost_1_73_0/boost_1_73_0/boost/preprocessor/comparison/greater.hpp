# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_COMPARISON_GREATER_HPP
# define BOOST_PREPROCESSOR_COMPARISON_GREATER_HPP
#
# include <boost/preprocessor/comparison/less.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_GREATER */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_GREATER(x, y) BOOST_PP_LESS(y, x)
# else
#    define BOOST_PP_GREATER(x, y) BOOST_PP_GREATER_I(x, y)
#    define BOOST_PP_GREATER_I(x, y) BOOST_PP_LESS(y, x)
# endif
#
# /* BOOST_PP_GREATER_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_GREATER_D(d, x, y) BOOST_PP_LESS_D(d, y, x)
# else
#    define BOOST_PP_GREATER_D(d, x, y) BOOST_PP_GREATER_D_I(d, x, y)
#    define BOOST_PP_GREATER_D_I(d, x, y) BOOST_PP_LESS_D(d, y, x)
# endif
#
# endif

/* greater.hpp
LW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9saXN0LW9ubHkuZFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlL+kOd/AAEAAJIBAAAqAAkAAAAAAAEAAAAAAKS3BQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9sb2NhbC1wb3J0LmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSE0gFBwABAACrAQAAMAAJAAAAAAABAAAAAAD1uAUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvbG9jYXRpb24tdHJ1c3RlZC5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUidR3aBgAgAAqAQAACgACQAAAAAAAQAAAAAATLoFAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2xvY2F0aW9uLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSJgqzlDwBAAAoAgAALQAJAAAAAAABAAAAAAD7vAUAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvbG9naW4tb3B0aW9ucy5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUuG7MTXYAAAAOgEAACkACQAAAAAAAQAAAAAAi74FAGN1cmwt
*/
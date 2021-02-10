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
# ifndef BOOST_PREPROCESSOR_SELECTION_MAX_HPP
# define BOOST_PREPROCESSOR_SELECTION_MAX_HPP
#
# include <boost/preprocessor/comparison/less_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
#
# /* BOOST_PP_MAX */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MAX(x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL(x, y), y, x)
# else
#    define BOOST_PP_MAX(x, y) BOOST_PP_MAX_I(x, y)
#    define BOOST_PP_MAX_I(x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL(x, y), y, x)
# endif
#
# /* BOOST_PP_MAX_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MAX_D(d, x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL_D(d, x, y), y, x)
# else
#    define BOOST_PP_MAX_D(d, x, y) BOOST_PP_MAX_D_I(d, x, y)
#    define BOOST_PP_MAX_D_I(d, x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL_D(d, x, y), y, x)
# endif
#
# endif

/* max.hpp
VBIAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9RVU9URS4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUkvHcOrQAwAA9QcAADMACQAAAAAAAQAAAAAA1VwSAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfUkFORE9NX0ZJTEUuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLauO1dRAYAAPcMAAAtAAkAAAAAAAEAAAAAAP9gEgBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1JBTkdFLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSQ3wfvpAEAADkCQAAMAAJAAAAAAABAAAAAACXZxIAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9SRUFEREFUQS4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUkUPQKbbBwAAOBIAADQACQAAAAAAAQAAAAAAfmwSAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfUkVBREZVTkNUSU9OLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS9MlJ
*/
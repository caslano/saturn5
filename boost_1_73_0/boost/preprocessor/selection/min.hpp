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
# ifndef BOOST_PREPROCESSOR_SELECTION_MIN_HPP
# define BOOST_PREPROCESSOR_SELECTION_MIN_HPP
#
# include <boost/preprocessor/comparison/less_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
#
# /* BOOST_PP_MIN */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MIN(x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL(y, x), y, x)
# else
#    define BOOST_PP_MIN(x, y) BOOST_PP_MIN_I(x, y)
#    define BOOST_PP_MIN_I(x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL(y, x), y, x)
# endif
#
# /* BOOST_PP_MIN_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MIN_D(d, x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL_D(d, y, x), y, x)
# else
#    define BOOST_PP_MIN_D(d, x, y) BOOST_PP_MIN_D_I(d, x, y)
#    define BOOST_PP_MIN_D_I(d, x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL_D(d, y, x), y, x)
# endif
#
# endif

/* min.hpp
waf8ueT/olr/pmz+bK3wMixZ5GndH02f8a81/Y9mlacGKumf/8t8Pn6D01LTktPQoGy1UvrFi02iHcaBj1+3IB+/zGH9/Rr5+HWMMiOpEdCzoY9fZD9//kv08eMJwQCuh/AxYwA3sVpFZPj4haKPCdTPV1WwSG1dtjfQxdvDkHWvaHJqpi6/YnvdYzRZhk2MwCVeulCX9n11qcebAvr8TNySmrTrbci3roa4l+VzCV1eaWLI
*/
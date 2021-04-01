# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_PUSH_BACK_HPP
# define BOOST_PREPROCESSOR_ARRAY_PUSH_BACK_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
# include <boost/preprocessor/array/detail/get_data.hpp>
#
# /* BOOST_PP_ARRAY_PUSH_BACK */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_PUSH_BACK(array, elem) BOOST_PP_ARRAY_PUSH_BACK_I(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array), elem)
# else
#    define BOOST_PP_ARRAY_PUSH_BACK(array, elem) BOOST_PP_ARRAY_PUSH_BACK_D(array, elem)
#    define BOOST_PP_ARRAY_PUSH_BACK_D(array, elem) BOOST_PP_ARRAY_PUSH_BACK_I(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array), elem)
# endif
#
# define BOOST_PP_ARRAY_PUSH_BACK_I(size, data, elem) (BOOST_PP_INC(size), (BOOST_PP_ARRAY_DETAIL_GET_DATA(size,data) BOOST_PP_COMMA_IF(size) elem))
#
# endif

/* push_back.hpp
/oU7FBxdmbg24riGXnXrIwPZBoB6xJWJqoamAhYXyc2pkm+4TBlXQFjk15La0XfLMt+PVM9hwfafC8RqDJMyign+3uQuXBlhBEPlrTMCIvFDtR8FmlY95GiRT3v+x+bcaVLWMFHBSD6mGCsdj3Xdu1c+vRNEDy9L87gSEiQYq1md5pR1U8Wlfrj2Qv+wpI1sOWvU1/Ng/ux4xVeXEPvkXbVQeGWkBYbpY2klw8YZeAzLzRiEjTc53Q0sytgDfJ+Ls0xqSJH96XsRNEyRD/iByTrSOAt7YLNzdPm+vdfGiDZNRNPGdU1/p0PHPdVyrPDXHc/opmXNbBH8jYjV25HEg07OpcmY47XLPANuCC8greOs6eKxVP98gAOqHg4WUAR1L86tmdecs1DJpdYHa7f6gexjTDAiMwYOlLWpRVXZ3eWP++9C026Afgew0rcyEcBdA5Rt2D0VTDK+AkUqdgw5iN/uJaGJeWRRgSVzVIKmTnU9aC2mPEV/doJkL/dPBxF+/RfyYgV8dKXyom7gdyKHdYVNC0+gkYJo1Ksdtysil/k7xiplS+OBqQpnKw==
*/
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
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_PARAMS_WITH_A_DEFAULT_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_PARAMS_WITH_A_DEFAULT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/facilities/intercept.hpp>
# include <boost/preprocessor/repetition/enum_binary_params.hpp>
#
# /* BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT */
#
# define BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(count, param, def) BOOST_PP_ENUM_BINARY_PARAMS(count, param, = def BOOST_PP_INTERCEPT)
#
# endif

/* enum_params_with_a_default.hpp
ymhAuXtfQh60e/XL6C2ymuqNnmCvPErhgyKLk9SxD2urbuSdRb5FWhKHuDNI0xK70YPyl5nz0DNW/iG1KKsEfWrql4M986e8CUGst5in6s/APubDt2Be/vkp5j5stU+9x2U5QPliFVUflluFfGdSN/Ltp9Y9o9XYfb+Dg70tnft5SahI3SjKa02fR8rvHhfI51xbxq8b67ks5kvm35c5FyiCT8N4voNc11HmKSXb2KfUusnV
*/
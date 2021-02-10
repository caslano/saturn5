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
CAAtZ0pS0NHZx6cEAAAHCgAAMwAJAAAAAAABAAAAAABB6BAAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9NQVhBR0VfQ09OTi4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUgfr8tTZBAAAnQoAADMACQAAAAAAAQAAAAAAQu0QAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfTUFYQ09OTkVDVFMuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKOKL+xTwQAAEIJAAAzAAkAAAAAAAEAAAAAAHXyEABjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX01BWEZJTEVTSVpFLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSMIJkz2gEAACjCQAAOQAJAAAAAAABAAAAAAAe9xAAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9NQVhGSUxFU0laRV9MQVJHRS4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUqnmNzkuBAAAEwkAADEACQAAAAAAAQAAAAAA5vsQAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9v
*/
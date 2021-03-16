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
YUpaaj9QrEWjtDg9W+w/4s8GFWflZmWUFMh9W/ydSXnWRjbruaJ1/jw/xNM+O7IGZdpnS/IYV4+KC8fkkLUfCOhmVNjhOPaieDYsnpUsKnL+ZS5TKezuz8ph8af35yVh0Z9Vwo4OnvfoLQu79baaLFNdK1Mx7C5TQ5UJizI1ZZloD0+R56CbFCNxa4fdOqav43brZRTVlWXqeehzWbf00G8gcRtq/K8OOr8byN/+5w1bZwtrp6lqz1KHmkq6M5U=
*/
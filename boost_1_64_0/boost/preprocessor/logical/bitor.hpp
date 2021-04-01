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
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITOR_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITOR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BITOR(x, y) BOOST_PP_BITOR_I(x, y)
# else
#    define BOOST_PP_BITOR(x, y) BOOST_PP_BITOR_OO((x, y))
#    define BOOST_PP_BITOR_OO(par) BOOST_PP_BITOR_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_BITOR_I(x, y) BOOST_PP_BITOR_ ## x ## y
# else
#    define BOOST_PP_BITOR_I(x, y) BOOST_PP_BITOR_ID(BOOST_PP_BITOR_ ## x ## y)
#    define BOOST_PP_BITOR_ID(id) id
# endif
#
# define BOOST_PP_BITOR_00 0
# define BOOST_PP_BITOR_01 1
# define BOOST_PP_BITOR_10 1
# define BOOST_PP_BITOR_11 1
#
# endif

/* bitor.hpp
SEIzyQDhji8f/uCv2lxsUbUmvXdFYUV4Kr1Or5h14ieLxRrO8Ma8pE5TzoVg4jC+CYl695jaiChC0wB5wiezdQNJYcP1xLJoHu5sUIxFZAudRpv8wz+HD577uHn4+S/YhejK3t7AGHmyYzh8uqJw/7q0VQ7sdp+fY5Lof/U9EpEr79uieAiELlZYsrd3ZmA24qd1uyoC3vYN4QF4z7y40p9d5KX4MEnuef9FlNfItbOddQutyhL88qzte8wXlcx2e3B6Q3GJauW3Eat5v8CUgwn/Bj5ioyl0akcAXzBG5PB8B2vodF3o/jUWWy3S1EKb7oxsIWPgagcAOWt96ifnUo6+1ucUIgOf/sV69BRCVzg0ocqVSEwc8ohATLDlI3IJRxDijnkMeTzL5vYZrDa9OlNB23uchJGb/xYqIiMYxCYYoqH9km5GQgUX4Ode81hWAw8ns0nPfcLB0fRAA8CGM9GYZeqcZHkD3a3tP7SOtWciJ6X5qgFBOuFVJGS7TNbXhDZUwqOAPMkQrt4Sqp/qLi073DhY+Y+nJRTHhg+koI28jMOek+pl6pHOSw==
*/
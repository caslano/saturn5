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
# ifndef BOOST_PREPROCESSOR_CONTROL_IF_HPP
# define BOOST_PREPROCESSOR_CONTROL_IF_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IF(cond, t, f) BOOST_PP_IIF(BOOST_PP_BOOL(cond), t, f)
# else
#    define BOOST_PP_IF(cond, t, f) BOOST_PP_IF_I(cond, t, f)
#    define BOOST_PP_IF_I(cond, t, f) BOOST_PP_IIF(BOOST_PP_BOOL(cond), t, f)
# endif
#
# endif

/* if.hpp
NxPbgvkcDelet1dDbcWYXW5ih/Hd8OGQfntr8D2yNQeZWD+sS2OcsY6OGqvELNjEmnHsJueHmXOvgt2B++gaE/sMyxfhLPvcc6eVfE40sR3jJBsP6Zw3+0HMMC9/MbG7MC+RzmNl0fzFyvY2m1jXnpJNgHTeBx2h6mN92WNi8XjcOhvq7O7fVCj77ymIGdq1kF7X9D6uE/6DwRtvxLhYIbn4uQ9gC7gfKk3sU7NkEyH9lOk9
*/
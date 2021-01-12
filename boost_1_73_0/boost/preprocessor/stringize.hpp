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
# ifndef BOOST_PREPROCESSOR_STRINGIZE_HPP
# define BOOST_PREPROCESSOR_STRINGIZE_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_STRINGIZE */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_STRINGIZE(text) BOOST_PP_STRINGIZE_A((text))
#    define BOOST_PP_STRINGIZE_A(arg) BOOST_PP_STRINGIZE_I arg
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_STRINGIZE(text) BOOST_PP_STRINGIZE_OO((text))
#    define BOOST_PP_STRINGIZE_OO(par) BOOST_PP_STRINGIZE_I ## par
# else
#    define BOOST_PP_STRINGIZE(text) BOOST_PP_STRINGIZE_I(text)
# endif
#
#if BOOST_PP_VARIADICS
# define BOOST_PP_STRINGIZE_I(...) #__VA_ARGS__
#else
# define BOOST_PP_STRINGIZE_I(text) #text
#endif
#
# endif

/* stringize.hpp
LcF6Sa8LJXeF+v1DTbJ7tcdz35VflPzZEdLTUdVX5x+Yj1Vu0D/vUj95UvqTPheepP6l9lilem3T+P6E6lOiflao7Y+/ofbLk135NM+XP7g92I+yJYdD7S572Z4VoXFP7SX7mzFL/VX2+lqi2lW/25ot+9VyV9AOmtXvdsnuD2u+Ui7//wO137UqV+PfTvmrnX9QP09Uvx3Q7zUPfWie2n2uxpVl8qvUw+ZPIQQ/M/Aevpl3
*/
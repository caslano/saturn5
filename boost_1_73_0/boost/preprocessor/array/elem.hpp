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
# ifndef BOOST_PREPROCESSOR_ARRAY_ELEM_HPP
# define BOOST_PREPROCESSOR_ARRAY_ELEM_HPP
#
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_ELEM */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_ELEM(i, array) BOOST_PP_TUPLE_ELEM(BOOST_PP_ARRAY_SIZE(array), i, BOOST_PP_ARRAY_DATA(array))
# else
#    define BOOST_PP_ARRAY_ELEM(i, array) BOOST_PP_ARRAY_ELEM_I(i, array)
#    define BOOST_PP_ARRAY_ELEM_I(i, array) BOOST_PP_TUPLE_ELEM(BOOST_PP_ARRAY_SIZE(array), i, BOOST_PP_ARRAY_DATA(array))
# endif
#
# endif

/* elem.hpp
+WrSf1h39IC1dyXf3tWBYbj+XFNauGSpXY/VKfNJ5y1MUz+ne4zXkH6iZO3vrL25piVK85cwXK+geraFxVDeJ85hLowxF6nN80l/9ukX91uSXWF61eaJYRjPa2y816K8T7zvcFGM+ZLLknsNybb0D//akuyjZm2irsEn2P8MaU2FXaE/yDn0uYlPxJhYtyXztYEzk+cyv2pJtcI0niOffmYY2rrCtucnlXXIu+3fiDHbdY/p
*/
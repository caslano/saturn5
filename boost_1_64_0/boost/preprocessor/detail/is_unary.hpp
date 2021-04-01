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
# ifndef BOOST_PREPROCESSOR_DETAIL_IS_UNARY_HPP
# define BOOST_PREPROCESSOR_DETAIL_IS_UNARY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/detail/check.hpp>
#
# /* BOOST_PP_IS_UNARY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IS_UNARY(x) BOOST_PP_CHECK(x, BOOST_PP_IS_UNARY_CHECK)
# else
#    define BOOST_PP_IS_UNARY(x) BOOST_PP_IS_UNARY_I(x)
#    define BOOST_PP_IS_UNARY_I(x) BOOST_PP_CHECK(x, BOOST_PP_IS_UNARY_CHECK)
# endif
#
# define BOOST_PP_IS_UNARY_CHECK(a) 1
# define BOOST_PP_CHECK_RESULT_BOOST_PP_IS_UNARY_CHECK 0, BOOST_PP_NIL
#
# endif

/* is_unary.hpp
7lltiLj2cre+7MOaCF2Yut84XEgenO+FN+k7Jui6Rqyx86uOPSRg7+AqIB+sDnj5pC3DgCFPirwpxIZP68ZFogiS5q8pygzbMB7iuGdvPtEclc+RTaNZbCxG1D7Z93JarMS3mc9ajmbDPJEZsjTcsdZS6GQVXYiHaPlRmWsg/80NrQHz/hAHJia0qG7nGRzu1drPe0UHdoR61w54VLeZgW1OiLyg93ReEFwQJHdUZPMZKLo4Dff+I2L+6zCXI4lmZgEl1hqAPeCgI+iQkzXF2KYtRow0mYPFdMPFwfWOrt9LWCn8fZs7AcyYmNAjlcu2RNYycUFLAneWCR17u68wDzbuQMkDK/aj+xN4CwQIlncrqLB2n+bQDBwP1MiMXLzzEt7k24aTN+tasYT2KBnAWOWD+Y/TjMsR1jrJHJB0m1a7fKnANLP5pg4X+tzzUk1LWNwKcjlRAxpdMlzefz/Ctjp/NrAeQki4ukqMphTOAymxil31zQhtHaOmWZHZ3cSc/wDLyU0KDJmXXvP47idfKxXag0wyWJ6jglvizeOy0E4PbjNpv9JSUX9JGg==
*/
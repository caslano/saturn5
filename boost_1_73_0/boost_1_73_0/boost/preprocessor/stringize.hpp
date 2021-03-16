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
94Je6NCJVchpKzUwaAjy1DswVt8zOuXDRjyFPCoeOdyYRRqtgh/ZAL60QjxcHTagJ3K1A+BH4VvwlYjHHn2A6D7IQrcSxK3INSsjV1j3FfRnlkab3jfoT8jXe8gdc9ojFoLcZSBWn45xzq9ONCQHMoxcqSFiOh/0cCFis+ww88egrmizDmUdMV+/gl/T4B8XwHdfj9hk/AzEFmWITWATzyFueW4LcnLktk/DHyesNWj1HRp9UAk2Hj6lBebjvj8=
*/
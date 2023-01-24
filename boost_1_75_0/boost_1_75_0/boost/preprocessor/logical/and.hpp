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
# ifndef BOOST_PREPROCESSOR_LOGICAL_AND_HPP
# define BOOST_PREPROCESSOR_LOGICAL_AND_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/bitand.hpp>
#
# /* BOOST_PP_AND */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_AND(p, q) BOOST_PP_BITAND(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# else
#    define BOOST_PP_AND(p, q) BOOST_PP_AND_I(p, q)
#    define BOOST_PP_AND_I(p, q) BOOST_PP_BITAND(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# endif
#
# endif

/* and.hpp
/SxXoyFmD1o1tMg6YxTVvKB8caywN1B0NOgdw0f9HmhMfM9qmihqy09eUZtTn2M7ZzDUNbh07urHbxZSRXnem3YoFHcvYPuz3z8k24SFOn2S1eK3swEGEpH8Gpsvq1IySYR22/j0bi9PbFm7owMGykZaIrvI8654b9DNN/8vjqtXxqQ5IHs9Pzvnjy9zC2j46Ua0BtUzmNk1FXE1FZjhn3jtN9yNx6hHKn0hukoUYMD3LBWP2Ni7U0n/7tkync6zpkvu9GGtT9Gp3P4Tzvb28A6dGXcwo73i9SHG2659LKlL3ecVtvaIJGH7NUt0yVGy+940+Z75TquckqqTXkSD0ydS5Z4Tmu5NyltVs6n01xqWAp2yuyuYd8VjBJABtYtu73gT+cl+zbVbbVRKdpqjqly+D63DPgR7N79o5VjZkcwhbbGT0NY+lPiVOf9BG5KK25xcNWNJCu/It5CDJkOeEwVyWxULmUOPU8Tn8y0qOORqWk1mKq6fM+OOkH3VxX4h4CpNsmtfcaYaK2c6N3k25GUywnCWP9SlCZIL4qwIqBp87KMl7FhMqdz6cNOpJ7VZR9lfT+CBw+H9Ul5nqlsLgXp7UEUXGFVrgOWjqqZedN5VEgovMenTGfNuV1dMa4lhONad1Wge7TPaVeGa2f3Qw+zntm3sR+1FQ4j7rMFsrqlOfq0cMzs0uhLT9sW/44t/yxf/nim2lbByiwVz
*/
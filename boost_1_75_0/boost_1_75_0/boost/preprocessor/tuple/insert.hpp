# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2013.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_INSERT_HPP
# define BOOST_PREPROCESSOR_TUPLE_INSERT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/insert.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_INSERT */
#
# define BOOST_PP_TUPLE_INSERT(tuple, i, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_INSERT(BOOST_PP_TUPLE_TO_ARRAY(tuple), i, elem)) \
/**/
#
# /* BOOST_PP_TUPLE_INSERT_D */
#
# define BOOST_PP_TUPLE_INSERT_D(d, tuple, i, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_INSERT_D(d, BOOST_PP_TUPLE_TO_ARRAY(tuple), i, elem)) \
/**/
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_INSERT_HPP

/* insert.hpp
3IQzfAHu+GYdDhBDlDHiFzfF3woIOWCkA5ZDEtJ5zhTpoAW1Ud22j9ynE2dfCwkVL/bZe/keyzDKAqZ+kw1qI7+0Qis/SUvPwPHOl8h9ruZfdGIM25BwNMyhJtaKm8Tz0Hzf0YrU4ERB1Wdrk+KZrKB9WicVgjD5XmnfBOaOnffP9Z/m1sfZJ1x0LOHdaXp6V4UWFo/hSj3HzdEj+x3vruceadHYE0UZzrAmFq6NLV0YzuOPA0SeZz3oehSpKHLZ3Z59J+fGnv9onuupFVeC2jl718SnPcpyUXT7YVmcwFxssAdr/lxp6Zt899xxt0bzUSqWH8VKmi+TrJM1dyJiircYjPdxTNXjqaEDK1b38aVPm2n4N+PuI71j9Q1deytpln5c6PsRzodBVklFo3GftDVxq3NPn2aZDV9s9/x4UY+ueLbdNxTCa9x2xdfNweN7UaYXPvktpZP7oqS5qMcR+Nq6DNCF5QTFdEd805NtyvPAnTvXPtrNe9VWqOsvDHHD/WtpPYehOTloyxOUwD3zRv+PxQXyEMGeVjNOUzRztJYmF3J3vYTLssAI+KkD4iRyptIQqkKtAWvGUtyWD+bZpUVepmzH3Kp3HSt/HMuRcRfzKEP/5vUxe/T4ptbCufnwl0sKZLIHmGHIfSBwJGcFRS6YG1gS6ROg7cuehfEz9lFzc+Nxj5VWVB7m+B3VojwEtvSz8NjmekwX80DD
*/
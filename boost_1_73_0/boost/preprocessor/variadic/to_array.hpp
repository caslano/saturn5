# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_VARIADIC_TO_ARRAY_HPP
# define BOOST_PREPROCESSOR_VARIADIC_TO_ARRAY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
# if BOOST_PP_VARIADICS_MSVC
#    include <boost/preprocessor/variadic/size.hpp>
# endif
#
# /* BOOST_PP_VARIADIC_TO_ARRAY */
#
# if BOOST_PP_VARIADICS
#    if BOOST_PP_VARIADICS_MSVC
#        define BOOST_PP_VARIADIC_TO_ARRAY(...) BOOST_PP_TUPLE_TO_ARRAY_2(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__),(__VA_ARGS__))
#    else
#        define BOOST_PP_VARIADIC_TO_ARRAY(...) BOOST_PP_TUPLE_TO_ARRAY((__VA_ARGS__))
#    endif
# endif
#
# endif

/* to_array.hpp
5rhuI1i+rPzHp8jZbuw4tYuLc2fPOTw4PKg4TXfhezNnEHmLsbd6rDg/mfKTXzy5375VQ+9nFceLHHdWNcCGT37ohMFD9OyuPAffZ/7EW4Te1HFDZ+qFk5U/xg9/4URPnvPgzzDdvbvP7e51xXl+8idPDOUlWDvhU7CeTZ0n96vnrLyJ538VIEt3FTnBA+r7gOiHESCuIz9YVJ0hQEbeah4yECAA1MLAcb+6/swdz/Azcp6i
*/
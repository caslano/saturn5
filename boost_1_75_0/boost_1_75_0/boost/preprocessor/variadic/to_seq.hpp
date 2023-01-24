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
# ifndef BOOST_PREPROCESSOR_VARIADIC_TO_SEQ_HPP
# define BOOST_PREPROCESSOR_VARIADIC_TO_SEQ_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/to_seq.hpp>
#
# /* BOOST_PP_VARIADIC_TO_SEQ */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_VARIADIC_TO_SEQ(...) BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__))
# endif
#
# endif

/* to_seq.hpp
pPJy54b/cdenN7ClmZl3HDY38+Mzk0969beQVgRMXnr5I5G3JdSozhuSzI+WqbZMDbr18ysKKzr2+Y2hWYXu5diWVYqGSLHtOY0UVXHz1r5WZTyS7zwQXdAqVFGt42wqdPgVSzhXGOx5FQq9ntrqMc5Nume+l9bdOpzDfd6a4SJauK3YPgJ8OCeZ/Mx7cIL15Bd4WFgvW5NIXe4/Kao6Hg45Q+KtE3pi0fAytbIcQplU8kfv9HjS2T11qrwWoz7UqnzFbDpD6WwPgP91Bd+85DbgwHzySy8TekIl9SZkpMgZZckIe+VJPNUbEZljx31b2mDatgePomaCyqMPHuD5sC2c7Nf5bvImUAXsRAj+sBvaHz/5gEQ+vv4mTA0/pdwfvXtwejzvpgsuXq2qFyHEGBNLSomHZv8LFFVE3/7Eyp0LigkKHrQhaDAbwc5pnzZzc9TTq15z3Juz9+G4/4J7lvvPwj//L9wz/L+UPzVzLzeO/wbs2+kuukPCnlPNdd/Cd6k9epYimAdrWFSSaaRqaK7EwNgg+iLKwRr9kMRsmiLc0vi41BQuppSlzBvwiMMu1/rIcPdBXu/3esVFY4nZIvpIMFKk+d+1tIg8FKRrkIUK27ehKRr2B8GHDSnhYWwaFOJGhJYPIhtVrlD+hzVXKDDuAQZbtQV4nZ9UQHBde/yVKSsP/4i3VERzmZXgbf14Om3Rm2CcAOL7V/UU
*/
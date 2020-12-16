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
# ifndef BOOST_PREPROCESSOR_COMPARISON_LESS_HPP
# define BOOST_PREPROCESSOR_COMPARISON_LESS_HPP
#
# include <boost/preprocessor/comparison/less_equal.hpp>
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/logical/bitand.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
#
# /* BOOST_PP_LESS */
#
# if BOOST_PP_CONFIG_FLAGS() & (BOOST_PP_CONFIG_MWCC() | BOOST_PP_CONFIG_DMC())
#    define BOOST_PP_LESS(x, y) BOOST_PP_BITAND(BOOST_PP_NOT_EQUAL(x, y), BOOST_PP_LESS_EQUAL(x, y))
# elif ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LESS(x, y) BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(x, y), BOOST_PP_LESS_EQUAL, 0 BOOST_PP_TUPLE_EAT_2)(x, y)
# else
#    define BOOST_PP_LESS(x, y) BOOST_PP_LESS_I(x, y)
#    define BOOST_PP_LESS_I(x, y) BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(x, y), BOOST_PP_LESS_EQUAL, 0 BOOST_PP_TUPLE_EAT_2)(x, y)
# endif
#
# /* BOOST_PP_LESS_D */
#
# if BOOST_PP_CONFIG_FLAGS() & (BOOST_PP_CONFIG_MWCC() | BOOST_PP_CONFIG_DMC())
#    define BOOST_PP_LESS_D(d, x, y) BOOST_PP_BITAND(BOOST_PP_NOT_EQUAL(x, y), BOOST_PP_LESS_EQUAL_D(d, x, y))
# elif ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LESS_D(d, x, y) BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(x, y), BOOST_PP_LESS_EQUAL_D, 0 BOOST_PP_TUPLE_EAT_3)(d, x, y)
# else
#    define BOOST_PP_LESS_D(d, x, y) BOOST_PP_LESS_D_I(d, x, y)
#    define BOOST_PP_LESS_D_I(d, x, y) BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(x, y), BOOST_PP_LESS_EQUAL_D, 0 BOOST_PP_TUPLE_EAT_3)(d, x, y)
# endif
#
# endif

/* less.hpp
rzgp6ljX+4DBLwQMfiFQ2C/ka1fERK5XSwTN4AMCBh8QMPiAgMEHBAw+IGDwAQGDDwgYfEDA4AMChvkeMMz3gGG+BwxrgIBhTgQMcyLgnROadmVMZL/+o6AZ1gUBw/lGwHAmEzDMnYDB/gMG+w8Yzn0Che0/X7ta2cFMQdPOgtLriBAVzTsn0Az2HziB62Xe88zs7N4wuO+gIbnT4Og50OSYcyBomANBwxwIGuZA0GDvQYO9Bw32HjTYe9Bg70GDvQcN9h402HvQYO9Bg20HDXYcNNhx0GDHQYMdBw12HDTYcdBgn0GDfQYN9hk02GLQYGNBr42peIl/3sZYjI7MMPvb5GPaWshgayGDrYUMthYy2FrIYGshg62FDLYWMthayGBrIYOthQy2FjLYWsjgW0MG+wsZfGvIYJMhg02GDDYZMthkyGB/IYP9hQz2FzLYX8hgfyGD/YUM9hf6E+ca7lnJIG7Fd2XW8N/Z/2Qf0/bCeXu6mIiW0RLNYI/hwvaYr02KibT/fQvNYKPhwmuCfG0K2lN1Ra7RtJmqLm9rdZmttMqt0Aw2HzbYfNhg82GDzYcNNh822HzYYPNhg82HDTYfNth32GDLYYMthw22HDbYctjgX8OF7Ttfm6f6tIbWp/crrUd9tMLriXxtsYo3WaX1rjHChedQvvagSltF65eHlRatNO/7r2HD/Asb5l/YsD4JG+Zk2LA+CRveqwob5m7YMHfDJ7A+V3M379GwNpkRdawzi0SDXSca7DrRYNeJBrtONNh1osGuE09gDaafu+ZeGEeYzh3vPaZvOt/gh9C8fgjN63MKtM0x2HI9kYelQHtTae9q2jtKK2sVaO8pLaA0r29C8/omNK9vQjOMIZp3DNG8Y4hmGEM07xiieccQzTCGaF7fhOb1TWgG34Tm9U1oXt+EZvBNaF7flK/tRuvq6krz+is0r79C8/omNMO1DM3rr9C8/grN4K/QvD4HzbuHQTP4ITSvH0Lz+iHNDpStLdds44DSVmraF0rro9J6fBOa1zeh/Yl1hXrkLZMRl+YMHWbwUa8fNXfFD37wgx/84Ac/nHDQf/9vcxTriDTWYp7f/wuVjlBFWHvw6Ia89fEyYY1CBk7eWlhp41MKtKJK23JmgVZcaV9rWkmlPRAq0Kqi/YA2p2iBdqrSyhYr0Gorrb4Wr77SntK0M9FqWSJ9nQKtIVoa2rlSoMUr7UxNa4w2Fm25prVSZdymlXGuSltRi9daxTtXi5egtMaaFlRpg1rarmhvok3StCEq7bNa2lFK+9oq0KagFbdZl2tp56C1QLtI09agDUFL0rS1qi5dNG296r/PNG0z2n2kDWja+2jvoCVrddmHVtPBlhyt/ypE6nyppnVCc9N+ouXXGW04cfZqWl+Vdp5WxjCljSpSoI1GW0jaylra29C+Q6uqaS+otBfaBdoWtCB5rdPq9wma21fZWtpv0dy27dHS/qzqnCWa3bur19x1umb3aG7/1de08mhuXTK08Y1SaSto8c5Cc+fM6hTN/lTaTrZmf2hunatraRPR3Do/qWnJKp4+F/orrbGmZaNdQb+8rtsk2kNow7TxGKPa1kKLdzva+8SroWmzVRl9NG0uWhTtX69py9HCaHU0baVK213TnkW7o+jR47ta9V8nTXtJ1aW1pm1U/XeO1n/b0FZ58juk8uulaYfRSuKX6mpak5Mj+VXX/FUzNNc2WmrxmqO5ffqi7jfQ3LalaFpbpQ3QtHZobci/qaYlobn995qmdVTlHtK0NFW/rlp7h6K5bYsVNG3/OI4y9mjj+7hKu8LS+h7N9VfPWFrfo20jbbSW3/No9P1R2iuGPthlaMeHqoynNe2I6pc=
*/
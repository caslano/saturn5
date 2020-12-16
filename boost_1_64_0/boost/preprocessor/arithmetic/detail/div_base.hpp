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
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_DETAIL_DIV_BASE_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_DETAIL_DIV_BASE_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/arithmetic/sub.hpp>
# include <boost/preprocessor/comparison/less_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_DIV_BASE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_DIV_BASE(x, y) BOOST_PP_WHILE(BOOST_PP_DIV_BASE_P, BOOST_PP_DIV_BASE_O, (0, x, y))
# else
#    define BOOST_PP_DIV_BASE(x, y) BOOST_PP_DIV_BASE_I(x, y)
#    define BOOST_PP_DIV_BASE_I(x, y) BOOST_PP_WHILE(BOOST_PP_DIV_BASE_P, BOOST_PP_DIV_BASE_O, (0, x, y))
# endif
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_DIV_BASE_P(d, rxy) BOOST_PP_DIV_BASE_P_IM(d, BOOST_PP_TUPLE_REM_3 rxy)
#    define BOOST_PP_DIV_BASE_P_IM(d, im) BOOST_PP_DIV_BASE_P_I(d, im)
# else
#    define BOOST_PP_DIV_BASE_P(d, rxy) BOOST_PP_DIV_BASE_P_I(d, BOOST_PP_TUPLE_ELEM(3, 0, rxy), BOOST_PP_TUPLE_ELEM(3, 1, rxy), BOOST_PP_TUPLE_ELEM(3, 2, rxy))
# endif
#
# define BOOST_PP_DIV_BASE_P_I(d, r, x, y) BOOST_PP_LESS_EQUAL_D(d, y, x)
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_DIV_BASE_O(d, rxy) BOOST_PP_DIV_BASE_O_IM(d, BOOST_PP_TUPLE_REM_3 rxy)
#    define BOOST_PP_DIV_BASE_O_IM(d, im) BOOST_PP_DIV_BASE_O_I(d, im)
# else
#    define BOOST_PP_DIV_BASE_O(d, rxy) BOOST_PP_DIV_BASE_O_I(d, BOOST_PP_TUPLE_ELEM(3, 0, rxy), BOOST_PP_TUPLE_ELEM(3, 1, rxy), BOOST_PP_TUPLE_ELEM(3, 2, rxy))
# endif
#
# define BOOST_PP_DIV_BASE_O_I(d, r, x, y) (BOOST_PP_INC(r), BOOST_PP_SUB_D(d, x, y), y)
#
# /* BOOST_PP_DIV_BASE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_DIV_BASE_D(d, x, y) BOOST_PP_WHILE_ ## d(BOOST_PP_DIV_BASE_P, BOOST_PP_DIV_BASE_O, (0, x, y))
# else
#    define BOOST_PP_DIV_BASE_D(d, x, y) BOOST_PP_DIV_BASE_D_I(d, x, y)
#    define BOOST_PP_DIV_BASE_D_I(d, x, y) BOOST_PP_WHILE_ ## d(BOOST_PP_DIV_BASE_P, BOOST_PP_DIV_BASE_O, (0, x, y))
# endif
#
# endif

/* div_base.hpp
GAPexuaiZph9vYJmIDyR5i4xVzAo1uV+IHh8MCCduwVNTcC82D1yXkPk/8eCR9Cc308Ej38Kndwv8M+KvPxcpPHVgLz8UtDcGkDzoEinXuTlIYEvE/jfCPxsgX9Y2IJ81ykp8vUHwU/udXlU4E8R8R8P0H2pTyZqY6r9c8l1oYl76J6E/X8W9s/91F1ij/mwkPFpxH034up9t1jvkfsB7BeauC//WeiOaH1rkUfPlfuGgufD/4H4z1Sb+CL9kP1sfJ7+C4j/EzHPvKDCH97L8fBhfC12jVibzTN65nPkvLVeX5Pn5w5YCL/KeGI+i8UJijvTOWghkxf7miAPeHGdBtvFweCRZXFU+3Ic20tTsZC9zb+Q5RXtgdQVDxMb8GV4yMplmxEgW/VCtg7GeDQJ/T8mwkkW5vvAaD++T1+HEn8uQzokz8dRnxsyPCLKuLQiSMfB87XLiAe3+1XmTRdWnz6I37Bn7Ief/JzLkcSX19vHhO94OeF5+DSxd0C2W6sEP7Jj2DPaPaYvpCfSpHl2QRPUrjUKmqA2qUnIItukNYJHUJu0VvCQbdI6oZ/Pir1Gcu3wNYKfbMNaBF62Pa0CL9ueiMDLtmejwMu2pkPgZVtzvMDLtmaL0GlQW9MteMi17BMIr89HMtv+KJtj+Qj7vajCPxe4jeIq2J5qsdeT4KZfd2dY7PW0ZYgwo6V2woc7hXDogxOfwn3wUxfaekg8pm7XThMyLEF7WSbmRb8esD9kCPqKL/TTDlJ4GHwvRv0bQXgRP5+LvFIb5p8PZnpYBNw7K11c0pQhcAT3yTRu8OBLcC8+4dOM98oKcW8k4fjeMjoHi7BcYyY4eJv9ZPRXl/cOZoffJ9gPA9bzzkI6hOe6CN/F9v28Hjo1sr6BwlxHbzT5RDoNlX5bfhPDU1wrA8njzmOKtuFI1t40qvor6t9bGL9swH7+t8EW6sLifhxhX++QfkLweafI5w3hAueLihz36z2OxJPX1TWV7pcX+2n3IA/vBj0vs/tgC9tZWyrPCu+uZG08xbmM5ZX0YM+N1qEM3ov03oX0OL+LCfY++rgMV4K+soLVN1vP+flY2tfo2nn4ajZf/CFRTw+n78MLxZnkhYXWvWhnodmDSnOO9izPRLC9D/SjxGupO5nnC18/i845TbkuEM0NJHUKEmj3v35ioTf398mF3h2Zhe0luzORGxy1nBmI872G8b0WfM+iubhtBdZxMJdJ4WR8nN+rqmG4VA9zaopXuZNK60lb92pJe//aZxbyve8knI7KpQUAsmKu1dWx4GlkCAkZzNsS17G0yorUjbGbd1VPXMu+Hrb5edjYMGS7gcJ8fZfikUxkMNHhRDLuWFiZhhFdMjEeB+0SrStXdIQpTZ3BqJ4dpPysx5zgF7jupmFHei9CyM63Bq9XFVEWym72wm70O03QQ00Jv68VebHr3Gn3grunmc0ApizJ7KssZ/sqZ4eRP2Nn+g2XtFv4WAe7idKudtRTAVrJ2lANbaOT1ggtCeOxxknvGN7lt9Ucwdepu72i7GwP4M3qfi8Bv5nSbXNII6wObHLGCaDl0m1mJ+0BVQKptNfibsZbWNn1FLlWzW1RnvP7ktfGE16cx2ftEQ8TnW2LOe/Zop95G9FzfLno536Ttf+ED5zruwN15ZOwEdQb2+ccwLlgxkfr/LuiPfgehZX9kq3Zt3V5eLcIN1OYy/5t4ft/CLnI53n7V0U+5NnvexBnMCxlBn1ItKM8TaxRLp/Ur3o2tg2+635jL6gvqVxqMJU0xuh2BSZAmy1kOJMaQ5O1dm1DM/n1oDr/EvBVPuHnrC35BcphDc7Vkf6t7+T33Ejf+iB0/CtmL3uhb16evxY=
*/
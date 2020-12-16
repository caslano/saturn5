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
# ifndef BOOST_PREPROCESSOR_LOGICAL_XOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_XOR_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/bitxor.hpp>
#
# /* BOOST_PP_XOR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_XOR(p, q) BOOST_PP_BITXOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# else
#    define BOOST_PP_XOR(p, q) BOOST_PP_XOR_I(p, q)
#    define BOOST_PP_XOR_I(p, q) BOOST_PP_BITXOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# endif
#
# endif

/* xor.hpp
0G0wT3O0XiluVvOxNKKa7LEXDIsNLVMCgCaNNEbEXhxneXK4oMIa5USa/1KkRphGBT9NgHZ/WQICRCKFNwSJHuf8PPKpcdFipMtfCOpEkRfcfkxDz1MV4eQ7Gpbnbsm3NjafMZKcXdPQLLGHBg/14yN4dl9Es7ZjEVj6FjnZtefSRX2GQPVdA5Z1XsRKDrXK4p193J1SaQlRnxqiLs1lBAsMxW5cKGYzMPI/szLuNS0DlvaWW3A8pOrcD8VjIcZaaw1dyHUxu2/Vmr24agpFa5TGg081eMRObDDsm/Tm/6i8P6650XGLa6MDfcmYaVqGYkJU9wuY+rheHjSoP57ka9llfhWXe6XsVNpJjaHk3u0e/WjFi055cIN3poxk3SGiSVFSRI9QahyaulwKA1htfo1B9tKP6zOwb3R738fOqXIeIKsCIRFtOrku6yDLo1qrpycXchsLvYly3dd1bhKx2TaSwuGWZOQ/Ub6pG97rtIwGHndPD6muAM+Tr3YiDylXsKq8wRq3zi0P6VbLxi4PDV2M1XvTb3zEOdhj3auf+bL0MuuF8Lw8QtHt4dORyo5KmztduoglZOU1IZsGuzzq5uosPQ68NOqIg8vqciDhaF559E5Q09nVWmq2M9qZsclZ5SP0YvCh0yVyTTm+Or9eOivRtmqwIsJWuLLhc/FuR4c9jrHp+bOi2PLosCcn8utyJp3z6PJk5HN9Wkvrsoig2J3O0hoxUOaMjkvXobI6Ul1ZJlip9m4L8DAGc6Tq5cnoFhgwUTSvbc3Xs0mYqq9Yw/KPwsPRz0gbuVdxtRJtsGkYlyLScC8RTi/XLRYLmq499sInJyVjvd3GtXoqnuN46sFxKWHvMDxpSp8j+UnfcI3QspOatyf3kOj1O1r3ujnSPVnyDp7R+WJzlcoxt/na9+S4U6e0YHHlb4Zhz8D9nKFhLVxN01FOtxam5svh6jkcniPFhDvw8/eyj2s8dE6EeZBjXGSSsX5U7lYXYhaDHHhRQgpvhIUZOCRDEsP5i3ZDCn/BXTbsa8z/BCV0XlROqnI7qnu2u470Y8RpHPUrb0Vy8LzXLfkmbRdajLl78ORko9MDHyQNFR80KS0mZ2hlcF9cWSr02lZXFlPbLH9CnlYJml4NaVUWjihNKoMkmcFwaSPC4tppITy36DdXJF7ytkZ6RJRq0Q3SK94m9hCgDHcdEsItPi1nBmHC3m6ep8J0fMnKKW6C9+S5tcy5tU4v5kdqjOuPT6j2AHkdLIYL4fFqbQ8a4ZjZUjKWW7v7GO7ukDGypOf/Z5osPsKGTL7HVYJMseo+r/d/4re+2dTrvhQPlyV0uAXrb+CSXpyExcw+GWTh6jQeXh4vDAz812ktBVV662FiKlE3EJmfc1zSysOxu4oSn/A1mqozaHNCD526mgITGGLxzRnl0nncqzOcvbJ2pjQl2jy0s8IgXgjmjMppWdVFJqI0o7KyaF94uEw760/g09NRfUuEvjmt6yztMh6pDldfydkcMzcbbY1lNtt3ZU0xtzBb2N3szs4ykk4SZzZ21tq1Wc3TMOuqDvTKJ9nbahO4jnE+yevtdu9rkX8xsAP/fCDYyEsuG5boqCPL7qFMIo92+2UyokNWJ3IzlJJId6hcsDXvuI5J5ifeajZTqafat1EmS3qlyXHQRcUj3Twa02WgG9jaXLag1cbvX0URJZFN3thkGds76yfZlRSqF04LV6RkarJOcOIgGWWh6rZGhbxgojil99BP6vvYGunk1f2aDtxR0a6Z8wzSKtSTeOMz5XTpIiyjm40u+daIKk4jqDNmaqL7KVnu5nEf7M9XC1A4jaqp3pfIRo8yryK97Xxu+n7TMw+a1vvf/XE=
*/
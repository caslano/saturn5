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
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_PARAMS_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_PARAMS_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
#
# /* BOOST_PP_ENUM_PARAMS */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_PARAMS(count, param) BOOST_PP_REPEAT(count, BOOST_PP_ENUM_PARAMS_M, param)
# else
#    define BOOST_PP_ENUM_PARAMS(count, param) BOOST_PP_ENUM_PARAMS_I(count, param)
#    define BOOST_PP_ENUM_PARAMS_I(count, param) BOOST_PP_REPEAT(count, BOOST_PP_ENUM_PARAMS_M, param)
# endif
#
# define BOOST_PP_ENUM_PARAMS_M(z, n, param) BOOST_PP_COMMA_IF(n) param ## n
#
# /* BOOST_PP_ENUM_PARAMS_Z */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_PARAMS_Z(z, count, param) BOOST_PP_REPEAT_ ## z(count, BOOST_PP_ENUM_PARAMS_M, param)
# else
#    define BOOST_PP_ENUM_PARAMS_Z(z, count, param) BOOST_PP_ENUM_PARAMS_Z_I(z, count, param)
#    define BOOST_PP_ENUM_PARAMS_Z_I(z, count, param) BOOST_PP_REPEAT_ ## z(count, BOOST_PP_ENUM_PARAMS_M, param)
# endif
#
# endif

/* enum_params.hpp
d2+JZNktnDUXMapdyr/pozfsZfoPM9QP4pdKcC+XCmdcY1VJCK3LUmGp30vJS/VuX59yy7zsG9SLzeJWIKu0sqBmW5Vyg02i9uluCrzPTklAvXvQvoyadc+wvlZ+neq7PWak8tjqR2KdsrWH+mwoN+1emKHbQ1NTzX2mX/tuOjjUNvpV2IUUl1mZyc0dHewhG0QJsjZaGfsU1FfMzlh1t2OSs43ENllWVGgkhna7ic+yEnfcYUu+jPMoxp3L0JdPhhJ32uTDoYwgY5PgfCCQ2rr5/lCS68pZ6UdT0mX00Ld7CQ3mIm7EvXpIVf11dY1zsvZWStUtPBaal+VUufDGxRcIZyoQK2sRWXeLcYKSI74Ya/qKg7eKhImJFrXBpKZvQG4xPNFzqbnC8znGe8LR+kK5PtcaQ9v+QpOh0YMeNpUZ2vYd3mBzbZmWTza07SZcmbhDJQz/FhseStlS1Se+Jdr2HmvaKbl/VxKX2hk6leyxns6hvKdkk8X1Pt5pJOZXVkIoLhxcOVtX0MtburtYFNYcl4wuo0Dr2xXoByKxLfATg6AWdpYupM84CKkJLi1NRcPsqdmGxno2GWftSy5s6gmlpjzYMdAMK585u7H6iup6625VSmZdfaeVNc6cVW1yRe5b+83I9tIF2dC+YmffgtL2SDZfh6+3K5LWpn3CvJJ+/M+Gz6m8Mtvb11vaSa39mOHsOUuldg3jPrts3VXV19nCy92daruXmfDP9LxMyejwqhcXYNvpxvNO15vFSY859dX2VxcGEmup0ktspO2ZW8KiX4IoDk3pZDtTNa/QyO0zP+ZAl51puz6UOy2+LpQ5zfsLMnHXhD/svJknqn4d2bDZaW+FyPbqkD/V34bp+GGDVt/aZMeoiUH4w8Cl9hbi+N2BbZiWylt72Npq62XU1mlGRc+3/nOKOZT+cqRuf42J4Q94HptW9qCRkU91Zhs/My1W/gkjl/kXkW610rmV5LWVHDNhMa/AkylLiLRSn7eyxUtFqq604eMlserZfpD2aiudXTHLqsQyzzuteatxyTIX+jgavsHy5r0ea3tl8HsOJ3boyYBtxgWTH/ZIoKv5P+vlqQMmOxP50mxyuk99LpDK+T6ldlj/6quvNu4Ex8Zu8yGR2oZ0WeqlRoH1BXUk7M3Z2TMz7MM0fohLWkw5VFtSUqXeZHl7DZkR3WIlOGhtfCztDhlGrRalvzF1J64+OXy2HkCYHPiIpV16fsJytlG1+W8l5udyz9HHRBbUUkVDjGgpr1hwY45xQC0efkX17Or6ilqTAFavbZP6lyGZmQ2N2bo51EvW61+MsGepzeDFheaoyMyLuLYr9VobVzvtZ448rwol7gjn60JZe46+3SK11qQIftbOrLqOF1EyLqOU+na+ntXwutXdIrEfflo4F2KtVMxtUvmx3KqpykvLw0KmBqfNwonOyMQUNjVl5MIByuNUI00X3UlWds1VhnvtafoOpqmlMjbion21RGQmYW8VzqQrZc6UcSuzvnxmxNyZWj2ky7sR3v52HZTRPHNzqWT/PSK1fopYvQ25zlHzSosZjy2lW/1WsW0qObsR//3IrIZ44Q4tc/eA8ToBnK3A79KUu7iAnctwrvFKeuj3IqPE4G3XzSJ8AJmjXa9WD2+YX4rkpteCfHsk1/mj5dsi+aKOLkJMSQnkiwP3PxHJxf2PR3Jx//5ILu5/BHlQ5Oy0oPqgSE1+yFzATqQ6cDKX/Ic8+1g5dYwZ+b1gqOUxX6x7/N26C2ZmNewtoH8S+ya9j4ecmTj+cyxJcvwvYmK05Uznjww5ny28mWl80tmVmetLxNRUP+Gc/oTQJHUWcKaYBBM4zGuPaGxqzGYqbdc=
*/
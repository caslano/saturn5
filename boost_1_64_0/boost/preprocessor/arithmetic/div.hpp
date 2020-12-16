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
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_DIV_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_DIV_HPP
#
# include <boost/preprocessor/arithmetic/detail/div_base.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_DIV */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_DIV(x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_DIV_BASE(x, y))
# else
#    define BOOST_PP_DIV(x, y) BOOST_PP_DIV_I(x, y)
#    define BOOST_PP_DIV_I(x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_DIV_BASE(x, y))
# endif
#
# /* BOOST_PP_DIV_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_DIV_D(d, x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_DIV_BASE_D(d, x, y))
# else
#    define BOOST_PP_DIV_D(d, x, y) BOOST_PP_DIV_D_I(d, x, y)
#    define BOOST_PP_DIV_D_I(d, x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_DIV_BASE_D(d, x, y))
# endif
#
# endif

/* div.hpp
9zLkHg0J9d4Udd8bhP+90XqP4F3e7xNGfw+LwYHe/hF5gwK2a+UUQN0kPYTpQM9mlCPTRGan2d7PUsk0C2an2Xr6xqHezcqG7I8UIizlEAfPyixIHyVN/eLywsC4mjCd2lUDuWGDvw7LUYe1tWS5upO+SqYkyQFGjmNMjkmS41YhfO8deF9fpww1upkGs2Dksx5n5UwQ3d2gq3WlIWL6LbMHDSJD/fJM6gP1z1xLsW9xj2EpXqrAaVzJWn0K5Zuyc8ChmUSeyi5USVuM+PvHWZS2VCUt6PnSlilthdKO0Tg0FXN9VbbvrQh4xIXDq+etERzAG4X0h/t9gNOANym4yaDGrwgKn2HjV1Ttt5+yxpXOtp6RrQOb9YS9KmbDhrnO4PQOdiOyHCG6A6UhGYKlaNXEgl6d+9fwjSnDjfde8x6w7cM9Q/0DI72bzJk8BjFr1JebuQlfeyWLTsX7Tss5Skbq/AR89ubeM/v+OzXnf0Vsfj6966J0f1Yia3wGr1Q0Uubsy6v4HAP2pK930+kv2t7dJ48t6brNgtaUZTrpzj90TvZe8w4D01Bb1D0MOutssBn/XmPNW14b889vziWdf11sznsu3arF+wc2m5a04Kw93+CVi9/emPlGi583ET/nxVx+zid+LmDz4LPrzTX3oK+oc6Qx//mysvXNrq4oW+cnvW9LdblxkBU3sNc7Z3ah7NsGji4hHjXxOlEWr7M7puIbxtSGBYtfWgKYjl3aX4jwW5muLRXTa9zvBpd3qIp5r3W+1ar6Qz90XYvDALh+vD1Wb++zZ3PvID7hu5OT4TBPnu/QdGrslVwEPOOJ+fNL48l1nZ0S6Pfnp/qHFZD38R1dHR2k6gS/2E2bKal75XYa2her8tKpjOEV7cT3KeSwPZR28IWjZLo3hcgxeRtaie+FDOqSPPtQSk9kZHBrOoWJA9/DwRkKi5888HxfBfwyOrAx1W3XwbBd7wxouw6rsR9xCdkt7eN/l89undiDy0O6++Ry1/RjCwbac/jW/GZO0aiBI/14D+lHu9/eFhAnsjNDe77vVXxLE6zaQu25rtVnkKvY3tl217O5G3k51I83F+TJyEFVJmib9ojofssToH203f9AlbLj2xA5CAcMK59B69hwI//h7RtHhnpME1hg3kc/aNnMD1k2/MNkMy+ra8PVx9rxsT79jUhdcBU4tdnlXrn4zWIbLH4+Rvx8lGz4x4mfT9S1LZhC4w5T3FNa8VzmFozmqJ9kZX+K+VU+bc3prorhsfwqnyFero7VOTtG9pVHePggJI9rrHp/zmqHa6msz1O6k2q3g4NZIaoI81LEtx9M/WvgSA7XMzncwORwoyWHm2J4LDl8gXi7OVYvxmr4tP6ekXivGUHNu9GJWywZfMmSwZepnK8w3bmG8f1VxvfXLL6/HsNj8X0b0fsGpV3mmx+eXcgzux5Rc0PxiPZlfsvXb+vXrbPGfRJqPqyz0Cvvm9+uwhc/m/wd4IUoyWzmrro79tK+36nyV4x9/y6vJ3juTWEez/lmoLrnmAKODbJNv8/a9C7Wpj+w2vTuGB6rTX9IbXoPm+Ndb+nVjy29+gnluTc25z0MxUqpWPD6FId5/P+M8f/zmD++6j68jzbPjvX7BfHwy5g/1t3FUxE8Hta6l7iRzS9/BRpNdC+xzumd22bfzoio+CoFMHNF6HmJ4rXX03zx13y+GFAO1XXeWqp7r95d6F5b4TfbT7Ta8PfUhr+jceEBkt8f6vmh5zG+/oe6a4GPsyjiX9JrCTSFS9q0aZpCWkotFWoaQiy11qTJpU1Jk5CkpSByXJJLcnDJHfdoKSoW8YGIUBEQUVHxCSoiQgV8ouALVARRfIA=
*/
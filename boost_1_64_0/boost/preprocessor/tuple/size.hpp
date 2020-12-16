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
# ifndef BOOST_PREPROCESSOR_TUPLE_SIZE_HPP
# define BOOST_PREPROCESSOR_TUPLE_SIZE_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/variadic/size.hpp>
#
# if BOOST_PP_VARIADICS
#    if BOOST_PP_VARIADICS_MSVC
#        define BOOST_PP_TUPLE_SIZE(tuple) BOOST_PP_CAT(BOOST_PP_VARIADIC_SIZE tuple,)
#    else
#        define BOOST_PP_TUPLE_SIZE(tuple) BOOST_PP_VARIADIC_SIZE tuple
#    endif
# endif
#
# endif

/* size.hpp
wiG4D8fI9Ff0dPv8b8n8M4uYf47M/6jM/zTWwTMYimcx3CiX8cqT7XkR++A5HIbncaxMf01PN23vZdb5ZxQxngEu1vmXQS98AltgZRyJVXEUVkPb+iwrfjyvyvpck/X5UcbzpoznbT2elMt43pfx/EXG846M508ynvf1eOrp9u253Dr/14uY/wOZ/0OZv7OLdTxd0BhPN+wg5d2xBBrj6It90R2HoweOk+mZerp9PPV98eHdIsZzNPtdBXwZW+B4TNC5td9MHKmP1fb+lvyd/pKkv2HS33DdH7n0lyr9pZn6C1lZfH9Hpb9T0t9p3R+59Hde+ss19Zf3d/p7xdna32Q0+nsDE3Ru7e9NNPqbJttviu3e2rxHSn++xjhJf4Nk+w2W408q1sc02f/TZf8YhW9jBs42xh0/xBdxBY7FtTgO10n5JinfqstN46XvF8yyFbF+7zIOFXEetsT52BEXYB9ciBm42DReOdJfrSL6qy2vtzroiXXRGxugD9bHmjq39tfCdn9fxkD6czHqSX+TZXtOk+05HZ/Dt9H2+pf2EUUsz3dyPL0sx9Pv5Xh6FcPwmqzvddPxdPea4l//78r2mymvv3ny+p8vr/8FGCblcfiBvP6Xyut/oWzfRThGpr+ip9vnH7K2+OPpcpn/Cpn/OjmefiTH048xXMrj8TM5nm6W4+l6OZ5uwLEy/TU93b49dq8tfnssle2xUrbHKtkeDJmtffC64tt/JO0/lfYbpf1npvZL/k77LdJ+h7TfKe13m9r7fVR8+yxpf0DaH5T22dI+wRh3ad9X2nsS8dK+v0VlWox66IeJ+IzkHTAZI3EQdsIB2B0HYh8pvyP95sl8XPjffaIMzzfJfKYp6+vmHdS30cbK+hhlPV7MVNbt/R72wFk4CGfjqzgX5+ECXIWLcQ9+gAekv8P4IR7HZZiLy/EKrsAfcCXexlX4K65GZdHtbetx6+Pi18PJYl0PNyyLVbAyemB99MRQ9MIe6I2D0MdiXQ9fnIelcBWWsVjXoxwekP4OYwU8jhUxFytZrOvxhMW6HpUt1vV40mJdjyBUFtrbtofcQw5+U3+7Hk1le7SU7REv2+MZ2R6tsQ0+i7HIc/0+0RZHYyi+g2H4R4zAP2Fn3C39ZWEXPIjRsl1iZLvE4nfYFa9hnGyXbviz0V62xwZLwT3T9D3a9Ho1NravUWBsK2+VWQV/wYb4K8Ya64w98QEOw4c4Hh/hBnTyUZk/ojOG0JcLRlmseVfJU9AdR2IpHIdl8FMsh5uxPO7ECvgVVsJcrIzfYhW8jlXxBlYz5ovV8ResgR5OvPdgJXTBp7AuJmM9XIkNjHYYjHexIQY5MxbYDptgT2yKmdgcN2JL3IKt8DC2xqvYBj1d2J5YGUMwBNtjGIZhCnbAORiBa7Ez7sQoPIpd8DRG401k/PR2y7QU3N9I36NJb7cGRIZst0by+bU1tsJnMQK/xC4YgkkYikMwDN/EjjgHI3EudsL5GIVLMQZXYFdchfG4BbvjV9gDD0n/Z7Av5uE7eAtn4O84C6tbON5gG1yKw3AFTsPVxnzxI2O++DEux0+N+eNG/AQ34UbcgJ/L9C0yfY9M34tb8CBuxYv4J7yJ2zDfYl0+d8ZxNpbFOVgD52Jd7IuN8Qtsh4yj3g4htnvRsK/JccGVaCLHgYYW+XsZA41yDMKmWBWbyfEktjLrIP3E9qIf/TcU24Vy47FXf26nTD6v78dOeACj8RDqv8ewBx7GfngEk/EYvoancBKeNcYDu7uqzAvYA29hT7SwEAPQHQeiDyZjZRyEVXEwNsUh+CyOxAhMxS74AvbEdOyH4zAZX0JjO/8BX8MJOB2n4ix8E1dhX9w=
*/
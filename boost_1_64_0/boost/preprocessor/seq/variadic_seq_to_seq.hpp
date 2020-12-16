# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2012.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_VARIADIC_SEQ_TO_SEQ_HPP
# define BOOST_PREPROCESSOR_SEQ_VARIADIC_SEQ_TO_SEQ_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_VARIADIC_SEQ_TO_SEQ */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_VARIADIC_SEQ_TO_SEQ(vseq) BOOST_PP_CAT(BOOST_PP_VARIADIC_SEQ_TO_SEQ_A vseq, 0)
#    define BOOST_PP_VARIADIC_SEQ_TO_SEQ_A(...) ((__VA_ARGS__)) BOOST_PP_VARIADIC_SEQ_TO_SEQ_B
#    define BOOST_PP_VARIADIC_SEQ_TO_SEQ_B(...) ((__VA_ARGS__)) BOOST_PP_VARIADIC_SEQ_TO_SEQ_A
#    define BOOST_PP_VARIADIC_SEQ_TO_SEQ_A0
#    define BOOST_PP_VARIADIC_SEQ_TO_SEQ_B0
# endif
#
# endif

/* variadic_seq_to_seq.hpp
OxoGKPstFrHfWgYd2X9qHbX7Eczjr0A5llL8T7NUHW3eUn3yFtlijerTjUj/eUrjwawM1RetOKOUgmJgIr0w8upH/vDofIbalBsE2fok0sqIaA+OdmeoXaTRhDTOpjRO0aXhd4UCjs6gR9aZDJ15pHOI2k1iujz+XSC5oK6N+auncp0J8fFsRLyyfv+c6now84ly+klndWosuyn+/vg0ti8+kw1KyGT2hBzWmeBilsQ8NiExjbnAV4DvBb+WWMgykl5hXyRls5P7fsZGJsexyWB3cg67LdnMViffyib3SzY328zMbWtgr9keI7tXo+xV5MeRAxK0PqnOR4dobDhPPTv9mu5NJjP7Rm5HfJ6geYwlxbN+iUN6zB0J5p+Zp5nuiylg2+NbmS9pPOU7G/k2Ur5DqU9so3yDs/RniZe38vBcuS2qaWYjzZVJDyR5TDydJPjdQ+n0G5DRvb1JWId4lX69DHorSG+nrs0FnKEQ/+u6baSTD50HSed5nQ7e3ZAbJumMhM6TpPNklv4cc4io37nkn08SkzBSjMM83sjaEp9CY9iWiD4l6ruC5pOVcVkxteyDWJ/aH1dTO/Biz5sojwPq2JyZlMg+SkxMsshpqL4w9ZP9+3biycJH2yiNDfGJWPteiFlpU1wFa4k3szng+fGYM/j6Br6X46eK+HeZV8bma+shZZ8iyrwd+mupbW/tNibKK0pZZz78Mpv8wgZE+lcZE+7pNiZ4fLJb5XHLi7BHKf5zWR+mfMg0PWXk1frQia3U701D2SXUBnYi7nMU99GsbG29VuaQl7WymaIs82Cnj8qSoPZlWka7oSl0tiG9baSzOlNLL9TZwjszDQwOv1fMN41I7wDpLshUzm6Yuo+UdW5BenVk37ABGVHTk/XqkNZZlFZexDjjcSt1sRA6TaSTo9PhR8MOvgQlndeRn4t00nU6LU431HChtoHbSeeNzEVJSezepPdiv0qroP0bny7i5D7kb+VvoZHvy+F7ma6bQeMwyVKFzE7zfTLJMoTsV02azCbW7ot0cTOEbKKIm4E1ekmniX0E26aTbHDmKX0GCnkZ28X9SPJhmXl9oI9ypMAfb1M5bs68JWYy297HIp6BiL4r2g2vlkSqg44BLH5WP6XPJVI/WMUcrL/67ODn7dSH2ZBu4w5DXylhy6E7E+vL9ViH34B1eKq6ti8vCyh7CGWsl3i8OqoTK+wcT/n/bIBaJ/z9uU5vp9JO3LwspHOzqDc5XblmsS8Ue9snyJ6xlrHsbozESWyMKY41mLaaqB/CR23kD1tWdsScpjZdkV8z8jtMuhdnqntk7ayM6ieJxnZJvld987Hcl5BX/7MpfIC2x5nK3aD6YIebh5+kzuHZ5JNBFD8L+edR/LP0c4CESUAdK4fR+LfR5ECcnUyS5eq4uDNpEJtmeshkp3XJQdjTQull6MagVmUAUW1aSP47Qb5X91hWsqkINl1GaXyVFbF+8QSE35ZA52bSeVvoiPVVSJ7sUxXfnUPzBFvGhsl2q+upu/qejzLNMst2L+R9kdJ7Q1fvfCst+yJb2P0Y+TLefBLmiPXsTiaZVrBWUYY6B42dcf1xUjge3I6TjxXMxYaY8pjDlMZ+Dl4DfgG821TIis2vsFRLNqu0fMamWONYG/hyaw57Ci8IPme9lbXFJJvnxprZ5bGT2O5Yea3AUO5XyM51Ojt9kuR2BJ0+N+msRFmyqU2dp1uX+eAcR7dx+AXolZNecfe1rLxkojHqPugsJp3dmYuwbrnZtpQNTc+iuWEIV6fnarxzyPNLAPZ1qw+qdq3eP5wpxhl+r9ZFrnkkRrtJTO4/Q5HGWirjVn0Z/ciJLjN4GaFzP9n1cuY=
*/
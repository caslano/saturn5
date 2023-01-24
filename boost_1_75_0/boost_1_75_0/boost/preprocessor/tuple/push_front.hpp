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
# ifndef BOOST_PREPROCESSOR_TUPLE_PUSH_FRONT_HPP
# define BOOST_PREPROCESSOR_TUPLE_PUSH_FRONT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/push_front.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
#
# /* BOOST_PP_TUPLE_PUSH_FRONT */
#
# define BOOST_PP_TUPLE_PUSH_FRONT(tuple, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_PUSH_FRONT(BOOST_PP_TUPLE_TO_ARRAY(tuple), elem)) \
/**/
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_PUSH_FRONT_HPP

/* push_front.hpp
EqmlsfzmD05dPYJeINqMdE24lavpF7Po6jAppv9WyG7+kf+N1xGzIJTnSWw0Ococd19IP7IZo50BYdesg0pWNwcv8a5z8ecfB/kEqkh1r77dEj+EGNlrFIyv5VZ5o0IN1N3GDjFnRKA8T7rdwNvevQD+qWvyWh4XJCDFBfwtBirt+WtUV8F5ge3W+hR7Qdgb2/jNu8ySJoBYVVkznv5qRha6TzROL1NYQAPjvA6/mutSfap/FTv2smrCUfyTOTgI6TLydLIPeS9k6S7xydk3IJD3Vzn7UsHJK/0GgZ/+eB8WZdCv9d2Q6VdmYAv3y+OXyTkD2Gs/FKoRHLRleDTh/fAM4Y97w3jeO50U/5gEeOg4CAEAZt9riAIRZIHi6hdZ6ZFv+J+Asx+fubf9Ps/IPtPw06M9w4WCWT3CQ/wss49HjV1eAVnp24ZVepNzNu8ThXPzW1zljocha6dYyTDYX1n+acSJ3OP/Efr/TZWgZG9p7exh/c8O7p6aY+mA+7cop2B0zg8fxQdpRv9M2Fn2xMFgUfgtFPoWLV6c4k5xH2hxL+7u7s4wSHF3CkUGp7g7g7u7u9vgPszuZpPdL5tscm7ub3jOvTlH8avWQACOafWdqTjCT6M0ahoSqrOwCrXU9ud3v5PFN0LXG+kEkn9PeTyIS+1/WnGLahTNzEnFnknmobZe0JadgZzxKBwX6Sc6fG9ddRPLh12M+dYy
*/
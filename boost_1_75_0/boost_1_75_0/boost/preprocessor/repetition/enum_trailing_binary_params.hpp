# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_TRAILING_BINARY_PARAMS_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_TRAILING_BINARY_PARAMS_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_ENUM_TRAILING_BINARY_PARAMS */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(count, p1, p2) BOOST_PP_REPEAT(count, BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M, (p1, p2))
# else
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(count, p1, p2) BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_I(count, p1, p2)
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_I(count, p1, p2) BOOST_PP_REPEAT(count, BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M, (p1, p2))
# endif
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M(z, n, pp) BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M_IM(z, n, BOOST_PP_TUPLE_REM_2 pp)
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M_IM(z, n, im) BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M_I(z, n, im)
# else
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M(z, n, pp) BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M_I(z, n, BOOST_PP_TUPLE_ELEM(2, 0, pp), BOOST_PP_TUPLE_ELEM(2, 1, pp))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M_I(z, n, p1, p2) BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M_II(z, n, p1, p2)
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M_II(z, n, p1, p2) , p1 ## n p2 ## n
# else
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M_I(z, n, p1, p2) , BOOST_PP_CAT(p1, n) BOOST_PP_CAT(p2, n)
# endif
#
# /* BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(z, count, p1, p2) BOOST_PP_REPEAT_ ## z(count, BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M, (p1, p2))
# else
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(z, count, p1, p2) BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z_I(z, count, p1, p2)
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z_I(z, count, p1, p2) BOOST_PP_REPEAT_ ## z(count, BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M, (p1, p2))
# endif
#
# endif

/* enum_trailing_binary_params.hpp
heRHZO+voBd5V9jdUW3P7CB8AvXamdoZl0ioPQL35fUL6gs9KB0RiUhDfEd8QxCdjG9anvlGI7JhZrL3ao9cj+Iv70oJru452N4F9Y7TKj9z+uymDlnmUk2pWQ98LaZqFe0BD8Sec3VcvhQjWS4zjQ/8Hb6O0yym33/1hGxQk3MZp4poTIGvKpNdeidhzcxJbCfJsaM2++bWlZqlTuaL9ZgpENvPhS4fMQJGaJvwGrpHCR3UmYenFgpkdf2T8q4KZmuSLCI6Sow08CFGP+7An460TSaXMys9s4MUNQjdZLV4BJINK2Kgy7cUMsVLtrBWZJM8W2hrqOmbtf2+aGXfVutn6vQT63okXZb32bhWwF77NHDblIC/aSW/Y+vPeTRsykHNgN42lAcQI5Im4UrQew7jnBoRdC8ojWBCgPstK7tQHsQYkV4JV/tIuqkwccr7wC2He+97OEaspdgevDmY9B2ynvpK0KuHUvyt6JJ+GcZC++PdrAVMWModL+nK+InrBVn5DQkWlr6ikB9NhZs6kLg+wdsv+G3rr7jUb5ES0H6fTwzboUM4qRPESGRMrVIP2l4uy2gg/901cqw6Au2cfZuuqYJpCen2p4DspF7hC5P7zO07nOfzUSVAihnSOQOOxPyJnYzMg0T8REr8jcNPemhoBf7vZzHTf+Vwgf9mV+EFGi5+kbiTjZPYaVPdaVLIiLdt9foTsyr7wI9s
*/
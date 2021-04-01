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
D4lx7uaE2RWznpqzE3r94TQ2Gms0VYtWOtMFmun5EwXyTqZ/kmr/Q0nEurDRxYrI5zubqPz2iNM2x7XqFGuDS8oGAGgU0EiYxzhGxMmaLrJQbciQM9lKwAxGf7Xd2wqTCMKIGkHSIjAvVXNG3wEBoW+xga8qI6doffKqUd5+JxcsBeSy4YB9D8hVonCa5IBfMRl19gKh2VQTbSCoqYkU3b1/wdArr5zc4P15SQhk9p9gscNfFHifI9P4eL9HBhU1b04+2QY1DKU8BZAU8vij9u0jm+HXkL2Bpn/oRCFzOe9C3lDGMnjazv8HAJcfDcPv/Bmi3dicmkaOVBhfCgdwbdodn/lUen8IJ5XbURMk4zLpbKrjHxMDe2mWl+fLwsWzvSkfweN162oGOthx56jPPRmWnC62JgixNDvxa2fUbF0YQu84wAwQU6aQVdaQRZ6/DBLyX5uZdnIuvHX5s+Vk7BwKTV67kbI/GGrpE1DFViWRg/ICWfgqmdsjFv69HbgfRPC0zHGCd6PC9FX62Z87ZvZFQnl/zj/Q6vl5RNyQNNbP7skQQVgp1Hh3VQ==
*/
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
sA2tAV1MZOv10rdLFSpATV6jFlH8NJpgj3jkv/gBmPLTbJIxpSaFOpnB3UJUUB9DN4Cab/Fvj5ysA/flaf1/2/9QJ1fZHj3Uwe9ssvNe4R9CwdL2/jHXnpUR2cXhgAqGWh9U73dwY7hMxIEBTwiHMFtRNKmf3ykA8UfOiOXpVhZ2ZuwJR/vUtO7d5Zzvf7m6un+rLQj3EL6j0VNiE+7zMOt9n1lt0TN89/YiDbh8jnXWf3t3PdMDZF/nZsJo2U0LMYtNNvFp3fJgrEKbcIV9em+2sm8WHTM9lR/gyBpaAsCAAv9zXfqFSRlEfs4AqV9n+FtMbGziQE75adlwGHVYvPBSkS8yclpxDc+Mw6HV3Z6dhSzyIypDyIo3OPLkA/jWbkUbZmQ2m+3REx4O4B4q40tw/Ag9nZsz0MFJTNfHza5FANE1HPZ3zzX2QhZuE/U2Gs5G11h0LpNzCe7TYq1wmv2fzU7YtoZ5L6eUq3U/b60ljwKo8UIkobpt0pfb53ksa4og5R5vOXm8vyMaoEsafFSnYCFgpymRYGia3oUjY+a3HhIPg0Ctwnw2tA==
*/
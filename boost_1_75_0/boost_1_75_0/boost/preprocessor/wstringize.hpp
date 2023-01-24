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
# ifndef BOOST_PREPROCESSOR_WSTRINGIZE_HPP
# define BOOST_PREPROCESSOR_WSTRINGIZE_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_WSTRINGIZE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_WSTRINGIZE(text) BOOST_PP_WSTRINGIZE_I(text)
# else
#    define BOOST_PP_WSTRINGIZE(text) BOOST_PP_WSTRINGIZE_OO((text))
#    define BOOST_PP_WSTRINGIZE_OO(par) BOOST_PP_WSTRINGIZE_I ## par
# endif
#
#if BOOST_PP_VARIADICS
# define BOOST_PP_WSTRINGIZE_I(...) BOOST_PP_WSTRINGIZE_II(#__VA_ARGS__)
#else
# define BOOST_PP_WSTRINGIZE_I(text) BOOST_PP_WSTRINGIZE_II(#text)
#endif
# define BOOST_PP_WSTRINGIZE_II(str) L ## str
#
# endif

/* wstringize.hpp
t/Tx404dRNu1EB76LoV0n0WQvGEmLDt/Bya5LofuYTehff9B8HVwisHzkv6zSnqKUoh3KMQ8RHuc2Vq52dBz5lLQ4vNH6+EzQWxn4/aP370D7ajxcKjjd3C63++gwetT/Dzg0po5EDrnT/Aa+i0+c6YBydkYH8f+gJODhkJOSqow95bq7B2KuchiLSIfFHf1+N4tpvAhI5nfRykrZA2LeZx7K57psqcp1/jnK00unJbvhBM4n074rRPo44qgn/TPU/zHy8f2w/yRv8GU/j8Y4It1PLp1vYI+YXUKeuTK8f2QGhMJk//4HvxWL6qwF3/WnfJ9mEgO51GWD0+fFc6UQezJAzB7aE/Yu3aJyb34Cf/MiFFw6NuucGqIDaQE+kF25h14ci8FbsWcAeXpMLh6XE4fypvr4xWY8/sWR3KmYArOXvcQnoOL+VOEx8CZP8TjfZzZ0hDuQMU4V38Z+NsNNIhzNcjgW5jBBnGuhhh8GTNU4O+/GOeqd4Gz+9z+yz17ezpo3ek7csy7L/fMd6d8c/JDsrdnAayctWBPG5AyRHJLK5hrZWXv4OGBx2ZWVs5aezo2s6cvx/GnMxXjeQcP3iuK0dXFuTKreDtpIkiwTRBOIRxvxHHvt8Df3TiORnHd+7+693917//q3v/V6P0fH1ZK2NqT4lwtlcmsh2slWmsxzlWgVCKVuUmsJT7CfktSiVwuW4p5HyHOlYQ+
*/
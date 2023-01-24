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
# ifndef BOOST_PREPROCESSOR_COMPARISON_GREATER_HPP
# define BOOST_PREPROCESSOR_COMPARISON_GREATER_HPP
#
# include <boost/preprocessor/comparison/less.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_GREATER */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_GREATER(x, y) BOOST_PP_LESS(y, x)
# else
#    define BOOST_PP_GREATER(x, y) BOOST_PP_GREATER_I(x, y)
#    define BOOST_PP_GREATER_I(x, y) BOOST_PP_LESS(y, x)
# endif
#
# /* BOOST_PP_GREATER_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_GREATER_D(d, x, y) BOOST_PP_LESS_D(d, y, x)
# else
#    define BOOST_PP_GREATER_D(d, x, y) BOOST_PP_GREATER_D_I(d, x, y)
#    define BOOST_PP_GREATER_D_I(d, x, y) BOOST_PP_LESS_D(d, y, x)
# endif
#
# endif

/* greater.hpp
aMbfRH21IDkfNor959cB552g0WQiHk3ZyIUObA+vQFDem3Wg4HC80/Pb+hgaqeZry5HmOcuRrEQQaBCk9I/acqaJZOcTlvk5Yl0PB/58jgdYczGeEo3A3mN6WVwU/Y8TpaO/OTPAvvts4RJoxinKRYpTJ760lBTnbsCfgDzg2Fx2FDp4d3ZMtMHIz59UEyydJr5Ok+T1bxpFsoegHNbexfcplxiu4laOIDsZ0B67kK1pM990g7jBsUFbd+XChZV/N6Hd5C8qZMohhPcfES8d0Ml0SAdB5ySZ8/4j32BOhBWOUM49zJMWK8YLV7GaQ/N1812vuFiN7ZNrKNVj9Ga4p9Kl8cyNJ9j/43oiKawzR7uri3rUpM1pG2C2/AoOlzxSHJqSDyIVw/ZzGwysEPl4ciJHG9c1Zdx9H+yFEhA/G1nhWRLXMiH8xBCx4VsydF7k7yox+KS3M8ezMdUlydNiosf8rVbzbCpF3MHL4bgO+qT1SRTbr+Ftk5G0LOq9cvWNCX7nFcOdzTv16RFxN8rCwGUJoVOaURoiT9n6JuiVvYk39tJ3kBINmeuzMriTOOgkx858m8wynTSbmxVuZ2PACWiqUdzJdfGMr5rT9Xp9+lb/gm42Ds2XIKhXTmab3QRqNmgYtXj5vZKKMl672VJsO6JyNqxGg4Y6X2WCUwJjk+9FFN9CjCb/E69KEq8Mh8bXZ8MPMsunDO1faAp8
*/
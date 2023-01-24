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
# ifndef BOOST_PREPROCESSOR_PUNCTUATION_COMMA_IF_HPP
# define BOOST_PREPROCESSOR_PUNCTUATION_COMMA_IF_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/punctuation/comma.hpp>
#
# /* BOOST_PP_COMMA_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_COMMA_IF(cond) BOOST_PP_IF(cond, BOOST_PP_COMMA, BOOST_PP_EMPTY)()
# else
#    define BOOST_PP_COMMA_IF(cond) BOOST_PP_COMMA_IF_I(cond)
#    define BOOST_PP_COMMA_IF_I(cond) BOOST_PP_IF(cond, BOOST_PP_COMMA, BOOST_PP_EMPTY)()
# endif
#
# endif

/* comma_if.hpp
+x9NnNyC/9XEieWWOuLeew09ZpcwvuRNkBmOMaebVkAaJZaqAkb+RCOjw/NAlWObTWietNVaQf8gvFw11Cwff4/np3R85zUVroFBcCGUTgCe3erkaFaZ4z8f9BZ0tGMqdjkpjpKPjzEbWXOi6tKNkrFeyKE6yBkX9XyFWZ2PA8dzM5+mzqsgeU/7ow0MTjPFzVHYN2qNkVc8xz+kkn7/Q6dRZM6dWanyKvaiUgJB4Btfc7elur7YAxgisKEQI8YEMfSpb7Ft2csIf0or8n/9vuoPEsuzQYch0nAnpfh5oVlbX2n+ZaEr4X3EN/Wy29+orgZPtnccK6bU1+g2vxmr4yo6/ahO5f71BxqCY78vVrEgQhRSIaM0VSpQ46KO3mEgj4cyUwCZxKbR3l10enatc7K1n88hjalY/eLALrgu5egKglqdTwhPL1W8kx35Adh/BiyAiR++6cLT0z+r1O3mKasKL070oVnwbIGxrX9nD4GPCgEL4w8872WGgLadz9662ok7cJmR41b31ggHs/jbVosa8VatffqfSBcHnycmgsBxH4G1pQ+cLZDd9kOR0/E4YTUY9ikkqx8EgqwTPehMOghuvAS8jcKTOBRN2IMlrcJhs4Zv/qklReqmak/dW6l/P0UkQeDMMNrijOxMdCGbT9ae9bDKWIm0idJN1o6mjaOPpY9ejag7/8PdaxF5CVkAgSIwrk8vsA0pO5CC
*/
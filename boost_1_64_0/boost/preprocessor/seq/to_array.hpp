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
# ifndef BOOST_PREPROCESSOR_SEQ_TO_ARRAY_HPP
# define BOOST_PREPROCESSOR_SEQ_TO_ARRAY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/enum.hpp>
# include <boost/preprocessor/seq/size.hpp>
#
# /* BOOST_PP_SEQ_TO_ARRAY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_TO_ARRAY(seq) (BOOST_PP_SEQ_SIZE(seq), (BOOST_PP_SEQ_ENUM(seq)))
# else
#    define BOOST_PP_SEQ_TO_ARRAY(seq) BOOST_PP_SEQ_TO_ARRAY_I(seq)
#    define BOOST_PP_SEQ_TO_ARRAY_I(seq) (BOOST_PP_SEQ_SIZE(seq), (BOOST_PP_SEQ_ENUM(seq)))
# endif
#
# endif

/* to_array.hpp
IXRSWZ9UHhaPe46JwEvh75R0OX1Rb3v4fQzudX7b0w+eT4IsegH37umbbqE05FQYv6c0rEoqQpYPjTjmllz+oBMRya+xLNXcF7oKJf2b/DpRbVvSRL/fKzl9TLR/ye4LS21SkIk+IE3y+p1hpX9YmFTh72zx8nIuRxu0ijbYL1obbJe8ASnYTdRV4HB6w/DLMTpJFL0JPZKLUrRfHF/bPD7LyKnf1xK57doi2m6Kru3ysFTRdvuLOj9dtMEUXRu0we9puI9mIW9HKbq2hvJDgqrVtSHrf6j8e81qGyvzzZkawlDKRBsr95d7naGQJjNDVlvNm16w1emSKEBpc32YFBEgy+OYVC11tEhBWUiyFC4Lt/vdOlmOFr9bIA+boIWJxLSw+aqdSoiWNzMpYWqKWphFOtPrb3F69UFfiDCrCKtwhp06G1mcRKl1SydFs63OGXR2SLjRx8kXxYkIpLAJkr2iqtrv7vR285l5PpuP2vD75nT4O3X+t85nvF4aUc1uqbWbnNfNVJ/H71PSUeRWJlX6OjtE+VQ5r5cKqdXjkxqdbRFxeP00hIOdrrAcoMh5HVX5XU5vhD6vn7qgH40tPKdHPvORPx/xIuLwummUOgJeDKpaHC1M7xRNbpbsXq/Upligyq1SWWiOz9Ue9PsUh2npHbnsDGrbcLVI7xcYEweJMTHzOMfETkTVOpd8r46H4mYCx+/YAy/93mOhmpk2DHyP/Pn4NyBi/OvUzcs8LFuMfyeI8WqsGP+ycK/4gY9/A+V7zQQxh3ZSrC6nt1Nil4qx7yffeez7ccp7FmyXxzdnwBkM8xWqGNtCHl+bV9Lm0NagpLQ95pM6w0GnV7TfGNbiD7ezPV1oRzGiHf00WjsKtwclpxvpqjbqZErj0QkmqNdHXdu1HF+bURPr7rTjy4O3i8ER7SJHNy/ysCGiXZwo6rJnWM+13FCxljsJOJHakZyu3i187XayXta9PUFfa0/cF1a0p1P07elH9oVuHyJ1YdEl2o/X679IcitjNu4vcs7Bnqj7PuTUaO3C2dYWlNowubR4j7HE0mn+KOv9yPQ0VxxvTmK9PyKibQzXtQ0eNlK0jVxRLz3DeraNPNE2TtO1jeG6NRZvF/m472mqtqYfrltnXSDaRoG+bfybfNJ1fHvPoOSSPGhDx7P7VHR7zfn77v9TWWyGCfq83mzcXviOy5IhK+bjv1WTZQjZSTq9QUJWoJMNE7K1Jk1WKGQ5Zk02Xsiu1MWdImTvirglLCaD29o6ttntbu5yhbH5CTXjgADXoTBG7c5Ac0unx+tu7gg3ez2+C7FlC/WIR7HU2BVSV0FRc4vH1zx7VGHz7NKS5vKqvMqmSl53px9HfqGgS82qOSSF+VFFnisQ4PEvVuPzDJxBjxRqpkVhh+T2YIGjJKkmkCefZwSC/gscjoLCktKS0qLRY4qb/S0XBLltUGxRs3YosXAG0xmS3Hk4/Ah4vFJewN3C9nwt8s515eTav5PDuL5mcB6yDUrh5mlSMIRlZLTEOF8E57UfLTAUdrcHAsfQcB1do9zvc9U39tDwOn1tzoCn2eNzeTvd6N8JJrnsvWp2+tw+LLp78Uyw04edvsTTO7ZGs2dUacnRXczVjq0RPaEqWFxWZ1fKFrVueJsKOuuQkieMKoK61ryZ0g6QwHeOzK3q+r7Rmp1hb0drj4J3c0blbHQGn9NL0Wuk8KSm5q6ivOLedbCVafVI7vL6xm46cspuqcvt6aLsfe4A29ujHcBokVbAg/wq6hzl/o4Ov6/3/KY1yBpHz60rFD0Hl9/X6mlT4vYM73IdJSzkopyPpuE9WqAkl4N04IvPRDuIXpu9tQ5RiUrzi+qC3r0=
*/
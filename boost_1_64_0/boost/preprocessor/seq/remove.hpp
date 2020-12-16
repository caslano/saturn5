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
# ifndef BOOST_PREPROCESSOR_SEQ_REMOVE_HPP
# define BOOST_PREPROCESSOR_SEQ_REMOVE_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/rest_n.hpp>
#
# /* BOOST_PP_SEQ_REMOVE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_REMOVE(seq, i) BOOST_PP_SEQ_FIRST_N(i, seq) BOOST_PP_SEQ_REST_N(BOOST_PP_INC(i), seq)
# else
#    define BOOST_PP_SEQ_REMOVE(seq, i) BOOST_PP_SEQ_REMOVE_I(seq, i)
#    define BOOST_PP_SEQ_REMOVE_I(seq, i) BOOST_PP_SEQ_FIRST_N(i, seq) BOOST_PP_SEQ_REST_N(BOOST_PP_INC(i), seq)
# endif
#
# endif

/* remove.hpp
sQM88sx558R2EyN3a+f2RN42wp0MLlmsXwjddO+7hTzLi3lZ1trr5vXBm4uJ3nSdn27RGxoHyUd61ocNQeM8Dd4/Py/CW8vv5S55ABx7CkpxRd7UTPscXPtRhpSlasP33sIWxPeLAdvf+9P8136CoDm829TgZMzbqYZhOj8Oi0mI9CyrkJrkCrlFspiFzJHmJPiGdeYueLcbZiIrlZUe08mh28b6VhegbjXY9Ir1Bgl5jOcPMJ0o+i1a26GYzhl4trv0HfqCrLaJJKgzdPR7pEAP7UTIjPs6P8BTdHK/d0e709zlbhnvN14br7vXF0w6CQy0RHPQDf0SKCXPAv9fjNeAI5sMFU0kMonSYNbpYq0oL6uiWRwtJ8L5X0T+yMEWQ8EQi8AN24C6y9DIh+qzSgKXW0n3RgPg+bdjV59iFmHYy/RB1iB/UFK/LGsYdNfvcLYjX78Tk693CAsVDAuFUpBCpDSJAtI6kAlkEzlILpG7pIAhjdrAU19jhDHGmG+sBpbO6FeJvwBTCc30JkFHWRH+awwS+FXQ2NdmciuTVR746oCUch182E7rDDKB91Z6JGqFkb83pp1pTzqYXqFfaCo7ClPraQ+yR9uz0Dys1JnkfvsKmPyV/QXoygp8lUROXM2p6zR22kCdx8OlLXZWO8ecC84N4C07UmBT3xSauW2hX99h4j/AFW92D6ITvus+Qw8ax0vmZfbyoK/i8DCNvd96HbyuQN/mmJv6P3jLlIlFoNPKywoywijzmGRFWSQrwyqgT46CItbF+4imrCVrg8ajC+sB3PbHyQ5jI9kY4HcKm8Hm4JSj2TK2iq0DmrfivHez/egGjrPT7Py/2Sv+65b2z6935us3mTf4U24JBqX6VswQ88Ql8QHeq4gMZGlZEUhqI7sgO9gE53JDxlGVwF19oT7L1U61T8WFx/KR+rXTKBruz4EKbIC7qhBM0+9zwkI9sEvJSRbShMwEDz3SN6LiRkWjutHQaGN00h5ll3FQ4+Suvh+lgAdbDff5k3kE/HMdLuwFMuz42LGKVkPw+1A4FvxLEdZe3cc9tbLQnGijytBK8C5dwEW/o5N0e7ADLuYyeOgzDdf9nG83tVsii+lgd/mr++cW+5Kd05HATJTzrb5LLkL2+otTEhhpBnQMQQMwxV3pPkSync7L4uXTqCit3+u19jqClSZ50d56b593xfNYSZx0C5ztTKjCTzi9UywuTiPg5fSudkSm/Xu+BnnOIX4S7e8HHver/3X125M14iKmn0TmQec3Rc7Ub0DfyRRwBaVVDbUY2n4K2/tFJYZWe0hnGsd4RJ2wLvT3+RFBS8x9LrK4sNB5jD8eCSejsJ3zSUGjHTg+rzkLU82FNxG9kLkJ+gd6gp6jEfrtbwm7rF3bXm3vtrM5lbE1U3R/FZNVjHTHfc2cz7qX3eHeXPBvIraLHcJvu8juspiXEJ3ggVYgrTrGCZBUW4wXTeDsOuuXvFfh18P+LT+zQW1RF9V1sFNWv59+M5M4aBA0C4bC8d6MwdOcsNBu/JGWlCWVSX3SlMwiC8j5rynUX6dxVcwOYOmtSFW7OoOdEWDWneiFPjgp0AXZrtDvL9ciK0jupcUvuoiGIgLnlpKnx1nVxK60w47c5REy0HmZrV/3jFGT1AFMP7Mv/Fn+AnDmA/8t0D7qX7xiuR88glK/Ct7F6MuqsNDIWPgRJA5JQP69NroWqUvak77Q8xFkLJlH/gA1P0MukhvkBUlqZDFy4YWgga1qYvRE7jYESj4TO3UBydsd9EGfjRwmQy5ZEilNPXOoOdWcg/06Zl4175gPzKfmK/MjWo0ilm+VtMqBhxtb31tTkcsdsI5ZF5FLZKASDqo=
*/
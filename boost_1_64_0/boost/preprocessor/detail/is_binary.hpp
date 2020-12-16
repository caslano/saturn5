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
# ifndef BOOST_PREPROCESSOR_DETAIL_IS_BINARY_HPP
# define BOOST_PREPROCESSOR_DETAIL_IS_BINARY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/detail/check.hpp>
#
# /* BOOST_PP_IS_BINARY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IS_BINARY(x) BOOST_PP_CHECK(x, BOOST_PP_IS_BINARY_CHECK)
# else
#    define BOOST_PP_IS_BINARY(x) BOOST_PP_IS_BINARY_I(x)
#    define BOOST_PP_IS_BINARY_I(x) BOOST_PP_CHECK(x, BOOST_PP_IS_BINARY_CHECK)
# endif
#
# define BOOST_PP_IS_BINARY_CHECK(a, b) 1
# define BOOST_PP_CHECK_RESULT_BOOST_PP_IS_BINARY_CHECK 0, BOOST_PP_NIL
#
# endif

/* is_binary.hpp
DH2dexbF30wCzSzWWIDjotR77bwPbZVSFyHVk5ZknWrQt+Lg5omzZB3WlasVwJU7RFHmwforejpBluywFm54uRzD2xHl3H6MztVTiTeKYeJ4unCKV1pqhGG2skdaeXu69PCG9vxIBh0N+L2+QhEPJY+D8min+GfNSyZJ7YrYuBdplq6IWDpNwaw73S7sfpAcvoh4tGgFK0BBUF5U3+nMd73R7AB/ZfR0eZHEaQ3tvaLVAX3Ihcd0F5k5xRKfoqPzF9DV22Tos9SFnGd1tGr10S1pvDfMTLJ4j4aO3SoDagKEONrW6hKoSXLaXqrmJ8D/sxtbnLz6hpaJSlRHaLDOl9/lnszvi+xpPDwGvshl/vUW6+AARBmRpGMJdRkVYRY1KL/vN7QneUPLoMsiHWMTqcN/l3DHElPfQp9xBP18BPzOd1MuxxyC5KGw7RVU1wAMOw2/autkaXn6AovRwHXpIiV6H3TSCaDvids5AJWuAqOcPu+Y27xFI9XCN9PM+/dCYnSRq+9SP784GQ6H7VtXxtFLjMLY+ZLj8yrmeSdPxqVwZH5eB3ZTZlxHTV6Eiver29/UxUcd1eZX0Uu86UZ91CSDYfyF1FOcVi6l9RIQ369zeGgiLwJ7CxQL5w6pdCbyEFGZk7RMzPz6RIuoqQNE5LMPaZYp1zvc0GVsQVUAJk7NE4+DixCjHR1Sv5FpUXr5F9Q+sLV5gyMVUQtHgviDgeuc7dLC3LZrJflcNZSgkEiQAic8ixJeCTmQrQ3v5GwC+OK/HMGeQo/di3wRz9R60SNGM0WTY/eoIsqOtSl9dY45Zp/ChfzWGaVO/pCasd0cKqMBCetLcPwoaydTfdgqM86lht/u+8Pxdqn9nl41R13zhvT9CKkSaCLnQuFBXQ+mSk2brV58tlN6cQF6cR3AXOlshFeDkFHXkect6f3Yx7kJohHqTSavyIz/NQOFVO6d6HebaQ7i7TlcAitnEepjBxG558+MD80HRuk7gArVHdukr+VQL+uGJGSoGNv0UHmggzVUDtPsa9ZUpBt48tXbLEvi94Fk7VAVqodSJgUwG+/dslUAxQdGojeXqJs2MfuhsbOPUqQZzcUsCKyIO8EEcFmzT48/ltqnz3/b6tMG4lKM+C9AQQzQJZJtdiPteCE6FImRboEacwSrYRyXZvlSFD/f5oijw34z5Ry+/mwxMf12dEk6tqLvWQqGVKZMmUyyk0jeA4kev71qknSi+C2b4jhR/F2uSfCwtV+llGM5E3lpZXsGrV3yO9ny78Y0aOF4LJwT7UURi5MB5Hy5mW7klvg3TnrNgeBTjJaUQ+ohJvGA5Mr420zSPzqWSEyCbibBZK9Rbmf5+gbRzj1MAvU4G75Q4LZgrK7fKP2+nlM/N3p2agGogSWfV7aatuwb4iOYND+78Rhq0C4MqpREOD6Krv4q9DRcmgFMLdsZG/ggUB4f8I+EQurWrSx/BNTHblP+KA4YdXaMr9efJH+kzFhPb5DSr+LB8z3o5GZiF5vHMxOaw6idmQ4mbHKcXCGz15sG6ocdcl7uIt6Q2phn30xZTKPnGs0rPlbFkmfiV3TVf+MufdlFi7z6hBD9qYe2cL+j15/vPPn1z5Qcqd7ohRz6heRABYQadUeQd75YwOLZ92zEMEMR5UXIvJFoHqYUXlf+uI49VeowPMZwl550eOhmUPRyC8STA+qUCEeYUNT9OjbG1beGqeMYznqMqHHIhVOaI7mMV/fCAyYJuYY73x6Mu9tcqo6gt7mNK+1UmzhVT+wjMKy9SG8WW/ugQGH1Q8p7fAU/8S712Xr9Qt02s6dIfSiMp07thEcfHFZHyBh0Ge+dq2oplF8F1ulELocHvI4=
*/
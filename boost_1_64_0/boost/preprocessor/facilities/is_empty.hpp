# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2003.
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_HPP
# define BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/facilities/is_empty_variadic.hpp>
#
# else
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC() && ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/facilities/identity.hpp>
# else
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/detail/split.hpp>
# endif
#
# /* BOOST_PP_IS_EMPTY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC() && ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_IS_EMPTY(x) BOOST_PP_IS_EMPTY_I(x BOOST_PP_IS_EMPTY_HELPER)
#    define BOOST_PP_IS_EMPTY_I(contents) BOOST_PP_TUPLE_ELEM(2, 1, (BOOST_PP_IS_EMPTY_DEF_ ## contents()))
#    define BOOST_PP_IS_EMPTY_DEF_BOOST_PP_IS_EMPTY_HELPER 1, BOOST_PP_IDENTITY(1)
#    define BOOST_PP_IS_EMPTY_HELPER() , 0
# else
#    if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#        define BOOST_PP_IS_EMPTY(x) BOOST_PP_IS_EMPTY_I(BOOST_PP_IS_EMPTY_HELPER x ())
#        define BOOST_PP_IS_EMPTY_I(test) BOOST_PP_IS_EMPTY_II(BOOST_PP_SPLIT(0, BOOST_PP_CAT(BOOST_PP_IS_EMPTY_DEF_, test)))
#        define BOOST_PP_IS_EMPTY_II(id) id
#    else
#        define BOOST_PP_IS_EMPTY(x) BOOST_PP_IS_EMPTY_I((BOOST_PP_IS_EMPTY_HELPER x ()))
#        define BOOST_PP_IS_EMPTY_I(par) BOOST_PP_IS_EMPTY_II ## par
#        define BOOST_PP_IS_EMPTY_II(test) BOOST_PP_SPLIT(0, BOOST_PP_CAT(BOOST_PP_IS_EMPTY_DEF_, test))
#    endif
#    define BOOST_PP_IS_EMPTY_HELPER() 1
#    define BOOST_PP_IS_EMPTY_DEF_1 1, BOOST_PP_NIL
#    define BOOST_PP_IS_EMPTY_DEF_BOOST_PP_IS_EMPTY_HELPER 0, BOOST_PP_NIL
# endif
#
# endif /* BOOST_PP_VARIADICS */
#
# endif /* BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_HPP */

/* is_empty.hpp
BLhaAC0EaCXATABkIknRXFR/8qgQj0MUcgEBzrFCCruZGiAAD9VmIgGyBeAmQKmUz2G2aaG4T5jlzYM7IRMkoPYX0W9diegV+sDFXj6RmmCvkdrrdXipHxRZ0zz5HAESRVoLxq/ItU68j5L3AwS4XrwDyXvgMhxTauUArEKc9FtHTmmlwfZLmV/JEiE6Fit6fApPv3k05GbDA4wmjwHEM4oL5XfR7OOlUE2YKm8kHNo/WefSMYRyuRm5iIKJpzkgYXe5kksFcumhel0mklZEupCH8WTbC4ML4IN0Wg/5g1x/SpFlYEqmWNSep+AzLp38pTMjze3TPpumWjjEes7073bCt1DCU6yEf1drJXyVJDyP1pbiIVp563RyDSDXBize1P9O7rO3RM5nMP1OHU78ssLTNS3tnUIaUWCSfSXovRz0FQ5aOFy69xhg6lmAZI3h4G8T7BHA9B6QfIUA3xXAfgLsJECrAA4S4DGRElGcw3LOYSNy0BXaTMMzQXEa4BXviEwMgdkMfan9V1D5NvEm2FIwswbnH69gA+QZdJpraeoykvcKqJpRVsrjaRmWnSM1emIHFtZYCT2+8muXVuelskZx+wyzohQ6ta4uVTJcbpoWgkePIn0dkeKElIweIR4fIZR+QAyoMvh0YoMqt/DUjpGG91Lvhldhh63Mu+F5hynEudJ847/lz6cs1SXlROzZLoO9OewSthNQ3TpdeNGoFXYanoMBj7hJO8pliGrzuBIemHlsWnep+VxLqfr7JFmdkSytJMbCKbb+C/bypKY0GKrWgo5gaB5VFKyA+XbwPhKcPBoyiV/H/RJhmSWEtx0hUUnqdPXryWxvI/sw2FngZVO9y9odD9QxcJnaC4vZNM0IaRxaP1m2r5f89tOU18HH3MAWiP0usr/47ql0gzpTcr6XIF7YOeG/IXpIbWNEviao1sMiOlHFskpd69dif/P9kq1VjmAG4BABJhHg+q8x4B2WDiTA3132Jno/QSsJ+q4NlaXobG6pGuMftodUqic8qMPRjN1xCUIA1eAiHnmFRE+8Cyhvg1Fu98vqGjlwL4IHbbp0IguoKqwkJpvgMhol8+BNCo3jMmlN3ggQYvaT84ixxlyGA95apeYqk66+kPXh3GVn6KkRWkRPpGgc+qssq1YLDUVEwp5oSMjsR4GGGU8jfkRCYip3iPzbA6lT5nL3m5MkWciB8E8CNqhf8hVCAdGmKdA9CAQawVzjqF2amy/i0gBcG7Zfcle3HGGGgGK9SsxHTMzRJaGIU4Wm8b0cHhIINtDtjboojy++k7tF/bO/UtRXxYpAXKsn/aOgwNbE+uK3JEbjvIwm63Ga0IV1tv7PC6VVjoqwbglph0mTdvhvYjZKY7Todn9S2n2TtPuqHiT6qaTpWx8VVQtvvsvNj/XzUR1pBO1NvPtLgy6ry2zQ3dKgDe9ZDboM5TAa67o16OIOaVBhM6VwtQinhVrxkXemA9oWUuoSOYFqkX9qEGqApqd51jmi/UD88KKWfAO7VGqKrijFMrUyrB74Q8Yy9QZJ3oWNK2iFeruODlUXc5P5kOgc3AlcxqMUmWhNNzPFuhjWOlkQDYzE0QHowZezWytDsP4h4YAa8Q4B3QS4AQAJHp2PmgB54+kNqxJrPaxHucKM/oRplcnY4uuBUHzvfU6jhk6w8+TAvhXeQegn6Clb451w6udhqhD5sKS3Wz6dklEFLXfYrybmOOQqGASHQpPw/1vsK6lgXJBBymCDU9b3gPrKoYyG+xHC4S7IGE8L/Ahqvh8QtnMozHeR7omywCPBgVmciw9JHuUkpR/AD5WZXBjJBcNGNSU0dwr1w85q7gdw9F1s0nTAAKxaxIU=
*/
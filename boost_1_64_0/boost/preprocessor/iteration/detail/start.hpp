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
# include <boost/preprocessor/slot/detail/shared.hpp>
#
# undef BOOST_PP_LOCAL_SE
#
# undef BOOST_PP_LOCAL_SE_DIGIT_1
# undef BOOST_PP_LOCAL_SE_DIGIT_2
# undef BOOST_PP_LOCAL_SE_DIGIT_3
# undef BOOST_PP_LOCAL_SE_DIGIT_4
# undef BOOST_PP_LOCAL_SE_DIGIT_5
# undef BOOST_PP_LOCAL_SE_DIGIT_6
# undef BOOST_PP_LOCAL_SE_DIGIT_7
# undef BOOST_PP_LOCAL_SE_DIGIT_8
# undef BOOST_PP_LOCAL_SE_DIGIT_9
# undef BOOST_PP_LOCAL_SE_DIGIT_10
#
# if BOOST_PP_SLOT_TEMP_3 == 0
#    define BOOST_PP_LOCAL_SE_DIGIT_3 0
# elif BOOST_PP_SLOT_TEMP_3 == 1
#    define BOOST_PP_LOCAL_SE_DIGIT_3 1
# elif BOOST_PP_SLOT_TEMP_3 == 2
#    define BOOST_PP_LOCAL_SE_DIGIT_3 2
# elif BOOST_PP_SLOT_TEMP_3 == 3
#    define BOOST_PP_LOCAL_SE_DIGIT_3 3
# elif BOOST_PP_SLOT_TEMP_3 == 4
#    define BOOST_PP_LOCAL_SE_DIGIT_3 4
# elif BOOST_PP_SLOT_TEMP_3 == 5
#    define BOOST_PP_LOCAL_SE_DIGIT_3 5
# elif BOOST_PP_SLOT_TEMP_3 == 6
#    define BOOST_PP_LOCAL_SE_DIGIT_3 6
# elif BOOST_PP_SLOT_TEMP_3 == 7
#    define BOOST_PP_LOCAL_SE_DIGIT_3 7
# elif BOOST_PP_SLOT_TEMP_3 == 8
#    define BOOST_PP_LOCAL_SE_DIGIT_3 8
# elif BOOST_PP_SLOT_TEMP_3 == 9
#    define BOOST_PP_LOCAL_SE_DIGIT_3 9
# endif
#
# if BOOST_PP_SLOT_TEMP_2 == 0
#    define BOOST_PP_LOCAL_SE_DIGIT_2 0
# elif BOOST_PP_SLOT_TEMP_2 == 1
#    define BOOST_PP_LOCAL_SE_DIGIT_2 1
# elif BOOST_PP_SLOT_TEMP_2 == 2
#    define BOOST_PP_LOCAL_SE_DIGIT_2 2
# elif BOOST_PP_SLOT_TEMP_2 == 3
#    define BOOST_PP_LOCAL_SE_DIGIT_2 3
# elif BOOST_PP_SLOT_TEMP_2 == 4
#    define BOOST_PP_LOCAL_SE_DIGIT_2 4
# elif BOOST_PP_SLOT_TEMP_2 == 5
#    define BOOST_PP_LOCAL_SE_DIGIT_2 5
# elif BOOST_PP_SLOT_TEMP_2 == 6
#    define BOOST_PP_LOCAL_SE_DIGIT_2 6
# elif BOOST_PP_SLOT_TEMP_2 == 7
#    define BOOST_PP_LOCAL_SE_DIGIT_2 7
# elif BOOST_PP_SLOT_TEMP_2 == 8
#    define BOOST_PP_LOCAL_SE_DIGIT_2 8
# elif BOOST_PP_SLOT_TEMP_2 == 9
#    define BOOST_PP_LOCAL_SE_DIGIT_2 9
# endif
#
# if BOOST_PP_SLOT_TEMP_1 == 0
#    define BOOST_PP_LOCAL_SE_DIGIT_1 0
# elif BOOST_PP_SLOT_TEMP_1 == 1
#    define BOOST_PP_LOCAL_SE_DIGIT_1 1
# elif BOOST_PP_SLOT_TEMP_1 == 2
#    define BOOST_PP_LOCAL_SE_DIGIT_1 2
# elif BOOST_PP_SLOT_TEMP_1 == 3
#    define BOOST_PP_LOCAL_SE_DIGIT_1 3
# elif BOOST_PP_SLOT_TEMP_1 == 4
#    define BOOST_PP_LOCAL_SE_DIGIT_1 4
# elif BOOST_PP_SLOT_TEMP_1 == 5
#    define BOOST_PP_LOCAL_SE_DIGIT_1 5
# elif BOOST_PP_SLOT_TEMP_1 == 6
#    define BOOST_PP_LOCAL_SE_DIGIT_1 6
# elif BOOST_PP_SLOT_TEMP_1 == 7
#    define BOOST_PP_LOCAL_SE_DIGIT_1 7
# elif BOOST_PP_SLOT_TEMP_1 == 8
#    define BOOST_PP_LOCAL_SE_DIGIT_1 8
# elif BOOST_PP_SLOT_TEMP_1 == 9
#    define BOOST_PP_LOCAL_SE_DIGIT_1 9
# endif
#
# if BOOST_PP_LOCAL_SE_DIGIT_3
#    define BOOST_PP_LOCAL_SE() BOOST_PP_SLOT_CC_3(BOOST_PP_LOCAL_SE_DIGIT_3, BOOST_PP_LOCAL_SE_DIGIT_2, BOOST_PP_LOCAL_SE_DIGIT_1)
# elif BOOST_PP_LOCAL_SE_DIGIT_2
#    define BOOST_PP_LOCAL_SE() BOOST_PP_SLOT_CC_2(BOOST_PP_LOCAL_SE_DIGIT_2, BOOST_PP_LOCAL_SE_DIGIT_1)
# else
#    define BOOST_PP_LOCAL_SE() BOOST_PP_LOCAL_SE_DIGIT_1
# endif

/* start.hpp
KyuR6R3KTzCxk0t4l1mjh0pS8afB7KksTkXf1EBYJDgSezEGLEjkeTDHbO2kypN67rwC/fWY2biBNLMOUNO4EWSdnKH803jXYv9Lnh28CsaLSOV8sT94f0djPXd5Hu2vsPArLEgKqKQvh51J0HOCqIIp3JEOzj1XYHhXNvkD+vt9U3FckfIHTrSTbxYkFw+m1u1ILeslnldJjJIbLdoWtPxYjG34Tnvuv8b+YeRYNUZmo9uYkp+Yd6n4GHDzYve4debLuOPh2H3WTCGxDmhORdNfWj6iB4DD+JMYUqZrSl2aEQTJxmpRl9/E3kmGgO3/k7g3MBGVkujnvL+I+5l6EFxuPK4raldfrs/mTO08C6GetABf8C6IVktUUz/y2mQCSvx3LXR3LJMaLmwSpoq4auprs2bxu3cF5D+F9g2dovjhJMj7mCk4xcgpohlLOyWJk5SW71nGriF2D7r7oDQygxl8yPZCvOFrp8PY34dyjA83OE+fAKy5QQ1uELUCZdC4YCFBnPiV23mZn0W8Qv2uydtLsHSQjYXs7pMIpuK9qLmcN2Ww/1UZ3LXkqA==
*/
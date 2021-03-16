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
# undef BOOST_PP_ITERATION_START_2
#
# undef BOOST_PP_ITERATION_START_2_DIGIT_1
# undef BOOST_PP_ITERATION_START_2_DIGIT_2
# undef BOOST_PP_ITERATION_START_2_DIGIT_3
# undef BOOST_PP_ITERATION_START_2_DIGIT_4
# undef BOOST_PP_ITERATION_START_2_DIGIT_5
# undef BOOST_PP_ITERATION_START_2_DIGIT_6
# undef BOOST_PP_ITERATION_START_2_DIGIT_7
# undef BOOST_PP_ITERATION_START_2_DIGIT_8
# undef BOOST_PP_ITERATION_START_2_DIGIT_9
# undef BOOST_PP_ITERATION_START_2_DIGIT_10
#
# if BOOST_PP_SLOT_TEMP_3 == 0
#    define BOOST_PP_ITERATION_START_2_DIGIT_3 0
# elif BOOST_PP_SLOT_TEMP_3 == 1
#    define BOOST_PP_ITERATION_START_2_DIGIT_3 1
# elif BOOST_PP_SLOT_TEMP_3 == 2
#    define BOOST_PP_ITERATION_START_2_DIGIT_3 2
# elif BOOST_PP_SLOT_TEMP_3 == 3
#    define BOOST_PP_ITERATION_START_2_DIGIT_3 3
# elif BOOST_PP_SLOT_TEMP_3 == 4
#    define BOOST_PP_ITERATION_START_2_DIGIT_3 4
# elif BOOST_PP_SLOT_TEMP_3 == 5
#    define BOOST_PP_ITERATION_START_2_DIGIT_3 5
# elif BOOST_PP_SLOT_TEMP_3 == 6
#    define BOOST_PP_ITERATION_START_2_DIGIT_3 6
# elif BOOST_PP_SLOT_TEMP_3 == 7
#    define BOOST_PP_ITERATION_START_2_DIGIT_3 7
# elif BOOST_PP_SLOT_TEMP_3 == 8
#    define BOOST_PP_ITERATION_START_2_DIGIT_3 8
# elif BOOST_PP_SLOT_TEMP_3 == 9
#    define BOOST_PP_ITERATION_START_2_DIGIT_3 9
# endif
#
# if BOOST_PP_SLOT_TEMP_2 == 0
#    define BOOST_PP_ITERATION_START_2_DIGIT_2 0
# elif BOOST_PP_SLOT_TEMP_2 == 1
#    define BOOST_PP_ITERATION_START_2_DIGIT_2 1
# elif BOOST_PP_SLOT_TEMP_2 == 2
#    define BOOST_PP_ITERATION_START_2_DIGIT_2 2
# elif BOOST_PP_SLOT_TEMP_2 == 3
#    define BOOST_PP_ITERATION_START_2_DIGIT_2 3
# elif BOOST_PP_SLOT_TEMP_2 == 4
#    define BOOST_PP_ITERATION_START_2_DIGIT_2 4
# elif BOOST_PP_SLOT_TEMP_2 == 5
#    define BOOST_PP_ITERATION_START_2_DIGIT_2 5
# elif BOOST_PP_SLOT_TEMP_2 == 6
#    define BOOST_PP_ITERATION_START_2_DIGIT_2 6
# elif BOOST_PP_SLOT_TEMP_2 == 7
#    define BOOST_PP_ITERATION_START_2_DIGIT_2 7
# elif BOOST_PP_SLOT_TEMP_2 == 8
#    define BOOST_PP_ITERATION_START_2_DIGIT_2 8
# elif BOOST_PP_SLOT_TEMP_2 == 9
#    define BOOST_PP_ITERATION_START_2_DIGIT_2 9
# endif
#
# if BOOST_PP_SLOT_TEMP_1 == 0
#    define BOOST_PP_ITERATION_START_2_DIGIT_1 0
# elif BOOST_PP_SLOT_TEMP_1 == 1
#    define BOOST_PP_ITERATION_START_2_DIGIT_1 1
# elif BOOST_PP_SLOT_TEMP_1 == 2
#    define BOOST_PP_ITERATION_START_2_DIGIT_1 2
# elif BOOST_PP_SLOT_TEMP_1 == 3
#    define BOOST_PP_ITERATION_START_2_DIGIT_1 3
# elif BOOST_PP_SLOT_TEMP_1 == 4
#    define BOOST_PP_ITERATION_START_2_DIGIT_1 4
# elif BOOST_PP_SLOT_TEMP_1 == 5
#    define BOOST_PP_ITERATION_START_2_DIGIT_1 5
# elif BOOST_PP_SLOT_TEMP_1 == 6
#    define BOOST_PP_ITERATION_START_2_DIGIT_1 6
# elif BOOST_PP_SLOT_TEMP_1 == 7
#    define BOOST_PP_ITERATION_START_2_DIGIT_1 7
# elif BOOST_PP_SLOT_TEMP_1 == 8
#    define BOOST_PP_ITERATION_START_2_DIGIT_1 8
# elif BOOST_PP_SLOT_TEMP_1 == 9
#    define BOOST_PP_ITERATION_START_2_DIGIT_1 9
# endif
#
# if BOOST_PP_ITERATION_START_2_DIGIT_3
#    define BOOST_PP_ITERATION_START_2 BOOST_PP_SLOT_CC_3(BOOST_PP_ITERATION_START_2_DIGIT_3, BOOST_PP_ITERATION_START_2_DIGIT_2, BOOST_PP_ITERATION_START_2_DIGIT_1)
# elif BOOST_PP_ITERATION_START_2_DIGIT_2
#    define BOOST_PP_ITERATION_START_2 BOOST_PP_SLOT_CC_2(BOOST_PP_ITERATION_START_2_DIGIT_2, BOOST_PP_ITERATION_START_2_DIGIT_1)
# else
#    define BOOST_PP_ITERATION_START_2 BOOST_PP_ITERATION_START_2_DIGIT_1
# endif

/* lower2.hpp
ZLudPXLl8A9ZpkpSpL8nPP1d5FNXNVmuuk+7Fnn6UFPyxvjwKv0r3lqS9yofXu++uKslbx2t7Sc9bRcxSe3VKpU2eo0sV89Th7ijqtTT9usk7/WSV8VG4atib517jyfjl+SP1drUJBD5fLP2ebKGW5M92HRTUoQ2Nt5pi3hyLGiNPe0WZcfGu9vdVLajmdaOWK3uugG3jP0++w5bSBm3aDL2a2vQbwpE2iiwQPxLqAdX/iBwPryuWuqodZKbZ6s=
*/
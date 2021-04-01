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
# undef BOOST_PP_LOCAL_FE
#
# undef BOOST_PP_LOCAL_FE_DIGIT_1
# undef BOOST_PP_LOCAL_FE_DIGIT_2
# undef BOOST_PP_LOCAL_FE_DIGIT_3
# undef BOOST_PP_LOCAL_FE_DIGIT_4
# undef BOOST_PP_LOCAL_FE_DIGIT_5
# undef BOOST_PP_LOCAL_FE_DIGIT_6
# undef BOOST_PP_LOCAL_FE_DIGIT_7
# undef BOOST_PP_LOCAL_FE_DIGIT_8
# undef BOOST_PP_LOCAL_FE_DIGIT_9
# undef BOOST_PP_LOCAL_FE_DIGIT_10
#
# if BOOST_PP_SLOT_TEMP_3 == 0
#    define BOOST_PP_LOCAL_FE_DIGIT_3 0
# elif BOOST_PP_SLOT_TEMP_3 == 1
#    define BOOST_PP_LOCAL_FE_DIGIT_3 1
# elif BOOST_PP_SLOT_TEMP_3 == 2
#    define BOOST_PP_LOCAL_FE_DIGIT_3 2
# elif BOOST_PP_SLOT_TEMP_3 == 3
#    define BOOST_PP_LOCAL_FE_DIGIT_3 3
# elif BOOST_PP_SLOT_TEMP_3 == 4
#    define BOOST_PP_LOCAL_FE_DIGIT_3 4
# elif BOOST_PP_SLOT_TEMP_3 == 5
#    define BOOST_PP_LOCAL_FE_DIGIT_3 5
# elif BOOST_PP_SLOT_TEMP_3 == 6
#    define BOOST_PP_LOCAL_FE_DIGIT_3 6
# elif BOOST_PP_SLOT_TEMP_3 == 7
#    define BOOST_PP_LOCAL_FE_DIGIT_3 7
# elif BOOST_PP_SLOT_TEMP_3 == 8
#    define BOOST_PP_LOCAL_FE_DIGIT_3 8
# elif BOOST_PP_SLOT_TEMP_3 == 9
#    define BOOST_PP_LOCAL_FE_DIGIT_3 9
# endif
#
# if BOOST_PP_SLOT_TEMP_2 == 0
#    define BOOST_PP_LOCAL_FE_DIGIT_2 0
# elif BOOST_PP_SLOT_TEMP_2 == 1
#    define BOOST_PP_LOCAL_FE_DIGIT_2 1
# elif BOOST_PP_SLOT_TEMP_2 == 2
#    define BOOST_PP_LOCAL_FE_DIGIT_2 2
# elif BOOST_PP_SLOT_TEMP_2 == 3
#    define BOOST_PP_LOCAL_FE_DIGIT_2 3
# elif BOOST_PP_SLOT_TEMP_2 == 4
#    define BOOST_PP_LOCAL_FE_DIGIT_2 4
# elif BOOST_PP_SLOT_TEMP_2 == 5
#    define BOOST_PP_LOCAL_FE_DIGIT_2 5
# elif BOOST_PP_SLOT_TEMP_2 == 6
#    define BOOST_PP_LOCAL_FE_DIGIT_2 6
# elif BOOST_PP_SLOT_TEMP_2 == 7
#    define BOOST_PP_LOCAL_FE_DIGIT_2 7
# elif BOOST_PP_SLOT_TEMP_2 == 8
#    define BOOST_PP_LOCAL_FE_DIGIT_2 8
# elif BOOST_PP_SLOT_TEMP_2 == 9
#    define BOOST_PP_LOCAL_FE_DIGIT_2 9
# endif
#
# if BOOST_PP_SLOT_TEMP_1 == 0
#    define BOOST_PP_LOCAL_FE_DIGIT_1 0
# elif BOOST_PP_SLOT_TEMP_1 == 1
#    define BOOST_PP_LOCAL_FE_DIGIT_1 1
# elif BOOST_PP_SLOT_TEMP_1 == 2
#    define BOOST_PP_LOCAL_FE_DIGIT_1 2
# elif BOOST_PP_SLOT_TEMP_1 == 3
#    define BOOST_PP_LOCAL_FE_DIGIT_1 3
# elif BOOST_PP_SLOT_TEMP_1 == 4
#    define BOOST_PP_LOCAL_FE_DIGIT_1 4
# elif BOOST_PP_SLOT_TEMP_1 == 5
#    define BOOST_PP_LOCAL_FE_DIGIT_1 5
# elif BOOST_PP_SLOT_TEMP_1 == 6
#    define BOOST_PP_LOCAL_FE_DIGIT_1 6
# elif BOOST_PP_SLOT_TEMP_1 == 7
#    define BOOST_PP_LOCAL_FE_DIGIT_1 7
# elif BOOST_PP_SLOT_TEMP_1 == 8
#    define BOOST_PP_LOCAL_FE_DIGIT_1 8
# elif BOOST_PP_SLOT_TEMP_1 == 9
#    define BOOST_PP_LOCAL_FE_DIGIT_1 9
# endif
#
# if BOOST_PP_LOCAL_FE_DIGIT_3
#    define BOOST_PP_LOCAL_FE() BOOST_PP_SLOT_CC_3(BOOST_PP_LOCAL_FE_DIGIT_3, BOOST_PP_LOCAL_FE_DIGIT_2, BOOST_PP_LOCAL_FE_DIGIT_1)
# elif BOOST_PP_LOCAL_FE_DIGIT_2
#    define BOOST_PP_LOCAL_FE() BOOST_PP_SLOT_CC_2(BOOST_PP_LOCAL_FE_DIGIT_2, BOOST_PP_LOCAL_FE_DIGIT_1)
# else
#    define BOOST_PP_LOCAL_FE() BOOST_PP_LOCAL_FE_DIGIT_1
# endif

/* finish.hpp
AuAy2mNkjxBWR3w4+OcZiHrCt7CymDSBdXQBnZgE/87NOK2fb0a3z+SaqYjRTPTR7TMH4v+kfl9wUZdFT1ZPGKxd8bjJ2lBmAZLsgb9Fw/Nd8RnsGPYQwoUiv8uKZqW7BbY4EiYEHjFX5P4vt/TCAWox3cdx5spwVCRlh9WOccwoVO8tDYWo5ACIy1QwIMNCqeglgI/ZdyAI/cKkJnqAzazSqiVnwtsGiOTnmVEBUsEss57TpHOEAlXN1zPz3/W40mLB+yeUANila8+z6ncjzFhR20jkP1jS7xxAHmbURBQkhCv3slDLn/4ehaAQhsbvh49UTOZ4s9eFoMMN1NBHVxQXQwqCDSJAtVfukYdB+41IG01G0Jh/8r+Sf1YBj56+XmJncuMFzSs/67KIAHCGoiUx/l5/FNKkQesBFvSrhbVYdLBNzDkeisXsr+W3qgu+R2rVhAy4KXznC+HDkHZhnpKO+qNBBGJqfbla8cpJaKvWs9P+fMoDLUI7A2ZT0xqhUjZwn0iPQsVLqYobxnImEOl4RMtVT/jmoGxJBJr2VInL+gQWmNarEXzfxA==
*/